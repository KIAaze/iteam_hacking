#ifndef _ROCKET_H_
#define _ROCKET_H_

#include "../weapon.hpp"

class iRocket : public iWeapon {
public:

	iRocket();
	~iRocket();

	void fire(int x, int y, int angle);
	void stepPhysics(int changeInTicks);
	void draw();
};

#endif
