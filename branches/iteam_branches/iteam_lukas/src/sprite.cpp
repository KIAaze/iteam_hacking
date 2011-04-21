#include <cstdio>

#include "SDL/SDL_rotozoom.h"

#include "sprite.hpp"

iSprite::iSprite() {
	construct("", 0, 0, NULL);
}

iSprite::iSprite(std::string filename) {
	construct(filename, 0, 0, NULL);
}

iSprite::iSprite(std::string filename, int x, int y) {
	construct(filename, x, y, NULL);
}

iSprite::iSprite(SDL_Surface* surface, int x, int y) {
	construct("", x, y, surface);
}

iSprite::~iSprite() {
	SDL_FreeSurface(this->surface);
}

void iSprite::draw() {
	if (this->textureColors == 4) {
		// enable alpha channels
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	glEnable(GL_TEXTURE_2D);
	
	// bind the texture
	glBindTexture(GL_TEXTURE_2D, this->texture);
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
}

void iSprite::translate(int x, int y) {
	this->x += x;
	this->y += y;
}

void iSprite::move(int x, int y) {
	this->x = x;
	this->y = y;
}

void iSprite::flipHorizontally() {
	this->surface = flipSurface(this->surface);
	this->setSurface(this->surface);
	this->mirrored = (this->mirrored == false);
}

void iSprite::rotate(int angle) {
	this->angle = angle % 360;
	if (this->angle == 0) {
		this->setSurface(this->origin); // unrotated surface
	}
	else {
		this->setSurface(SDL_DisplayFormat(rotozoomSurface(
			this->surface, 45.0, 1, 1)));
	}
}

void iSprite::setSurface(SDL_Surface* surface) {
	glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
		GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
		GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, this->textureColors,
        this->surface->w, this->surface->h, 0, this->textureFormat, 
        GL_UNSIGNED_BYTE, this->surface->pixels);
    this->surface = surface;
    this->width = surface->w;
    this->height = surface->h;
    this->textureColors = surface->format->BytesPerPixel;
    if (this->textureColors == 4) { // alpha channel
		if (surface->format->Rmask == 0x000000ff) {
			this->textureFormat = GL_RGBA;
		}
        else {
			this->textureFormat = GL_BGRA;
		}
	}
	else if (this->textureColors == 3) { // no alpha channel
		if (surface->format->Rmask == 0x000000ff) {
			this->textureFormat = GL_RGB;
		}
        else {
			this->textureFormat = GL_BGR;
		}
	}
}

SDL_Surface* iSprite::flipSurface(SDL_Surface* surface) {
	SDL_Surface* mirror = NULL;
	// for RGBA surfaces only
	if (this->textureFormat == GL_RGBA || 
			this->textureFormat == GL_BGRA) {
		mirror = SDL_CreateRGBSurface(surface->flags, surface->w,
			surface->h, surface->format->BitsPerPixel,
			surface->format->Rmask, surface->format->Gmask,
			surface->format->Bmask, surface->format->Amask);
		Uint32* source = (Uint32*) surface->pixels;
		Uint32* destination = (Uint32*) mirror->pixels;
		for (int i = 0; i < surface->h; i++) {
			for (int j = 0; j < surface->w; j++) {
				destination[i * surface->w + j] = source[(i + 1) *
					surface->w - j];
			}
		}
	}
	else {
		printf("Surface mirroring only works with RGBA and BGRA \
			surfaces.\n");
	}
	return mirror;
}

void iSprite::construct(std::string filename, int x, int y,
		SDL_Surface* surface) {
	this->x = x;
	this->y = y;
	this->width = 0;
	this->height = 0;
	this->filename = filename;
	this->texture = 0;
	this->textureFormat = 0;
	this->textureColors = 0;
	this->mirrored = false;
	this->angle = 0;
	if (surface != NULL) {
		this->setSurface(surface);
	}
	else if ((this->surface = IMG_Load(filename.c_str()))) {
		// Check for power of 2
		if ((this->surface->w & (this->surface->w - 1)) != 0) {
			printf("Texture warning: width not a power of 2 (%s)\n", 
				filename.c_str()); 
		}
		if ((this->surface->h & (this->surface->h - 1)) != 0) {
			printf("Texture warning: height not a power of 2 (%s)\n", 
				filename.c_str()); 
		}
		// Determine colors via SDL_Surface
		this->textureColors = this->surface->format->BytesPerPixel;
		if (this->textureColors == 4) { // alpha channel
			if (this->surface->format->Rmask == 0x000000ff) {
				this->textureFormat = GL_RGBA;
			}
            else {
				this->textureFormat = GL_BGRA;
			}
		}
		else if (this->textureColors == 3) { // no alpha channel
			if (this->surface->format->Rmask == 0x000000ff) {
				this->textureFormat = GL_RGB;
			}
            else {
				this->textureFormat = GL_BGR;
			}
		}
		else {
			printf("Texture error: not a color image (%s)", 
				filename.c_str());
			this->texture = 0; // the same as NULL?
        }
        // Generate the OpenGL texture
        this->setSurface(this->surface);
		
		// Set attributes based on bitmap
		this->width = this->surface->w;
		this->height = this->surface->h;
		
		// make a copy of the new surface for rotations
		this->origin = SDL_DisplayFormatAlpha(this->surface);
		this->rotated = SDL_DisplayFormatAlpha(this->surface);
	}
	else {
		printf("SDL error: %s (%s)\n", SDL_GetError(), 
			filename.c_str());
		this->setSurface(SDL_CreateRGBSurface(SDL_OPENGL, 0, 0, 32,
			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000));
	}
}
