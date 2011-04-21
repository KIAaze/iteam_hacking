#include "color.hpp"

iColor::iColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	// the default, (255, 255, 255, 255), is a solid black
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

iColor::~iColor() {
	
}

SDL_Color iColor::getSDLColor() {
	SDL_Color color = {this->r, this->g, this->b};
	return color;
}
