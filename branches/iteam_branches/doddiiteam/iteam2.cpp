#include <vector>

#include "globals.h"
#include "firstGame.h"

using namespace std;
using namespace gp2d;
using namespace iteam;

gp2d::gameTimer	myGameTimer;

unsigned int yStartTime;

int main()
{	
	atexit(SDL_Quit);	
	
	firstGame myGame;
		
	//Initialise the OpenGL screen etc
	myGame.init();
	
	myGame.LoadScenes();	
	myGame.AddStates();
	myGame.currentState = TITLE_SCREEN;
	
	myGameTimer.start();							// Start the delta timer
	
	while(1) {

		gp2d::Cls();
		gp2d::CatchEvents();
		
		// checks if it needs to change the state
		myGame.isStateChanged();
		
		if (myGame.game_keysHandler() == false)
		{
			break;
		}
		
		if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }

		// Draws the background and terrain based on what state it is running
		myGame.game_drawState();
		myGame.game_handlePlayers();
		myGame.game_handleMusic();
		myGame.game_handleGUI();
		myGame.game_updateCamera();
		
		gp2d::ShowFPS();
		gp2d::Sync();
	}
	
	SDL_Quit();
}
