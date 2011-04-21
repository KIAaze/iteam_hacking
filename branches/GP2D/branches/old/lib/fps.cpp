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

FPS CONTROLLER (version 0.0.1)
By DARKGuy

MODIFICATIONS BY:
Doddi
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

#include "gp2d.h"
#include "core.h"

namespace gp2d {

	GLfloat GetDelta ( GLfloat velocity, unsigned int deltaTicks ) {
		GLfloat result;

		GLfloat secPerFrame = deltaTicks / 1000.0f;// Stored in seconds
		result = velocity * secPerFrame;

		return result;
	}

	// Limits the FPS
	void SetFPS ( int rate ) {
		if ( Globals.FPS_max == 0 ) { Globals.FPS_max = 200; }// If no one set the max FPS, set them to 200.
		if ( Globals.FPS_min == 0 ) { Globals.FPS_min = 0; }// Same with min FPS.
		if ( rate >= Globals.FPS_min && rate <= Globals.FPS_max ) {// If the desired framerate is within range...
			Globals.FPS_frames = 0;// Set FPS_frames to 0.
			Globals.FPS_rate = rate;// Set FPS_rate to .
			Globals.FPS_ticks = ( 1000.0 / ( float ) rate );// Get the ticks.
		}
	}

	// Waits for the required time for archieving the FPS desired.
	void FPSDelay() {
		int oldticks;// Old time
		int newticks;// New time

		Globals.FPS_frames++;// Increment frames.

		oldticks = SDL_GetTicks();// Get the old time
		newticks = Globals.FPS_oldticks+ ( int ) ( ( float ) Globals.FPS_frames*Globals.FPS_ticks );// Get the new time

		if ( oldticks <= newticks ) {// Too slow, let's wait.
			SDL_Delay ( newticks - oldticks );
		} else {// Too fast! keep up :).
			Globals.FPS_frames = 0;
			Globals.FPS_oldticks = SDL_GetTicks();
		}
	}

}
