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

#define	GP2D_KEYDOWN 		0
#define	GP2D_KEYPRESSED		1
#define	GP2D_KEYUP			2
#define	GP2D_MOUSEDOWN		3
#define	GP2D_MOUSEUP		4
#define	GP2D_MOUSEMOTION	5

namespace gp2d {

	enum GP2D_CURSORTYPES {
		GP2D_CURSOR_NORMAL=0,
		GP2D_CURSOR_WAITING,//1
		GP2D_CURSOR_CROSS,//2
		GP2D_NUMCURSORS//3
	};
	typedef enum GP2D_CURSORTYPES GP2DCursor;

	class CursorType {
		public:
			CursorType();
			~CursorType();
			void AddCursor ( GP2DCursor type, gp2d::Texture *tex );
			void SetCursor ( GP2DCursor type );
			static void Update ( int mx, int my );
			void Draw(int x, int y);
			void Enable ( bool enable );

		private:
			static int mouseX, mouseY;
			bool Enabled;
			GP2DCursor CurrentCursor;
		public:
			gp2d::Texture CursorTextures[3];
	};

	class MouseType {
		public:
			MouseType();
			~MouseType();

			void callMouseUp ( SDL_Event *e );
			void callMouseDown ( SDL_Event *e );
			void callMouseMotion ( SDL_Event *e );

		private:
			bool isDown;

		public:// TODO: Need to change back toprivate at some point
			void ( *MouseDown ) ( int mx, int my );
			void ( *MouseUp ) ( int mx, int my );
			void ( *MouseMove ) ( int mx, int my );
	};

	class KeyType {
		public:
			KeyType();
			~KeyType();

			void callKeyUp ( SDL_Event *e );
			void callKeyDown ( SDL_Event *e );
			void callKeyPressed ( SDL_Event *e );

		private:
			bool isDown;
			bool isPressed;

			unsigned int lastRepeat;
		public:// TODO: Need to change back toprivate at some point
			unsigned int repeatInterval;// How often to repeat the PRESSED callback function
			void ( *keyDown ) ();
			void ( *keyUp ) ();
			void ( *keyPressed ) ();

			bool isKeyDown() { return isDown; }
	};

	class inputHandler {
		public:
			inputHandler();
			~inputHandler();

			SDLKey current_keysym_sym;//current key value for use with ShowChar in iteam
			Uint16 current_keysym_unicode;//current unicode value for use with ShowChar in iteam

			void registerInputCallback ( unsigned int key, void ( *func ) (), int type, unsigned int repeat=0 );
			void registerInputCallback ( unsigned int key, void ( *func ) ( int mx, int my ), int type, unsigned int repeat=0 );
			void unregisterInputCallback ( unsigned int key );

// This is the generic mouse handling stuff for entire game
			void registerMouseMoveCallback ( void ( *func ) ( int mx, int my ) );
			void unregisterMouseMoveCallback();

			void ( *MouseMovementCallback ) ( int mx, int my );
			void ( *UnregisteredKeyUpCallback ) ( SDL_Event *e );
			int processEvents();
		private:
			map<unsigned int, KeyType*> inputHandlerKeyState;
			map<unsigned int, MouseType*> inputHandlerMouseState;
	};

}

#endif
