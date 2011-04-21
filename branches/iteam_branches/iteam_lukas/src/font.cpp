#include "font.hpp"

iFont::iFont() {
	this->loadFont("media/font.ttf", "media/font.ttf", 12);
}

iFont::iFont(std::string filename, int size) {
	this->loadFont(filename, filename, size);
}

iFont::iFont(std::string fontname, std::string filename, int size) {
	this->loadFont(fontname, filename, size);
}

iFont::~iFont() {
	if (this->ttf != NULL) {
		TTF_CloseFont(this->ttf);
	}
}

void iFont::loadFont(std::string fontname, std::string filename,
		int size) {
	this->ttf = TTF_OpenFont(filename.c_str(), size);
	if (this->ttf == NULL) {
		printf("Failed to load font: %s\n", TTF_GetError());
	}
	this->fontName = fontname;
}

void iFont::setStyle(int style) {
	// 0 = normal
	// 1 = bold
	// 2 = italic
	// 4 = underline
	TTF_SetFontStyle(this->ttf, style);
}
