#ifndef _firstgamestates_h
#define _firstgamestates_h

#include "gamestate.h"

namespace iteam
{
	class prerunState :  public gameState
	{
		public:
			prerunState();			
			~prerunState();
	
			// Used to draw the background (not sure if needed)		
			bool gs_drawState(void);
			
			// Handle player intervention (this could be moving characters or menu options)		
			bool gs_handlePlayers(void);
		
			bool gs_handleKeys(void);
			
			//Handles looping music and sound FX		
			bool gs_handleMusic(void);
			
			// Updating of the GUI interface		
			bool gs_handleGUI(void);
			
			bool gs_UpdateCamera(void);
			
			// Used to load in unique textures, sound etc		
			bool gs_loadState(void);
			
			// Used to keep information stored statically into memory		
			bool gs_exitingState(void);
			
			// Used to clean up this space freeing memory etc		
			bool gs_terminatingState(void);
				
		private:
			
			int countdownValue;
			int tempCountdownValue;
	};
	
	
	
////////////////////////////////////////////////
////////////////////////////////////////////////	
	
	
	class runningState :  public gameState
	{
		public:
			runningState();			
			~runningState();
		
		// Used to handle keys specific to this game state		
		bool gs_handleKeys(void);
		
		// Used to draw the background (not sure if needed)		
		bool gs_drawState(void);
		
		// Handle player intervention (this could be moving characters or menu options)		
		bool gs_handlePlayers(void);
		
		//Handles looping music and sound FX		
		bool gs_handleMusic(void);
		
		// Updating of the GUI interface		
		bool gs_handleGUI(void);
	
		bool gs_updateCamera(void);
		
		// Used to load in unique textures, sound etc		
		bool gs_loadState(void);
		
		// Used to keep information stored statically into memory		
		bool gs_exitingState(void);
		// Used to clean up this space freeing memory etc		
		bool gs_terminatingState(void);			
		
	};	
}
#endif
