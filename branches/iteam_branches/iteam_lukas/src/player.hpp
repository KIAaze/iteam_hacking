#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>

#include "sprite.hpp"
#include "physical.hpp"
#include "weapon.hpp"

class iPlayer {

public:

	iSprite* sprite;
	iPhysical* physical;
	iWeapon* weapon;
	int standingAngle;
	int firingAngle; // relative to the standing angle
	
	iPlayer();
	iPlayer(std::string filename);
	iPlayer(std::string filename, int x, int y);
	~iPlayer();
	virtual void translate(int x, int y);
	virtual void move(int x, int y);
	virtual void stepPhysics(int changeInTicks);
	virtual void draw();
	
protected:

	virtual void construct(std::string filename, int x, int y);

};

#endif

