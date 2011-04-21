#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "camera.hpp"

iCamera::iCamera() {
	this->width = 0;
	this->height = 0;
}

iCamera::iCamera(int width, int height) {
	this->width = width;
	this->height = height;
}

iCamera::~iCamera() {
	
}

void iCamera::translate(int x, int y) {
	glTranslatef(-(float) x, -(float) y, 0.0f);
}

void iCamera::lookAt(int x, int y) {
	glLoadIdentity();
	glTranslatef(-(float) x, -(float) y, 0.0f);
};

void iCamera::lookAt(iSprite* sprite) {
	this->lookAt(sprite->x + sprite->width/2 - this->width/2,
		sprite->y + sprite->height/2  - this->height/2);
}
