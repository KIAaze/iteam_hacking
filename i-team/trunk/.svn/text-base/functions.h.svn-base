/*! \file functions.h
\brief Header for the main in-game functions (for now).
*/
#ifndef _ITEAM_FUNCTIONS_H
#define _ITEAM_FUNCTIONS_H

#include "physics.h"

namespace iteam {

	void InitialiseMouse();

	/*! \brief forces the main while(1) loop of the game to exit */
	void quitOrAdvanceProgram ( void );

	/*! \brief gameQuit is called to release memory and close SDL safely
			This function is used by atexit() function						 */
	void gameQuit();

	/*! \brief Inits the GP2D system and sets it up for the game.

	This sets the screen resolution (for iteam use), some variables and starts the GP2D system. Initializes video, audio, sets the Max. FPS to 60 and sets SDL to run SDL_Quit when our game ends or gets closed.
	*/
	int Init();

	/*! \brief Loads fonts, graphics, sounds, players, backgrounds, etc and sets them up on the scene (this should change).

	This function creates the camera, loads game fonts, music, sound, adds two players, loads the terrain and its background layers, it loads the GUI and a countdown sprite. It also initializes the weapon subsystem by Mike.
	This should change too, so Load() would be used when a new game starts, and load everything up in a different way. Or maybe a preloading function when the game starts for the GUI & fonts and other stuff wouldn't be bad,
	and just to load the players and terrain when a new fight comes in.
	*/
	int LoadGameData();

	/*! \brief This function cleans up what Load has loaded. */
	int CleanGameData();

	/*! \brief Draws the background layers. */
	void DrawBackground();

	/*! \brief Draws the terrain. */
	void DrawTerrain();

	/*! \brief Draws the GUI, and optionally for debugging purposes, it displays the Camera's X & Y (this should be removed in the future). */
	void DrawGUI();

	/*! \brief Passes the turn to the next player. */
	void NextTurn();

//==========================from mickey's branch.
	int LoadSinglePlayer();

	void DestroyRunningGame();

	void InitPhysics();

	void InitWeapons ( PhysicsSystem *physics );

	void DoIteamBehaviours();

//========= from globals.h
//no need to externalize functions
	void RegisterGlobalKeys();
// 	extern void RegisterIngameKeys();
	void UnRegisterGlobalKeys();
// 	extern void UnRegisterIngameKeys();

}

#endif
