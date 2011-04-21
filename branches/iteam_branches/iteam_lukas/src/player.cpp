#include "player.hpp"

iPlayer::iPlayer() {
	construct("", 0, 0);
}

iPlayer::iPlayer(std::string filename) {
	construct(filename, 0, 0);
}

iPlayer::iPlayer(std::string filename, int x, int y) {
	construct(filename, x, y);
}

iPlayer::~iPlayer() {
	delete this->sprite;
	delete this->physical;
}

void iPlayer::translate(int x, int y) {
	this->sprite->translate(x, y);
	this->physical->translate(x, y);
}

void iPlayer::move(int x, int y) {
	this->sprite->move(x, y);
	this->physical->move(x, y);
}

void iPlayer::stepPhysics(int changeInTicks) {
	this->physical->stepPhysics(changeInTicks);
	this->sprite->move((int)this->physical->x, (int)this->physical->y);
}

void iPlayer::draw() {
	this->sprite->draw();
}

void iPlayer::construct(std::string filename, int x, int y) {
	if (filename.empty()) {
		this->sprite = new iSprite();
	}
	else {
		this->sprite = new iSprite(filename, x, y);
	}
	this->physical = new iPhysical(x, y);
	//this->physical->gravityConstant = 0.0f;
	this->standingAngle = 90;
	this->firingAngle = 45;
}
