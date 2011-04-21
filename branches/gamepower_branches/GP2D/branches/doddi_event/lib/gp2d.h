/*

	This file is part of GamePower 2D.

    GamePower 2D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 2D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 2D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 2D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  - libsdl1.2-dev
                          - libsdl-image1.2-dev
                          - libsdl-mixer1.2-dev
                        * FreeType development libraries
                          - libfreetype6-dev

MAIN HEADER FILE (version 0.0.1)
By DARKGuy

MODIFICATIONS BY:
No one at the moment.
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

#ifndef _GP2D_MAIN_H
#define _GP2D_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <vector>
#include <algorithm>

#include "core.h"
#include "3dmath.h"
#include "audio.h"
#include "camera.h"
#include "timer.h"
#include "fps.h"
#include "spritesheet.h"
#include "sprite.h"
#include "freetype.h"
#include "collision.h"
#include "fstream" // include fstream to see if files exist
#include "inputhandler.h"
#include "gui_system.h"

#ifdef _WIN32
	#include "windows.h"	// If we're on Windows, we need this...
	#include "ft2build.h"	// And this. This file comes from the freetype2 installation program for GNUWin32 (MinGW). Read the wiki for more details.
	#include FT_FREETYPE_H	// Same here.
#endif

namespace gp2d {

	// Self-explanatory global structure.
	struct GlobalStruct {
		int   FPS_frames;
		int   FPS_rate;
		int   FPS_oldticks;
		int   FPS_max;
		int   FPS_min;
		int   FPS_fixed;
		float FPS_ticks;
		int   FPS;
		bool  DebugMode;
	};

	extern const int CULL_CW;	// Cull mode clockwise
	extern const int CULL_CCW;	// Cull mode counter-clockwise

	extern GlobalStruct Globals;	// Declare the global structure as Globals

	extern int SCREEN_WIDTH;		// Screen width, height & depth.
	extern int SCREEN_HEIGHT;
	extern int SCREEN_DEPTH;
	extern int VIEWPORT_WIDTH;		// OpenGL viewport width & height.
	extern int VIEWPORT_HEIGHT;

	extern int VideoFlags;						// SDL video flags.
	extern SDL_Surface *Screen;				// SDL Screen surface.
	extern const SDL_VideoInfo *VideoInfo;	// SDL Video information structure.
	extern float bg[3];							// Background color.

	extern int  AudioCalls;
	extern int  AudioMaxChannels;
	extern bool AudioAllocateNewChannels;

}

#endif
