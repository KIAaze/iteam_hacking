#include "SDL.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

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

int getKey(char *name)
{
	SDL_Event keyevent;    //The SDL event that we will poll to get events.
	bool done=false;
	int value;
	while (1)//loop until a key or mouse button is pressed
	{
		while(SDL_PollEvent(&keyevent))//Poll our SDL key event for any keystrokes.
		{
			if(keyevent.type==SDL_KEYDOWN)
			{
				value=keyevent.key.keysym.sym;
				sprintf(name,SDL_GetKeyName(keyevent.key.keysym.sym));
				done=true;
			}
			if(keyevent.type==SDL_MOUSEBUTTONDOWN)
			{
				value=-keyevent.button.button;
				sprintf(name,"mouse %d",-value);
				done=true;
			}
		}
		if(done) break;
	}
	return(value);
}

//Attempt at a function returning 0 if nothing has been pressed
//Unfortunately less responsive to keypresses. Not usable as is.
int getKey_2(char *name)
{
	SDL_Event keyevent;
	bool done=false;
	int value;
		while(SDL_PollEvent(&keyevent))
		{
			if(keyevent.type==SDL_KEYDOWN)
			{
				value=keyevent.key.keysym.sym;
				sprintf(name,SDL_GetKeyName(keyevent.key.keysym.sym));
				done=true;
				return(value);
			}
			if(keyevent.type==SDL_MOUSEBUTTONDOWN)
			{
				value=-keyevent.button.button;
				sprintf(name,"mouse %d",-value);
				done=true;
				return(value);
			}
		}
	return(0);
}

int main(int argc, char **argv)
{
   SDL_Init( SDL_INIT_VIDEO );

   SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0,
      SDL_HWSURFACE | SDL_DOUBLEBUF );

   SDL_WM_SetCaption( WINDOW_TITLE, 0 );

   //SDL_Event keyevent;    //The SDL event that we will poll to get events.

   bool gameRunning = true;

   while (gameRunning)
   {
	int k;
	char str[18];
/*	strcpy(str,"press a key");
	SDL_PollEvent(&keyevent);
	if(keyevent.type==SDL_QUIT) gameRunning=false;*/
	k=getKey(str);
	cout<<k<<":"<<str<<endl;
	if(k==27) gameRunning=false;
   }

   SDL_Quit();

   return 0;
}
