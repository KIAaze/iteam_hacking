#include "intro.h"
using namespace std;
using namespace gp2d;

namespace game {

iteamIntro::iteamIntro(){
	setState(FADE_IN);
	timer = new GP2DTimer();
	iteam* engine = iteam::instance();
	splash = new GP2DSprite("data/gui/intro.png");
	splash->setWidth(engine->window()->getWidth());
	splash->setHeight(engine->window()->getHeight());
	splash->setPosition(0.0f,engine->window()->getHeight());	
	splash->setAlpha(0.0f);
}

iteamIntro::~iteamIntro(){ cout << "BYEEE" << endl; }

void iteamIntro::run(){

	iteam* engine = iteam::instance();
	if(!timer->isStarted()){ timer->start(); }
	
	switch (getState()) {
		case FADE_IN:
			if(splash->getAlpha() < 1.0f){
				splash->setAlpha( (float)timer->getTicks() / 1500.0f );
			} else {
				timer->stop();
				timer->reset();
				timer->start();
				setNextState(WAIT);
				nextState();
			}
			break;
		case WAIT:
			if(timer->getTicks() > 2000.0f){
				timer->stop();
				timer->reset();
				timer->start();
				setNextState(FADE_OUT);
				nextState();
			}
			break;
		case FADE_OUT:
			if(splash->getAlpha() > 0.0f){
				splash->setAlpha( 1.0f - ((float)timer->getTicks() / 1500.0f) );
			} else {
				timer->stop();
				setNextState(END);
				nextState();
			}
			break;
		case END:
			engine->setNextState(engine->FREE_INTRO);
			engine->nextState();
			break;
	}
	engine->director()->useGuiCamera();
	splash->draw();

}

}
