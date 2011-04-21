#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include <vector>
#include "globals.h"
#include "game.h"
#include "gamescene.h"

using namespace std;

namespace iteam
{			
	class gameState
	{	
	public:		
		gameState();
		~gameState();
			
	protected:
		//TODO: Possibly make this a list of scenes per state???????
		int currentScene;
		vector <gameScene*> ptrScenes;									// Scene information for this state
	
	public:
		game			*ptrParent;
	
		void addScene(gameScene *ptr);
		void setScene (int val);
		gameScene* getScene(int val);
				
		// Used to handle keys specific to this game state		
		virtual bool gs_handleKeys(void) {
			return 0;
		};
		
		// Used to draw the background (not sure if needed)
		virtual bool gs_drawState(void) {
			return 0;
		};
		
		// Handle player intervention (this could be moving characters or menu options)		
		virtual bool gs_handlePlayers(void) {
			return 0;
		};
		
		//Handles looping music and sound FX
		virtual bool gs_handleMusic(void) {
			return 0;
		};
		
		// Updating of the GUI interface		
		virtual bool gs_handleGUI(void) {
			return 0;
		};
	
		// Update the position of the camera
		virtual bool gs_updateCamera(void) {
			return 0;
		}
		
		// Used to load in unique textures, sound etc		
		virtual bool gs_loadState(void) {
			return 0;
		};
		
		// Used to keep information stored statically into memory		
		virtual bool gs_exitingState(void) {
			return 0;
		};
		
		// Used to clean up this space freeing memory etc		
		virtual bool gs_terminatingState(void) {
			return 0;
		};
	};
}

#endif /* _GAMESTATE_H */
