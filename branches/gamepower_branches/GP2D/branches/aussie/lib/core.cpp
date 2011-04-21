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

NOTE: Most stuff is commented in the header file, so the only commented stuff here 
      will be the content of each function, if a comment is needed to be made.
*/

#include "gp2d.h"
#include "core.h"

namespace gp2d {

	// ******************************************************************************
	// Variables, structures, constants, etc.
	// ******************************************************************************
	GlobalStruct Globals;

	const int CULL_CW = GL_CW;
	const int CULL_CCW = GL_CCW;

	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int SCREEN_DEPTH;
	int VIEWPORT_WIDTH;
	int VIEWPORT_HEIGHT;

	int VideoFlags;
	SDL_Surface *Screen;
	const SDL_VideoInfo *VideoInfo;

	float bg[3];

	SDL_Event Event;
	Uint8 *Keystate;

	Mix_Music * Song;

	// ******************************************************************************
	// Main functions go here
	// ******************************************************************************

	void RandomSeed(){
		srand((unsigned)time(0)); 
	}

	int EventResizeWindow() {
		if(Event.type == SDL_VIDEORESIZE){ return true; } else { return false; }
	}

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
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
		VIEWPORT_WIDTH = width;
		VIEWPORT_HEIGHT = height;

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
	void ResizeWindow(bool Auto, int NewWidth, int NewHeight, bool stretch) {
		if(Auto == true){
			NewWidth = Event.resize.w;
			NewHeight = Event.resize.h;
		}
		GLfloat ratio;
		if ( NewWidth <= 0 ) { NewWidth = 1; }
		if ( NewHeight <= 0 ) { NewHeight = 1; }

		SCREEN_WIDTH = NewWidth;
		SCREEN_HEIGHT = NewHeight;
		if(stretch == false){				// If we're not stretching the display, then let's add
			VIEWPORT_WIDTH = NewWidth;		// more screen space by increasing the OpenGL viewport.
			VIEWPORT_HEIGHT = NewHeight;
		}

		Screen = SDL_SetVideoMode( NewWidth, NewHeight, SCREEN_DEPTH, VideoFlags );
		if ( !Screen ) {
			PrintDebug("<ERROR> GP3DResizeWindow() -> Could not get a surface after resize.\nError string:\n\n",SDL_GetError());
		}

		glViewport( 0, 0, ( GLsizei )NewWidth, ( GLsizei )NewHeight );
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
		if(Globals.FPS_rate != 0){ FPSDelay(); }
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

	// ==============================================================================
	// Loads a texture
	// ==============================================================================

	void Texture::Load(const char filename[]){
		GLuint texture;
		SDL_Surface * image2 = IMG_Load(filename);
		SDL_Surface * imgFile = SDL_DisplayFormatAlpha(image2);

		width = (GLfloat)image2->w;
		height = (GLfloat)image2->h;
		imgF = image2;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		id = texture;
		/*
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if(imgFile->format->BitsPerPixel == 32 || imgFile->format->BitsPerPixel == 24){
			glTexImage2D(GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgFile->pixels);
		} else { glTexImage2D(GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgFile->pixels); }
		*/
		if(imgFile->format->BitsPerPixel == 32 || imgFile->format->BitsPerPixel == 24){
			glTexImage2D(GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgFile->pixels);
		} else { glTexImage2D(GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgFile->pixels); }
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		
	}
	void Texture::Modify(SDL_Surface *image2){
		GLuint texture;

		SDL_Surface * imgFile = SDL_DisplayFormatAlpha(image2);

		glDeleteTextures(1, &id);	// Delete the existing texture
		
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		this->id = texture;

		if(imgFile->format->BitsPerPixel == 32 || imgFile->format->BitsPerPixel == 24) {
			glTexImage2D(GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgFile->pixels);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgFile->pixels); 
		}
	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void SetPointSize(GLfloat newsize) { glPointSize(newsize); }
	void EnableSmoothPoints() { glEnable(GL_POINT_SMOOTH); }
	void BeginPoints() { glBegin(GL_POINTS); }
	void EndPoints() { glEnd(); }
	void DrawPixel(GLfloat x, GLfloat y) { glVertex3f(x, y, 0.0f); }
	void SetColor3(GLfloat r, GLfloat g, GLfloat b) { glColor3f(r,g,b); }
	
	void BeginLines() { glBegin(GL_LINES); }
	void DrawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
		glVertex3f(x1,y1,0.0f);
		glVertex3f(x2,y2,0.0f);
	}
	void DrawRectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
		DrawLine(x1,y1,x2,y1);
		DrawLine(x1,y1,x1,y2);
		DrawLine(x1,y2,x2,y2);
		DrawLine(x2,y1,x2,y2);
	}
	void EndLines() { glEnd(); }

	GLfloat CurveValueGLf(GLfloat destination, GLfloat current, GLfloat steps){ 
		GLfloat returnvalue;
		returnvalue = (destination-current)/steps+current;
		return returnvalue;
	}

	/* returns pixel value at (x,y)

		Taken from the SDL Wiki.
	*/
	Uint32 GetPixel(SDL_Surface *surface, Uint32 x, Uint32 y)
	{
    	int bpp = surface->format->BytesPerPixel;
    	/* Here p is the address to the pixel we want to retrieve */
    	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    	switch(bpp) {
    	case 1:
        	return *p;
    	case 2:
        	return *(Uint16 *)p;
    	case 3:
        	if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            	return p[0] << 16 | p[1] << 8 | p[2];
        	else
            	return p[0] | p[1] << 8 | p[2] << 16;
    	case 4:
        	return *(Uint32 *)p;
    	default:
        	return 0;       /* shouldn't happen, but avoids warnings */
    	}
	}

	bool SetPixelAlpha(SDL_Surface *surface, Uint32 x, Uint32 y)
	{
		Uint8	pr, pg, pb, pa;
    	int bpp = surface->format->BytesPerPixel;
    	/* Here p is the address to the pixel we want to retrieve */
    	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    	switch(bpp) {
    	case 1:
			return false;
    	case 2:
        	return false;
    	case 3:
			return false;		
    	case 4:
        	*((Uint32*)p) = 0x00FFFFFF;					// Red=0x00, Green=0x00, Blue=0x00, Alpha=0x00
			return true;
    	default:
        	return false;       /* shouldn't happen, but avoids warnings */
    	}
	}
	
	int iRand(int from, int to){ return rand()%to+from; }

}
