#include "globals.h"
#include "gamestate.h"

namespace iteam
{
		
	gameState::gameState() {
		currentScene = 0;
	}
	
	gameState::~gameState() {
	}

	void gameState::addScene(gameScene *ptr) {
		ptrScenes.push_back(ptr);
	}
	
	void gameState::setScene (int val) {
		currentScene = val;
	}
	
	gameScene* gameState::getScene(int val) {
		setScene(val);
		return ptrScenes[currentScene];		
	}
	
}
