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
*/

#include "gp2d.h"
#include "core.h"
#include "inputhandler.h"

namespace gp2d {

	int CursorType::mouseX=0;
	int CursorType::mouseY=0;

	CursorType::CursorType() {
		PrintDebug ( "[CursorType::CursorType] called" );
		mouseX=0;
		mouseY=0;
		Enabled=false;
		CurrentCursor=GP2D_CURSOR_NORMAL;

		// Set all textures to NULL
		/*		for (int idx=0; idx<3; idx++) {
					CursorTextures[idx] = NULL;
				}*/
	}
	CursorType::~CursorType() {
		// Delete all textures that have been created
// 		for (int idx=0; idx<3; idx++) {
// 			if (glIsTexture(CursorTextures[idx].id)) {
// 				delete CursorTextures[idx];
// 				CursorTextures[idx] = NULL;
// 			}
// 		}

		ShowCursor();
	}

	void CursorType::AddCursor ( GP2DCursor type, gp2d::Texture *tex ) {
		PrintDebug ( "[CursorType::AddCursor] called" );
		if ( type < GP2D_NUMCURSORS ) {
			if ( !glIsTexture ( tex->id ) ) {
				printf ( "[CursorType::AddCursor] FATAL ERROR: no texture\n" );exit ( 47 );
			}
			CursorTextures[type] = *tex;
			PrintDebug ( "cursor %i added\n", type );
		}
		else {
			PrintDebug ( "Invalid cursor type\n" );
		}
	}

	void CursorType::SetCursor ( GP2DCursor type ) {

		if ( type < GP2D_NUMCURSORS ) {
			if ( glIsTexture ( CursorTextures[type].id ) ) {
				PrintDebug ( "cursor %i set\n", type );
				CurrentCursor = type;
			}
			else {
				printf ( "FATAL ERROR: Cursor not initialised\n" );
				exit ( 28 );
			}
		}
		else {
			PrintDebug ( "Invalid cursor selected\n" );
		}
	}

	void CursorType::Enable ( bool enable ) {

		Enabled = enable;

		if ( enable ) {
			HideCursor();
		}
		else {
			ShowCursor();
		}
	}

	void CursorType::Update ( int mx, int my ) {
		/*		float fx = ( -SCREEN_WIDTH/2.0f ) +mx;
				float fy = ( -SCREEN_HEIGHT/2.0f ) +my;
				mouseX = ( int ) fx;
				mouseY = ( int ) fy;*/
          //get x,y of the click in the same coord system as player
          mouseX=mx-(VIEWPORT_WIDTH/2);
          mouseY=my-(VIEWPORT_HEIGHT/2);
	}

#define CURSOR_SIZE	16
	void CursorType::Draw(int x, int y) {
		if ( Enabled ) {
			if ( !glIsTexture ( CursorTextures[CurrentCursor].id ) ) {
				printf ( "FATAL ERROR: Cursor not initialised\n" );
				exit ( 28 );
			}

			glTranslatef ( mouseX+x,mouseY+y,0 );// Move to the sprite's coordinate.
			glRotatef ( 180,0,0,1 );// Rotate 180ÃÂº in Z

			//PrintDebug("currentcursor=%i, is=%i\n", CurrentCursor, CursorTextures[CurrentCursor]->id);
			glBindTexture ( GL_TEXTURE_2D, CursorTextures[CurrentCursor].id );

			EnableTexturing();// Enable texturing, just in case
			glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );// Set blending parameters, for PNGs
			glEnable ( GL_BLEND );// Enable blending.

			glBegin ( GL_QUADS );
			glColor4f ( 1,1,1,1 );// Set the sprite's alpha
			glTexCoord2f ( 1, 1 ); glVertex3f ( -CURSOR_SIZE, -CURSOR_SIZE, 0 );
			glTexCoord2f ( 1, 0 ); glVertex3f ( -CURSOR_SIZE,  CURSOR_SIZE, 0 );
			glTexCoord2f ( 0, 0 ); glVertex3f ( CURSOR_SIZE,  CURSOR_SIZE, 0 );
			glTexCoord2f ( 0, 1 ); glVertex3f ( CURSOR_SIZE, -CURSOR_SIZE, 0 );
			glEnd();
		}
	}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

	MouseType::MouseType() {
		isDown = false;

		MouseDown = NULL;
		MouseUp = NULL;
		MouseMove = NULL;
	}

	MouseType::~MouseType() {
		PrintDebug ( "MouseType Destructor called\n" );
	}

	void MouseType::callMouseDown ( SDL_Event *e ) {
		if ( this->isDown == false ) {
			this->isDown = true;
			//Check we have a callback function for DOWN to call
			if ( this->MouseDown != NULL ) {
				this->MouseDown ( e->motion.x, e->motion.y );
			}
		}
	}

	void MouseType::callMouseUp ( SDL_Event *e ) {
		if ( this->isDown == true ) {
			this->isDown = false;
			if ( this->MouseUp != NULL ) {
				this->MouseUp ( e->motion.x, e->motion.y );
			}
		}
	}

	void MouseType::callMouseMotion ( SDL_Event *e ) {
		if ( this->MouseMove != NULL ) {
			this->MouseMove ( e->motion.x, e->motion.y );
		}
	}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

	KeyType::KeyType() {
		isDown = false;
		isPressed = false;
		lastRepeat = 0;
		repeatInterval = 0;

		keyDown = NULL;
		keyUp = NULL;
		keyPressed = NULL;
	}

	KeyType::~KeyType() {
		PrintDebug ( "KeyType Destructor called\n" );
	}

	void KeyType::callKeyDown ( SDL_Event *e ) {
		if ( this->isDown == false ) {
			this->isDown = true;
			//Check we have a callback function for DOWN to call
			if ( this->keyDown != NULL ) {
				this->keyDown();
			}
		}
		else { // See if its time to repeat a pressed callback function
			PrintDebug ( "no repeat registered\n" );
			if ( this->keyPressed != NULL ) {
				PrintDebug ( "Repeat key\n" );
//				if (gblCurrentTime - lastRepeat > repeatInterval) {
				this->keyPressed();
//				}
			}
		}
	}

	void KeyType::callKeyUp ( SDL_Event *e ) {
		if ( this->isDown == true ) {
			this->isDown = false;
			if ( this->keyUp != NULL ) {
				this->keyUp();
			}
		}
	}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
	inputHandler::inputHandler() {
		UnregisteredKeyUpCallback = NULL;
	}

	inputHandler::~inputHandler() {
		// Get rid of all registered keys
		std::map<unsigned int, KeyType*>::iterator idx;

		while ( !inputHandlerKeyState.empty() ) {
			//PrintDebug("deleting\n");
			idx=inputHandlerKeyState.begin();
			delete inputHandlerKeyState[0];
			inputHandlerKeyState.erase ( idx );
		}
	}

	//Note that it returns 0 by default and -1 if an unregistered key goes down
	int inputHandler::processEvents() {

		SDL_Event e;

		while ( SDL_PollEvent ( &e ) ) {
			switch ( e.type ) {
				case SDL_KEYDOWN:
					PrintDebug ( "key down\n" );
					if ( this->inputHandlerKeyState[e.key.keysym.sym] != NULL ) {
						this->inputHandlerKeyState[e.key.keysym.sym]->callKeyDown ( &e );
					}
					else {
						PrintDebug ( "Key not registered\n" );
						current_keysym_sym=e.key.keysym.sym;
						current_keysym_unicode=e.key.keysym.unicode;
						//PrintDebug("%d=%d\n",current_keysym_unicode,e.key.keysym.unicode);
						return ( -1 );
					}
					break;
				case SDL_KEYUP:
					if ( this->inputHandlerKeyState[e.key.keysym.sym] != NULL ) {
						this->inputHandlerKeyState[e.key.keysym.sym]->callKeyUp ( &e );
					}
					else {
						PrintDebug ( "Key not registered\n" );
						if ( UnregisteredKeyUpCallback != NULL ) {
							UnregisteredKeyUpCallback ( &e );
						}
					}
					break;
				case SDL_MOUSEMOTION:
					if ( this->inputHandlerMouseState[SDL_MOUSEMOTION] != NULL ) {
						this->inputHandlerMouseState[SDL_MOUSEMOTION]->callMouseMotion ( &e );
					}
					else {
						//PrintDebug ( "mousedown motion not registered X=%i, Y=%i\n", e.motion.x, e.motion.y );
					}

					if ( MouseMovementCallback != NULL ) {
						MouseMovementCallback ( e.motion.x, e.motion.y );
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if ( this->inputHandlerMouseState[e.button.button] != NULL ) {
						this->inputHandlerMouseState[e.button.button]->callMouseDown ( &e );
					}
					else {
						PrintDebug ( "mousedown button not registered=%i\n", e.button.button );
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if ( this->inputHandlerMouseState[e.button.button] != NULL ) {
						this->inputHandlerMouseState[e.button.button]->callMouseUp ( &e );
					}
					else {
						PrintDebug ( "mouseup button not registered=%i\n", e.button.button );
					}
					break;
				default:
//						PrintDebug("Something else happened, type=%i\n",e.type);
					break;
					return ( 0 );
			}
		}
		return 0;
	}

	void inputHandler::registerMouseMoveCallback ( void ( *func ) ( int mx, int my ) ) {
		MouseMovementCallback = func;
	}
	void inputHandler::unregisterMouseMoveCallback() {
		MouseMovementCallback = NULL;
	}

	void inputHandler::registerInputCallback ( unsigned int key, void ( *func ) (), int type, unsigned int repeat ) {

		if ( inputHandlerKeyState[key] == NULL ) {
			inputHandlerKeyState[key] = new KeyType();
		}

		switch ( type ) {
			case GP2D_KEYDOWN:
				PrintDebug ( "register a keydown\n" );
				inputHandlerKeyState[key]->keyDown = func;
				break;
			case GP2D_KEYPRESSED:
				PrintDebug ( "register a key pressed\n" );
				inputHandlerKeyState[key]->keyPressed = func;
				break;
			case GP2D_KEYUP:
				PrintDebug ( "register a keyup\n" );
				inputHandlerKeyState[key]->keyUp = func;
				inputHandlerKeyState[key]->repeatInterval = repeat;
				break;
			default:
				PrintDebug ( "Error: incorrect key callback registered\n" );
				break;
		}
	}
	void inputHandler::registerInputCallback ( unsigned int key, void ( *func ) ( int mx, int my ), int type, unsigned int repeat ) {

		if ( inputHandlerMouseState[key] == NULL ) {
			inputHandlerMouseState[key] = new MouseType();
		}

		switch ( type ) {
			case GP2D_MOUSEDOWN:
				PrintDebug ( "register a mouse down\n" );
				inputHandlerMouseState[key]->MouseDown = func;
				break;
			case GP2D_MOUSEUP:
				PrintDebug ( "register a mouse up\n" );
				inputHandlerMouseState[key]->MouseUp = func;
				break;
			case GP2D_MOUSEMOTION:
				PrintDebug ( "register a mouse move\n" );
				inputHandlerMouseState[SDL_MOUSEMOTION]->MouseMove = func;
				break;
			default:
				PrintDebug ( "Error: incorrect mouse callback registered\n" );
				break;
		}
	}

	void inputHandler::unregisterInputCallback ( unsigned int key ) {

		// TODO: This is dangerous - need to check for invalid entries here first
		if ( key==SDL_BUTTON_LEFT || key==SDL_BUTTON_RIGHT || key==SDL_MOUSEMOTION ) {
			if ( inputHandlerMouseState[key] != NULL ) {
				delete inputHandlerMouseState[key];
				map<unsigned int, MouseType*>::iterator it = inputHandlerMouseState.find ( key );
				inputHandlerMouseState.erase ( it );
				PrintDebug ( "mouse handler deleted\n" );
			}
			else {
				PrintDebug ( "Mouse input handler not registered\n" );
			}
		}
		else {
			if ( inputHandlerKeyState[key] != NULL ) {
				delete inputHandlerKeyState[key];
				map<unsigned int, KeyType*>::iterator it = inputHandlerKeyState.find ( key );
				inputHandlerKeyState.erase ( it );
				PrintDebug ( "key handler deleted\n" );
			}
			else {
				PrintDebug ( "Key input handler not registered\n" );
			}
		}
	}

}

