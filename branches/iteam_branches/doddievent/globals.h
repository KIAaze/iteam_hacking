/*! \file globals.h
\brief Holds the names of the global variables used throughout all the game code.

This is just a bunch of "extern" variable declarations... they are a "fake" image of the real variables. It will tell the compiler that the variable exists and to not to search for it.
Thus, we need to re-declare that variable. Most of the variables declared as extern in Globals.h are really declared at iteam.cpp
*/

#ifndef _ITEAM_GLOBALS_H
#define _ITEAM_GLOBALS_H
#include "library_h/gp2d.h"

#define IT_PLAYER_SUSI 1			/**< Susi's ID, code-wise: 1. See an example of this in Players.cpp/.h */
#define IT_PLAYER_FACE_LEFT true	/**< Boolean flag for the Mirror property of a GP2D::Sprite. This is just so it can be read easier on the code rather than true/false and not knowing which direction the player is facing */
#define IT_PLAYER_FACE_RIGHT false	/**< Boolean flag for the Mirror property of a GP2D::Sprite. This is just so it can be read easier on the code rather than true/false and not knowing which direction the player is facing */

using namespace gp2d;
#include "players.h"
#include "weapons.h"
#include "functions.h"
#include "mainmenu.h"
#include <iostream>

/*! \namespace iteam
\brief Main namespace.

This is where all the iteam-related functions are and will be declared, this is so it doesn't interfere with GP2D functions, variables or similar, unless explicitly stated.
*/
namespace iteam {
	
	extern vector <iteam::PlayerObj> Player;	/**< Holds a vector of all the players on the game scene. */

	extern vector <gp2d::Sprite> Level;
	extern vector <gp2d::Sprite> InGameGUI;
	extern vector <gp2d::Font>   Font;
	extern vector <gp2d::Timer>  Timer;
	extern vector <gp2d::Sound>  Audio;
	extern vector <gp2d::Music>  Song;

	extern gp2d::Camera Cam;					/**< GP2D camera. */

	extern int GameResW;						/**< Screen resolution width (in pixels). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int GameResH;						/**< Screen resolution height (in pixels). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/

	extern int CurPlayer;						/**< Current player's ID relative to the Player Vector. <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int CountdownValue;					/**< A small countdown value/flag for animating the countdown sprite. <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern bool GameRunning;					/**< Determines if the players can fight (true) or if they're waiting for the countdown to finish (false). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int Seconds, SecondsCounter;

	extern bool bQuitGame;
	extern void RegisterGlobalKeys();

	enum GAME_STATES {
		ITEAM_PREINTRO=0,
		ITEAM_INTRO,
		ITEAM_PREMAINMENU,
		ITEAM_MAINMENU,
		ITEAM_PRECOUNTDOWN,
		ITEAM_COUNTDOWN,
		ITEAM_PRERUNNING,
		ITEAM_RUNNING
	} ;
	typedef enum GAME_STATES GameState;
	extern GameState gameState;
}

	extern gp2d::inputHandler	*KeyHandler;	/**< This is the global system to handle all key inputs to the game >*/
#endif
