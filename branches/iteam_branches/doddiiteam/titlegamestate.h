#ifndef _titlegamestates_h
#define _titlegamestates_h

#include "globals.h"
#include "gamestate.h"

namespace iteam
{
	class titleState :  public gameState
	{
		public:
			titleState();
			~titleState();
				
			bool gs_loadState(void);
		
			// Used to draw the background (not sure if needed)		
			bool gs_drawState(void);
					
			bool gs_handlePlayers(void);
		
			bool gs_handleKeys(void);
					
			// Updating of the GUI interface		
			bool gs_handleGUI(void);
		
		private:
			gp2d::gameTimer 	titleTimer;
//			GLfloat 		cameraVelocityX;
//			GLfloat 		cameraVelocityY;		
	};	
}
#endif
