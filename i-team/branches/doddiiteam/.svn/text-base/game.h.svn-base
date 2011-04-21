#ifndef _GAME_H
#define _GAME_H

#include "globals.h"
#include "gamestate.h"
#include "gamescene.h"

namespace iteam {

	class gameState;
		
	class game
	{
	public:
		game();
		~game();
		
			// TODO:
//		static int GameResW;
//		static int GameResH;
		
		int numberOfStates;
		int currentState;
		int lastState;
		int currentPlayer;
	
		gameState *ptrStates[MAX_GAMESTATES];

		virtual bool Init() {
			return true;
		}
	
		bool AddGameState(gameState *ptrGameState);
	
		bool game_keysHandler();
		bool game_drawState();
		bool game_handlePlayers();
		bool game_handleMusic();
		bool game_handleGUI();
		bool game_updateCamera();
		bool game_loadState();
		bool game_exitingState();
		bool game_terminatingState();		
		void isStateChanged();
	};
}

#endif /* _GAME_H */
