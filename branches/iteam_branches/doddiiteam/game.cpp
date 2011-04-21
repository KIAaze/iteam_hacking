#include "globals.h"
#include "gamestate.h"

namespace iteam
{
		
	game::game() {
		currentState = 0;
		lastState = 0xFFFF;
		numberOfStates = 0;		
	}
	
	game::~game() {
	}
	
	void game::isStateChanged(void) {
		
		// Does the current state want to relinquich running
		// to someone else
		if (lastState != currentState) {
			printf("State changed\n");
			if (lastState != 0xFFFF) {
				ptrStates[lastState]->gs_exitingState();
			}
			lastState = currentState;
			ptrStates[currentState]->gs_loadState();			
		}
	}
	
	bool game::AddGameState(gameState *ptrGameState) {		
		ptrStates[numberOfStates] = ptrGameState;	//Store the new state		
		numberOfStates++;											// Add the number of states within the game				
		return true;
	}
	
	bool game::game_keysHandler() {		
		// Handle state driven keyhandler		
		ptrStates[currentState]->gs_handleKeys();		
		return true;
	}
	
	bool game::game_drawState() {
		// Handle state driven drawState
		ptrStates[currentState]->gs_drawState();		
		return true;		
	}
	
	bool game::game_handlePlayers() {		
		// Handle state driven handlePlayers
		ptrStates[currentState]->gs_handlePlayers();
		return true;		
	}
	
	bool game::game_handleMusic() {		
		// Handle state driven music
		ptrStates[currentState]->gs_handleMusic();
		return true;		
	}
	
	bool game::game_handleGUI() {		
		// Handle state driven GUI
		ptrStates[currentState]->gs_handleGUI();		
		return true;		
	}
	
	bool game::game_updateCamera() {		
		//Handle state driven camera
		ptrStates[currentState]->gs_updateCamera();		
		return true;
	}
	
	bool game::game_loadState() {		
		// Handle state driven loadState
		ptrStates[currentState]->gs_loadState();		
		return true;		
	}
	
	bool game::game_exitingState() {		
		// Handle state driven exiting state
		ptrStates[currentState]->gs_exitingState();		
		return true;		
	}
	
	bool game::game_terminatingState() {		
		// Handle state driven terminatingState
		ptrStates[currentState]->gs_terminatingState();		
		return true;		
	}

}
