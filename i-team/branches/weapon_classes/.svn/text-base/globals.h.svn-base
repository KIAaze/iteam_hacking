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

/**< Susi's ID, code-wise: 1. See an example of this in Players.cpp/.h */
#define IT_PLAYER_SUSI 1

/**< Boolean flag for the Mirror property of a GP2D::Sprite. This is just so it can be read easier on the code rather than true/false and not knowing which direction the player is facing */
#define IT_PLAYER_FACE_LEFT true

/**< Boolean flag for the Mirror property of a GP2D::Sprite. This is just so it can be read easier on the code rather than true/false and not knowing which direction the player is facing */
#define IT_PLAYER_FACE_RIGHT false

#define IT_GRAVITY 500
#define IT_FRICTION 500
#define IT_VELOCITY_MAX 50

#define THUMBS_WIDTH 284	/**< X start position of the inventory */

#define THUMBS_HEIGHT 28	/**< Height of the inventory relative to the bottom of the screen */

#define PI 3.14159265

#define IT_GRAVITY_DEFAULT 100

// ================ PHYSICAL PROPERTIES ================

#define IT_MAX_WEAPON_VELOCITY 1.0
#define IT_BOUNCY_WEAPON 1
#define IT_NONEBOUNCY_WEAPON 0
#define IT_WEAPON_GRAVITY 1
#define IT_NO_WEAPON_GRAVITY 0
#define IT_NB_OF_WEAPONS 5

// ================ WEAPON TYPES =====================

#define IT_WT_GRENADE 				0
#define IT_WT_MISSILE				1
#define IT_WT_CLUSTERBOMB			2
#define IT_WT_DYNAMITE				3
#define IT_WT_RAZOR_LEAVES			4
#define IT_WT_RAZOR_LEAVES_X3			5
#define IT_WT_BANDAID				6
#define IT_WT_PISTOL				7
#define IT_WT_ROCKET				8

// ================ WEAPON COMPONENTS ================

#define IT_WC_GRENADE			0
#define IT_WC_BULLET			1

// ================ WEAPON PROPERTIES ================

#define IT_WT_GRENADE_TIME_DEFAULT	3
#define IT_WT_DYNAMITE_TIME_DEFAULT	10

#define IT_WT_GRENADE_BLAST_RADIUS		60.0
#define IT_WT_CLUSTERBOMB_BLAST_RADIUS		60.0
#define IT_WT_DYNAMITE_BLAST_RADIUS		240.0
#define IT_WT_MISSILE_BLAST_RADIUS		120.0
#define IT_WT_RAZOR_LEAVES_BLAST_RADIUS		120.0
#define IT_WT_RAZOR_LEAVES_X3_BLAST_RADIUS	50.0

#define IT_WT_GRENADE_BLAST_FACTOR		100.
#define IT_WT_CLUSTERBOMB_BLAST_FACTOR		100.
#define IT_WT_DYNAMITE_BLAST_FACTOR		100.
#define IT_WT_MISSILE_BLAST_FACTOR		200.0
#define IT_WT_RAZOR_LEAVES_BLAST_FACTOR		200.0
#define IT_WT_RAZOR_LEAVES_X3_BLAST_FACTOR	50.0

#define IT_WT_GRENADE_BLAST_DAMAGE		10.
#define IT_WT_CLUSTERBOMB_BLAST_DAMAGE		10.
#define IT_WT_DYNAMITE_BLAST_DAMAGE		10.
#define IT_WT_MISSILE_BLAST_DAMAGE		50.0
#define IT_WT_RAZOR_LEAVES_BLAST_DAMAGE		50.0
#define IT_WT_RAZOR_LEAVES_X3_BLAST_DAMAGE	30.0

#define IT_WT_MISSILE_ACCEL		200.0
#define IT_WT_RAZOR_LEAVES_ACCEL	0.0

#define IT_WT_BANDAID_HEAL_FACTOR	42.0

// ================  EXPLOSION STUFF ===================
#define EXPLOSION_HALO_WIDTH 		5

// =========== WEAPON IDs ===============
// NOTE: These are suggested names but can be changed
// 		to suite any type of weapon
#define GRENADE 	0
#define TRIPLE_GRENADE 	1
#define ROCKET 		2
#define MACHINE_GUN	3
#define PISTOL 		4

//code for easy debugging
#define LOG( str ) if (debugOn) fprintf( stderr, str );
#define DEBUGCODE if (debugOn)
#define DOUT(x) if (debugOn) fprintf(stderr, "%s = %d\n", #x, x);

using namespace gp2d;
// #include "Player.h"
#include "settings.h"

/*! \namespace iteam
\brief Main namespace.

This is where all the iteam-related functions are and will be declared, this is so it doesn't interfere with GP2D functions, variables or similar, unless explicitly stated.
*/

namespace iteam {
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
		ITEAM_COUNTDOWNPRE,//9
		ITEAM_COUNTDOWN,
		ITEAM_COUNTDOWNPOST,
		ITEAM_RUNNINGPRE,
		ITEAM_RUNNING,
		ITEAM_RUNNINGPOST,
		ITEAM_GAMEOVERPRE,
		ITEAM_GAMEOVER,
		ITEAM_GAMEOVERPOST,
	} ;
	typedef enum GAME_STATES GameState;

	typedef map <int,Sprite*> SpriteMap;
	extern SpriteMap supermap;

	//declared in iteam.cpp
	extern int gnDebug;/**debugging level. 0=no debugging info*/
	extern bool draw_tanks;/**Do you want tanks?*/
	extern bool music_on;
	extern GameState initial_gamestate;/**Initial gamestate*/

	//other
// 	extern iteam::WeaponsList* iteamWeapons;
	extern vector <gp2d::Texture*> Player_Texture;
	extern vector <gp2d::Texture*> Weapon_Texture;
	extern vector <gp2d::Texture*> Explosion_Texture;

	extern gp2d::Sprite Tank_base;/**< Tank_base sprite. */
	extern gp2d::Sprite Tank_canon;/**< Tank_canon sprite. */

	extern vector <gp2d::Sprite> Level;
	extern vector <gp2d::Sprite> InGameGUI;
	extern vector <gp2d::Font>   Font;
	extern vector <gp2d::Timer>  GameTimer;
	extern vector <gp2d::Sound>  Audio;
	extern vector <gp2d::Music>  Song;
	extern gp2d::Sprite AnglePointer;/**< Used to display shooting angle. */
	extern gp2d::Sprite WeaponSelector;/**< Used to highlight selected weapon. */

	extern gp2d::Camera Cam;/**< GP2D camera. */

	extern int GameResW;/**< Screen resolution width (in pixels). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int GameResH;/**< Screen resolution height (in pixels). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/

	extern int CurPlayer;/**< Current player's ID relative to the Player Vector. <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int CountdownValue;/**< A small countdown value/flag for animating the countdown sprite. <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern bool GameRunning;/**< Determines if the players can fight (true) or if they're waiting for the countdown to finish (false). <-- THIS APPEARS DUPLICATED. HOW TO REMOVE??*/
	extern int Seconds, SecondsCounter;

	extern gp2d::Timer  iTimer;/**< used for Mike's weapons maybe?. */
	extern GLfloat Gravity;
	extern int grenade_time;
	extern int dynamite_time;
	extern unsigned int CurrentWeapon;/**< Current weapon*/
	extern settings options;

	extern bool bStartshaking;

	extern bool bQuitGame;

	extern int can;

	extern GameState gameState;
	extern GameState nextState;

	extern GLfloat TERRAIN_XMIN;
	extern GLfloat TERRAIN_XMAX;
	extern GLfloat TERRAIN_YMIN;
	extern GLfloat TERRAIN_YMAX;

	extern GLfloat CAM_XMIN;
	extern GLfloat CAM_XMAX;
	extern GLfloat CAM_YMIN;
	extern GLfloat CAM_YMAX;

	extern int talk;
	extern char message[256];
	extern char message_buffer[3][256];

}
//namespace end

extern gp2d::GuiManager 	*GuiMan;
extern gp2d::inputHandler	*KeyHandler;	/**< This is the global system to handle all key inputs to the game >*/
extern gp2d::CursorType		*GameCursor;
#endif
