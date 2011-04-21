#include <cstdio>

#include "physical.hpp"

iPhysical::iPhysical() {
	construct(0, 0);
}

iPhysical::iPhysical(int x, int y) {
	construct(x, y);
}

iPhysical::~iPhysical() {
	
}

void iPhysical::stepPhysics(int changeInTicks) {
	float time = ((float)changeInTicks) / 1000.0f; // millisecond -> seconds
	this->xVelocity += this->xAcceleration * time;
	this->yVelocity += this->yAcceleration * time;
	this->yVelocity += this->gravityConstant * time;
	this->x += this->xVelocity;
	if (this->yVelocity > this->terminalVelocity) {
		this->yVelocity = this->terminalVelocity;
	}
	this->y += this->yVelocity;
}

void iPhysical::translate(int x, int y) {
	this->x += x;
	this->y += y;
}

void iPhysical::move(int x, int y) {
	this->x = x;
	this->y = y;
}

void iPhysical::freeze() {
	xVelocity = 0.0f;
	yVelocity = 0.0f;
	xAcceleration = 0.0f;
	yAcceleration = 0.0f;
}

void iPhysical::construct(int x, int y) {
	this->x = (float) x;
	this->y = (float) y;
	this->xVelocity = 0.0f;
	this->yVelocity = 0.0f;
	this->xAcceleration = 0.0f;
	this->yAcceleration = 0.0f;
	this->gravityConstant = 5.0f;
	this->terminalVelocity = 5.0f;
}
