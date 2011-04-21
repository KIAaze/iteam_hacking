/*

	This file is part of GamePower 3D.

	GamePower 3D is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	GamePower 3D is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with GamePower 3D; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 3D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  (libsdl1.2-dev, libsdl-image1.2-dev)

MAIN HEADER FILE (version 0.0.3
BY DARKGUY

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the main header file.
===================================================================================
CHANGELOG:

0.0.3:
-> First release. this header file will hold -all- the neccessary stuff needed for
	using the GP3D library and must be included in order to use the library.

0.0.1:
-> It was not existant to this moment.
===================================================================================
*/

#ifndef _GP3D_MAIN_H
#define _GP3D_MAIN_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "core.h"
#include "light.h"
#include "3dmath.h"
#include "effects.h"
#include "camera.h"
#include "primitive.h"
#include "fileio.h"
#include "loaders/md2.h"

namespace gp {
	struct GlobalStruct {						// Global structure, here are going to be
														// all of the global variables.
		int FPS;										// FPS
		bool DebugMode;							// Debug Mode enabled or disabled?
	};

	extern const int PRIM_CUBE;				// Cube primitive
	extern const int PRIM_PYRAMID;			// Pyramid primitive, and so on...
	extern const int PRIM_SPHERE;
	extern const int PRIM_TORUS;
	extern const int VIEW_PERSPECTIVE;		// Perspective view
	extern const int VIEW_ORTHO;				// Orthogonal view
	extern const int CULL_CW;					// Clockwise culling
	extern const int CULL_CCW;					// Counter-clockwise culling

	extern GlobalStruct Globals;				// Declare the global structure as Globals

	extern int SCREEN_WIDTH;					// These hold the screen Width, Height & Depth
	extern int SCREEN_HEIGHT;
	extern int SCREEN_DEPTH;

	extern int VideoFlags;						// Video flags used (only for SDL)
	extern SDL_Surface *Screen;				// Screen surface
	extern const SDL_VideoInfo *VideoInfo;	// Video info structure
	extern float bg[3];							// Background color (and alpha?)
}

#endif
