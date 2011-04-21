#include <iostream>
#include <sstream>

#include "graphics.h"
#include "input.h" // for inputhandler

using namespace std;

namespace gp {

// The one and only instance of the window.
// Firstly initialized to NULL, or else we get some errors :)
GPWindow* GPWindow::m_instance = NULL;

GPWindow* GPWindow::getInstance() {
    if(m_instance == NULL) { // instance not already created?
        // then create it!
        m_instance = new GPWindow();
        // Set the default video API to SDL
        m_instance->setRenderMode(GPWindow::GP_OPENGL);
    }

    // and return it.
    return m_instance;
}

/**
 * Create a window instance. Done by using GPWindow::getInstance().
 */
GPWindow::GPWindow() :
        m_fullScreen(false),
        m_bgColor(NULL),
        m_surfaceScreen(NULL),
        m_videoFlags(0) {

    m_videoAPI = GPWindow::GP_OPENGL; // defaults to opengl rendering, rox more.
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
    m_fullScreen = !m_fullScreen; // flip the fullscreen boolean indication
    if(m_surfaceScreen != NULL) {
		m_videoFlags ^= SDL_FULLSCREEN;
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
		m_surfaceScreen = SDL_SetVideoMode(m_screenWidth, m_screenHeight, m_screenDepth, m_videoFlags); 
		
        std::vector<GPTexture*>::iterator iter;
        for(iter = m_textures.begin(); iter != m_textures.end(); iter++)
        {
          (*iter)->Generate();
        }
		
		setGraphicsDefaults();
    } else {
        throw GPException("Fullscreen toggle failed");
    }
}

/**
 * Returns the height of the window.
 */
int GPWindow::getHeight() const {
    return m_screenHeight;
}

/**
 * Returns the width of the window.
 */
int GPWindow::getWidth() const {
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
    if(m_videoAPI == GP_SDL){
    } else {
        glShadeModel(GL_SMOOTH); // smooth shading.
        glEnable(GL_LINE_SMOOTH); // smooth lining (anti aliasing?)
        glEnable(GL_POINT_SMOOTH); // point smoothing
        glEnable(GL_POLYGON_SMOOTH); // polygon smoothing
        glEnable(GL_BLEND); // enable (alpha) blending.
    }
}

/**
 * Sets the window title.
 */
void GPWindow::setWindowTitle(string title) {
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
void GPWindow::clearScreen() {
    GPWindow* window = GPWindow::getInstance();
    if(window->getRenderMode() == GPWindow::GP_SDL){
        gpByte r, g, b;
        if(m_bgColor == NULL) {
            r = g = b = 0;
        } else {
            r = m_bgColor->r;
            g = m_bgColor->g;
            b = m_bgColor->b;
        }
        gpUint32 bgcolor = SDL_MapRGB(m_surfaceBackground->format, r, g, b);
        SDL_FillRect(m_surfaceBackground, 0, bgcolor);
        SDL_BlitSurface(m_surfaceBackground, NULL, window->getSurface(), NULL);
    } else {
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
}

/**
 * Synchronize buffers.
 */
void GPWindow::sync() {
    GPWindow* window = GPWindow::getInstance();
    if(window->getRenderMode() == GPWindow::GP_SDL){
        SDL_UpdateRect(window->getSurface(),0,0,0,0);
    } else {
        glFlush(); // Force execution of GL commands in finite time using
        SDL_GL_SwapBuffers(); // swap the buffers.
    }
}

/**
 * Check the status of the window if it is opened or not.
 */
bool GPWindow::isCreated() {
    return m_surfaceScreen != NULL;
}

/**
 * Does the actual work. Will throw an exception if GPEngine::initVideo() or
 * GPEngine::initAll() was not called first.
 */
void GPWindow::createWindow(int width, int height, int bpp) throw(GPException) {
    const SDL_VideoInfo* m_videoInfo = SDL_GetVideoInfo();

    if(m_videoInfo == NULL) {
        throw GPException("Unable to create a window: video was not initialized.");
    }

    if(m_videoAPI == GP_SDL){
        m_videoFlags ^= SDL_DOUBLEBUF | SDL_HWPALETTE; // set default flags for SDL only
    } else {
        m_videoFlags ^= SDL_OPENGL | SDL_HWPALETTE; // set default flags for
                                                   // OpenGL
    }

    // check to see if a surface can be stored in mem:
    if (m_videoInfo->hw_available) {
        m_videoFlags ^= SDL_HWSURFACE;
    } else {
        m_videoFlags ^= SDL_SWSURFACE;
    }

	/*
     * According to:
	 * http://www.devolution.com/pipermail/sdl/2005-June/069332.html
	 * This flag is useless
	 
    if (m_videoInfo->blit_hw) {
        m_videoFlags |= SDL_HWACCEL;
    }
	
     */

    if(m_videoAPI == GP_SDL){
    } else {
        // Sets up OpenGL double buffering
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, true);
    }

    // check whether the video mode is supported.
    int modeOK = SDL_VideoModeOK(width, height, bpp, m_videoFlags);

    if(modeOK != 0) {
        // this next function actually OPENS the window too!
        m_surfaceScreen = SDL_SetVideoMode(width, height, bpp, m_videoFlags);
        m_screenWidth = width;
        m_screenHeight = height;
        m_screenDepth = bpp;

        if(m_surfaceScreen == NULL) {
            throw GPException("Video framebuffer surface could not be created", SDL_GetError());
        }

        if(m_videoAPI == GP_SDL){
            m_surfaceBackground = SDL_CreateRGBSurface(SDL_HWSURFACE, m_screenWidth, m_screenHeight, m_screenDepth, 0, 0, 0, 0);
        }

    } else {
        // video mode here is not supported. Throw up an exception so we know
        // it is not supported.
        stringstream s;
        s << "Video mode " << width << "x" << height << "x" << bpp
          << " is not supported. Bitmask video flags: " << m_videoFlags;
        throw GPException(s.str());
    }

}

/*
 * Changes the rendering API to use.
 */
void GPWindow::setRenderMode(const GPRenderMode mode) {
    m_videoAPI = mode;
}

/*
 * Returns the current rendering API.
 */
GPWindow::GPRenderMode GPWindow::getRenderMode() const {
    return m_videoAPI;
}

void GPWindow::addTexture(GPTexture* tex) {
	m_textures.push_back(tex);
	clog << "Texture added" << endl;	
}

//==============================================================================

/**
 * Create!
 */
GPCamera::GPCamera() {
    // lastly, update the camera.
    updateCamera();
}

/**
 * Destroy!
 */
GPCamera::~GPCamera() {
}

/**
 * Updates our camera.
 */
void GPCamera::updateCamera() throw(GPException) {
}
/**
 * Set range.
 */
void GPCamera::setRange(gpDouble range) {
    m_range = range;
}

/**
 * Get range.
 */
gpDouble GPCamera::getRange() const {
    return m_range;
}

/**
 * Sets x, y positions.
 */
void GPCamera::setPosition(gpFloat x, gpFloat y) {
    m_posX = x;
    m_posY = y;
    updateCamera();
}

gpFloat GPCamera::getX() const {
    return m_posX;
}

gpFloat GPCamera::getY() const {
    return m_posY;
}

//==============================================================================

GPGameCamera::GPGameCamera(gpDouble range) throw (GPException) {
    if(range < 0) {
        // if the default of lower than zero is applied, get the window height, divide
        // it by 2 and use that as a range.
        GPWindow* window = GPWindow::getInstance();
        if(window == NULL) {
            throw GPException("No GPWindow instance found");
        } else {
            // window can be not null, but still not created.
            if(!window->isCreated()) {
                throw GPException("GPWindow can not be allocated (is it created?)");
            }

            range = static_cast<gpDouble>(window->getHeight() / 2);
        }
    }

    setRange(range);
}

void GPGameCamera::updateCamera() throw (GPException) {
    GPWindow* window = GPWindow::getInstance();
    if(window->getRenderMode() == GPWindow::GP_SDL){

    } else {
        if(!window->isCreated()) {
            // well, the window cannot be allocated. Be sure to notify the
            // programmer by throwing an exception.
            throw GPException("GPWindow can not be allocated (is it created?)");
        }

        int height = window->getHeight();
        int width = window->getWidth();

        // no division by zeroes, plx!
        if (height == 0) {
            height = 1;
        }

        // the aspect ratio of the 'window'
        GLfloat aspectRatio = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);

        glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

        // make sure to change the projection matrix.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (width <= height) {
            glOrtho(-m_range, m_range,
                    -m_range / aspectRatio, m_range / aspectRatio,
                    -m_range, m_range);
        } else {
            glOrtho(-m_range * aspectRatio, m_range * aspectRatio,
                    -m_range, m_range,
                    -m_range, m_range);
        }

        // this translates the orthographic projection to the desired x and y.
        // don't know why exactly this works, but some website refer to it as 'working'.
        glTranslatef(-getX(), -getY(), 0.0f);
    }
}

//==============================================================================

GPGuiCamera::GPGuiCamera() throw (GPException) :
        m_rangeLeft(0),
        m_rangeRight(100),
        m_rangeTop(100),
        m_rangeBottom(0) {

}

void GPGuiCamera::updateCamera() throw (GPException) {
    GPWindow* window = GPWindow::getInstance();
    if(window->getRenderMode() == GPWindow::GP_SDL){

    } else {
        if(!window->isCreated()) {
            // well, the window cannot be allocated. Be sure to notify the
            // programmer by throwing an exception.
            throw GPException("GPWindow can not be allocated (is it created?)");
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, window->getWidth(), window->getHeight());
        glOrtho(m_rangeLeft, m_rangeRight, m_rangeBottom, m_rangeTop, -1.0, 1.0);
    }
}

void GPGuiCamera::setDefaults() throw (GPException) {
    GPWindow* window = GPWindow::getInstance();
    if(!window->isCreated()) {
        // well, the window cannot be allocated. Be sure to notify the
        // programmer by throwing an exception.
        throw GPException("GPWindow can not be allocated (is it created?)");
    }

    m_rangeLeft = 0;
    m_rangeRight = window->getWidth();
    m_rangeBottom = 0;
    m_rangeTop = window->getHeight();
}

//==============================================================================

GPDirector::GPDirector(GPCamera* gamecam, GPCamera* guicam) :
        m_gamecam(gamecam),
        m_guicam(guicam),
        m_flag(true) {
}

GPDirector::~GPDirector() {
}

void GPDirector::useGameCamera() {
    if(!m_flag) {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        m_gamecam->updateCamera();

        m_flag = false;
    }
}

void GPDirector::useGuiCamera() {
    if(m_flag) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        m_guicam->updateCamera();

        m_flag = true;
    }
}

//==============================================================================
void GPTexture::Generate() {
    if(m_surface != NULL) {
        int l_surface;

        if (m_isPowerOfTwo) {
            l_surface = GL_TEXTURE_2D;
        } else {
            l_surface = GL_TEXTURE_RECTANGLE_NV;
        }

        glGenTextures(1, &m_texID);
        glBindTexture(l_surface, m_texID);
        glTexImage2D(l_surface, 0, 4, m_surface->w, m_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);
        glTexEnvf(l_surface, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        glTexParameterf(l_surface, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(l_surface, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(l_surface, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(l_surface, GL_TEXTURE_WRAP_T, GL_REPEAT);

        clog << "Texture generated" << endl;
    }
}

GPTexture::GPTexture () throw (GPException) {
    GPWindow* window = GPWindow::getInstance();
    Uint8 bpp = window->getSurface()->format->BitsPerPixel;
    SDL_Surface* surf = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, 256, 256, bpp, 0, 0, 0, 0);
    if (surf == NULL) {
        throw GPException("Unable to create an empty RGB 256x256 surface", SDL_GetError());
    }

    m_surface = SDL_DisplayFormatAlpha (surf);
    m_width = m_surface->w;
    m_height = m_surface->h;
    m_pixels = m_surface->pixels;

    m_textureRepeatX = 1.0f;
    m_textureRepeatY = 1.0f;
    m_textureOffsetX = 0.0f;
    m_textureOffsetY = 0.0f;

    m_isPowerOfTwo = true;

    SDL_FreeSurface(surf);
	
	window->addTexture(this);
}

GPTexture::GPTexture(string file) throw(GPException) {
    m_texName = file;
    m_textureRepeatX = 1.0f;
    m_textureRepeatY = 1.0f;
    m_textureOffsetX = 0.0f;
    m_textureOffsetY = 0.0f;

    GPWindow* window = GPWindow::getInstance();
    SDL_Surface* surf = IMG_Load(file.c_str());
    if(surf != NULL) {
            int l_surface;
            m_surface = SDL_DisplayFormatAlpha(surf);
            m_width = m_surface->w;
            m_height = m_surface->h;
            m_pixels = m_surface->pixels;

            // Formula provided by RTFM_FTW from ##OpenGL :O
            if (!((int)m_width & ((int)m_width - 1)) && !((int)m_height & ((int)m_height - 1))) {
                m_isPowerOfTwo = true;
            } else {
                m_isPowerOfTwo = false;
            }

            if (m_isPowerOfTwo) {
                l_surface = GL_TEXTURE_2D;
            } else {
                l_surface = GL_TEXTURE_RECTANGLE_NV;
            }

            glGenTextures(1, &m_texID);
            glBindTexture(l_surface, m_texID);
            glTexImage2D(l_surface, 0, 4, m_surface->w, m_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);
            glTexEnvf(l_surface, GL_TEXTURE_ENV_MODE, GL_MODULATE);

            glTexParameterf(l_surface, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(l_surface, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(l_surface, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterf(l_surface, GL_TEXTURE_WRAP_T, GL_REPEAT);

            clog << "Texture loaded (OGL): " << file << ", "
                 << m_width  << "x" << m_height << endl;

            if (m_isPowerOfTwo) {
                clog << "Texture is a POT texture" << endl;
            } else {
                clog << "Texture is a NPOT texture" << endl;
            }

            // free the OLD surface, but do not free the alpha surface m_surface.
            SDL_FreeSurface(surf);
			
			window->addTexture(this);
			
    } else {
        // Something bad happened. IMG_GetError probably returns some useful
        // information, so throw an exception indicating the problem. It might
         // for instance be a file which can not be found.
        throw GPException("Texture creation failed", IMG_GetError());
    }

}

/**
 * Deletes texture resources.
 */
GPTexture::~GPTexture() {
    GPWindow* window = GPWindow::getInstance();
    if(window->getRenderMode() == GPWindow::GP_SDL){
        SDL_FreeSurface(m_surface);
    } else {
        if(m_surface != NULL) {
            SDL_FreeSurface(m_surface);

            // make sure we only delete the OpenGL texture if it
            // is indeed an OpenGL texture.
            if(glIsTexture(m_texID)) {
                glDeleteTextures(1, &m_texID);
            }
        }
    }
}

unsigned int GPTexture::getId() const {
    return m_texID;
}

string GPTexture::getName() const {
    return m_texName;
}

float GPTexture::getWidth() const {
    return m_width;
}

float GPTexture::getHeight() const {
    return m_height;
}

GLfloat GPTexture::getTextureRepeatX() const {
    return m_textureRepeatX;
}

GLfloat GPTexture::getTextureRepeatY() const {
    return m_textureRepeatY;
}

void GPTexture::setTextureRepeatX(GLfloat value) {
    m_textureRepeatX = value;
}

void GPTexture::setTextureRepeatY(GLfloat value) {
    m_textureRepeatY = value;
}

GLfloat GPTexture::getTextureOffsetX() const {
    return m_textureOffsetX;
}

GLfloat GPTexture::getTextureOffsetY() const {
    return m_textureOffsetY;
}

void GPTexture::setTextureOffsetX(GLfloat value) {
    m_textureOffsetX = value;
}

void GPTexture::setTextureOffsetY(GLfloat value) {
    m_textureOffsetY = value;
}

void* GPTexture::getPixels() {
    return m_pixels;
}


SDL_Surface* GPTexture::getSurface() {
    return m_surface;
}

bool GPTexture::isPowerOfTwo() {
    return m_isPowerOfTwo;
}

/**
 * Changes the texture's surface.
 */
void GPTexture::setSurface(SDL_Surface* surf) {
    if(surf == NULL) {
        cerr << "GPTexture::setSurface() : surface was NULL" << endl;
        return;
    }

    if(m_surface != NULL) {
        // free the m_surface first before initializing another. This fixes a
        // memory leak, especially with the GPText class. It would increase
        // dependent on the size of the resulting surface) in an x amount of
        // memory increase per y seconds.
        SDL_FreeSurface(m_surface);
    }

    // Now create the new Surface.
    m_surface = surf;
    m_width = m_surface->w;
    m_height = m_surface->h;
    m_pixels = m_surface->pixels;

    if(glIsTexture(m_texID)) {  // if the current texID was a texture, delete it.
        glDeleteTextures(1, &m_texID);
    }

    glGenTextures(1, &m_texID);
    glBindTexture(GL_TEXTURE_2D, m_texID);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, m_surface->w, m_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, m_surface->pixels);
    // XXX: next to params are not really necessary.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFinish();

}

//==============================================================================

GPRect::GPRect(gpFloat xx, gpFloat yy, gpFloat ww, gpFloat hh) :
        x(xx),
        y(yy),
        w(ww),
        h(hh) {
}

GPRect::~GPRect() {
}

//==============================================================================

GPColor::GPColor(gpByte red, gpByte green, gpByte blue, gpByte alpha) :
    r(red),
    g(green),
    b(blue),
    a(alpha) {
}

GPColor::GPColor(const GPColor& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

GPColor GPColor::operator +(const GPColor& color) {
    return GPColor(r + color.r, g + color.g, b + color.b, a + color.a);
}

GPColor GPColor::operator -(const GPColor& color) {
    return GPColor(r - color.r, g - color.g, b - color.b, a - color.a);
}

GPColor GPColor::operator ^(const GPColor& color) {
    return GPColor(r ^ color.r, g ^ color.g, b ^ color.b, a ^ color.a);
}

GPColor GPColor::brighter() const {
    GPColor newone = *this;
    // be sure to clamp the maximum color value to 0xFF positive.
    newone.r = ((newone.r + 0x10) > 0xFF ? 0xFF : newone.r + 0x10);
    newone.g = ((newone.g + 0x10) > 0xFF ? 0xFF : newone.g + 0x10);
    newone.b = ((newone.b + 0x10) > 0xFF ? 0xFF : newone.b + 0x10);

    return newone;
}

GPColor GPColor::darker() const {
    GPColor newone = *this;
    // be sure to clamp the maximum color value to 0xFF positive.
    newone.r = ((newone.r - 0x10) < 0x00 ? 0x00 : newone.r - 0x10);
    newone.g = ((newone.g - 0x10) > 0x00 ? 0x00 : newone.g - 0x10);
    newone.b = ((newone.b - 0x10) > 0x00 ? 0x00 : newone.b - 0x10);

    return newone;
}


const GPColor GPColor::GP_COLOR_WHITE   = GPColor(                );
const GPColor GPColor::GP_COLOR_BLACK   = GPColor(0x00, 0x00, 0x00);
const GPColor GPColor::GP_COLOR_RED     = GPColor(0xFF, 0x00, 0x00);
const GPColor GPColor::GP_COLOR_GREEN   = GPColor(0x00, 0xFF, 0x00);
const GPColor GPColor::GP_COLOR_BLUE    = GPColor(0x00, 0x00, 0xFF);


//==============================================================================

/**
 * GPObject constructor.
 */
GPObject::GPObject() {
    init();
}

GPObject::GPObject(float x, float y) {
    init();
    m_x = x;
    m_y = y;
}

GPObject::GPObject(float x, float y, float z) {
    init();
    m_x = x;
    m_y = y;
    m_z = z;
}

/**
 * Destroy the object. Virtual destructor.
 */
GPObject::~GPObject() {
    clearBoundingBoxes();
}

/**
 * Do some initializing here of local class members.
 */
void GPObject::init() {
    m_x = 0.0f; // initialize the coordinates and all that to 0.0f.
    m_y = 0.0f;
    m_z = 0.0f;
    m_x_scale = 1.0f;
    m_y_scale = 1.0f;
    m_z_scale = 1.0f;
    m_height = 0.0f;
    m_width = 0.0f;
    m_x_velocity = 0.0f;
    m_y_velocity = 0.0f;
    m_angle_X = 0.0f;
    m_angle_Y = 0.0f;
    m_angle_Z = 0.0f;
}

/*
 * Shitload of getters functions over here.
 */

float GPObject::getX() const {
    return m_x;
}
float GPObject::getY() const {
    return m_y;
}
float GPObject::getZ() const {
    return m_z;
}
float GPObject::getWidth() const {
    return m_width;
}
float GPObject::getHeight() const {
    return m_height;
}
gpFloat GPObject::getScale_X() const {
    return m_x_scale;
}
gpFloat GPObject::getScale_Y() const {
    return m_y_scale;
}
gpFloat GPObject::getScale_Z() const {
    return m_z_scale;
}
void GPObject::getScale(gpFloat& X, gpFloat& Y, gpFloat& Z) const {
    X=m_x_scale;
    Y=m_y_scale;
    Z=m_z_scale;
}
float GPObject::getVelocity_X() const {
    return m_x_velocity;
}
float GPObject::getVelocity_Y() const {
    return m_y_velocity;
}
float GPObject::getRotation_X() const {
    return m_angle_X;
}
float GPObject::getRotation_Y() const {
    return m_angle_Y;
}
float GPObject::getRotation_Z() const {
    return m_angle_Z;
}
float GPObject::getRotCenter_X() const {
    return m_RotCenter_X;
}
float GPObject::getRotCenter_Y() const {
    return m_RotCenter_Y;
}
float GPObject::getRotCenter_Z() const {
    return m_RotCenter_Z;
}

/*
 * Shitload of setter methods right here.
 */

void GPObject::setX(float x) {
    m_x = x;
}
void GPObject::setY(float y) {
    m_y = y;
}
void GPObject::setZ(float z) {
    m_z = z;
}
void GPObject::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
}
void GPObject::setWidth(float w) {
    m_width = w;
}
void GPObject::setHeight(float h) {
    m_height = h;
}
void GPObject::setScale_X(float s) {
    m_x_scale = s;
}
void GPObject::setScale_Y(float s) {
    m_y_scale = s;
}
void GPObject::setScale_Z(float s) {
    m_z_scale = s;
}
void GPObject::setScale(gpFloat sX, gpFloat sY, gpFloat sZ) {
    m_x_scale=sX;
    m_y_scale=sY;
    m_z_scale=sZ;
}
void GPObject::setSize(float w, float h) {
    m_width = w;
    m_height = h;
}

void GPObject::setVelocity_X(float xvel) {
    m_x_velocity = xvel;
}
void GPObject::setVelocity_Y(float yvel) {
    m_y_velocity = yvel;
}
void GPObject::setRotation_X(float angle) {
    m_angle_X = angle;
}
void GPObject::setRotation_Y(float angle) {
    m_angle_Y = angle;
}
void GPObject::setRotation_Z(float angle) {
    m_angle_Z = angle;
}
void GPObject::setRotCenter_X(float a_X) {
    m_RotCenter_X = a_X;
}
void GPObject::setRotCenter_Y(float a_Y) {
    m_RotCenter_Y = a_Y;
}
void GPObject::setRotCenter_Z(float a_Z) {
    m_RotCenter_Z = a_Z;
}
void GPObject::setRotCenter(float a_x,float a_y,float a_z) {
    m_RotCenter_X = a_x;
    m_RotCenter_Y = a_y;
    m_RotCenter_Z = a_z;
}
vector<GPRect>& GPObject::getBoundingBoxes() {
    return m_boundingBoxes;
}
void GPObject::clearBoundingBoxes() {
    m_boundingBoxes.clear();
}
void GPObject::addBoundingBox(GPRect rect) {
    m_boundingBoxes.push_back(rect);
}

//==============================================================================

GPSprite::GPSprite() :
    m_alpha(1.0f),
    m_anim_frame(0),
    m_anim_frames(0),
    m_anim_loop(true),
    m_anim_frameStart(0),
    m_anim_frameEnd(0),
    m_anim_backwards(false),
    m_texture(NULL) {

    setWidth(0.0f);
    setHeight(0.0f);
}

GPSprite::GPSprite(GPTexture* texture) :
    m_alpha(1.0f),
    m_anim_frame(0),
    m_anim_frames(0),
    m_anim_loop(true),
    m_anim_frameStart(0),
    m_anim_frameEnd(0),
    m_anim_backwards(false) {

    addTexture(texture);

    // just to have the rotation be around the center of the image by default
    // (TODO: will need to be adapted for spritesheets)
    this->setRotCenter(m_texture->getWidth() / 2.0, -m_texture->getHeight() / 2.0, 0);
    this->createAnimFrame(0, 0, m_texture->getSurface()->w, m_texture->getSurface()->h);
}

int GPSprite::addTexture(GPTexture* texture) {
    m_textures.push_back(texture);
    m_texture = m_textures[m_textures.size()-1];

    setWidth(m_texture->getWidth());
    setHeight(m_texture->getHeight());

    // Just to have the rotation be around the center of the image by default
    // (TODO: will need to be adapted for spritesheets)
    this->setRotCenter(m_texture->getWidth() / 2.0, -m_texture->getHeight() / 2.0, 0);
    return m_textures.size()-1;
}

void GPSprite::useTexture(unsigned int value) {
    if(value >= 0 && value <= m_textures.size() - 1) {
        m_texture = m_textures[value];
    }
}

GPSprite::~GPSprite() {
    // not much to delete here by default, especially not the
    // GPTexture instance, because it can be used by other sprites.
}

GPTexture* GPSprite::getTexture() const {
    return m_texture;
}

gpInt32 GPSprite::createAnim(gpInt32 framesWidth, gpInt32 framesHeight, gpInt32 orgx, gpInt32 orgy, gpInt32 width, gpInt32 height) {
    for(int fy = 0; fy <= framesHeight; fy++) {
        for(int fx = 0; fx <= framesWidth; fx++) {
            GPRect rect;
            rect.x = static_cast<gpFloat>(orgx + (fx * width)) / m_texture->getSurface()->w;
            rect.y = static_cast<gpFloat>(orgy + (fy * height)) / m_texture->getSurface()->h;
            rect.w = (static_cast<gpFloat>(orgx + (fx * width)) + static_cast<gpFloat>(width)) / m_texture->getSurface()->w;
            rect.h = (static_cast<gpFloat>(orgy + (fy * height)) + static_cast<gpFloat>(height)) / m_texture->getSurface()->h;

            m_animRects.push_back(rect);
        }
    }

    m_anim_frames = m_animRects.size()-1;
    m_anim_frameEnd = m_anim_frames;

    return m_anim_frameEnd;
}

gpInt32 GPSprite::createAnimFrame(gpInt32 x, gpInt32 y, gpInt32 width, gpInt32 height) {
    GPRect rect;
    rect.x = static_cast<gpFloat>(x / m_texture->getSurface()->w);
    rect.y = static_cast<gpFloat>(y / m_texture->getSurface()->h);
    rect.w = static_cast<gpFloat>((x + static_cast<gpFloat>(width)) / m_texture->getSurface()->w);
    rect.h = static_cast<gpFloat>((y + static_cast<gpFloat>(height)) / m_texture->getSurface()->h);

    m_animRects.push_back(rect);
    m_anim_frames = m_animRects.size()-1;
    m_anim_frameEnd = m_anim_frames;

    return m_anim_frameEnd;
}

gpInt32 GPSprite::getFrame() {
    return m_anim_frame;
}

gpInt32 GPSprite::getFrames() {
    return m_animRects.size() -1 ;
}

void GPSprite::setAnimRange(gpInt32 start, gpInt32 end) {
    m_anim_frameStart = start;
    m_anim_frameEnd   = end;

    if(m_anim_frame > m_anim_frameEnd) {
        m_anim_frame = m_anim_frameEnd;
    }

    if(m_anim_frame < m_anim_frameStart) {
        m_anim_frame = m_anim_frameStart;
    }
}

void GPSprite::setAnimBackwards(gpBool val){
    m_anim_backwards = true;
}

void GPSprite::setAnimFrame(gpInt32 frame) {
    if (frame<0){ frame=0; }
    m_anim_frame = frame;
}

void GPSprite::setAnimNextFrame() {
    if(m_anim_backwards == true){
        m_anim_frame = m_anim_frame - 1;
        if(m_anim_frame < m_anim_frameEnd){
            if(m_anim_loop == true){
                m_anim_frame = m_anim_frameStart;
            } else {
                m_anim_frame = m_anim_frameEnd;
            }
        }
    } else {
        m_anim_frame = m_anim_frame + 1;
        if(m_anim_frame > m_anim_frameEnd){
            if(m_anim_loop == true){
                m_anim_frame = m_anim_frameStart;
            } else {
                m_anim_frame = m_anim_frameEnd;
            }
        }
    }
}

void GPSprite::setAnimLoop(gpBool val) {
    m_anim_loop = val;
}

void GPSprite::draw() {

    GPWindow* window = GPWindow::getInstance();
    if(window->getRenderMode() == GPWindow::GP_SDL){

        /* FIXME: azzkikr: I commented this because I changed the camera stuff.
         * Please somebody check out this later (DARKGuy?) to fix this back. The
         * reason I commented this out, is because I changed the way the camera
         * functions. I made GPCamera a virtual base class, and created two other
         * camera's : a game and a gui cam, with different params. Therefore, I had
         * to remove the window->getCamera() (and the like) functions because they
         * no longer had any use still.
         */
//        SDL_Rect dst;
//        dst.x = static_cast<Sint16>(getX() + window->getCamera()->getX()); // static casting, avoids warnings
//        dst.y = static_cast<Sint16>(getY() + window->getCamera()->getY()); // during compilation.
//        dst.w = m_texture->getSurface()->w;
//        dst.h = m_texture->getSurface()->h;
//
//        SDL_BlitSurface(m_texture->getSurface(), NULL, window->getSurface(), &dst);

    } else {

        // enable texturization

        GLfloat x1, y1, x2, y2;
        gpBool isPowerOfTwo = getTexture()->isPowerOfTwo();
        GLenum textureMode;

        if (isPowerOfTwo) {
            textureMode = GL_TEXTURE_2D;
        } else {
            textureMode = GL_TEXTURE_RECTANGLE_NV;
        }

        glEnable(textureMode);

        // blending function, used to make alpha parts transparent or some sort.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        // enable alpha

        glAlphaFunc(GL_GREATER, 0.1f);
        glEnable(GL_ALPHA_TEST);
        glBindTexture(textureMode, m_texture->getId()); // make sure we use the correct texture ID.
        glDisable(GL_POLYGON_SMOOTH);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(getX(), getY(), getZ());

        glRotatef(getRotation_X(), 1.0f, 0.0f, 0.0f);
        glRotatef(getRotation_Y(), 0.0f, 1.0f, 0.0f);
        glRotatef(getRotation_Z(), 0.0f, 0.0f, 1.0f);

        glBegin(GL_QUADS);
            glColor4f(1.0f, 1.0f, 1.0f, m_alpha);  // Set the sprite's alpha (for PNG)

            /*
             * The following texture coordinate mappings look retarded. This is
             * because SDL flips the textures, vertically.
             *
             * Vertices:      Texture coordinates:
             *   1--4               2--3
             *   |  |               |  |
             *   2--3               1--4
             */

            if (isPowerOfTwo){
                x1 = m_animRects[m_anim_frame].x + (m_texture->getTextureOffsetX());
                y1 = m_animRects[m_anim_frame].y + (m_texture->getTextureOffsetY());
                x2 = m_animRects[m_anim_frame].w + (m_texture->getTextureRepeatX()-1.0f);
                y2 = m_animRects[m_anim_frame].h + (m_texture->getTextureRepeatY()-1.0f);
            } else {
                x1 = ( m_animRects[m_anim_frame].x + (m_texture->getTextureOffsetX())      ) * m_texture->getSurface()->w;
                y1 = ( m_animRects[m_anim_frame].y + (m_texture->getTextureOffsetY())      ) * m_texture->getSurface()->h;
                x2 = ( m_animRects[m_anim_frame].w + (m_texture->getTextureRepeatX()-1.0f) ) * m_texture->getSurface()->w;
                y2 = ( m_animRects[m_anim_frame].h + (m_texture->getTextureRepeatY()-1.0f) ) * m_texture->getSurface()->h;
            }

            glTexCoord2f(x1, y1); glVertex3f(getScale_X()*0, getScale_Y()*0, getScale_Z()*getZ());
            glTexCoord2f(x1, y2); glVertex3f(getScale_X()*0, getScale_Y()*(-getHeight()), getScale_Z()*getZ());
            glTexCoord2f(x2, y2); glVertex3f(getScale_X()*getWidth(), getScale_Y()*(-getHeight()), getScale_Z()*getZ());
            glTexCoord2f(x2, y1); glVertex3f(getScale_X()*getWidth(), getScale_Y()*0, getScale_Z()*getZ());

        glEnd();

        glDisable(textureMode); // either GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_NV
        glDisable(GL_BLEND);

    }
}


void GPSprite::setAlpha(GLfloat alpha) {
    m_alpha = alpha;
}

GLfloat GPSprite::getAlpha() const {
    return m_alpha;
}

Uint8 GPSprite::getSurfaceAlpha(SDL_Surface* surface, int x, int y) const {
    // FIXME: there probably has to be some kind of routine to check if the pixels
    // and/or surface are not NULL etc etc.
    if(x <= 0 || x >= surface->w || y <= 0 || y >= surface->h) {
        return 0x00;
    }

    Uint32* pixels = (Uint32*) surface->pixels;
    Uint32 pix = pixels[surface->w * y + x];
    Uint8 r, g, b, a;
    SDL_GetRGBA(pix, surface->format, &r, &g, &b, &a);

    return a;
}

void GPSprite::computeEdges() {
    GPTexture* tex = m_texture;
    SDL_Surface* surface = tex->getSurface();

    clog << "Computing edges for sprite with texture " << tex->getName() << endl;
    clearBoundingBoxes();
    SDL_PixelFormat* format = surface->format;

    // When we are editing, or reading raw pixels from a surface it is
    // a requirement by SDL to lock the surface.
    SDL_LockSurface(surface);
    Uint32* pixels = (Uint32*)surface->pixels;

    Uint8 pix_env[3][3];

    for(int x = 0; x < surface->w - 1; x++) {
        for (int y = 0; y < surface->h - 1; y++) {
            Uint32 current_pix = pixels[surface->w * y + x];
            Uint8 r,g,b,a;
            SDL_GetRGBA(current_pix, format, &r, &g, &b, &a);
            if(a == 0x00) {
                // calculate average of alpha pix around the curr x,y
                /*
                 * Try to get the pixels in the surroundings:
                 *
                 *  ___________
                 * |___|___|___|  [0 0], [0 1], [0 2]
                 * |___|***|___|  [1 0], [1 1], [1 2]
                 * |___|___|___|  [2 0], [2 1], [2 2]
                 *
                 *
                 * [1 1], or [***] is the current pixel. The surrounding pixels
                 * are checked for an average of non alpha. If there are
                 * non-alpha pixels around it, an edge has been detected.
                 */

                // TODO: make a one dimensional array of it (or is it premature optimization?)
                pix_env[0][0] = getSurfaceAlpha(surface, x - 1, y - 1); // top left
                pix_env[0][1] = getSurfaceAlpha(surface, x, y - 1); // top middle
                pix_env[0][2] = getSurfaceAlpha(surface, x + 1, y - 1); // top right

                pix_env[1][0] = getSurfaceAlpha(surface, x - 1, y); // middle left
                pix_env[1][1] = getSurfaceAlpha(surface, x, y); // this is the current analyzed pixel.
                pix_env[1][2] = getSurfaceAlpha(surface, x + 1, y); // middle right

                pix_env[2][0] = getSurfaceAlpha(surface, x - 1, y + 1); // down left
                pix_env[2][1] = getSurfaceAlpha(surface, x, y + 1); // down middle
                pix_env[2][2] = getSurfaceAlpha(surface, x + 1, y + 1); // down right

                bool edge_hit = false;
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        if (pix_env[i][j] > 0x00) { // is value not alpha?
                            // we hit an edge.
                            edge_hit = true;

                            // break out of loop, can't be arsed to do two breaks
                            // or some else. Just set i and j to anything bigger than 3.
                            i = 4;
                            j = 4;
                        }
                    }
                }

                if(edge_hit) {
                    /*
                     * Note: since we are detecting edges from top to bottom, left to right,
                     * this means the y coordinate of the rectangle needs to be negated, or
                     * else we receive a positive y coordinate when we are going downwards!
                     */
                    GPRect rect(x, -y, 1, 1);
                    addBoundingBox(rect);
                }
            }
        }
    }

    // ... and unlock it when we are done with it!
    SDL_UnlockSurface(surface);
}

//==============================================================================

GPCursor::GPCursor() {
}

GPCursor::GPCursor(GPTexture* tex) {
    addTexture(tex);
}

GPCursor::~GPCursor() {

}

gpBool GPCursor::isDefPointerVisible() {
    return SDL_ShowCursor(-1);
}

void GPCursor::setDefPointerVisible(gpBool enabled) {
    SDL_ShowCursor(enabled);
}

void GPCursor::updatePosition() throw (GPException) {
    GPWindow* window = GPWindow::getInstance();
    if(window == NULL) {
        throw GPException("GPWindow instance was NULL");
    } else {
        if(!window->isCreated()) {
            throw GPException("GPWindow is not created!");
        } else {
            // Make use of the static functions GPInputHandler
            // provides, to just get the mouse position without
            // the need of registering an event with the input
            // handler, just to get the mouse position.
            gpFloat x, y;
            GPPoint p = GPMouseHandler::getMousePosition();
            x = p.x;
            y = p.y;
            setPosition(x, window->getHeight() - y);
        }
    }
}

//==============================================================================

void drawRectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z)
{

    glBegin(GL_LINES);
        // top left to top right
        glVertex3f(x1, y1, z);
        glVertex3f(x2, y1, z);
        // top right to bottom right
        glVertex3f(x2, y1, z);
        glVertex3f(x2, y2, z);
        // bottom left to bottom right
        glVertex3f(x1, y2, z);
        glVertex3f(x2, y2, z);
        // top left to bottom left
        glVertex3f(x1, y1, z);
        glVertex3f(x1, y2, z);
    glEnd();

}

    Uint32 GetPixel ( SDL_Surface *surface, Uint32 x, Uint32 y )
    {

        if ( x < 0 ) { exit(67); }
        if ( y < 0 ) { exit(67); }
        if ( x >= ( Uint32 ) surface->w ) { exit(67); }
        if ( y >= ( Uint32 ) surface->h ) { exit(67); }

        int bpp = surface->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        Uint8 *p = ( Uint8 * ) surface->pixels + y * surface->pitch + x * bpp;
        switch ( bpp )
        {
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

    bool GetPixelRGBA ( SDL_Surface* surf, Uint32 x, Uint32 y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a )
    {
        //make sure we are inside the surface
        if ( x < 0 ||  y < 0 || x >= ( Uint32 ) surf->w || y >= ( Uint32 ) surf->h ) return ( false );
        SDL_GetRGBA ( GetPixel ( surf,x,y ),surf->format,&r,&g,&b,&a );
        return ( true );
    }

    Uint8 GetPixelR ( SDL_Surface* surf, Uint32 x, Uint32 y )
    {
        Uint8 r,g,b,a;
        //make sure we are inside the surface
        if ( x < 0 ||  y < 0 || x >= ( Uint32 ) surf->w || y >= ( Uint32 ) surf->h ) return ( -1 );
        SDL_GetRGBA ( GetPixel ( surf,x,y ),surf->format,&r,&g,&b,&a );
        return ( r );
    }

    Uint8 GetPixelG ( SDL_Surface* surf, Uint32 x, Uint32 y )
    {
        Uint8 r,g,b,a;
        //make sure we are inside the surface
        if ( x < 0 ||  y < 0 || x >= ( Uint32 ) surf->w || y >= ( Uint32 ) surf->h ) return ( -1 );
        SDL_GetRGBA ( GetPixel ( surf,x,y ),surf->format,&r,&g,&b,&a );
        return ( g );
    }

    Uint8 GetPixelB ( SDL_Surface* surf, Uint32 x, Uint32 y )
    {
        Uint8 r,g,b,a;
        //make sure we are inside the surface
        if ( x < 0 ||  y < 0 || x >= ( Uint32 ) surf->w || y >= ( Uint32 ) surf->h ) return ( -1 );
        SDL_GetRGBA ( GetPixel ( surf,x,y ),surf->format,&r,&g,&b,&a );
        return ( b );
    }

    Uint8 GetPixelA ( SDL_Surface* surf, Uint32 x, Uint32 y )
    {
        Uint8 r,g,b,a;
        //make sure we are inside the surface
        if ( x < 0 ||  y < 0 || x >= ( Uint32 ) surf->w || y >= ( Uint32 ) surf->h ) return ( -1 );
        SDL_GetRGBA ( GetPixel ( surf,x,y ),surf->format,&r,&g,&b,&a );
        return ( a );
    }

} // namespace gp
