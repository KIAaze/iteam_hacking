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
	int Load_Textures();

	/*! \brief Loads fonts, graphics, sounds, players, backgrounds, etc and sets them up on the scene (this should change). */

	/*! \brief Draws the background layers. */
	void DrawBackground();

	/*! \brief Draws the terrain. */
	void DrawTerrain();

//==========================from mickey's branch.
	int LoadSinglePlayer();

	void InitPhysics();

	void InitWeapons ( PhysicsSystem *physics );

//========= from globals.h
//no need to externalize functions
	void RegisterGlobalKeys();
// 	extern void RegisterIngameKeys();
	void UnRegisterGlobalKeys();
// 	extern void UnRegisterIngameKeys();

}

#endif
