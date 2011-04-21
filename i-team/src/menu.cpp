#include "menu.h"
using namespace std;
using namespace gp2d;

namespace game {

iteamMenu::iteamMenu(){
	setState(FADE_IN);
	timer = new GP2DTimer();
	iteam* engine = iteam::instance();
	bg = new GP2DSprite("data/gui/bg-menu.png");
	bg->setWidth(engine->window()->getWidth());
	bg->setHeight(engine->window()->getHeight());
	bg->setPosition(0.0f,engine->window()->getHeight());	
	bg->setAlpha(0.0f);
}

iteamMenu::~iteamMenu(){ cout << "BYEEE" << endl; }

void iteamMenu::run(){

	iteam* engine = iteam::instance();
	if(!timer->isStarted()){ timer->start(); }
	
	switch (getState()) {
		case FADE_IN:
			if(bg->getAlpha() < 1.0f){
				bg->setAlpha( (float)timer->getTicks() / 1500.0f );
			} else {
				timer->stop();
				timer->reset();
				timer->start();
				setNextState(MENU);
				nextState();
			}
		break;
		case MENU:
		break;
		case FADE_OUT:
			if(bg->getAlpha() > 0.0f){
				bg->setAlpha( 1.0f - ((float)timer->getTicks() / 1500.0f) );
			} else {
				timer->stop();
				setNextState(END);
				nextState();
			}
			break;
		case END:
			engine->quit();
		break;
	}
	engine->director()->useGuiCamera();
	bg->draw();

}

}
