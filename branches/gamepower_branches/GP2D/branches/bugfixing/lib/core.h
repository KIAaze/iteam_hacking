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

CORE FUNCTIONS (version 0.0.1)
By DARKGuy

MODIFICATIONS BY:
No one at the moment.
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

#ifndef _GP2D_CORE_H
#define _GP2D_CORE_H

#include "gp2d.h"

namespace gp2d {

	extern SDL_Event Event;// Event variable.
	extern Uint8 *Keystate;// Keypress variable.
	class Camera;

	//added by KIAaze
	/** Is the window minimized? **/
	extern bool m_bMinimized;
	//-----------------------

	class Texture {
			//attributes
		public:
			char TextureName[256];
			GLuint id;// Texture ID.
			GLfloat width, height;// Texture width & height.
			SDL_Surface * imgF;// Holds the loaded SDL surface, mainly
			// used for collision routines.

			//methods
		public:
			void Load ( const char filename[] );// Load a texture.
			void Modify ( SDL_Surface *image2 );// Modify the texture to the current SDL_Surface

			//The big two
		public:
			Texture();//default constructor
			Texture ( const char filename[] );//special constructor

			//The big three
		public:
			Texture ( const Texture& );//copy constructor
			Texture& operator= ( const Texture& );//assignment operator
			~Texture();//destructor

	};

	void RandomSeed();// Generate a random seed.
	int EventResizeWindow();// Window resizing event detector.
	int SetDataDir ( const char DataDir[] );//Sets location where data will be looked for. It is initialized to "." when Init() is called.

	void SetDebug ( bool );// Sets debugging mode on/off.
	void PrintDebug ( const char *fmt,... );// Prints a debug output

	int Init();// Init the engine.
	void Cls();// Clears the screen.
	void Sync();// Syncs the frames.
	void ShowFPS();// Shows the FPS on the window's titlebar.
	int SetVideoMode ( int,int,int,bool,bool );// Sets a video mode.
	void ResizeWindow ( bool, int, int, bool );// Resizes the window.

	// These functions are self-explanatory.
	void SetBackgroundColor ( float,float,float,float );
	void ToggleFullscreen();
	void EnableCulling();
	void DisableCulling();
	void SwapCullingMode ( int );
	void EnableLighting();
	void DisableLighting();
	void EnableTexturing();
	void DisableTexturing();
	void EnableDepth();
	void DisableDepth();
	void RotateTextureMatrix ( float );

	void SetPointSize ( GLfloat );// Sets the OpenGL "pixel" size (in pixels).
	void EnableSmoothPoints();// Enables antialiased points.
	void BeginPoints();// Begin drawing points.
	void EndPoints();// Stop drawing points.
	void DrawPixel ( GLfloat, GLfloat );// Draw a point in x,y.
	void SetColor3 ( GLfloat, GLfloat, GLfloat );// Same as glColor3f.

	void BeginLines();// Begin drawing lines.
	void DrawLine ( GLfloat, GLfloat, GLfloat, GLfloat );// Draw a line from x1,y1 to x2,y2.
	void DrawRectangle ( GLfloat, GLfloat, GLfloat, GLfloat );// Draw a rectangle from top-left to bottom-right.
	void DrawLine ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat r, GLfloat g, GLfloat b );// Draw a line from x1,y1 to x2,y2 with color (r,g,b).
	void DrawRectangle ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat r, GLfloat g, GLfloat b );// Draw a rectangle from top-left to bottom-right with color (r,g,b).
	void EndLines();// Stop drawing lines.

	GLfloat CurveValueGLf ( GLfloat, GLfloat, GLfloat );// Smooth translation from a value to another value.

	//modified by KIAaze
	//now returns int instead of void
	int CatchEvents();// Catch the SDL events.
	SDL_Event getEvent();//return SDL_Event "Event"

	//--------------------------

	int KeyPressed ( int );// Was a key pressed? which one?.

	//added by KIAaze
	int KeyDown ( int Key );// Returns true when Key goes down
	int KeyUp ( int Key );// Returns true when Key goes up
	int Close_Event ( void );// Returns true on Close event

	/** The mouse has been moved.
		@param iButton	Specifies if a mouse button is pressed.
		@param iX	The mouse position on the X-axis in pixels.
		@param iY	The mouse position on the Y-axis in pixels.
		@param iRelX	The mouse position on the X-axis relative to the last position, in pixels.
		@param iRelY	The mouse position on the Y-axis relative to the last position, in pixels.

		@bug The iButton variable is always NULL.
	**/
	int MouseMoved	( int& iButton,
	                 int& iX,
	                 int& iY,
	                 int& iRelX,
	                 int& iRelY );

	/** A mouse button has been released.
		@param iButton	Specifies if a mouse button is pressed.
		@param iX	The mouse position on the X-axis in pixels.
		@param iY	The mouse position on the Y-axis in pixels.
		@param iRelX	The mouse position on the X-axis relative to the last position, in pixels.
		@param iRelY	The mouse position on the Y-axis relative to the last position, in pixels.
	**/
	int MouseButtonUp	( int& iButton,
	                    int& iX,
	                    int& iY,
	                    int& iRelX,
	                    int& iRelY );

	/** A mouse button has been pressed.
		@param iButton	Specifies if a mouse button is pressed.
		@param iX	The mouse position on the X-axis in pixels.
		@param iY	The mouse position on the Y-axis in pixels.
		@param iRelX	The mouse position on the X-axis relative to the last position, in pixels.
		@param iRelY	The mouse position on the Y-axis relative to the last position, in pixels.
	**/
	int MouseButtonDown	( int& iButton,
	                      int& iX,
	                      int& iY,
	                      int& iRelX,
	                      int& iRelY );

	/** Window is active again. **/
	void WindowActive	();

	/** Window is inactive. **/
	void WindowInactive	();

	/** Returns true if window is minimized.
		If window is active, it calls WindowActive and sets m_bMinimized to false.
		If window is inactive, it calls WindowInactive and sets m_bMinimized to true.
	**/
	bool CheckWindowState();
//-----------------------------------

	Uint32 GetPixel( SDL_Surface*, Uint32, Uint32 );// Get a pixel's information.
	bool SetPixelAlpha ( SDL_Surface*, Uint32, Uint32);// Sets the pixel information to Black and fully transparent

//--------------------------
//I created those 4 functions because I find them easier to use, more general and safer.
//All functions return true if the pixel asked for is inside the surface and false otherwise.
//*Color: takes 1 Uint32 value in the RGBA format
//*RGBA: takes 4 Uint8 values representing the colors+alpha
//This RGBA/Color system is based on the SDL gfx library. ;)
//If add=true, a pixel with the given color+alpha is drawn over the current pixel. (blending?)
//If add=false, the current pixel's color is set to the given color+alpha. (default)
	bool SetPixelColor( SDL_Surface* surf, Uint32 x, Uint32 y, Uint32 color, bool add=false );
	bool SetPixelRGBA( SDL_Surface* surf, Uint32 x, Uint32 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool add=false );
	bool GetPixelColor( SDL_Surface* surf, Uint32 x, Uint32 y, Uint32 &color );
	bool GetPixelRGBA( SDL_Surface* surf, Uint32 x, Uint32 y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a );
//--------------------------

	bool FileExists ( const char filename[] );

	int iRand ( int, int );

	void ShowCursor();
	void HideCursor();

	int closest_power_of_two ( double x );
	double scale_factor ( int texSize, int x_current );
	SDL_Surface* resize ( SDL_Surface* image, int texSize );
	bool SDL_OGL_SaveScreenshot(const char *FileName);
}

#endif
