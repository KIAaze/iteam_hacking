#include "window.hpp"

#include <sstream>
#include <iostream>

#include <GL/gl.h>
#include <GL/glext.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace std;

namespace gp {

/**
 * Create a window instance.
 *
 * Defaults is a windowed screen, black background and zero flags and screen
 * surface, which must be initialized afterwards with createWindow.
 */
GPWindow::GPWindow() :
        m_fullScreen(false),
        m_bgColor(new GPColor(GPColor::GP_COLOR_BLACK)),
        m_surfaceScreen(NULL),
        m_videoFlags(0) {
}

/**
 * Destructor. Deletes some resources occupied by this object.
 */
GPWindow::~GPWindow() {
    SDL_FreeSurface(m_surfaceScreen);
}

/**
 * Toggles fullscreen mode on, or off. Internally, a bool will be set stating
 * whether the screen is currently in fullscreen mode.
 */
void GPWindow::toggleFullScreen() throw(GPException) {
    m_fullScreen = !m_fullScreen; /// flip the fullscreen boolean indication
    if(m_surfaceScreen != NULL) {
		m_videoFlags ^= SDL_FULLSCREEN;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
		m_surfaceScreen = SDL_SetVideoMode(m_screenWidth, m_screenHeight, m_screenDepth, m_videoFlags);

        /// Reload textures, so we don't get them all white when we're finished.
        std::map<std::string, GPTexture*>::iterator iter;
        for(iter = m_textures.begin(); iter != m_textures.end(); iter++)
        {
          (*iter).second->Generate();
        }

		setGraphicsDefaults();
    } else {
        throw GPException("Fullscreen toggle failed");
    }
}

/**
 * Returns the height of the window.
 */
gpInt32 GPWindow::getHeight() const {
    return m_screenHeight;
}

/**
 * Returns the width of the window.
 */
gpInt32 GPWindow::getWidth() const {
    return m_screenWidth;
}

/**
 * Returns the screen surface (used for the SDL rendering mode and the blitting routine)
 */
SDL_Surface* GPWindow::getSurface() {
    return m_surfaceScreen;
}

void GPWindow::setBackgroundColor(GPColor* color) {
    m_bgColor = color;
}

/**
 * Input grabbing of events.
 */
void GPWindow::setInputGrabEnabled(bool enabled) {
    if(enabled) {
        SDL_WM_GrabInput(SDL_GRAB_ON);
    } else {
        SDL_WM_GrabInput(SDL_GRAB_OFF);
    }
}


/**
 * Graphic defaults. Can be called at any time.
 */
void GPWindow::setGraphicsDefaults() {
	glShadeModel(GL_SMOOTH); /// smooth shading.
	glEnable(GL_LINE_SMOOTH); /// smooth lining (anti aliasing?)
	glEnable(GL_POINT_SMOOTH); /// point smoothing
	glEnable(GL_POLYGON_SMOOTH); /// polygon smoothing
	glEnable(GL_BLEND); /// enable (alpha) blending.
}

/**
 * Sets the window title.
 */
void GPWindow::setTitle(string title) {
    SDL_WM_SetCaption(title.c_str(), NULL);
}

/**
 * Sets the no-frame flag.
 */
void GPWindow::setFlagNoFrame() {
    m_videoFlags ^= SDL_NOFRAME;
}

/**
 * Sets resizable flag.
 */
void GPWindow::setFlagResizable() {
    m_videoFlags ^= SDL_RESIZABLE;
}


/**
 * Clear the screen.
 */
void GPWindow::clear() {
	gpFloat r, g, b, a;
	if(m_bgColor == NULL) {
		r = g = b = 0.0f;
		a = 1.0f;
	} else {
		r = static_cast<gpFloat>(m_bgColor->r) / 0xFF;
		g = static_cast<gpFloat>(m_bgColor->g) / 0xFF;
		b = static_cast<gpFloat>(m_bgColor->b) / 0xFF;
		a = static_cast<gpFloat>(m_bgColor->a) / 0xFF;
	}
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT */);
}

/**
 * Synchronize buffers.
 */
void GPWindow::render() {
	glFlush(); /// Force execution of GL commands in finite time using
	SDL_GL_SwapBuffers(); /// swap the buffers.
}

/**
 * Check the status of the window if it is opened or not.
 */
gpBool GPWindow::isCreated() {
    return m_surfaceScreen != NULL;
}

/**
 * Does the actual work. Will throw an exception if GPEngine::initVideo() or
 * GPEngine::initAll() was not called first.
 */
void GPWindow::create(int width, int height, int bpp, std::string title) throw(GPException) {
    const SDL_VideoInfo* m_videoInfo = SDL_GetVideoInfo();

    if(m_videoInfo == NULL) {
        throw GPException("Unable to create a window: video was not initialized.");
    }

	m_videoFlags ^= SDL_OPENGL | SDL_HWPALETTE; /// set default flags for OpenGL

    /// check to see if a surface can be stored in mem:
    if (m_videoInfo->hw_available) {
        m_videoFlags ^= SDL_HWSURFACE;
    } else {
        m_videoFlags ^= SDL_SWSURFACE;
    }

	/// Sets up OpenGL double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);

    /// check whether the video mode is supported.
    int modeOK = SDL_VideoModeOK(width, height, bpp, m_videoFlags);

    if(modeOK != 0) {
        /// this next function actually OPENS the window too!
        m_surfaceScreen = SDL_SetVideoMode(width, height, bpp, m_videoFlags);
        m_screenWidth = width;
        m_screenHeight = height;
        m_screenDepth = bpp;

        if(m_surfaceScreen == NULL) {
            throw GPException("Video framebuffer surface could not be created", SDL_GetError());
        }

        setTitle(title);

        m_gameCamera = new GPGameCamera();
        m_guiCamera = new GPGuiCamera();

        m_gameCamera->setWindow(this);
        m_guiCamera->setWindow(this);

        m_gameCamera->setRange(static_cast<gpFloat>(height / 2));
        m_gameCamera->updateCamera();

        m_cameraDirector = new GPDirector(m_gameCamera, m_guiCamera);

    } else {
        /// video mode here is not supported. Throw up an exception so we know
        /// it is not supported.
        stringstream s;
        s << "Video mode " << width << "x" << height << "x" << bpp
          << " is not supported. Bitmask video flags: " << m_videoFlags;
        throw GPException(s.str());
    }

}

void GPWindow::addTexture(std::string name, GPTexture* tex) {
    m_textures[name] = tex;
	clog << "Texture added" << endl;
}

void GPWindow::addTexture(std::string name, std::string filename) {
    addTexture(name, new GPTexture(filename));
}

GPTexture* GPWindow::getTexture(std::string name) {
    return m_textures[name];
}

void GPWindow::setDirector(GPDirector* director) {
    m_cameraDirector = director;
}

GPDirector* GPWindow::getDirector() {
    return m_cameraDirector;
}

}
