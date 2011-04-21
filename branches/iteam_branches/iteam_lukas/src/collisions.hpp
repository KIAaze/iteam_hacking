#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "sprite.hpp"

typedef struct {
	bool collided;
	int x;
	int y;
} collisionResult;

class iCollisions {
	
public:
	
	iCollisions();
	~iCollisions();
	bool boxCollision(iSprite* sprite1, iSprite* sprite2);
	bool pixelCollision(iSprite* sprite1, iSprite* sprite2, int skip);
	collisionResult pixelCollisionDetailed(iSprite* sprite1,
		iSprite* sprite2, int skip);
	
private:

	bool pixelTransparent(SDL_Surface* surface, int x, int y);
	
};

#endif


