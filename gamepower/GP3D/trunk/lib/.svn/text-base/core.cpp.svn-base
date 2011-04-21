/*

	This file is part of GamePower 3D.

    GamePower 3D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 3D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 3D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 3D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  (libsdl1.2-dev, libsdl-image1.2-dev)

CORE FUNCTIONS FILE (version 0.0.3)
BY DARKGUY

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the main core file, where the system, video/sound/etc. functions are
defined.
===================================================================================
CHANGELOG:

0.0.3:
-> Full code rewrite. Too many changes to list, but everything was moved to
	a namespace, there are new functions and some variables were taken out.

0.0.1:
-> First code release, basic video/system handling and created a header file for
   basic primitive handling.
===================================================================================
*/

#include "gp3d.h"
#include "core.h"

namespace gp {

	// ******************************************************************************
	// Variables, structures, constants, etc.
	// ******************************************************************************
	GlobalStruct Globals;				// Global structure

	const int PRIM_CUBE    = 1;		// Cube primitive
	const int PRIM_PYRAMID = 2;		// Pyramid primitive, and so on...
	const int PRIM_SPHERE  = 3;		// ...
	const int PRIM_TORUS   = 4;		// ...
	const int VIEW_PERSPECTIVE = 1;	// Perspective view
	const int VIEW_ORTHO = 2;			// Orthogonal view
	const int CULL_CW = GL_CW;			// Clockwise culling mode
	const int CULL_CCW = GL_CCW;		// Counter-Clockwise culling mode

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int SCREEN_DEPTH;

	int VideoFlags;
	SDL_Surface *Screen;					// Screen surface
	const SDL_VideoInfo *VideoInfo;

	float bg[3];							// Background color [0]=Red, [1]=Green, [2]=Blue, [3]=Alpha?

	SDL_Event Event;						// Event catcher
	Uint8 *Keystate;						// Keystrokes catcher


	// ******************************************************************************
	// Main functions go here
	// ******************************************************************************

	// ==============================================================================
	// Prints debug info
	// ==============================================================================
	void PrintDebug(char *text) {
		if(Globals.DebugMode == true){ printf("[GamePower] %s\n",text); }
	}
	void PrintDebug(const char text[]) {
		if(Globals.DebugMode == true){ printf("[GamePower] %s\n",text); }
	}
	// ==============================================================================
	// Prints debug info, same as above but with optional parameter
	// ==============================================================================
	void PrintDebug(char *text,char *text2) {
		if(Globals.DebugMode == true){ printf("[GamePower] %s%s\n",text,text2); }
	}
	// ==============================================================================
	// Enables and disables debug mode
	// ==============================================================================
	void SetDebug(bool value) {
		if(value == true){ Globals.DebugMode = true; }
		if(value == true){ PrintDebug("SYSTEM: Debug mode: Enabled."); } else { PrintDebug("SYSTEM: Debug mode: Disabled."); }
		if(value == false){ Globals.DebugMode = false; }
	}

	// ==============================================================================
	// Initializes everything
	// ==============================================================================
	int Init() {
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
			PrintDebug("<ERROR> Init() -> Error in SDL_Init(SDL_INIT_EVERYTHING).\nError string:\n\n",SDL_GetError());
		} else {
			PrintDebug("VIDEO: [Good] SDL initialized");
			VideoInfo = SDL_GetVideoInfo();
			if ( !VideoInfo )	{
				PrintDebug("<ERROR> ::Init () -> Video query failed.\nError string:\n\n",SDL_GetError());
				return -1;
			} else {
				return 1;
			}
		}
		return 0;
	}

	// ==============================================================================
	// Sets the video mode, and opens a window with the specified settings
	// ==============================================================================
	int SetVideoMode(int width, int height, int depth, bool fullscreen, bool resizable) {
		int bpp;

		VideoFlags  = SDL_OPENGL;                              PrintDebug("VIDEO: OpenGL flag set.");
		VideoFlags |= SDL_GL_DOUBLEBUFFER;                     PrintDebug("VIDEO: Double Buffer flag set.");
		VideoFlags |= SDL_HWPALETTE;                           PrintDebug("VIDEO: Hardware Palette flag set.");
		if(fullscreen == true) { VideoFlags |= SDL_FULLSCREEN; PrintDebug("VIDEO: OpenGL flag set."); }
		if(resizable == true) { VideoFlags |= SDL_RESIZABLE;   PrintDebug("VIDEO: Resizable flag set."); }

		if (VideoInfo->hw_available == 1) {
			VideoFlags |= SDL_HWSURFACE;
			PrintDebug("VIDEO: [Good] Surfaces can be stored in hardware memory.");
		} else {
			VideoFlags |= SDL_SWSURFACE;
			PrintDebug("VIDEO: [Bad] Surfaces cannot be stored in hardware memory.");
		}

		if (VideoInfo->blit_hw) {
			VideoFlags |= SDL_HWACCEL;
			PrintDebug("VIDEO: [Good] Hardware blitting can be done");
			if(VideoInfo->blit_hw_CC){
				PrintDebug("VIDEO: [Good] Hardware color keys are accelerated");
			} else {
				PrintDebug("VIDEO: [Bad] Hardware color keys aren't accelerated");
			}
			if(VideoInfo->blit_hw_A){
				PrintDebug("VIDEO: [Good] Hardware alpha blits are accelerated");
			} else {
				PrintDebug("VIDEO: [Bad] Hardware alpha blits aren't accelerated");
			}
		} else {
			PrintDebug("VIDEO: [Bad] Hardware blitting cannot be done");
			PrintDebug("VIDEO: [Good] Software blitting can be done");
			if(VideoInfo->blit_sw_CC){
				PrintDebug("VIDEO: [Good] Software color keys are accelerated");
			} else {
				PrintDebug("VIDEO: [Bad] Software color keys aren't accelerated");
			}
			if(VideoInfo->blit_sw_A){
				PrintDebug("VIDEO: [Good] Software alpha blits are accelerated");
			} else {
				PrintDebug("VIDEO: [Bad] Software alpha blits aren't accelerated");
			}
		}

		if( SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ) != 0) {
			PrintDebug("<ERROR> SetVideoMode() -> OpenGL cannot use double buffering!\nError string:\n\n",SDL_GetError());
			return -1;
		} else {
			PrintDebug("VIDEO: [Good] OpenGL set to double buffering");
		}

		// TODO: Pass the "VIDEO: Checking mode %i x %i @ %i bpp",width,height,depth" to PrintDebug
		// PrintDebug();

		bpp=SDL_VideoModeOK(width, height, depth, VideoFlags);
		if(!bpp){
			// TODO: Pass the "VIDEO: Unable to use the video mode %i x %i @ %i bpp",width,height,depth" to PrintDebug
			// PrintDebug();
			return -1;
		} else {
			Screen = SDL_SetVideoMode(width, height, depth, VideoFlags);
			if( !Screen ) {
				PrintDebug("<ERROR> SetVideoMode -> Surface not available. Video mode set failed.\nError string:\n\n",SDL_GetError());
				return -1;
			} else {
				// TODO: Pass the "VIDEO: Using mode %ix%i@%ibpp\n",width,height,depth" to PrintDebug
				// PrintDebug();
				return 1;
			}
		}
	}

	// ==============================================================================
	// Resizes the current window
	// ==============================================================================
	void ResizeWindow(bool Auto, int NewWidth, int NewHeight, Camera *cam) {
		if(Auto == true){
			NewWidth = Event.resize.w;
			NewHeight = Event.resize.h;
		}
		GLfloat ratio;
		if ( NewWidth <= 0 ) { NewWidth = 1; }
		if ( NewHeight <= 0 ) { NewHeight = 1; }

		Screen = SDL_SetVideoMode( NewWidth, NewHeight, SCREEN_DEPTH, VideoFlags );
		if ( !Screen ) {
			PrintDebug("<ERROR> GP3DResizeWindow() -> Could not get a surface after resize.\nError string:\n\n",SDL_GetError());
		}

		ratio = ( GLfloat )NewWidth / ( GLfloat )NewHeight;
		glViewport( 0, 0, ( GLsizei )NewWidth, ( GLsizei )NewHeight );
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity( );
		gluPerspective( cam->CameraFov, ratio, cam->CameraMinRange, cam->CameraMaxRange );
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
	}

	// ==============================================================================
	// Clears the screen
	// ==============================================================================
	void Cls() {
		glClearColor(bg[0],bg[1],bg[2],bg[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// ==============================================================================
	// Flips the buffers
	// ==============================================================================
	void Sync() {
		glFlush();
		SDL_GL_SwapBuffers();
	}

	// ==============================================================================
	// Shows the FPS on the window's titlebar
	// ==============================================================================
	void ShowFPS() {
		static float fps           = 0.0f;
		static float previousTime  = 0.0f;
		static char  strFPS[20]    = {0};
		float currentTime = (SDL_GetTicks() * 0.001f);
		++fps;
		if( currentTime - previousTime > 1.0f )
		{
			previousTime = currentTime;
			sprintf(strFPS, "FPS: %i", int(fps));
			SDL_WM_SetCaption(strFPS,strFPS);
			Globals.FPS = int(fps);
			fps = 0.0f;
		}
	}

	// ==============================================================================
	// Changes the background color used to clear the screen
	// ==============================================================================
	void SetBackgroundColor(float red, float blue, float green, float alpha) {
		bg[0] = red;	bg[1] = blue; bg[2] = green; bg[3] = alpha;
	}

	void ToggleFullscreen() { SDL_WM_ToggleFullScreen(Screen);	}	// Toggles fullscreen
	void EnableCulling() { glEnable(GL_CULL_FACE); }					// Enables culling
	void DisableCulling() { glDisable(GL_CULL_FACE); }					// Disables culling
	void SwapCullingMode(int type) { glFrontFace(type); }				// Changes the culling mode
	void EnableLighting() { glEnable(GL_LIGHTING); }					// Enables lighting
	void DisableLighting() { glDisable(GL_LIGHTING); }					// Disables lighting
	void EnableTexturing() { glEnable(GL_TEXTURE_2D); }				// Enables texturing
	void DisableTexturing() { glDisable(GL_TEXTURE_2D); }				// Disables texturing
	void EnableDepth() { glEnable(GL_DEPTH_TEST); }						// Enables the depth pass
	void DisableDepth() { glDisable(GL_DEPTH_TEST); }					// Disables the depth pass

	// ==============================================================================
	// Loads a texture
	// ==============================================================================
	GLuint LoadTexture(const char filename[]){
		GLuint texture;
		SDL_Surface * image2 = IMG_Load(filename); if (image2 == NULL){ return false; }
		SDL_Surface * imgFile = SDL_DisplayFormatAlpha(image2); if (imgFile == NULL){ return false; }
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// TODO: Check if it's compatible with the functions used above, and if not, how to
		// TODO: generate the mipmaps then?

		// gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgFile->w, imgFile->h, GL_RGB, GL_UNSIGNED_BYTE, imgFile->pixels);

		if(imgFile->format->BitsPerPixel == 32 || imgFile->format->BitsPerPixel == 24){
			glTexImage2D(GL_TEXTURE_2D, 0, 3, imgFile->w, imgFile->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgFile->pixels);
		} else { glTexImage2D(GL_TEXTURE_2D, 0, 3, imgFile->w, imgFile->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgFile->pixels); }

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (imgFile) {
			if (imgFile->pixels){ free(imgFile->pixels); }
			free(imgFile);
		}

		return texture;
	}

	// ==============================================================================
	// Rotates the texture matrix
	// ==============================================================================
	void RotateTextureMatrix(float angle){
		glMatrixMode(GL_TEXTURE);
		glRotatef(angle,0.0f,0.0f,1.0f);
		glScalef(-1.0f,1.0f,1.0f);
	}

	// ==============================================================================
	// Gets the SDL events
	// ==============================================================================
	void CatchEvents() {
		SDL_PollEvent(&Event);
	}

	// ==============================================================================
	// Gets the pressed key
	// ==============================================================================
	int KeyPressed(int Key) {
		Keystate = SDL_GetKeyState(NULL);
		if(Keystate[Key]){ return(1); } else { return(0); }
	}

}
