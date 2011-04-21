#include "text.hpp"
#include "utility.hpp"

iText::iText() {
	construct(new iFont(), "", new iColor());
}

iText::iText(iFont* font) {
	construct(font, "", new iColor());
}

iText::iText(std::string text) {
	construct(new iFont(), text, new iColor());
}

iText::iText(std::string text, iColor* color) {
	construct(new iFont(), text, color);
}

iText::iText(iFont* font, std::string text) {
	construct(font, text, new iColor());
}

iText::iText(iFont* font, std::string text, iColor* color) {
	construct(font, text, color);
}

void iText::draw() {	
	glDisable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    glBlendFunc(GL_ONE, GL_ONE);

    glBindTexture(GL_TEXTURE_2D, this->texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glBegin(GL_QUADS);
        // bottom left
		glTexCoord2i(0, 0);
		glVertex3f(this->x, this->y, 0.0f);
		// bottom right
		glTexCoord2i(1, 0);
		glVertex3f(this->x + this->width, this->y, 0.0f);
		// top right
		glTexCoord2i(1, 1);
		glVertex3f(this->x + this->width, this->y + this->height, 0.0f);
		// top left
		glTexCoord2i(0, 1);
		glVertex3f(this->x, this->y + this->height, 0.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
    glFinish();
}

void iText::setText(std::string text) {
	int x, y;
	x = this->x;
	y = this->y;
	construct(this->font, text, this->color);
	this->move(x, y);
	updateSurface();
}

void iText::setFont(iFont* font) {
	if (font != NULL) {
		int x, y;
		x = this->x;
		y = this->y;
		construct(font, this->text, this->color);
		this->move(x, y);
		updateSurface();
	}
}

void iText::setColor(iColor* color) {
	if (color != NULL) {
		int x, y;
		x = this->x;
		y = this->y;
		construct(this->font, this->text, color);
		this->move(x, y);
		updateSurface();
	}
}

void iText::setStyle(int style) {
	if (this->font != NULL && style >= 0 && style <= 4 && style != 3) {
		this->font->setStyle(style);
		updateSurface();
	}
}

void iText::move(int x, int y) {
	this->x = x;
	this->y = y;
}

void iText::updateSurface() {
	SDL_Surface* initial;
	
	initial = TTF_RenderText_Blended(font->ttf, text.c_str(),
		color->getSDLColor());
		
	this->width = nextPowerOfTwo(initial->w);
	this->height = nextPowerOfTwo(initial->h);
	
	this->surface = SDL_CreateRGBSurface(0, this->width, this->height,
		32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_BlitSurface(initial, 0, this->surface, 0);
	
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->width, this->height, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, this->surface->pixels);
		
	SDL_FreeSurface(initial);
}

void iText::construct(iFont* font, std::string text, iColor* color) {
	this->font = font;
	this->text = text;
	this->color = color;
	this->x = 0;
	this->y = 0;
	updateSurface();
}
