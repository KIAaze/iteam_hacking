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

TIMER FUNCTIONS (version 0.0.1)
By Doddi

MODIFICATIONS BY:
DARKGuy
===================================================================================
*/

#include "gp2d.h"
#include "core.h"
#include "timer.h"

namespace gp2d {

	Timer::Timer() {
		startTicks = 0;
		pausedTicks = 0;
		paused = false;
		started = false;
	}

	void Timer::Start ( void ) {
		started = true;// Start the timer
		paused = false;// Make sure we are not paused
		this->startTicks = SDL_GetTicks();// Grab the current tick count
	}

	void Timer::Stop ( void ) {
		started = false;// Stop the timer
		paused =false;// Make sure we are not paused
	}

	void Timer::Pause ( void ) {
		if (	( paused == false ) && ( started == true )	) {
			paused = true;
			pausedTicks = SDL_GetTicks() - startTicks;
		}
	}

	void Timer::Unpause ( void ) {
		if ( paused == true ) {
			paused = false;
			startTicks = SDL_GetTicks() - pausedTicks;
		}
	}

	int Timer::GetTicks ( void ) {
		if ( started == true ) {
			if ( paused == true ) {
				return pausedTicks;
			} else {
				return SDL_GetTicks() - startTicks;
			}
		}
		return 0;
	}

	bool Timer::IsStarted() {
		return started;
	}

	bool Timer::IsPaused() {
		return paused;
	}

}
