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

#ifndef _GP2D_TIMER_H
#define _GP2D_TIMER_H

namespace gp2d {

	class Timer	{
//attributes
		private:
			bool started;
			bool paused;
			unsigned int startTicks;
			unsigned int pausedTicks;
//methods
		public:
			Timer();
			void Start ( void );
			void Stop ( void );
			void Pause ( void );
			void Unpause ( void );
			int GetTicks ( void );
			bool IsStarted();
			bool IsPaused();
	};

}

#endif
