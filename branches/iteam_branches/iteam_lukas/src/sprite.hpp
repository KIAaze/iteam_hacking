#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "SDL/SDL_image.h"

class iSprite {
	
public:

	int x;
	int y;
	int width;
	int height;
	std::string filename;
	GLuint texture;
	GLenum textureFormat;
	GLint textureColors;
	SDL_Surface* surface;
	SDL_Surface* origin; // unrotated, compensates for blurring
	SDL_Surface* rotated;
	bool mirrored; // true if surface has been flipped
	int angle; // degrees
	
	iSprite();
	iSprite(std::string filename);
	iSprite(std::string filename, int x, int y);
	iSprite(SDL_Surface* surface, int x, int y);
	~iSprite();
	void draw();
	void translate(int x, int y);
	void move(int x, int y);
	void flipHorizontally();
	void rotate(int angle); // purely graphical, does not affect collisions
	void setSurface(SDL_Surface* surface);
	
private:

	void construct(std::string filname, int x, int y,
		SDL_Surface* surface);
	SDL_Surface* flipSurface(SDL_Surface* surface);
	
};

#endif
