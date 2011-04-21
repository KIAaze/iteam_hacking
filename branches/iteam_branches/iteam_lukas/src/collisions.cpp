#include <cstdio>

#include "SDL/SDL.h"

#include "collisions.hpp"

iCollisions::iCollisions() {
	
}

iCollisions::~iCollisions() {
	
}

bool iCollisions::boxCollision(iSprite* sprite1, iSprite* sprite2) {
	if ((sprite1->x + sprite1->width) <= sprite2->x) { return false; }
	if (sprite1->x >= (sprite2->x + sprite2->width)) { return false; }
	if ((sprite2->y + sprite2->height) <= sprite1->y) { return false; }
	if (sprite2->y >= (sprite1->y + sprite1->height)) { return false; }

	return true;
}

bool iCollisions::pixelCollision(iSprite* sprite1, iSprite* sprite2,
		int skip) {
	return pixelCollisionDetailed(sprite1, sprite2, skip).collided;
}

collisionResult iCollisions::pixelCollisionDetailed(iSprite* sprite1,
		iSprite* sprite2, int skip) {
	// if the bounding boxes don't collide, we won't bother with pixels
	collisionResult result = {false, 0, 0};
	
	if (!boxCollision(sprite1, sprite2)) {
		return result; // false
	}
	
	// for those familiar with SDL, you'll recognize this is similar
	// to SDL_Collide's algorithm
	int xStart = sprite1->x > sprite2->x ? sprite1->x : sprite2->x;
	int xEnd = sprite1->x + sprite1->width < sprite2->x +
		sprite2->width ? sprite1->x + sprite1->width : sprite2->x +
		sprite2->width;
	int yStart = sprite1->y > sprite2->y ? sprite1->y : sprite2->y;
	int yEnd = sprite1->y + sprite1->height < sprite2->y +
		sprite2->height ? sprite1->y + sprite1->height : sprite2->y +
		sprite2->height;
	
	//printf("(%d, %d) -> (%d, %d)\n", xStart, xEnd, yStart, yEnd);
		
	// the above slices out a region in which the two surfaces are
	// overlapping, the next part loops through the pixels, skipping
	// the amount set by "skip" each loop
	for (int x = xStart; x <= xEnd; x += skip) {
		for (int y = yStart; y <= yEnd; y += skip) {
			if (!(pixelTransparent(sprite1->surface, x - sprite1->x,
				y - sprite1->y)) && !(pixelTransparent(sprite2->surface,
				x - sprite2->x, y - sprite2->y))) {
					result.collided = true;
					result.x = x;
					result.y = y;
					return result; // true
				}
		}
	}
	
	return result; // false
}

// I won't lie, this is basically identical to SDL_Collide's code
bool iCollisions::pixelTransparent(SDL_Surface* surface, int x, int y) {
	if (SDL_MUSTLOCK(surface)) {
		SDL_LockSurface(surface);
	}
	
	if (x > surface->w || y > surface->h) {
		return false;
	}

	int bpp = surface->format->BytesPerPixel;
	/*here p is the address to the pixel we want to retrieve*/
	Uint8* p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp;

	Uint32 pixelcolor = 0; // asigned to zero to avoid compiler warning

	switch (bpp)
	{
		case(1):
			pixelcolor = *p;
		break;

		case(2):
			pixelcolor = *(Uint16*)p;
		break;

		case(3):
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				pixelcolor = p[0] << 16 | p[1] << 8 | p[2];
			}
			else {
				pixelcolor = p[0] | p[1] << 8 | p[2] << 16;
			}
		break;

		case(4):
			pixelcolor = *(Uint32*)p;
		break;
	}

	if(SDL_MUSTLOCK(surface)) {
		SDL_UnlockSurface(surface);
	}
	return (pixelcolor == surface->format->colorkey);
}
