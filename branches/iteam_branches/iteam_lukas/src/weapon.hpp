#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "sprite.hpp"
#include "physical.hpp"

class iWeapon {
public:

	iSprite* sprite;
	iPhysical* physical;
	
	virtual void fire(int x, int y, int angle) = 0;
	virtual void stepPhysics(int changeInTicks) = 0;
	virtual void draw() = 0;
};

#endif
