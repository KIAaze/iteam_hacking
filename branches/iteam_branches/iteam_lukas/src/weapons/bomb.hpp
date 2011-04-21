#ifndef _BOMB_H_
#define _BOMB_H_

#include "../weapon.hpp"

class iBomb : public iWeapon {
public:

	iBomb();
	~iBomb();

	void fire(int x, int y, int angle);
	void stepPhysics(int changeInTicks);
	void draw();
};

#endif

