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

	char DATA_DIR[256];

	int VideoFlags;
	SDL_Surface *Screen;
	const SDL_VideoInfo *VideoInfo;

	float bg[3];

	SDL_Event Event;
	Uint8 *Keystate;

//added by KIAaze
	/** Is the window minimized? **/
	bool m_bMinimized=false;
//---------------------

// ******************************************************************************
// Main functions go here
// ******************************************************************************

	void RandomSeed() {
		srand ( ( unsigned ) time ( 0 ) );
	}

	int EventResizeWindow() {
		if ( Event.type == SDL_VIDEORESIZE ) { return true; }
		else { return false; }
		return true; // suppresses a warning
	}

	int SetDataDir ( const char DataDir[] ) {
		strcpy ( DATA_DIR,DataDir );
		return ( 0 );
	}

// ==============================================================================
// Prints debug info
// ==============================================================================
	void PrintDebug ( const char *fmt... ) {
		if ( Globals.DebugMode == true ) {
			char text[256];// Holds Our String
			va_list ap;// Pointer To List Of Arguments
			va_start ( ap, fmt );// Parses The String For Variables
			vsprintf ( text, fmt, ap );// And Converts Symbols To Actual Numbers
			va_end ( ap );// Results Are Stored In Text
			printf ( "[GamePower] %s\n",text );
		}
	}

// ==============================================================================
// Enables and disables debug mode
// ==============================================================================
	void SetDebug ( bool value ) {
		if ( value == true ) { Globals.DebugMode = true; }
		if ( value == true ) { PrintDebug ( "SYSTEM: Debug mode: Enabled." ); }
		else { PrintDebug ( "SYSTEM: Debug mode: Disabled." ); }
		if ( value == false ) { Globals.DebugMode = false; }
	}

// ==============================================================================
// Initializes everything
// ==============================================================================
	int Init() {
		SetDataDir ( "." );//sets default directory to current directory
		if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 ) {
			PrintDebug ( "<ERROR> Init() -> Error in SDL_Init(SDL_INIT_EVERYTHING).\nError string:\n\n%s",SDL_GetError() );
		}
		else {
			PrintDebug ( "VIDEO: [Good] SDL initialized" );
			VideoInfo = SDL_GetVideoInfo();
			if ( !VideoInfo ) {
				PrintDebug ( "<ERROR> ::Init () -> Video query failed.\nError string:\n\n%s",SDL_GetError() );
				return -1;
			}
			else {
				return 1;
			}
		}
		return 0;
	}

	// ==============================================================================
	// Sets the video mode, and opens a window with the specified settings
	// ==============================================================================
	int SetVideoMode ( int width, int height, int depth, bool fullscreen, bool resizable ) {
		int bpp;
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
		VIEWPORT_WIDTH = width;
		VIEWPORT_HEIGHT = height;

		//The SDL_OPENGL flag doesn't work with the default GUIlib. :(
		//...and if removed, i-team segfaults...so it might be better to rework GUIlib
		VideoFlags  = SDL_OPENGL;                              PrintDebug ( "VIDEO: OpenGL flag set." );
		VideoFlags |= SDL_GL_DOUBLEBUFFER;                     PrintDebug ( "VIDEO: Double Buffer flag set." );
		VideoFlags |= SDL_HWPALETTE;                           PrintDebug ( "VIDEO: Hardware Palette flag set." );
		if ( fullscreen == true ) { VideoFlags |= SDL_FULLSCREEN; PrintDebug ( "VIDEO: OpenGL flag set." ); }
		if ( resizable == true ) { VideoFlags |= SDL_RESIZABLE;   PrintDebug ( "VIDEO: Resizable flag set." ); }

		if ( VideoInfo->hw_available == 1 ) {
			VideoFlags |= SDL_HWSURFACE;
			PrintDebug ( "VIDEO: [Good] Surfaces can be stored in hardware memory." );
		}
		else {
			VideoFlags |= SDL_SWSURFACE;
			PrintDebug ( "VIDEO: [Bad] Surfaces cannot be stored in hardware memory." );
		}

		if ( VideoInfo->blit_hw ) {
			VideoFlags |= SDL_HWACCEL;
			PrintDebug ( "VIDEO: [Good] Hardware blitting can be done" );
			if ( VideoInfo->blit_hw_CC ) {
				PrintDebug ( "VIDEO: [Good] Hardware color keys are accelerated" );
			}
			else {
				PrintDebug ( "VIDEO: [Bad] Hardware color keys aren't accelerated" );
			}
			if ( VideoInfo->blit_hw_A ) {
				PrintDebug ( "VIDEO: [Good] Hardware alpha blits are accelerated" );
			}
			else {
				PrintDebug ( "VIDEO: [Bad] Hardware alpha blits aren't accelerated" );
			}
		}
		else {
			PrintDebug ( "VIDEO: [Bad] Hardware blitting cannot be done" );
			PrintDebug ( "VIDEO: [Good] Software blitting can be done" );
			if ( VideoInfo->blit_sw_CC ) {
				PrintDebug ( "VIDEO: [Good] Software color keys are accelerated" );
			}
			else {
				PrintDebug ( "VIDEO: [Bad] Software color keys aren't accelerated" );
			}
			if ( VideoInfo->blit_sw_A ) {
				PrintDebug ( "VIDEO: [Good] Software alpha blits are accelerated" );
			}
			else {
				PrintDebug ( "VIDEO: [Bad] Software alpha blits aren't accelerated" );
			}
		}

		if ( SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1 ) != 0 ) {
			PrintDebug ( "<ERROR> SetVideoMode() -> OpenGL cannot use double buffering!\nError string:\n\n%s",SDL_GetError() );
			return -1;
		}
		else {
			PrintDebug ( "VIDEO: [Good] OpenGL set to double buffering" );
		}

// TODO: Pass the "VIDEO: Checking mode %i x %i @ %i bpp",width,height,depth" to PrintDebug

		PrintDebug ( "VIDEO: Checking mode %ix%i@%i bpp",width,height,depth );
		bpp=SDL_VideoModeOK ( width, height, depth, VideoFlags );
		if ( !bpp ) {
			PrintDebug ( "VIDEO: <ERROR> Unable to use video mode %ix%i@%i bpp",width,height,depth );
			return -1;
		}
		else {
			Screen = SDL_SetVideoMode ( width, height, depth, VideoFlags );
			if ( !Screen ) {
				PrintDebug ( "<ERROR> SetVideoMode -> Surface not available. Video mode set failed.\nError string:\n\n%s",SDL_GetError() );
				return -1;
			}
			else {
				PrintDebug ( "VIDEO: Using video mode %ix%i@%i bpp",width,height,depth );
				return 1;
			}
		}
	}

	// ==============================================================================
	// Resizes the current window
	// ==============================================================================
	void ResizeWindow ( bool Auto, int NewWidth, int NewHeight, bool stretch ) {
		if ( Auto == true ) {
			NewWidth = Event.resize.w;
			NewHeight = Event.resize.h;
		}
		// GLfloat ratio;
		if ( NewWidth <= 0 ) { NewWidth = 1; }
		if ( NewHeight <= 0 ) { NewHeight = 1; }

		SCREEN_WIDTH = NewWidth;
		SCREEN_HEIGHT = NewHeight;
		if ( stretch == false ) { // If we're not stretching the display, then let's add
			VIEWPORT_WIDTH = NewWidth;// more screen space by increasing the OpenGL viewport.
			VIEWPORT_HEIGHT = NewHeight;
		}

		Screen = SDL_SetVideoMode ( NewWidth, NewHeight, SCREEN_DEPTH, VideoFlags );
		if ( !Screen ) {
			PrintDebug ( "OPENGL: <ERROR> ResizeWindow() -> Could not get a surface after resize.\nError string:\n\n%s",SDL_GetError() );
		}

		glViewport ( 0, 0, ( GLsizei ) NewWidth, ( GLsizei ) NewHeight );
	}

	// ==============================================================================
	// Clears the screen
	// ==============================================================================
	void Cls() {
		glClearColor ( bg[0],bg[1],bg[2],bg[3] );
		glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

	// ==============================================================================
	// Flips the buffers
	// ==============================================================================
	void Sync() {
		glFlush();
		SDL_GL_SwapBuffers();
		if ( Globals.FPS_rate != 0 ) { FPSDelay(); }
	}

	// ==============================================================================
	// Shows the FPS on the window's titlebar
	// ==============================================================================
	void ShowFPS() {
		static float fps           = 0.0f;
		static float previousTime  = 0.0f;
		static char  strFPS[20]    = {0};
		float currentTime = ( SDL_GetTicks() * 0.001f );
		++fps;
		if ( currentTime - previousTime > 1.0f ) {
			previousTime = currentTime;
			sprintf ( strFPS, "FPS: %i", int ( fps ) );
			SDL_WM_SetCaption ( strFPS,strFPS );
			Globals.FPS = int ( fps );
			fps = 0.0f;
		}
	}

	// ==============================================================================
	// Changes the background color used to clear the screen
	// ==============================================================================
	void SetBackgroundColor ( float red, float blue, float green, float alpha ) {
		bg[0] = red;	bg[1] = blue; bg[2] = green; bg[3] = alpha;
	}

	void ToggleFullscreen() { SDL_WM_ToggleFullScreen ( Screen );	}// Toggles fullscreen
	void EnableCulling() { glEnable ( GL_CULL_FACE ); }// Enables culling
	void DisableCulling() { glDisable ( GL_CULL_FACE ); }// Disables culling
	void SwapCullingMode ( int type ) { glFrontFace ( type ); }// Changes the culling mode
	void EnableLighting() { glEnable ( GL_LIGHTING ); }// Enables lighting
	void DisableLighting() { glDisable ( GL_LIGHTING ); }// Disables lighting
	void EnableTexturing() { glEnable ( GL_TEXTURE_2D ); }// Enables texturing
	void DisableTexturing() { glDisable ( GL_TEXTURE_2D ); }// Disables texturing
	void EnableDepth() { glEnable ( GL_DEPTH_TEST ); }// Enables the depth pass
	void DisableDepth() { glDisable ( GL_DEPTH_TEST ); }// Disables the depth pass

	// ==============================================================================
	// Rotates the texture matrix
	// ==============================================================================
	void RotateTextureMatrix ( float angle ) {
		glMatrixMode ( GL_TEXTURE );
		glRotatef ( angle,0.0f,0.0f,1.0f );
		glScalef ( -1.0f,1.0f,1.0f );
	}

	// ==============================================================================
	// Gets the SDL events
	// ==============================================================================
	//modified by KIAaze
	//Now returns value of SDL_PollEvent
	int CatchEvents() {
		return ( SDL_PollEvent ( &Event ) );
	}
	SDL_Event getEvent() {return ( Event );}

	//-----------------------------

	// ==============================================================================
	// Gets the pressed key
	// ==============================================================================
	int KeyPressed ( int Key ) {
		Keystate = SDL_GetKeyState ( NULL );
		if ( Keystate[Key] ) { return ( 1 ); }
		else { return ( 0 ); }
	}

	//Added by KIAaze
	// ==============================================================================
	// Returns true if Key is pressed down
	// ==============================================================================
	int KeyDown ( int Key ) {
		if ( Event.type==SDL_KEYDOWN )
			if ( Event.key.keysym.sym==Key ) { return ( 1 ); }
			else { return ( 0 ); }
		else
			return ( 0 );
	}

	// ==============================================================================
	// Returns true if Key is released
	// ==============================================================================
	int KeyUp ( int Key ) {
		if ( Event.type==SDL_KEYUP )
			if ( Event.key.keysym.sym==Key ) { return ( 1 ); }
			else { return ( 0 ); }
		else
			return ( 0 );
	}

	// ==============================================================================
	// Returns true on Close event
	// ==============================================================================
	int Close_Event ( void ) {
		if ( Event.type==SDL_QUIT )
			return ( 1 );
		else
			return ( 0 );
	}

	// ==============================================================================
	// Returns 1 on mouse moved, 0 otherwise.
	// ==============================================================================
	int MouseMoved	( int& iButton,
	                 int& iX,
	                 int& iY,
	                 int& iRelX,
	                 int& iRelY ) {
		if ( Event.type==SDL_MOUSEMOTION ) {
			iButton=Event.button.button;
			iX=Event.motion.x;
			iY=Event.motion.y;
			iRelX=Event.motion.xrel;
			iRelY=Event.motion.yrel;
			return ( 1 );
		}
		else
			return ( 0 );
	}

	// ==============================================================================
	// Returns iButton on mouse button up
	// ==============================================================================
	int MouseButtonUp	( int& iButton,
	                    int& iX,
	                    int& iY,
	                    int& iRelX,
	                    int& iRelY ) {
		if ( Event.type==SDL_MOUSEBUTTONUP ) {
			iButton=Event.button.button;
			iX=Event.motion.x;
			iY=Event.motion.y;
			iRelX=Event.motion.xrel;
			iRelY=Event.motion.yrel;
			return ( iButton );
		}
		else
			return ( 0 );
	}

	// ==============================================================================
	// Returns iButton on mouse button down
	// ==============================================================================
	int MouseButtonDown	( int& iButton,
	                      int& iX,
	                      int& iY,
	                      int& iRelX,
	                      int& iRelY ) {
		if ( Event.type==SDL_MOUSEBUTTONDOWN ) {
			iButton=Event.button.button;
			iX=Event.motion.x;
			iY=Event.motion.y;
			iRelX=Event.motion.xrel;
			iRelY=Event.motion.yrel;
			return ( iButton );
		}
		else
			return ( 0 );
	}

	// ==============================================================================
	// Returns true if window is minimized.
	// If window is active, it calls WindowActive and sets m_bMinimized to false.
	// If window is inactive, it calls WindowInactive and sets m_bMinimized to true.
	// ==============================================================================
	bool CheckWindowState() {
		if ( Event.type==SDL_ACTIVEEVENT ) {
			if ( Event.active.state & SDL_APPACTIVE ) {
				if ( Event.active.gain ) {
					m_bMinimized = false;
					WindowActive();
				}
				else {
					m_bMinimized = true;
					WindowInactive();
				}
			}
		}
		return ( m_bMinimized );
	}

	/** Window is active again. **/
	void WindowActive	() {
		PrintDebug ( "WindowActive\n" );
	}

	/** Window is inactive. **/
	void WindowInactive	() {
		PrintDebug ( "WindowInactive\n" );
	}
	//----------------------------------------------

	//The big two
	//default constructor
	Texture::Texture() {
		PrintDebug ( "Texture: default constructor called" );
		id=0;
		width=0.0;
		height=0.0;
		imgF = NULL;
		strcpy ( TextureName,"" );
	}
	//special constructor
	Texture::Texture ( const char filename[] ) {
		PrintDebug ( "Texture: special constructor called" );
		id=0;
		width=0.0;
		height=0.0;
		imgF = NULL;
		strcpy ( TextureName,filename );
		this->Load ( filename );
	}

	//The big three
	//copy constructor
	Texture::Texture ( const Texture& t ) {
		PrintDebug ( "Texture: copy constructor called" );
		strcpy ( TextureName,t.TextureName );
		this->Modify ( t.imgF );
		/*		id=t.id;
				width=t.id;
				height=t.id;
				imgF = SDL_DisplayFormatAlpha(t.imgF);*/
	}
	//assignment operator
	Texture& Texture::operator= ( const Texture& t ) {
		PrintDebug ( "[Texture::operator=]Texture: assignment operator called" );
		PrintDebug ( "TextureName=%s",TextureName );
		if ( this != &t ) {
			// first delete old
			//============================
			if ( imgF ) {
				PrintDebug ( "[Texture::operator=]WARNING: imgF is NOT NULL=>deleting" );
				SDL_FreeSurface ( imgF );
			}
			else {
				PrintDebug ( "[Texture::operator=]WARNING: imgF is NULL" );
			}
			if ( glIsTexture ( id ) ) {
				PrintDebug ( "[Texture::operator=]WARNING: id is a texture=>deleting %s ",TextureName );
				glDeleteTextures ( 1, &id );
			}
			else {
				PrintDebug ( "[Texture::operator=]WARNING: id is NOT a texture" );
			}
			//============================
			//then copy
			strcpy ( TextureName,t.TextureName );
			this->Modify ( t.imgF );
			/*			id=t.id;
						width=t.id;
						height=t.id;
						imgF = SDL_DisplayFormatAlpha(t.imgF);*/
		}
		return ( *this );
	}
	//destructor
	Texture::~Texture() {
		PrintDebug ( "[Texture::~Texture]Texture: destructor called for %s",TextureName );

		//============================
		if ( imgF ) {
			PrintDebug ( "[Texture::~Texture]WARNING: imgF is NOT NULL=>deleting" );
			SDL_FreeSurface ( imgF );
		}
		else {
			PrintDebug ( "[Texture::~Texture]WARNING: imgF is NULL" );
		}
		if ( glIsTexture ( id ) ) {
			PrintDebug ( "[Texture::~Texture]WARNING: id is a texture=>deleting %s ",TextureName );
			glDeleteTextures ( 1, &id );
		}
		else {
			PrintDebug ( "[Texture::~Texture]WARNING: id is NOT a texture" );
		}
		//============================

	}

	// ==============================================================================
	// Loads a texture
	// ==============================================================================

	void Texture::Load ( const char filename[] ) {
		strcpy ( TextureName, filename );
		PrintDebug ( "[Texture::Load] called" );
		//--------------------------------------------------
		//file->SDL_Surface
		if ( !FileExists ( filename ) ) { printf ( "[Texture::Load]FATAL ERROR: File not found\n" ); exit ( 27 ); }
		SDL_Surface * image2 = IMG_Load ( filename );
		// handle error
		if ( !image2 ) {
			PrintDebug ( "[Texture::Load]IMG_Load: %s\n", IMG_GetError() );
		}
		//--------------------------------------------------
		//copy SDL_Surface
		SDL_Surface * imgFile = SDL_DisplayFormatAlpha ( image2 );
		//--------------------------------------------------
		//free resources
		PrintDebug ( "[Texture::Load] freeing temp surface!!!!\n" );
		SDL_FreeSurface ( image2 );
		//--------------------------------------------------
		//resize
		GLint texSize;
		glGetIntegerv ( GL_MAX_TEXTURE_SIZE, &texSize );
		PrintDebug ( "[Texture::Load]texSize=%i; width=%i; height=%i;\n",texSize,imgFile->w,imgFile->h );
		imgFile=resize ( imgFile,texSize );
		//--------------------------------------------------
		//============================
		if ( glIsTexture ( id ) ) {
			printf ( "[Texture::Load]FATAL ERROR: id is a texture=>deleting\n" );
			exit ( 3 );
			glDeleteTextures ( 1, &id );
		}
		else {
			PrintDebug ( "[Texture::Load]WARNING: id is NOT a texture" );
		}
		//============================
		//--------------------------------------------------
		//ready texture for openGL
		GLuint texture;
		glGenTextures ( 1, &texture );
		glBindTexture ( GL_TEXTURE_2D, texture );
		id = texture;//id attribute

		if ( imgFile->format->BitsPerPixel == 32 || imgFile->format->BitsPerPixel == 24 )
			glTexImage2D ( GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgFile->pixels );
		else
			glTexImage2D ( GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgFile->pixels );

		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		//--------------------------------------------------
		//copy attributes
		id = texture;//id attribute
		imgF = imgFile;//imgF attribute
		width = imgFile->w;//width attribute
		height = imgFile->h;//height attribute
		//--------------------------------------------------
		//PrintDebug
		PrintDebug ( "[Texture::Load] %s loaded. Size=(%ix%i)",filename,imgFile->w,imgFile->h );
		//--------------------------------------------------
	}

	void Texture::Modify ( SDL_Surface *image2 ) {
		PrintDebug ( "[Texture::Modify] called" );
		if ( !image2 ) {
			printf ( "[Texture::Modify] FATAL ERROR: no SDL_Surface\n" );exit ( 81 );
		}
		//--------------------------------------------------
		//copy SDL_Surface
		SDL_Surface * imgFile = SDL_DisplayFormatAlpha ( image2 );
		//SDL_FreeSurface ( image2 );

		//--------------------------------------------------
		//resize
		GLint texSize;
		glGetIntegerv ( GL_MAX_TEXTURE_SIZE, &texSize );
		PrintDebug ( "[Texture::Modify]texSize=%i; width=%i; height=%i;\n",texSize,imgFile->w,imgFile->h );
		imgFile=resize ( imgFile,texSize );
		//--------------------------------------------------
		//============================
		if(glIsTexture(id))
		{
			PrintDebug("[Texture::Modify]WARNING: id is a texture=>deleting");
			//exit(-1);
			glDeleteTextures(1, &id);
		}
		else
		{
			PrintDebug("[Texture::Modify]WARNING: id is NOT a texture");
		}
		//============================
		//--------------------------------------------------
		//ready texture for openGL
		GLuint texture;
		glGenTextures ( 1, &texture );
		glBindTexture ( GL_TEXTURE_2D, texture );

		if ( imgFile->format->BitsPerPixel == 32 || imgFile->format->BitsPerPixel == 24 )
			glTexImage2D ( GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgFile->pixels );
		else
			glTexImage2D ( GL_TEXTURE_2D, 0, 4, imgFile->w, imgFile->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgFile->pixels );

		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		//--------------------------------------------------
		//copy attributes
		id = texture;//id attribute
		imgF = imgFile;//imgF attribute
		width = imgFile->w;//width attribute
		height = imgFile->h;//height attribute
		//--------------------------------------------------
		//PrintDebug
		PrintDebug ( "[Texture::Modify] Texture modified. Size=(%ix%i)",imgFile->w,imgFile->h );
		//--------------------------------------------------
	}

	void SetPointSize ( GLfloat newsize ) { glPointSize ( newsize ); }
	void EnableSmoothPoints() { glEnable ( GL_POINT_SMOOTH ); }
	void BeginPoints() { glBegin ( GL_POINTS ); }
	void EndPoints() { glEnd(); }
	void DrawPixel ( GLfloat x, GLfloat y ) { glVertex3f ( x, y, 0.0f ); }
	void SetColor3 ( GLfloat r, GLfloat g, GLfloat b ) { glColor3f ( r,g,b ); }

	void BeginLines() { glBegin ( GL_LINES ); }
	void EndLines() { glEnd(); }

	void DrawLine ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ) {
		glVertex3f ( x1,y1,0.0f );
		glVertex3f ( x2,y2,0.0f );
	}
	void DrawRectangle ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ) {
		DrawLine ( x1,y1,x2,y1 );
		DrawLine ( x1,y1,x1,y2 );
		DrawLine ( x1,y2,x2,y2 );
		DrawLine ( x2,y1,x2,y2 );
	}

	void DrawLine ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat r, GLfloat g, GLfloat b ) {
		gp2d::DisableTexturing();
		glDisable ( GL_BLEND );
		gp2d::BeginLines();
		SetColor3 ( r,g,b );
		gp2d::DrawLine ( x1,y1,x2,y2 );
		gp2d::EndLines();
		glEnable ( GL_BLEND );
		gp2d::EnableTexturing();
	}
	void DrawRectangle ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat r, GLfloat g, GLfloat b ) {
		gp2d::DisableTexturing();
		glDisable ( GL_BLEND );

		gp2d::BeginLines();
		SetColor3 ( r,g,b );
		gp2d::DrawRectangle ( x1,y1,x2,y2 );
		gp2d::EndLines();

		glEnable ( GL_BLEND );
		gp2d::EnableTexturing();
	}

	GLfloat CurveValueGLf ( GLfloat destination, GLfloat current, GLfloat steps ) {
		GLfloat returnvalue;
		returnvalue = ( destination-current ) /steps+current;
		return returnvalue;
	}

	/* returns pixel value at (x,y)

		Taken from the SDL Wiki.
	*/
	Uint32 GetPixel( SDL_Surface *surface, Uint32 x, Uint32 y ) {

		if ( x < 0 ) { PrintDebug ( "<ERROR> GetPixel -> X less than zero! (x<0)." ); }
		if ( y < 0 ) { PrintDebug ( "<ERROR> GetPixel -> Y less than zero! (y<0)." ); }
		if ( x > ( Uint32 ) surface->w ) { PrintDebug ( "<ERROR> GetPixel -> X greather than surface's width! (x>surface->w)." ); }
		if ( y > ( Uint32 ) surface->h ) { PrintDebug ( "<ERROR> GetPixel -> Y greather than surface's height! (y>surface->h)." ); }

		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to retrieve */
		Uint8 *p = ( Uint8 * ) surface->pixels + y * surface->pitch + x * bpp;
		switch ( bpp ) {
			case 1:
				return *p;
			case 2:
				return * ( Uint16 * ) p;
			case 3:
				if ( SDL_BYTEORDER == SDL_BIG_ENDIAN )
					return p[0] << 16 | p[1] << 8 | p[2];
				else
					return p[0] | p[1] << 8 | p[2] << 16;
			case 4:
				return * ( Uint32 * ) p;
			default:
				return 0;       /* shouldn't happen, but avoids warnings */
		}
	}

	bool SetPixelAlpha ( SDL_Surface *surface, Uint32 x, Uint32 y ) {

		if ( x < 0 ) { PrintDebug ( "<ERROR> SetPixelAlpha -> X less than zero! (x<0)." );exit ( 47 ); }
		if ( y < 0 ) { PrintDebug ( "<ERROR> SetPixelAlpha -> Y less than zero! (y<0)." );exit ( 47 ); }
		if ( x > ( Uint32 ) surface->w ) { PrintDebug ( "<ERROR> SetPixelAlpha -> X greather than surface's width! (x>surface->w)." );exit ( 47 ); }
		if ( y > ( Uint32 ) surface->h ) { PrintDebug ( "<ERROR> SetPixelAlpha -> Y greather than surface's height! (y>surface->h)." );exit ( 47 ); }

		// Uint8	pr, pg, pb, pa;
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to retrieve */
		Uint8 *p = ( Uint8 * ) surface->pixels + y * surface->pitch + x * bpp;
		switch ( bpp ) {
			case 1:
				return false;
			case 2:
				return false;
			case 3:
				return false;
			case 4:
				* ( ( Uint32* ) p ) = 0x00FFFFFF;// Red=0x00, Green=0x00, Blue=0x00, Alpha=0x00
				return true;
			default:
				return false;       /* shouldn't happen, but avoids warnings */
		}
	}

//----------------------
//added by KIAaze
	bool SetPixelColor( SDL_Surface* surf, Uint32 x, Uint32 y, Uint32 color, bool add )
	{
		//make sure we are inside the surface
		if ( x < 0 ||  y < 0 || x > ( Uint32 ) surf->w || y > ( Uint32 ) surf->h ) return(false);

		if(add)
		{
			pixelColor(surf,x,y,color);
			return(true);
		}
		else
		{
			int bpp = surf->format->BytesPerPixel;
			/* Here p is the address to the pixel we want to retrieve */
			Uint8 *p = ( Uint8 * ) surf->pixels + y * surf->pitch + x * bpp;
			switch ( bpp ) {
				case 1:
					return false;
				case 2:
					return false;
				case 3:
					return false;
				case 4:
					* ( ( Uint32* ) p ) =     SDL_MapRGBA(surf->format,(color & 0xFF000000)>>24,(color & 0x00FF0000)>>16,(color & 0x0000FF00)>>8,(color & 0x000000FF));;
					return true;
				default:
					return false;
			}
		}
	}

	bool SetPixelRGBA( SDL_Surface* surf, Uint32 x, Uint32 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool add )
	{
		return(SetPixelColor( surf, x, y, ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a, add));
	}

	bool GetPixelColor( SDL_Surface* surf, Uint32 x, Uint32 y, Uint32 &color )
	{
		//make sure we are inside the surface
		if ( x < 0 ||  y < 0 || x > ( Uint32 ) surf->w || y > ( Uint32 ) surf->h ) return(false);

		Uint8 r,g,b,a;
		SDL_GetRGBA(GetPixel(surf,x,y),surf->format,&r,&g,&b,&a);
		color= ((Uint32) r << 24) | ((Uint32) g << 16) | ((Uint32) b << 8) | (Uint32) a;
		return(true);
	}

	bool GetPixelRGBA( SDL_Surface* surf, Uint32 x, Uint32 y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a )
	{
		//make sure we are inside the surface
		if ( x < 0 ||  y < 0 || x > ( Uint32 ) surf->w || y > ( Uint32 ) surf->h ) return(false);

		SDL_GetRGBA(GetPixel(surf,x,y),surf->format,&r,&g,&b,&a);
		//if(a>0) exit(102);
		return(true);
	}
//----------------------

	bool FileExists ( const char filename[] ) {
		// check if the file exists
		// there may very well be a better way to do this
		// but this works crossplatform, I believe
		// added by compwiz
		std::ifstream input;
		input.open ( filename, std::ifstream::in );
		input.close();
		if ( input.fail() ) {
			PrintDebug ( "File %s does not exist.",filename );
			return false;
		}
		return true;
	}

	int iRand ( int from, int to ) { return rand() %to+from; }

	void ShowCursor() { SDL_ShowCursor ( SDL_ENABLE ); }
	void HideCursor() { SDL_ShowCursor ( SDL_DISABLE ); }

	int closest_power_of_two ( double x ) {
		return ( 1 << ( int ) floor ( ( log ( ( double ) x ) /log ( 2.0f ) ) + 0.5f ) );
	}

	double scale_factor ( int texSize, int x_current ) {
		int x_wanted=closest_power_of_two ( x_current );
		if ( x_wanted > texSize ) x_wanted = texSize;
		double ret = x_wanted/ ( double ) x_current;
		return ( ret );
	}

	SDL_Surface* resize ( SDL_Surface* image, int texSize ) {
		SDL_Surface* ret;
		double sf_h=scale_factor ( texSize,image->h );
		double sf_w=scale_factor ( texSize,image->w );

		if ( sf_h!=1 || sf_w!=1 ) {
			PrintDebug ( "[resize] <WARNING> Texture size is maximum than the allowed by the video card (%ix%i). Resizing to (%fx%f)",texSize,texSize,sf_w*image->w,sf_h*image->h );
			ret = zoomSurface ( image,sf_w,sf_h,SMOOTHING_ON );
			return ( ret );
		}
		else return ( image );
	}

	bool SDL_OGL_SaveScreenshot(const char *FileName)
	{
	
		int N=4;
	
	// Create two arrays of unsigned bytes (chars). 4 bytes per pixel (RGBA)
	unsigned char *pixels = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT * N];
	unsigned char *pixelsbuf = new unsigned char[SCREEN_WIDTH * SCREEN_HEIGHT * N];
	
		//SDL_GL_SwapBuffers();

		// Read the front buffer
		glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, /*GL_BGRA*/ GL_RGBA, GL_UNSIGNED_BYTE, pixelsbuf);
	
	// Copy lines of pixels from pixelsbuf to pixels, flipping the image at the same time.
	for(int i=0; i < SCREEN_HEIGHT; ++i)
		memcpy(pixels+(SCREEN_HEIGHT-i-1)*SCREEN_WIDTH*N, pixelsbuf+i*SCREEN_WIDTH*N, SCREEN_WIDTH*N);
	
		Screen->pixels = pixels;
		SDL_SaveBMP(Screen, FileName);
	// 	SDL_FreeSurface(screen);
	// 	screen = 0;
	
		delete pixels;
		delete pixelsbuf;
	
		pixels = 0;
		pixelsbuf = 0;
		printf("screenshot taken\n");
		return true;
	}

}
