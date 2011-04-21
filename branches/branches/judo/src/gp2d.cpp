/*****
 *
 *  GamePower 3D (GP3D) and GamePower 2D (GP2D) are a portable OpenGL/SDL 
 *  wrapper using C/C++ designedspecifically for professional game making
 *  in various platforms such as Windows, Linux and Macintosh by
 *  exploiting the portable capabilities of OpenGL and SDL.
 *  Copyright (C) 2007 Gamepower development team
 *
 *  This file is part of GamePower.
 *
 *  GamePower is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  GamePower is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GamePower.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****/
 
#include "gp2d.h"

namespace gp2d {

    bool  g_DebugMode;                   // Debug mode:
                                         // 0 = No debug
                                         // 1 = Simple
                                         // 2 = Verbose
                                         // 3 = Full

    Uint32 g_VideoAPI;                   // Video API to use (SDL or OpenGL)
                                          
    int   g_FPSframes;                   // ··.
    int   g_FPSrate;                     //   |
    int   g_FPSoldticks;                 //   |
    int   g_FPSmax;                      //   |\ FPS
    int   g_FPSmin;                      //   |/ Info
    int   g_FPSfixed;                    //   |
    float g_FPSticks;                    //   |
    int   g_FPS;                         // ··'

    std::string g_DataDir;               // GP2D File operations working path
    bool g_AbsolutePaths = true;         // Should GP2D use absolute paths? (true by default)

    int g_ScreenWidth;                   // Screen width
    int g_ScreenHeight;                  // Screen height
    int g_ScreenDepth;                   // Screen depth
    int g_ViewportWidth;                 // OpenGL viewport width
    int g_ViewportHeight;                // OpenGL viewport height

    float g_BackgroundColor[3];          // Background color.

    SDL_Surface *g_SDLScreen;            // SDL Screen surface.
    Uint32 g_SDLVideoFlags;              // SDL Video flags.
    const SDL_VideoInfo *g_SDLVideoInfo; // SDL Video information structure.

    bool g_WindowMinimized = false;      // Is the window minimized?
    bool g_Fullscreen = false;           // Are we in fullscreen mode? (false by default)

    SDL_Event g_SDLEvent;                // SDL Event
    Uint8 *g_InputKeystate;              // SDL Keyboard state
	
    // *************************************************************************
    // Core/Main functions go here.
    // *************************************************************************
    //
    // This means functions for handling random numbers, resizing the game 
    // window, initialization functions and so on.
    // 
    // *************************************************************************

        // =========================================================================
        // Function:   RandomSeed
        // Author:     DARKGuy
        // Parameters: None
        // Returns:    None
        // =========================================================================
        // Description:
        //   Generates a random seed.
        // =========================================================================
        void randomSeed(){
            srand((unsigned)time(0));
        }

        // =========================================================================
        // Function:   EventResizeWindow
        // Author:     KIAaze
        // Parameters: None
        // Returns:    Boolean
        // =========================================================================
        // TODO: This should be changed to an event itself, not a function. Find a
        // way to make GP2D use/handle events as events, not as functions :p
        //
        // Description:
        //   Tells if the user wants to resize the window by grabbing a
        // SDL_VIDEORESIZE event from SDL.
        // =========================================================================
        int eventResizeWindow() {
            if(g_SDLEvent.type == SDL_VIDEORESIZE){ return true; } else { return false; }
            return true; // suppresses a warning
        }

        // =========================================================================
        // Function:   setDebug
        // Author:     DARKGuy
        // Parameters: Debug mode - Boolean
        // Returns:    None
        // =========================================================================
        // Description:
        //   Enables/disables debug mode
        // =========================================================================
        void setDebug(bool value){
            g_DebugMode = value;
        }

        // =========================================================================
        // Function:   printDebug
        // Author:     DARKGuy
        // Parameters: Text & parameters, printf()-style - const char*
        // Returns:    None
        // =========================================================================
        // Description:
        //   Prints some debug information with [GamePower] before it.
        // =========================================================================
        void printDebug(const char *fmt...){
		    if(g_DebugMode == true){
    			char		text[256];			    // Holds Our String
    			va_list		ap;						// Pointer To List Of Arguments
    			va_start(ap, fmt);				    // Parses The String For Variables
    				vsprintf(text, fmt, ap);	    // And Converts Symbols To Actual Numbers
    			va_end(ap);							// Results Are Stored In Text
    			printf("[GamePower] %s\n",text);    // Print our debug text
    		}
	    }

        // =========================================================================
        // Function:   setVideoFlags
        // Author:     DARKGuy
        // Parameters: Video Flags - Uint32
        // Returns:    None
        // =========================================================================
        // Description:
        //   Sets the video flags going to be used for SDL_SetVideoMode
        // =========================================================================
        void setVideoFlags(Uint32 flags){
            if(flags==0){                                   // If no flags are specified...
                if(g_VideoAPI == GP2D_SDL)   { g_SDLVideoFlags = GP2D_DEFAULT_VIDEO_FLAGS; }
                if(g_VideoAPI == GP2D_OPENGL){ g_SDLVideoFlags = GP2D_DEFAULT_VIDEO_FLAGS | SDL_OPENGL; }
                flags = g_SDLVideoFlags;
            } else {                                        // Else...
                if(g_VideoAPI == GP2D_SDL)   { g_SDLVideoFlags = flags; }
                if(g_VideoAPI == GP2D_OPENGL){ g_SDLVideoFlags = flags | SDL_OPENGL; }                
            }                                               // EndSDL_WM_ToggleFullScreen

            // This bit is self-explanatory
		    if(g_DebugMode == true){
		        printDebug("App is setting the SDL Video flags to:");
                if(checkFlag(flags,GP2D_DEFAULT_VIDEO_FLAGS)){ printDebug("=> DEFAULT SETTING      (GP2D_DEFAULT_VIDEO_FLAGS)"); }
                if(checkFlag(flags,GP2D_SWMODE)){              printDebug("* Software mode         (GP2D_SWMODE)"); }
                if(checkFlag(flags,GP2D_HWMODE)){              printDebug("* Hardware mode         (GP2D_HWMODE)"); }
                if(checkFlag(flags,GP2D_ANYMODE)){             printDebug("* Any video mode        (GP2D_ANYMODE)"); }
                if(checkFlag(flags,GP2D_DOUBLEBUF)){           printDebug("* Double Buffering      (GP2D_DOUBLEBUF)"); }
                if(checkFlag(flags,GP2D_ASYNCBLIT)){           printDebug("* Asynchronous Blitting (GP2D_ASYNCBLIT)"); }
                if(checkFlag(flags,GP2D_FULLSCREEN)){          printDebug("* Fullscreen            (GP2D_FULLSCREEN)"); }
                if(checkFlag(flags,GP2D_HWPALETTE)){           printDebug("* Hardware palette      (GP2D_HWPALETTE)"); }
                if(checkFlag(flags,GP2D_RESIZABLE)){           printDebug("* Resizable window      (GP2D_RESIZABLE)"); }
                if(checkFlag(flags,GP2D_NOFRAME)){             printDebug("* Remove window frames  (GP2D_NOFRAME)"); }                
                if(checkFlag(flags,SDL_OPENGL)){               printDebug("* OpenGL API            (SDL_OPENGL)"); }                
    		}
	    }
	    
        // =========================================================================
        // Function:   checkFlag
        // Author:     DARKGuy
        // Parameters: Flags to check in - Uint32
        //             Flag to check for - Uint32
        // Returns:    Boolean
        // =========================================================================
        // Description:
        //   Checks whether a flag exists inside a flag set
        // =========================================================================
        bool checkFlag(Uint32 flagToCheck, Uint32 flag){
            if (flagToCheck & flag){    // If flag is inside flagToCheck
                return true;            //   It does!
    		} else {                    // Else
                return false;           //   It doesn't
            }                           // End
	    }
	    
        // =========================================================================
        // Function:   setGLAttribute
        // Author:     DARKGuy
        // Parameters: Attribute - Uint32
        // Returns:    None
        // =========================================================================
        // Description:
        //   Sets the OpenGL Attribute going to be used for SDL_SetVideoMode
        // =========================================================================
        void setGLAttribute(SDL_GLattr attrib, int value){        
            // This bit is self-explanatory
		    if(g_DebugMode == true){
		        std::string att;
		        if(attrib==SDL_GL_RED_SIZE){           att="SDL_GL_RED_SIZE"; }
		        if(attrib==SDL_GL_GREEN_SIZE){         att="SDL_GL_GREEN_SIZE"; }
		        if(attrib==SDL_GL_BLUE_SIZE){          att="SDL_GL_BLUE_SIZE"; }
		        if(attrib==SDL_GL_ALPHA_SIZE){         att="SDL_GL_ALPHA_SIZE"; }
		        if(attrib==SDL_GL_BUFFER_SIZE){        att="SDL_GL_BUFFER_SIZE"; }
		        if(attrib==SDL_GL_DOUBLEBUFFER){       att="SDL_GL_DOUBLEBUFFER"; }
		        if(attrib==SDL_GL_DEPTH_SIZE){         att="SDL_GL_DEPTH_SIZE"; }
		        if(attrib==SDL_GL_STENCIL_SIZE){       att="SDL_GL_STENCIL_SIZE"; }
		        if(attrib==SDL_GL_ACCUM_RED_SIZE){     att="SDL_GL_ACCUM_RED_SIZE"; }
		        if(attrib==SDL_GL_ACCUM_GREEN_SIZE){   att="SDL_GL_ACCUM_GREEN_SIZE"; }
		        if(attrib==SDL_GL_ACCUM_BLUE_SIZE){    att="SDL_GL_ACCUM_BLUE_SIZE"; }
		        if(attrib==SDL_GL_ACCUM_ALPHA_SIZE){   att="SDL_GL_ACCUM_ALPHA_SIZE"; }
		        if(attrib==SDL_GL_STEREO){             att="SDL_GL_STEREO"; }
		        if(attrib==SDL_GL_MULTISAMPLEBUFFERS){ att="SDL_GL_MULTISAMPLEBUFFERS"; }
		        if(attrib==SDL_GL_MULTISAMPLESAMPLES){ att="SDL_GL_MULTISAMPLESAMPLES"; }
		        if(attrib==SDL_GL_SWAP_CONTROL){       att="SDL_GL_SWAP_CONTROL"; }
                printDebug("App is setting an OpenGL attribute: %s = %i",att.c_str(),value);
    		}
    		// Set the SDL OpenGL attribute and its specified value
            SDL_GL_SetAttribute(attrib,value);            
	    }

        // =========================================================================
        // Function:   init
        // Author:     DARKGuy
        // Parameters: None
        // Returns:    Boolean
        // =========================================================================
        // Description:
        //   Initializes SDL and everything that's needed in order to work correctly
        // =========================================================================
        int init(){
            if(SDL_Init(SDL_INIT_EVERYTHING) != 0){ // If SDL fails to initialize...
                if(g_DebugMode==true){              // And we're in debug mode in order to inform the user
                    printDebug("ERROR: Error in SDL_Init(SDL_INIT_EVERYTHING).\nError string:\n%s",SDL_GetError());
                }
            } else { // SDL initialized! :D
                printDebug("SDL Initialized");
                g_SDLVideoInfo = SDL_GetVideoInfo(); // Get info about the video modes available
                if (!g_SDLVideoInfo){ // If we can't get the list of video modes available...
                    if(g_DebugMode==true){ // And we are in debug mode in order to inform the user
                        printDebug("ERROR: Error in SDL_GetVideoInfo().\nError string:\n%s",SDL_GetError());
                    }
                    return -1; // FALSE: Cannot init because we couldn't get info about the video modes available
                } else {
                    return 1; // TRUE: We could initialize SDL and get info about the video modes available
                }
            }
            return -1; // Return false by default (it'll never happen anyways, duh)
        }

        // =========================================================================
        // Function:   setVideoAPI
        // Author:     DARKGuy
        // Parameters: API to use - Uint32 (flag)
        // Returns:    None
        // =========================================================================
        // Description:
        //   Sets the video API to use (SDL or OpenGL)
        // =========================================================================
        void setVideoAPI(Uint32 API){
            // This bit is self-explanatory
		    if(g_DebugMode == true){
		        std::string att;
		        if(API==GP2D_SDL){    att="SDL (pure 2D)"; }
		        if(API==GP2D_OPENGL){ att="OpenGL (hardware-accelerated 2D)"; }
                printDebug("Setting video API to : %s",att.c_str());
    		}
    		// Set the video API to specified
            g_VideoAPI = API;
	    }

        // =========================================================================
        // Function:   setVideoMode
        // Author:     DARKGuy
        // Parameters: Screen/Window width in pixels  - int
        //             Screen/Window height in pixels - int
        //             Bits-per-pixel (bpp)           - int
        // Returns:    Boolean
        // =========================================================================
        // Description:
        //   Initializes a window with the flags specified previously by the user
        // =========================================================================
        bool setVideoMode(int width, int height, int bpp){
            int tmp;
            if(g_DebugMode==true){
                printDebug("Checking video mode \"%ix%i@%i\" ...",width,height,bpp);
            }
            tmp=SDL_VideoModeOK(width, height, bpp, g_SDLVideoFlags);
            if(!tmp){
                if(g_DebugMode==true){
                    printDebug("ERROR: Video mode \"%ix%i@%i\" not available!",width,height,bpp);
                }
                return false;
            } else {
                if(g_DebugMode==true){
                    printDebug("Closest bpp available to the chosen one (%i): %i",bpp,tmp);
                    printDebug("=> Video mode check OK");
                    printDebug("Using video mode \"%ix%i@%i\"",width,height,tmp);
                }
                g_SDLScreen    = SDL_SetVideoMode(width, height, tmp, g_SDLVideoFlags);
                if(g_DebugMode==true){
                    printDebug("Getting current video information...");
                }
                g_SDLVideoInfo = SDL_GetVideoInfo();
                if(g_DebugMode==true){
                    printDebug("=> OK");
                }
                if(g_DebugMode==true){
                    std::string answer;
                    printDebug("============================================================");
                    printDebug("Video information");
                    printDebug("============================================================");
                    printDebug("Amount of video memory (in Kilobytes): %i",g_SDLVideoInfo->video_mem);

                    if(g_SDLVideoInfo->wm_available){ answer="Yes"; } else { answer="No"; }
                        printDebug("Is there a window manager available? %s (%i)",answer.c_str(),g_SDLVideoInfo->wm_available);
                        printDebug("");
                    if(g_SDLVideoInfo->hw_available){ answer="Yes"; } else { answer="No"; }
                        printDebug("Is it possible to create hardware surfaces?          %s (%i)",answer.c_str(),g_SDLVideoInfo->hw_available);
                    if(g_SDLVideoInfo->blit_hw){ answer="Yes"; } else { answer="No"; }
                        printDebug("Are hardware to hardware blits accelerated?          %s (%i)",answer.c_str(),g_SDLVideoInfo->blit_hw);
                    if(g_SDLVideoInfo->blit_hw_CC){ answer="Yes"; } else { answer="No"; }
                        printDebug("Are hardware to hardware colorkey blits accelerated? %s (%i)",answer.c_str(),g_SDLVideoInfo->blit_hw_CC);
                    if(g_SDLVideoInfo->blit_hw_A){ answer="Yes"; } else { answer="No"; }
                        printDebug("Are hardware to hardware alpha blits accelerated?    %s (%i)",answer.c_str(),g_SDLVideoInfo->blit_hw_A);
                    if(g_SDLVideoInfo->blit_sw){ answer="Yes"; } else { answer="No"; }
                        printDebug("Are software to hardware blits accelerated?          %s (%i)",answer.c_str(),g_SDLVideoInfo->blit_sw);
                    if(g_SDLVideoInfo->blit_sw_CC){ answer="Yes"; } else { answer="No"; }
                        printDebug("Are software to hardware colorkey blits accelerated? %s (%i)",answer.c_str(),g_SDLVideoInfo->blit_sw_CC);
                    if(g_SDLVideoInfo->blit_sw_A){ answer="Yes"; } else { answer="No"; }
                        printDebug("Are software to hardware alpha blits accelerated?    %s (%i)",answer.c_str(),g_SDLVideoInfo->blit_sw_A);
                    if(g_SDLVideoInfo->blit_fill){ answer="Yes"; } else { answer="No"; }
                        printDebug("Are color fills accelerated?                         %s (%i)",answer.c_str(),g_SDLVideoInfo->blit_fill);
                        printDebug("");
                        printDebug("Pixel format information:");
                        // TODO: Is <=8 safe, or is it better <8 ?
                        if(g_SDLVideoInfo->vfmt->BitsPerPixel<=8){
                            printDebug("  Palette number of colours: %i",g_SDLVideoInfo->vfmt->palette->ncolors);
                        } else {
                            printDebug("  Palette: True color");
                        }
                        printDebug("  Bits-per-pixel (BPP): %u",g_SDLVideoInfo->vfmt->BitsPerPixel);
                        printDebug("  Bytes-per-pixel: %u",g_SDLVideoInfo->vfmt->BytesPerPixel);
                        printDebug("  Precision loss of each color component (2*RGBA) (loss):");
                        printDebug("    Red:   %u",g_SDLVideoInfo->vfmt->Rloss);
                        printDebug("    Green: %u",g_SDLVideoInfo->vfmt->Gloss);
                        printDebug("    Blue:  %u",g_SDLVideoInfo->vfmt->Bloss);
                        printDebug("    Alpha: %u",g_SDLVideoInfo->vfmt->Aloss);
                        printDebug("  Binary left shift of each color component in the pixel value (shift):");
                        printDebug("    Red:   %u",g_SDLVideoInfo->vfmt->Rshift);
                        printDebug("    Green: %u",g_SDLVideoInfo->vfmt->Gshift);
                        printDebug("    Blue:  %u",g_SDLVideoInfo->vfmt->Bshift);
                        printDebug("    Alpha: %u",g_SDLVideoInfo->vfmt->Ashift);
                        printDebug("  Binary mask used to retrieve individual color values (mask):");
                        printDebug("    Red:   %u",g_SDLVideoInfo->vfmt->Rmask);
                        printDebug("    Green: %u",g_SDLVideoInfo->vfmt->Gmask);
                        printDebug("    Blue:  %u",g_SDLVideoInfo->vfmt->Bmask);
                        printDebug("    Alpha: %u",g_SDLVideoInfo->vfmt->Amask);
                        printDebug("  Pixel value of transparent pixels: %u",g_SDLVideoInfo->vfmt->colorkey);
                        printDebug("  Overall surface alpha value:       %u",g_SDLVideoInfo->vfmt->alpha);
                    printDebug("============================================================");
                }

                if(checkFlag(g_SDLVideoFlags,GP2D_FULLSCREEN)){ g_Fullscreen = true; }

                return true;
            }
            return false;
        }
        
        // =========================================================================
        // Function:   sync
        // Author:     DARKGuy
        // Parameters: None
        // Returns:    Boolean
        // =========================================================================
        // Description:
        //   Flips the video buffers
        // =========================================================================
        bool sync(){
            if(g_VideoAPI==GP2D_SDL){
                if(SDL_Flip(g_SDLScreen)){
                    return true;
                } else {
                    return false;
                }
            } else {
                SDL_GL_SwapBuffers();
                return true;
            }
        }

        // =========================================================================
        // Function:   loadImage
        // Author:     DARKGuy
        // Parameters: Image to load - const char[]
        // Returns:    SDL_Surface
        // =========================================================================
        // Description:
        //   Loads an image as a SDL_Surface
        // =========================================================================
        SDL_Surface* loadImage(const char filename[]){
            std::string tmp;
            SDL_Surface *null = NULL;

            tmp = g_DataDir + filename;
            if(!fileExists(tmp.c_str())){ return null; }

            SDL_Surface *image = SDL_DisplayFormatAlpha(IMG_Load(tmp.c_str()));

            if(!image) {
                printDebug("ERROR: Cannot load image \"%s\"",filename);
                printDebug("       Reason: \"%s\"",IMG_GetError());
            } else {
                printDebug("Image \"%s\" loaded.",filename);
                return image;
            }
            return null;
        }

        // =========================================================================
        // Function:   fileExists
        // Author:     compwiz
        // Parameters: Filename to check - const char[]
        // Returns:    Boolean
        // =========================================================================
        // Description:
        //   Check if the file exists. There may very well be a better way to do
        //   this but this works crossplatform, I believe.
        // =========================================================================
        bool fileExists(const char filename[]){
            std::ifstream input;
            input.open(filename, std::ifstream::in);
            input.close();
            if(input.fail()) {
                printDebug("ERROR: File \"%s\" does not exist.",filename);
                return false;
            }
            return true;
        }

        // =========================================================================
        // Function:   binaryPath
        // Author:     DARKGuy
        // Parameters: Full path to get the directory out from - char*
        // Returns:    Current program's path - std::string
        // =========================================================================
        // Description:
        //   Returns the current program's path / working dir.
        // =========================================================================
        std::string binaryPath(char *argv){
            std::string path;
            size_t pos;
            path = argv;
            if((pos=path.find_last_of("/")) || (pos=path.find_last_of("\\"))){
                path = path.substr(0,pos);
                #ifdef _WIN32
                    path = path + "\";
                #else
                    path = path + "/";
                #endif
                return path;
            }
            return NULL;
        }

        // =========================================================================
        // Function:   setPath
        // Author:     DARKGuy
        // Parameters: Path to set - std::string
        // Returns:    None
        // =========================================================================
        // Description:
        //   Sets the program's path / working dir.
        // =========================================================================
        void setPath(std::string path){
            g_DataDir = path;
        }

        // =========================================================================
        // Function:   useAbsolutePaths
        // Author:     DARKGuy
        // Parameters: Value to set - Boolean
        // Returns:    None
        // =========================================================================
        // Description:
        //   It defines if GP2D should use absolute paths or relative paths when
        //   executing file operations.
        // =========================================================================
        void useAbsolutePaths(bool value){
            g_AbsolutePaths=value;
        }

        // =========================================================================
        // Function:   cls
        // Author:     DARKGuy
        // Parameters: None
        // Returns:    None
        // =========================================================================
        // Description:
        //   Clears the screen.
        // TODO:
        //   Make it use the background color defined by the user in g_BackgroundColor
        // =========================================================================
        void cls(){
            if(g_VideoAPI==GP2D_SDL){
                SDL_FillRect(g_SDLScreen,NULL,SDL_MapRGB(g_SDLVideoInfo->vfmt,0,0,0));
            }
        }

        // =========================================================================
        // Function:   setWindowTitle
        // Author:     DARKGuy
        // Parameters: Window's title to set - std::string
        // Returns:    None
        // =========================================================================
        // Description:
        //   Changes the window's titlebar text
        // =========================================================================
        void setWindowTitle(std::string title){
            SDL_WM_SetCaption(title.c_str(), NULL);            
        }

        // =========================================================================
        // Function:   setKeyRepeat
        // Author:     DARKGuy
        // Parameters: TODO: Get their description from the SDL DocWiki
        // Returns:    None
        // =========================================================================
        // Description:
        //   TODO: Get it from the SDL DocWiki
        // =========================================================================        
        int setKeyRepeat(int delay, int interval){
            return SDL_EnableKeyRepeat(delay,interval);
        }

        int switchVideoMode(){
            int retVal = 0;
            if((retVal = SDL_WM_ToggleFullScreen(g_SDLScreen))){
                g_Fullscreen = true;
                return retVal;
            } else {
                g_Fullscreen = false;
                return retVal;
            }
            return retVal;
        }
}

