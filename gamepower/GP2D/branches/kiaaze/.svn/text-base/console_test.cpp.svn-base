//Program to test Jorgerosa's animations.
//Copy all animations from jorgerosa's folder on the FTP into data for it to work.
//Press TAB to switch between animations.

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "lib/gp2d.h"

using namespace gp2d;

vector <string> name;

#include "lib/GUI.h"
#include "lib/GUI_widgets.h"
#include "lib/GUI_output.h"


/* Variables that we'll need to clean up */
GUI *gui;
GUI_TermWin *terminal;
enum image_names {
	IMAGE_SCROLL_UP,
	IMAGE_SCROLL_DN,
	NUM_IMAGES
};
char *image_files[NUM_IMAGES] = {
	"scroll_up.bmp", "scroll_dn.bmp"
};
SDL_Surface *images[NUM_IMAGES];


void ShowChar(SDLKey key, Uint16 unicode)
{
	if ( unicode && (unicode <= 255) ) {
		Uint8 ch;

		ch = (Uint8)unicode;
		terminal->AddText((char *)&ch, 1);
	}
}

void cleanup(void)
{
	int i;

	/* Delete the GUI */
	delete gui;

	/* Clean up any images we have */
	for ( i=0; i<NUM_IMAGES; ++i ) {
		if ( images[i] ) {
			SDL_FreeSurface(images[i]);
		}
	}
}

void Output(SDL_Surface *screen, const char *title, const char *text)
{
	GUI_Output *output;

	output = GUI_CreateOutput(screen, 60, 5, NULL);
	if ( output ) {
		unsigned int i, pos;
		char formatted_text[1024];
#if 1
		/* Center the text in our window */
		pos = 0;
		formatted_text[pos++] = '\n';
		formatted_text[pos++] = '\n';
		for ( i=0; i<((60-strlen(text))/2); ++i ) {
			formatted_text[pos++] = ' ';
		}
		formatted_text[pos] = '\0';
		strcat(formatted_text, text);
#else
		strcpy(formatted_text, text);
#endif

		/* Run the output window with our text */
		GUI_AddOutput(output, formatted_text);
		GUI_ShowOutput(output, 1);
		GUI_DeleteOutput(output);
	}
}

int main(void)
{
	int GameResW = 800;
	int GameResH = 600;
	
	gp2d::SetDebug(true);
	gp2d::Init();
	gp2d::SetVideoMode(800,600,32,false,true);
	gp2d::SetFPS(30);
	gp2d::RandomSeed();
	gp2d::InitAudio(48000,AUDIO_S16,2,4096);
	atexit(SDL_Quit);
	
	gp2d::SetDataDir(".");

	gp2d::Camera Cam;
	Cam.Create();

	cout<<Cam.GetX()<<","<<Cam.GetY()<<endl;

	gp2d::Sprite Title;
	Title.Load("data/gui/intro.png");
	Title.width[0]=800;
	Title.height[0]=600;
	Title.Move(400,300);
	Title.alpha[0]=1;
	
	gp2d::Sprite Console;
	Console.Load("data/gui/black.png");
	Console.width[0]=800;
	Console.height[0]=300;
	Console.Move(400,150);
	Console.alpha[0]=0.5;

	gp2d::SetBackgroundColor(0,0,0,1);

	gp2d::GuiManager 	*GuiMan;
	gp2d::inputHandler	*KeyHandler;	/**< This is the global system to handle all key inputs to the game >*/
	gp2d::CursorType	*GameCursor;

	KeyHandler = new gp2d::inputHandler();

//	KeyHandler->registerInputCallback(SDLK_UP, scroll_up, GP2D_KEYDOWN);
//	KeyHandler->registerInputCallback(SDLK_DOWN, scroll_dn, GP2D_KEYDOWN);

////////////////////////////////////

	SDL_Surface *screen=get_Screen();
	int x, y, i;
	int error;
	GUI_Widget *widget;
	SDL_Rect null_rect = { 0, 0, 0, 0 };
	GUI_Menu *menu;
////////////////////
/*	// Initialize SDL 
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	int VideoFlags;
		VideoFlags  = SDL_OPENGL;
		VideoFlags |= SDL_GL_DOUBLEBUFFER;
		VideoFlags |= SDL_HWPALETTE;

	// Get a video mode for display 
	screen = SDL_SetVideoMode(640, 480, 0,SDL_HWSURFACE);
	if ( screen == NULL ) {
		fprintf(stderr, "Couldn't set video mode: %s\n",SDL_GetError());
		exit(1);
	}
	SDL_WM_SetCaption("GUI Hello!", "hello");*/
/////////////////////
	// Create a GUI container 
	printf("Create a GUI container \n");
	gui = new GUI(screen);

	FILE *f=fopen("debug.log","a");
	fprintf(f,"RAAAAAAAAAAAAAAAAAAAAAAAAAAAHHHHHH!!!!\n");
	fclose(f);


	// Load our images 
	for ( i=0; i<NUM_IMAGES; ++i ) {
		images[i] = NULL;
	}
	error = 0;
	for ( i=0; i<NUM_IMAGES; ++i ) {
		images[i] = SDL_LoadBMP(image_files[i]);
		if ( images[i] == NULL ) {
			fprintf(stderr, "Couldn't load '%s': %s\n",
					image_files[i], SDL_GetError());
			++error;
		}
	}
	if ( error ) {
		cleanup();
		exit(1);
	}

	// We also want a small text window with scroll buttons 
	x = images[IMAGE_SCROLL_UP]->w;
	terminal = new GUI_TermWin(x, 18, screen->w-x, 32, NULL, ShowChar, 32);
	terminal->AddText("Keystrokes will go here: ");
	gui->AddWidget(terminal);
	y = images[IMAGE_SCROLL_UP]->h;
	widget = new GUI_ScrollButtons(0,18, images[IMAGE_SCROLL_UP], null_rect,
					0, y+18, images[IMAGE_SCROLL_DN],
					SCROLLBAR_VERTICAL, terminal);
	gui->AddWidget(widget);

SDL_UnlockSurface(screen);
//SDL_WM_ToggleFullScreen(screen);
		gp2d::Font   FNTGameGUI;
		FNTGameGUI.Load("data/gui/ingame/eras_bold.TTF", 11);

//	gui->Run(NULL);
///////////////////////////
	int c=0;
	while(1)
	{
		gp2d::Cls();
	
		Cam.Begin();
			Title.Draw();
		Cam.End();
		Cam.Begin();
			if(c) Console.Draw();
		Cam.End();

		Cam.Begin();
	      Text(FNTGameGUI, 10,64+17*16, 0,1,1,1, 1,1,1, "DOH!!!!!!");
		Cam.End();

		//gui->Display();
	
		gui->Run(NULL);

		gp2d::ShowFPS();
		gp2d::Sync();

		while(CatchEvents())
		{
			if(gp2d::KeyDown(SDLK_TAB))
			{
				c=(c+1)%2;
				printf("toggling console: c=%d\n",c);
				//SDL_WM_ToggleFullScreen(screen);
				//terminal->Scroll(1);
			}
		}
		if(gp2d::Close_Event()) break;
	}
//////////////////////
	/* To make the compiler happy */
		FNTGameGUI.Clean();
	cleanup();
	return(0);
}
/*
	SDL_Surface *screen;
	int x, y, i;
	int error;
	GUI_Widget *widget;
	SDL_Rect null_rect = { 0, 0, 0, 0 };
	GUI_Menu *menu;

	// Initialize SDL 
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	// Get a video mode for display 
	screen = SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);
	if ( screen == NULL ) {
		fprintf(stderr, "Couldn't set video mode: %s\n",SDL_GetError());
		exit(1);
	}
	SDL_WM_SetCaption("GUI Hello!", "hello");

	// Create a GUI container 
	gui = new GUI(screen);

	// Load our images 
	for ( i=0; i<NUM_IMAGES; ++i ) {
		images[i] = NULL;
	}
	error = 0;
	for ( i=0; i<NUM_IMAGES; ++i ) {
		images[i] = SDL_LoadBMP(image_files[i]);
		if ( images[i] == NULL ) {
			fprintf(stderr, "Couldn't load '%s': %s\n",
					image_files[i], SDL_GetError());
			++error;
		}
	}
	if ( error ) {
		cleanup();
		exit(1);
	}

	// We also want a small text window with scroll buttons 
	x = images[IMAGE_SCROLL_UP]->w;
	terminal = new GUI_TermWin(x, 18, screen->w-x, 32, NULL, ShowChar, 32);
	terminal->AddText("Keystrokes will go here: ");
	gui->AddWidget(terminal);
	y = images[IMAGE_SCROLL_UP]->h;
	widget = new GUI_ScrollButtons(0,18, images[IMAGE_SCROLL_UP], null_rect,
					0, y+18, images[IMAGE_SCROLL_DN],
					SCROLLBAR_VERTICAL, terminal);
	gui->AddWidget(widget);

	// Run the GUI, and then clean up when it's done. 
	gui->Run(NULL);
	Output(screen,"-= Thanks =-","Thanks for trying the C++ GUI interface");
	cleanup();
	exit(0);
*/
