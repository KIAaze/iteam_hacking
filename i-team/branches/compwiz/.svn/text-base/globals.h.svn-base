/*! \file globals.h
\brief Holds the names of the global variables used throughout all the game code.

This is just a bunch of "extern" variable declarations... they are a "fake" image of the real variables. It will tell the compiler that the variable exists and to not to search for it.
Thus, we need to re-declare that variable. Most of the variables declared as extern in Globals.h are really declared at iteam.cpp
*/

#ifndef _ITEAM_GLOBALS_H
#define _ITEAM_GLOBALS_H

#ifdef _WIN32
#include "../../gamepower/GP2D/trunk/lib/gp2d.h"
#else
#include "library_h/gp2d.h"
#endif

#define IT_PLAYER_SUSI 1			/**< Susi's ID, code-wise: 1. See an example of this in Players.cpp/.h */
#define IT_PLAYER_FACE_LEFT true	/**< Boolean flag for the Mirror property of a GP2D::Sprite. This is just so it can be read easier on the code rather than true/false and not knowing which direction the player is facing */
#define IT_PLAYER_FACE_RIGHT false	/**< Boolean flag for the Mirror property of a GP2D::Sprite. This is just so it can be read easier on the code rather than true/false and not knowing which direction the player is facing */

#define IT_GRAVITY 500
#define IT_FRICTION 500
#define IT_VELOCITY_MAX 50

#define THUMBS_WIDTH 284	/**< X start position of the inventory */
#define THUMBS_HEIGHT 28	/**< Height of the inventory relative to the bottom of the screen */

//code for easy debugging
#define LOG( str ) if (debugOn) fprintf( stderr, str );
#define DEBUGCODE if (debugOn)
#define DOUT(x) if (debugOn) fprintf(stderr, "%s = %d\n", #x, x);

using namespace gp2d;
#include "players.h"
#include "weapons.h"
#include "functions.h"
#include "mainmenu.h"
#include "basicwidget.h"
#include "settings.h"
#include "iteam_maths.h"

/*! \namespace iteam
\brief Main namespace.

This is where all the iteam-related functions are and will be declared, this is so it doesn't interfere with GP2D functions, variables or similar, unless explicitly stated.
*/
namespace iteam {

	extern vector <iteam::PlayerObj> Player;	/**< Holds a vector of all the players on the game scene. */

	extern gp2d::Sprite Tank_base;				/**< Tank_base sprite. */
	extern gp2d::Sprite Tank_canon;				/**< Tank_canon sprite. */

	extern vector <gp2d::Sprite> Level;
	extern vector <gp2d::Sprite> InGameGUI;
	extern vector <gp2d::Font>   Font;
	extern vector <gp2d::Timer>  Timer;
	extern vector <gp2d::Sound>  Audio;
	extern vector <gp2d::Music>  Song;
	extern gp2d::Sprite AnglePointer;			/**< Used to display shooting angle. */
	extern gp2d::Sprite WeaponSelector;			/**< Used to highlight selected weapon. */

	extern gp2d::Camera Cam;					/**< GP2D camera. */

	extern int GameResW;						/**< Screen resolution width (in pixels). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int GameResH;						/**< Screen resolution height (in pixels). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/

	extern int CurPlayer;						/**< Current player's ID relative to the Player Vector. <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int CountdownValue;					/**< A small countdown value/flag for animating the countdown sprite. <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern bool GameRunning;					/**< Determines if the players can fight (true) or if they're waiting for the countdown to finish (false). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int Seconds, SecondsCounter;

	extern gp2d::Timer  iTimer;					/**< used for Mike's weapons maybe?. */
	extern GLfloat Gravity;
	extern int grenade_time;
	extern int dynamite_time;
	extern int CurrentWeapon;	/**< Current weapon*/
	extern settings options;

    extern bool PauseTime;

	extern bool bStartshaking;

	extern bool bQuitGame;
	extern void RegisterGlobalKeys();
// 	extern void RegisterIngameKeys();
	extern void UnRegisterGlobalKeys();
// 	extern void UnRegisterIngameKeys();

	extern int	can;
	extern Button *btn;

	enum GAME_STATES {
		ITEAM_INTROPRE=0,
		ITEAM_INTRO,
		ITEAM_INTROPOST,
		ITEAM_OPTIONSMENUPRE,
		ITEAM_OPTIONSMENU,
		ITEAM_OPTIONSMENUPOST,
		ITEAM_MAINMENUPRE,
		ITEAM_MAINMENU,
		ITEAM_MAINMENUPOST,
		ITEAM_COUNTDOWNPRE,
		ITEAM_COUNTDOWN,
		ITEAM_DOWNPOST,
		ITEAM_RUNNINGPRE,
		ITEAM_RUNNING,
		ITEAM_RUNNINGPOST,
	} ;
	typedef enum GAME_STATES GameState;
	extern GameState gameState;
	extern GameState nextState;

	extern int talk;
	extern char message[256];
	extern char message_buffer[3][256];
}

	extern gp2d::GuiManager 	*GuiMan;
	extern gp2d::inputHandler	*KeyHandler;	/**< This is the global system to handle all key inputs to the game >*/
	extern gp2d::CursorType		*GameCursor;
#endif










