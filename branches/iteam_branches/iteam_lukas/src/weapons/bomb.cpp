#include <cmath>

#include "bomb.hpp"

iBomb::iBomb() {
	this->sprite = new iSprite("media/weapons/bomb.png");
	this->physical = new iPhysical();
}

iBomb::~iBomb() {
	delete this->sprite;
	delete this->physical;
}

void iBomb::fire(int x, int y, int angle) {
	this->physical->move(x, y);
	this->sprite->move(x, y);
	angle = angle * 3.14159 / 180.0;
	this->physical->yVelocity = -5 * sin(angle);
	this->physical->xVelocity = 5 * cos(angle);
}

void iBomb::stepPhysics(int changeInTicks) {
	this->physical->stepPhysics(changeInTicks);
	this->sprite->x = this->physical->x;
	this->sprite->y = this->physical->y;
}

void iBomb::draw() {
	this->sprite->draw();
}

