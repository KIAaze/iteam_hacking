#include <cmath>
#include <climits>

#include "SDL/SDL_gfxPrimitives.h"

#include "terrain.hpp"

iTerrain::iTerrain() {
	construct("");
}

iTerrain::iTerrain(std::string filename) {
	construct(filename);
}

iTerrain::~iTerrain() {
	delete this->sprite;
}

void iTerrain::draw() {
	this->sprite->draw();
}

void iTerrain::addExplosion(int x, int y, int radius) {
	if (radius <= 0) {
		return;
	}
	if (SDL_MUSTLOCK(this->sprite->surface)) {
		SDL_LockSurface(this->sprite->surface);
	}
	Uint32* pixels = (Uint32*) this->sprite->surface->pixels;
	for (int i = x - radius; i <= x + radius; i++) {
		for (int j = y - radius; j <= y + radius; j++) {
			if (((i - x) * (i - x) + (j - y) * (j - y)) <= radius * radius) {
				pixels[((j) * this->sprite->width) + (i)] =	0x00000000;
			}
		}
	}
	if (SDL_MUSTLOCK(this->sprite->surface)) {
		SDL_UnlockSurface(this->sprite->surface);
	}
	this->sprite->setSurface(this->sprite->surface);
}

void iTerrain::construct(std::string filename) {
	this->collisions = new iCollisions();
	if (filename.empty()) {
		this->sprite = new iSprite();
	}
	else {
		this->sprite = new iSprite(filename);
	}
}

void iTerrain::placeOnTerrain(iPlayer* player) {
	
}

int iTerrain::getTerrainHeightAbove(iPlayer* player) {
	int originalY = player->sprite->y;
	for (int i = originalY; 
			i > this->sprite->y - player->sprite->height; i--) {
		player->sprite->y = i;
		if (this->collisions->pixelCollision(this->sprite,
				player->sprite, 1) == false) {
			player->sprite->y = originalY;
			return i;
		}
	}
	return INT_MAX;
}

int iTerrain::getTerrainHeightBelow(iPlayer* player) {
	int originalY = player->sprite->y;
	for (int i = originalY; 
			i < this->sprite->y + player->sprite->height
			+ this->sprite->height; i++) {
		player->sprite->y = i;
		if (this->collisions->pixelCollision(this->sprite,
				player->sprite, 1) == false) {
			player->sprite->y = originalY;
			return i;
		}
	}
	return INT_MAX;
}
