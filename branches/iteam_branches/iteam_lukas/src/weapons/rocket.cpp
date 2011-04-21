#include <cmath>

#include "rocket.hpp"

iRocket::iRocket() {
	this->sprite = new iSprite("media/weapons/rocket.png");
	this->physical = new iPhysical();
}

iRocket::~iRocket() {
	delete this->sprite;
	delete this->physical;
}

void iRocket::fire(int x, int y, int angle) {
	this->physical->move(x, y);
	this->sprite->move(x, y);
	angle = angle * 3.14159 / 180.0;
	this->physical->yVelocity = -5 * sin(angle);
	this->physical->xVelocity = 5 * cos(angle);
}

void iRocket::stepPhysics(int changeInTicks) {
	this->physical->stepPhysics(changeInTicks);
	this->sprite->x = this->physical->x;
	this->sprite->y = this->physical->y;
}

void iRocket::draw() {
	this->sprite->draw();
}
