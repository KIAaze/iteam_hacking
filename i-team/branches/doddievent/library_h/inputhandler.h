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

INPUTHANDLER FUNCTIONS (version 0.0.1)
By Doddi

===================================================================================
*/

#ifndef _GP2D_INPUTHANDLER_H
#define _GP2D_INPUTHANDLER_H

#include "gp2d.h"
#include <SDL/SDL_thread.h>
#include <map>

#define GP2D_DEFINE_HASH_TYPE(type, variable)	typedef std::map<std::string, type> variable;
#define	GP2D_KEYDOWN 		0
#define	GP2D_KEYPRESSED	1
#define	GP2D_KEYUP			2

namespace gp2d {

	class keyType {
		public:
			keyType();
			~keyType();
		
			void callKeyUp(SDL_Event *e);
			void callKeyDown(SDL_Event *e);
			void callKeyPressed(SDL_Event *e);

		private:
			bool isDown;
			bool isPressed;

			unsigned int lastRepeat;
		public:										// TODO: Need to change back toprivate at some point
			unsigned int repeatInterval;		// How often to repeat the PRESSED callback function
			void (*keyDown)();
			void (*keyUp)();
			void (*keyPressed)();

			bool isKeyDown() { return isDown; }
	};

	class inputHandler {
		public:
			inputHandler(int(*func)(void));
			~inputHandler();

			void registerInputCallback(unsigned int key, void (*func)(), int type, unsigned int repeat=0);
			void unregisterInputCallback(unsigned int key);

			bool	bQuit;
			int(*initialisationFunction)(void);
			SDL_Thread	*inputThread;
//			SDL_mutex	*inputMutex;
			map<unsigned int, keyType*> inputHandlerKeyState;

		private:
			void	shutDownThread(void);
	};

}

#endif
