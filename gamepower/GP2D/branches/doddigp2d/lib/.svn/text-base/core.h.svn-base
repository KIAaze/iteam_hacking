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
	extern SDL_Event Event;	// Event variable.
	extern Uint8 *Keystate;	// Keypress variable.
	class Camera;

	class Texture {
   	public:
			GLuint id;									// Texture ID.
			GLfloat width, height;					// Texture width & height.
			SDL_Surface * imgF;						// Holds the loaded SDL surface, mainly
															// used for collision routines.
      	void Load(const char filename[]);	// Load a texture.
		void Modify(SDL_Surface *image2);	// Modify the exture to the current SDL_Surface
	};
	
	void RandomSeed();			// Generate a random seed.
	int EventResizeWindow();	// Window resizing event detector.

	void SetDebug(bool);								// Sets debugging mode on/off.
															//                                TODO:
	void PrintDebug(char *text);					// Prints a debug output     <-.- these functions should be changed
	void PrintDebug(char *text, char *text2);	// Prints a debug output too <-'- for something more flexible.

	int Init();											// Init the engine.
	void Cls();											// Clears the screen.
	void Sync();										// Syncs the frames.
	void ShowFPS();									// Shows the FPS on the window's titlebar.
	int SetVideoMode(int,int,int,bool,bool);	// Sets a video mode.
	void ResizeWindow(bool, int, int, bool);	// Resizes the window.

	// These functions are self-explanatory.
	void SetBackgroundColor(float,float,float,float);
	void ToggleFullscreen();
	void EnableCulling();
	void DisableCulling();
	void SwapCullingMode(int);
	void EnableLighting();
	void DisableLighting();
	void EnableTexturing();
	void DisableTexturing();
	void EnableDepth();
	void DisableDepth();
	void RotateTextureMatrix(float);

	void SetPointSize(GLfloat);						// Sets the OpenGL "pixel" size (in pixels).
	void EnableSmoothPoints();							// Enables antialiased points.
	void BeginPoints();									// Begin drawing points.
	void EndPoints();										// Stop drawing points.
	void DrawPixel(GLfloat, GLfloat);				// Draw a point in x,y.
	void SetColor3(GLfloat, GLfloat, GLfloat);	// Same as glColor3f.

	void BeginLines();													// Begin drawing lines.
	void DrawLine(GLfloat, GLfloat, GLfloat, GLfloat);			// Draw a line from x1,y1 to x2,y2.
	void DrawRectangle(GLfloat, GLfloat, GLfloat, GLfloat);	// Draw a rectangle from top-left to bottom-right.
	void EndLines();														// Stop drawing lines.

	GLfloat CurveValueGLf(GLfloat, GLfloat, GLfloat);			// Smooth translation from a value to another value.

	void CatchEvents();	// Catch the SDL events.
	int KeyPressed(int);	// Was a key pressed? which one?.

	Uint32 GetPixel(SDL_Surface*, Uint32, Uint32);	// Get a pixel's information.
	bool SetPixelAlpha(SDL_Surface*, Uint32, Uint32);	// Sets the pixel information to Black and fully transparent

	int iRand(int, int);

}

#endif
