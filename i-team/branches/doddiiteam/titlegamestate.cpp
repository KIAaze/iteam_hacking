#include "globals.h"
#include "players.h"
#include "firstGame.h"

namespace iteam
{
	
	// TODO: Need to find a way to register these scenes
	// in a more streamlined way
	#define	GET_TITLESCENE	((titleGameScene*)getScene(0))
	
	titleState::titleState() {		
	}

	titleState::~titleState() {
	}
	
	bool titleState::gs_loadState(void) {

		titleTimer.start();
		
		// Initialises component timer, frames etc
		// TODO consider changing to a for loop
		GET_TITLESCENE->intialise();
	}
	
	// Used to draw the background (not sure if needed)		
	bool titleState::gs_drawState(void) {
		
		GET_TITLESCENE->drawScollingTitleScreen(titleTimer.getTicks());
		GET_TITLESCENE->drawPressSpace();

		titleTimer.start();	
		
		return true;
	};
	
	
	bool titleState::gs_handlePlayers(void) {
				
		GET_TITLESCENE->drawDoughnut();
		
	}
	
	bool titleState::gs_handleKeys(void) {

		if (gp2d::KeyPressed(SDLK_SPACE)) {
			ptrParent->currentState = PRE_RUN;			
		}
		
		return true;
	}
	
	
	// Updating of the GUI interface		
	bool titleState::gs_handleGUI(void) {
		return true;
	};
}
