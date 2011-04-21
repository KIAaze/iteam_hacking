#include "globals.h"
#include "players.h"
#include "firstGame.h"

namespace iteam
{
	
	// TODO: Need to find a way to register these scenes
	// in a more streamlined way
	#define	GET_PRERUNSCENE		((prerunGameScene*)getScene(0))
	#define	GET_RUNNINGSCENE	((runningGameScene*)getScene(0))	
	
	prerunState::prerunState() {		
	}

	prerunState::~prerunState() {
	}
	
	bool prerunState::gs_loadState(void) {
		printf("preRun state called\n");
		GET_PRERUNSCENE->initialise();		
	}
	
	// Used to draw the background (not sure if needed)		
	bool prerunState::gs_drawState(void) {
		GET_PRERUNSCENE->drawMap();		
		return true;
	};
	
	
	// Handle player intervention (this could be moving characters or menu options)		
	bool prerunState::gs_handlePlayers(void) {
		
		// If we have reached our countdown then jump to the next state		
		if (GET_PRERUNSCENE->updateCountdown() == false) {
			ptrParent->currentState = RUNNING;
		}				
		return true;
	}

	bool prerunState::gs_handleKeys(void) {		
		return true;
	}
	
	//Handles looping music and sound FX		
	bool prerunState::gs_handleMusic(void) {
		return 0;
	};
	
	// Updating of the GUI interface		
	bool prerunState::gs_handleGUI(void) {		
		GET_PRERUNSCENE->updateGUI();
		GET_PRERUNSCENE->displayCameraCoords();
		return true;
	};

	bool prerunState::gs_UpdateCamera(void) {
		GET_PRERUNSCENE->updateCamera();
		return true;
	}
	
	// Used to keep information stored statically into memory		
	bool prerunState::gs_exitingState(void) {
		return 0;
	};
	
	// Used to clean up this space freeing memory etc		
	bool prerunState::gs_terminatingState(void) {
		return 0;
	};
	
	
	/////////////////////////////////////
	/////////////////////////////////////
	
	runningState::runningState() {
	}
	
	runningState::~runningState() {
	}
	
	bool runningState::gs_loadState(void) {
		printf("Running state called\n");
		GET_RUNNINGSCENE->initialise();		
	}
	
	// Used to handle keys specific to this game state		
	bool runningState::gs_handleKeys(void) {
				
		// Fire a weapon
		if (gp2d::KeyPressed(SDLK_SPACE)) {
			GET_RUNNINGSCENE->FireMissile();
		}
		
		return true;
	};
	
	// Used to draw the background (not sure if needed)		
	bool runningState::gs_drawState(void) {
		
		GET_RUNNINGSCENE->drawMap();
		
		return true;
	};
	
	// Handle player intervention (this could be moving characters or menu options)		
	bool runningState::gs_handlePlayers(void) {			

		GET_RUNNINGSCENE->updatePlayers();
		GET_RUNNINGSCENE->updateMissiles();
		GET_RUNNINGSCENE->drawPlayerName();
	
		GET_RUNNINGSCENE->drawPlayerPosition();
		GET_RUNNINGSCENE->drawMissilePosition();		
		
/*	
		ptrPlayer = getScene()->GetPlayer("Player2");
		ptrPlayer->MoveMe(ptrTerrain);
		ptrCam->Begin();
		ptrPlayer->DrawMe();
		ptrCam->Begin();

		//ptrPlayer->DrawName();
		Text(	*ptrFont,																					\
					(ptrPlayer->x+(VIEWPORT_WIDTH/2)-ptrCam->GetX())-18,	\
					(ptrPlayer->y+(VIEWPORT_HEIGHT/2)-ptrCam->GetY())-48,	\
					0,1,1,1, 0.1,0.1,0.1,																	\
					ptrPlayer->Name);
		Text(	*ptrFont,																					\
					(ptrPlayer->x+(VIEWPORT_WIDTH/2)-ptrCam->GetX())-20,	\
					(ptrPlayer->y+(VIEWPORT_HEIGHT/2)-ptrCam->GetY())-50,	\
					0,1,1,1, 1, 1, 1,																		\
					ptrPlayer->Name);
	*/	
		return true;
	}
	
	//Handles looping music and sound FX		
	bool runningState::gs_handleMusic(void) {
		return 0;
	}
	
	// Updating of the GUI interface		
	bool runningState::gs_handleGUI(void) {
		
		GET_RUNNINGSCENE->updateGUI();
		GET_RUNNINGSCENE->displayCameraCoords();
		
		return true;
	}

	bool runningState::gs_updateCamera(void) {

		GET_RUNNINGSCENE->updateCamera();
		return true;		
	}
	

	// Used to keep information stored statically into memory		
	bool runningState::gs_exitingState(void) {
		return 0;
	}
	
	// Used to clean up this space freeing memory etc		
	bool runningState::gs_terminatingState(void) {
		return 0;
	}
	
}
