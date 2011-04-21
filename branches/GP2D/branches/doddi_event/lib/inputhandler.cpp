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


	MouseType::MouseType() {
		isDown = false;

		MouseDown = NULL;
		MouseUp = NULL;
		MouseMove = NULL;
	}

	MouseType::~MouseType() {
		printf("MouseType Destructor called\n");
	}

	void MouseType::callMouseDown(SDL_Event *e) {
		if (this->isDown == false) {
			this->isDown = true;
			//Check we have a callback function for DOWN to call
			if (this->MouseDown != NULL) {		
				this->MouseDown(e->motion.x, e->motion.y);
			}
		}
	}

	void MouseType::callMouseUp(SDL_Event *e) {
		if (this->isDown == true) {
			this->isDown = false;
			if (this->MouseUp != NULL) {
				this->MouseUp(e->motion.x, e->motion.y);
			}
		}
	}

	void MouseType::callMouseMotion(SDL_Event *e) {
		if (this->MouseMove != NULL) {
			this->MouseMove(e->motion.x, e->motion.y);
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
		printf("KeyType Destructor called\n");
	}

	void KeyType::callKeyDown(SDL_Event *e) {
		if (this->isDown == false) {
			this->isDown = true;
			//Check we have a callback function for DOWN to call
			if (this->keyDown != NULL) {		
				this->keyDown();
			}
		}
		else { // See if its time to repeat a pressed callback function
			printf("no repeat registered\n");
			if (this->keyPressed != NULL) {
				printf("Repeat key\n");
//				if (gblCurrentTime - lastRepeat > repeatInterval) {
					this->keyPressed();
//				}
			}
		}
	}

	void KeyType::callKeyUp(SDL_Event *e) {
		if (this->isDown == true) {
			this->isDown = false;
			if (this->keyUp != NULL) {
				this->keyUp();
			}
		}
	}

	/////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	int inputHandlerFunction(void *data) {
		SDL_Event e;
		inputHandler *runningHandler = (inputHandler*)data;

		printf("Intialise video and other stuff\n");
		runningHandler->initialisationFunction();
		SDL_EnableKeyRepeat(100, 100);

		printf("InputHandler Thread started\n");
		while(runningHandler->bQuit == false) {

			SDL_Delay(100);	//Let someone else have a go

			while (SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_KEYDOWN:
						printf("key down\n");
						if (runningHandler->inputHandlerKeyState[e.key.keysym.sym] != NULL) {
							runningHandler->inputHandlerKeyState[e.key.keysym.sym]->callKeyDown(&e);
						}
						else {
							printf("Key not registered\n");
						}
						break;
					case SDL_KEYUP:
						if (runningHandler->inputHandlerKeyState[e.key.keysym.sym] != NULL) {
							runningHandler->inputHandlerKeyState[e.key.keysym.sym]->callKeyUp(&e);
						}
						else {
							printf("Key not registered\n");
						}
						break;
					case SDL_MOUSEMOTION:
						if (runningHandler->inputHandlerMouseState[SDL_MOUSEMOTION] != NULL) {
							runningHandler->inputHandlerMouseState[SDL_MOUSEMOTION]->callMouseMotion(&e);
						}
						else {
							printf("mousedown motion not registered X=%i, Y=%i\n", e.motion.x, e.motion.y);
						}
						break;
					case SDL_MOUSEBUTTONDOWN:
						if (runningHandler->inputHandlerMouseState[e.button.button] != NULL) {
							runningHandler->inputHandlerMouseState[e.button.button]->callMouseDown(&e);
						}
						else {
							printf("mousedown button not registered=%i\n", e.button.button);
						}
						break;
					case SDL_MOUSEBUTTONUP:
						if (runningHandler->inputHandlerMouseState[e.button.button] != NULL) {
							runningHandler->inputHandlerMouseState[e.button.button]->callMouseUp(&e);
						}
						else {
							printf("mouseup button not registered=%i\n", e.button.button);
						}
						break;
					default:
//						printf("Something else happened, type=%i\n",e.type);
						break;

				}
			}
		}

	}

	inputHandler::inputHandler(int(*initfunc)(void)) {
		bQuit = false;

		initialisationFunction = initfunc;

		inputThread = SDL_CreateThread(inputHandlerFunction, this);
	}

	inputHandler::~inputHandler() {
		// Get rid of all regsitered keys
		std::map<unsigned int, KeyType*>::iterator idx;

		while(!inputHandlerKeyState.empty()) {
			printf("deleting\n");
			idx=inputHandlerKeyState.begin();
			delete inputHandlerKeyState[0];
			inputHandlerKeyState.erase(idx);
		}

		printf("shutting down thread\n");
		shutDownThread();
	}

	void inputHandler::shutDownThread(void) {
		bQuit = true;
		SDL_WaitThread(inputThread, NULL);
		printf("inputHandler thread killed\n");
//		SDL_DestroyMutex(inputMutex);
		printf("inputHandler mutex destroyed\n");
	}

	void inputHandler::registerInputCallback(unsigned int key, void (*func)(), int type, unsigned int repeat) {

		if (inputHandlerKeyState[key] == NULL) {
			inputHandlerKeyState[key] = new KeyType();
		}

		switch (type) {
			case GP2D_KEYDOWN:
				printf("register a keydown\n");
				inputHandlerKeyState[key]->keyDown = func;
				break;
			case GP2D_KEYPRESSED:
				printf("register a key pressed\n");
				inputHandlerKeyState[key]->keyPressed = func;
				break;
			case GP2D_KEYUP:
				printf("register a keyup\n");
				inputHandlerKeyState[key]->keyUp = func;
				inputHandlerKeyState[key]->repeatInterval = repeat;
				break;
			default:
				printf("Error: incorrect key callback registered\n");
				break;
		}
	}
	void inputHandler::registerInputCallback(unsigned int key, void (*func)(int mx, int my), int type, unsigned int repeat) {

		if (inputHandlerMouseState[key] == NULL) {
			inputHandlerMouseState[key] = new MouseType();
		}

		switch (type) {
			case GP2D_MOUSEDOWN:
				printf("register a mouse down\n");
				inputHandlerMouseState[key]->MouseDown = func;
				break;
			case GP2D_MOUSEUP:
				printf("register a mouse up\n");
				inputHandlerMouseState[key]->MouseUp = func;
				break;
			case GP2D_MOUSEMOTION:
				printf("register a mouse move\n");
				inputHandlerMouseState[SDL_MOUSEMOTION]->MouseMove = func;
				break;
			default:
				printf("Error: incorrect mouse callback registered\n");
				break;
		}
	}
	
	void inputHandler::unregisterInputCallback(unsigned int key) {

		if (key==GP2D_KEYDOWN || key==GP2D_KEYUP || key==GP2D_KEYPRESSED) {
			if (inputHandlerKeyState[key] != NULL) {
				delete inputHandlerKeyState[key];
				map<unsigned int, KeyType*>::iterator it = inputHandlerKeyState.find(key);
				inputHandlerKeyState.erase(it);
			}
			else {
				printf("Key input handler not registered\n");
			}
		}
		else if (key==GP2D_MOUSEDOWN || key==GP2D_MOUSEUP || key==GP2D_MOUSEMOTION) {
			if (inputHandlerMouseState[key] != NULL) {
				delete inputHandlerMouseState[key];
				map<unsigned int, MouseType*>::iterator it = inputHandlerMouseState.find(key);
				inputHandlerMouseState.erase(it);
			}
			else {
				printf("Mouse input handler not registered\n");
			}
		}
		else {
			printf("Invalid unregisteration call\n");
		}
	}

}

