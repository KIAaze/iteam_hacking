#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "SDL Start";

void MouseMoved		(const int& iButton,
					const int& iX, 
					const int& iY, 
					const int& iRelX, 
					const int& iRelY)
{
	cout<<"MouseMoved: "<<iButton<<","<<iX<<","<<iY<<","<<iRelX<<","<<iRelY<<endl;
}

void MouseButtonUp	(const int& iButton, 
					const int& iX, 
					const int& iY, 
					const int& iRelX, 
					const int& iRelY)
{
	cout<<"MouseButtonUp"<<endl;
}

void MouseButtonDown	(const int& iButton, 
					const int& iX, 
					const int& iY, 
					const int& iRelX, 
					const int& iRelY)
{
	cout<<"MouseButtonDown"<<endl;
}

/** Is the window minimized? **/
bool m_bMinimized;

/** Window is active again. **/
void WindowActive	()
{
	cout<<"WindowActive"<<endl;
}

/** Window is inactive. **/
void WindowInactive	()
{
	cout<<"WindowInactive"<<endl;
}

int main(int argc, char **argv)
{
   SDL_Init( SDL_INIT_VIDEO );

   SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0,
      SDL_HWSURFACE | SDL_DOUBLEBUF );
   SDL_WM_SetCaption( WINDOW_TITLE, 0 );

   int batImageX = 24;
   int batImageY = 63;
   int batWidth = 65;
   int batHeight = 44;

   // We change these to make the bat move
   int batX_1 = 100;
   int batY_1 = 100;
   int batX_2 = 100;
   int batY_2 = 100;

   int speed=10;

   SDL_Event keyevent;    //The SDL event that we will poll to get events.

   bool gameRunning = true;

   bool keysHeld[323] = {false}; // everything will be initialized to false

   int charxvel=0;
   int charyvel=0;
   int charx=0;
   int chary=0;

   while (gameRunning)
   {
	// Declare it
	Uint8* keystates;
	
	// Initialize it
	keystates = SDL_GetKeyState(0);  // or SDL_GetKeyState(NULL)
	
	// Then in the loop, use it
	if(keystates[SDLK_UP])
	{
		//move up at a constant rate
		cout<<"up pressed"<<endl;
		charyvel = -1;
	}

	while (SDL_PollEvent(&keyevent))   //Poll our SDL key event for any keystrokes.
	{
		cout<<"SDL_PollEvent"<<endl;
		switch(keyevent.type)
		{


			case SDL_MOUSEMOTION:
				MouseMoved(
					keyevent.button.button, 
					keyevent.motion.x, 
					keyevent.motion.y, 
					keyevent.motion.xrel, 
					keyevent.motion.yrel);
				break;
	
			case SDL_MOUSEBUTTONUP:
				MouseButtonUp(
					keyevent.button.button, 
					keyevent.motion.x, 
					keyevent.motion.y, 
					keyevent.motion.xrel, 
					keyevent.motion.yrel);
				break;
	
			case SDL_MOUSEBUTTONDOWN:
				MouseButtonDown(
					keyevent.button.button, 
					keyevent.motion.x, 
					keyevent.motion.y, 
					keyevent.motion.xrel, 
					keyevent.motion.yrel);
				break;
	
			case SDL_ACTIVEEVENT:
				if ( keyevent.active.state & SDL_APPACTIVE ) {
					if ( keyevent.active.gain ) {
						m_bMinimized = false;
						WindowActive();
					} else {
						m_bMinimized = true;
						WindowInactive();
					}
				}
				break;


			case SDL_QUIT:
			gameRunning = false;
			break;

			case SDL_KEYDOWN:
			cout<<"SDL_KEYDOWN"<<endl;
			switch(keyevent.key.keysym.sym){
				case SDLK_ESCAPE:
				gameRunning = false;
				break;
				case SDLK_LEFT:
				charxvel = -1;
				break;
				case SDLK_RIGHT:
				charxvel = 1;
				break;
				case SDLK_UP:
				charyvel = -1;
				break;
				case SDLK_DOWN:
				charyvel = 1;
				break;
				default:
				break;
			}
			break;
			case SDL_KEYUP:
			cout<<"SDL_KEYUP"<<endl;
			switch(keyevent.key.keysym.sym){
				case SDLK_LEFT:
				charxvel = 0;
				break;
				case SDLK_RIGHT:
				charxvel = 0;
				break;
				case SDLK_UP:
				charyvel = 0;
				break;
				case SDLK_DOWN:
				charyvel = 0;
				break;
				default:
				break;
			}
			break;
		}
	}
	
	charx += charxvel;
	chary += charyvel;

      // Draw the scene
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
      SDL_Flip(screen);
   }

   SDL_Quit();

   return 0;
}
