#include <iostream>
#include <sstream>

#include "graphics.h"
#include "input.h" // for inputhandler

using namespace std;

namespace gp2d {

// The one and only instance of the window.
// Firstly initialized to NULL, or else we get some errors :)
GP2DWindow* GP2DWindow::m_instance = NULL;

GP2DWindow* GP2DWindow::getInstance() {
    if(m_instance == NULL) { // instance not already created?
        // then create it!
        m_instance = new GP2DWindow();
        // Set the default video API to SDL
        m_instance->setRenderMode(GP2DWindow::GP2D_OPENGL);
    }

    // and return it.
    return m_instance;
}

/**
 * Create a window instance. Done by using GP2DWindow::getInstance().
 */
GP2DWindow::GP2DWindow() :
        m_fullScreen(false),
        m_bgColor(NULL),
        m_surfaceScreen(NULL) {

    m_videoAPI = GP2DWindow::GP2D_OPENGL; // defaults to opengl rendering, rox more.
}

/**
 * Destructor. Deletes some resources occupied by this object.
 */
GP2DWindow::~GP2DWindow() {
    SDL_FreeSurface(m_surfaceScreen);
}

/**
 * Toggles fullscreen mode on, or off. Internally, a bool will be set stating
 * whether the screen is currently in fullscreen mode.
 */
void GP2DWindow::toggleFullScreen() throw(GP2DException) {
    m_fullScreen = !m_fullScreen; // flip the fullscreen boolean indication
    if(m_surfaceScreen != NULL) {
        SDL_WM_ToggleFullScreen(m_surfaceScreen);
    } else {
        throw GP2DException("Fullscreen toggle failed");
    }
}

/**
 * Returns the height of the window.
 */
int GP2DWindow::getHeight() const {
    return m_screenHeight;
}

/**
 * Returns the width of the window.
 */
int GP2DWindow::getWidth() const {
    return m_screenWidth;
}

/**
 * Returns the screen surface (used for the SDL rendering mode and the blitting routine)
 */
SDL_Surface* GP2DWindow::getSurface() {
    return m_surfaceScreen;
}

void GP2DWindow::setBackgroundColor(GP2DColor* color) {
    m_bgColor = color;
}

/**
 * Input grabbing of events.
 */
void GP2DWindow::setInputGrabEnabled(bool enabled) {
    if(enabled) {
        SDL_WM_GrabInput(SDL_GRAB_ON);
    } else {
        SDL_WM_GrabInput(SDL_GRAB_OFF);
    }
}


/**
 * Graphic defaults. Can be called at any time.
 */
void GP2DWindow::setGraphicsDefaults() {
    if(m_videoAPI == GP2D_SDL){
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
void GP2DWindow::setWindowTitle(string title) {
    SDL_WM_SetCaption(title.c_str(), NULL);
}

/**
 * Sets the no-frame flag.
 */
void GP2DWindow::setFlagNoFrame() {
    m_videoFlags |= SDL_NOFRAME;
}

/**
 * Sets resizable flag.
 */
void GP2DWindow::setFlagResizable() {
    m_videoFlags |= SDL_RESIZABLE;
}


/**
 * Clear the screen.
 */
void GP2DWindow::clearScreen() {
    GP2DWindow* window = GP2DWindow::getInstance();
    if(window->getRenderMode() == GP2DWindow::GP2D_SDL){
        gp2dByte r, g, b;
        if(m_bgColor == NULL) {
            r = g = b = 0;
        } else {
            r = m_bgColor->r;
            g = m_bgColor->g;
            b = m_bgColor->b;
        }
        gp2dUint32 bgcolor = SDL_MapRGB(m_surfaceBackground->format, r, g, b);
        SDL_FillRect(m_surfaceBackground, 0, bgcolor);
        SDL_BlitSurface(m_surfaceBackground, NULL, window->getSurface(), NULL);
    } else {
        gp2dFloat r, g, b, a;
        if(m_bgColor == NULL) {
            r = g = b = 0.0f;
            a = 1.0f;
        } else {
            r = static_cast<gp2dFloat>(m_bgColor->r) / 0xFF;
            g = static_cast<gp2dFloat>(m_bgColor->g) / 0xFF;
            b = static_cast<gp2dFloat>(m_bgColor->b) / 0xFF;
            a = static_cast<gp2dFloat>(m_bgColor->a) / 0xFF;
        }
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT */);
    }
}

/**
 * Synchronize buffers.
 */
void GP2DWindow::sync() {
    GP2DWindow* window = GP2DWindow::getInstance();
    if(window->getRenderMode() == GP2DWindow::GP2D_SDL){
        SDL_UpdateRect(window->getSurface(),0,0,0,0);
    } else {
        glFlush(); // Force execution of GL commands in finite time using
        SDL_GL_SwapBuffers(); // swap the buffers.
    }
}

/**
 * Check the status of the window if it is opened or not.
 */
bool GP2DWindow::isCreated() {
    return m_surfaceScreen != NULL;
}

/**
 * Does the actual work. Will throw an exception if GP2DEngine::initVideo() or
 * GP2DEngine::initAll() was not called first.
 */
void GP2DWindow::createWindow(int width, int height, int bpp) throw(GP2DException) {
    const SDL_VideoInfo* m_videoInfo = SDL_GetVideoInfo();

    if(m_videoInfo == NULL) {
        throw GP2DException("Unable to create a window: video was not initialized.");
    }

    if(m_videoAPI == GP2D_SDL){
        m_videoFlags = SDL_DOUBLEBUF | SDL_HWPALETTE; // set default flags for SDL only
    } else {
        m_videoFlags = SDL_OPENGL | SDL_HWPALETTE; // set default flags for
                                                   // OpenGL
    }

    // check to see if a surface can be stored in mem:
    if (m_videoInfo->hw_available) {
        m_videoFlags |= SDL_HWSURFACE;
    } else {
        m_videoFlags |= SDL_SWSURFACE;
    }

    // check to see if hardware blits can be done
    if (m_videoInfo->blit_hw) {
        m_videoFlags |= SDL_HWACCEL;
    }

    if(m_videoAPI == GP2D_SDL){
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
            throw GP2DException("Video framebuffer surface could not be created", SDL_GetError());
        }

        if(m_videoAPI == GP2D_SDL){
            m_surfaceBackground = SDL_CreateRGBSurface(SDL_HWSURFACE, m_screenWidth, m_screenHeight, m_screenDepth, 0, 0, 0, 0);
        }

    } else {
        // video mode here is not supported. Throw up an exception so we know
        // it is not supported.
        stringstream s;
        s << "Video mode " << width << "x" << height << "x" << bpp
          << " is not supported. Bitmask video flags: " << m_videoFlags;
        throw GP2DException(s.str());
    }

}

/*
 * Changes the rendering API to use.
 */
void GP2DWindow::setRenderMode(const GP2DRenderMode mode) {
    m_videoAPI = mode;
}

/*
 * Returns the current rendering API.
 */
GP2DWindow::GP2DRenderMode GP2DWindow::getRenderMode() const {
    return m_videoAPI;
}

//==============================================================================

/**
 * Create!
 */
GP2DCamera::GP2DCamera() {
    // lastly, update the camera.
    updateCamera();
}

/**
 * Destroy!
 */
GP2DCamera::~GP2DCamera() {
}

/**
 * Updates our camera.
 */
void GP2DCamera::updateCamera() throw(GP2DException) {
}
/**
 * Set range.
 */
void GP2DCamera::setRange(gp2dDouble range) {
    m_range = range;
}

/**
 * Get range.
 */
gp2dDouble GP2DCamera::getRange() const {
    return m_range;
}

/**
 * Sets x, y positions.
 */
void GP2DCamera::setPosition(gp2dFloat x, gp2dFloat y) {
    m_posX = x;
    m_posY = y;
    updateCamera();
}

gp2dFloat GP2DCamera::getX() const {
    return m_posX;
}

gp2dFloat GP2DCamera::getY() const {
    return m_posY;
}

//==============================================================================

GP2DGameCamera::GP2DGameCamera(gp2dDouble range) throw (GP2DException) {
    if(range < 0) {
        // if the default of lower than zero is applied, get the window height, divide
        // it by 2 and use that as a range.
        GP2DWindow* window = GP2DWindow::getInstance();
        if(window == NULL) {
            throw GP2DException("No GP2DWindow instance found");
        } else {
            // window can be not null, but still not created.
            if(!window->isCreated()) {
                throw GP2DException("GP2DWindow can not be allocated (is it created?)");
            }

            range = static_cast<gp2dDouble>(window->getHeight() / 2);
        }
    }

    setRange(range);
}

void GP2DGameCamera::updateCamera() throw (GP2DException) {
    GP2DWindow* window = GP2DWindow::getInstance();
    if(window->getRenderMode() == GP2DWindow::GP2D_SDL){

    } else {
        if(!window->isCreated()) {
            // well, the window cannot be allocated. Be sure to notify the
            // programmer by throwing an exception.
            throw GP2DException("GP2DWindow can not be allocated (is it created?)");
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

GP2DGuiCamera::GP2DGuiCamera() throw (GP2DException) :
        m_rangeLeft(0),
        m_rangeRight(100),
        m_rangeTop(100),
        m_rangeBottom(0) {

}

void GP2DGuiCamera::updateCamera() throw (GP2DException) {
    GP2DWindow* window = GP2DWindow::getInstance();
    if(window->getRenderMode() == GP2DWindow::GP2D_SDL){

    } else {
        if(!window->isCreated()) {
            // well, the window cannot be allocated. Be sure to notify the
            // programmer by throwing an exception.
            throw GP2DException("GP2DWindow can not be allocated (is it created?)");
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, window->getWidth(), window->getHeight());
        glOrtho(m_rangeLeft, m_rangeRight, m_rangeBottom, m_rangeTop, -1.0, 1.0);
    }
}

void GP2DGuiCamera::setDefaults() throw (GP2DException) {
    GP2DWindow* window = GP2DWindow::getInstance();
    if(!window->isCreated()) {
        // well, the window cannot be allocated. Be sure to notify the
        // programmer by throwing an exception.
        throw GP2DException("GP2DWindow can not be allocated (is it created?)");
    }

    m_rangeLeft = 0;
    m_rangeRight = window->getWidth();
    m_rangeBottom = 0;
    m_rangeTop = window->getHeight();
}

//==============================================================================

GP2DDirector::GP2DDirector(GP2DCamera* gamecam, GP2DCamera* guicam) :
        m_gamecam(gamecam),
        m_guicam(guicam),
        m_flag(true) {
}

GP2DDirector::~GP2DDirector() {
}

void GP2DDirector::useGameCamera() {
    if(!m_flag) {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        m_gamecam->updateCamera();

        m_flag = false;
    }
}

void GP2DDirector::useGuiCamera() {
    if(m_flag) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        m_guicam->updateCamera();

        m_flag = true;
    }
}

//==============================================================================

GP2DTexture::GP2DTexture () throw (GP2DException) {
    GP2DWindow* window = GP2DWindow::getInstance();
    Uint8 bpp = window->getSurface()->format->BitsPerPixel;
    SDL_Surface* surf = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, 256, 256, bpp, 0, 0, 0, 0);
    if (surf == NULL) {
        throw GP2DException("Unable to create an empty RGB 256x256 surface", SDL_GetError());
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
}

GP2DTexture::GP2DTexture(string file) throw(GP2DException) {
    m_texName = file;
    m_textureRepeatX = 1.0f;
    m_textureRepeatY = 1.0f;
    m_textureOffsetX = 0.0f;
    m_textureOffsetY = 0.0f;

    GP2DWindow* window = GP2DWindow::getInstance();
    SDL_Surface* surf = IMG_Load(file.c_str());
    if(surf != NULL) {
        if(window->getRenderMode() == GP2DWindow::GP2D_SDL){
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

            clog << "Texture loaded: " << file << ", "
                 << m_width  << "x" << m_height << endl;
        } else {

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
        }
    } else {
        // Something bad happened. IMG_GetError probably returns some useful
        // information, so throw an exception indicating the problem. It might
         // for instance be a file which can not be found.
        throw GP2DException("Texture creation failed", IMG_GetError());
    }

}

/**
 * Deletes texture resources.
 */
GP2DTexture::~GP2DTexture() {
    GP2DWindow* window = GP2DWindow::getInstance();
    if(window->getRenderMode() == GP2DWindow::GP2D_SDL){
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

unsigned int GP2DTexture::getId() const {
    return m_texID;
}

string GP2DTexture::getName() const {
    return m_texName;
}

float GP2DTexture::getWidth() const {
    return m_width;
}

float GP2DTexture::getHeight() const {
    return m_height;
}

GLfloat GP2DTexture::getTextureRepeatX() const {
    return m_textureRepeatX;
}

GLfloat GP2DTexture::getTextureRepeatY() const {
    return m_textureRepeatY;
}

void GP2DTexture::setTextureRepeatX(GLfloat value) {
    m_textureRepeatX = value;
}

void GP2DTexture::setTextureRepeatY(GLfloat value) {
    m_textureRepeatY = value;
}

GLfloat GP2DTexture::getTextureOffsetX() const {
    return m_textureOffsetX;
}

GLfloat GP2DTexture::getTextureOffsetY() const {
    return m_textureOffsetY;
}

void GP2DTexture::setTextureOffsetX(GLfloat value) {
    m_textureOffsetX = value;
}

void GP2DTexture::setTextureOffsetY(GLfloat value) {
    m_textureOffsetY = value;
}

void* GP2DTexture::getPixels() {
    return m_pixels;
}


SDL_Surface* GP2DTexture::getSurface() {
    return m_surface;
}

bool GP2DTexture::isPowerOfTwo() {
    return m_isPowerOfTwo;
}

/**
 * Changes the texture's surface.
 */
void GP2DTexture::setSurface(SDL_Surface* surf) {
    if(surf == NULL) {
        cerr << "GP2DTexture::setSurface() : surface was NULL" << endl;
        return;
    }

    if(m_surface != NULL) {
        // free the m_surface first before initializing another. This fixes a
        // memory leak, especially with the GP2DText class. It would increase
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

GP2DRect::GP2DRect(gp2dFloat xx, gp2dFloat yy, gp2dFloat ww, gp2dFloat hh) :
        x(xx),
        y(yy),
        w(ww),
        h(hh) {
}

GP2DRect::~GP2DRect() {
}

//==============================================================================

GP2DColor::GP2DColor(gp2dByte red, gp2dByte green, gp2dByte blue, gp2dByte alpha) :
    r(red),
    g(green),
    b(blue),
    a(alpha) {
}

GP2DColor::GP2DColor(const GP2DColor& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
}

GP2DColor GP2DColor::operator +(const GP2DColor& color) {
    return GP2DColor(r + color.r, g + color.g, b + color.b, a + color.a);
}

GP2DColor GP2DColor::operator -(const GP2DColor& color) {
    return GP2DColor(r - color.r, g - color.g, b - color.b, a - color.a);
}

GP2DColor GP2DColor::operator ^(const GP2DColor& color) {
    return GP2DColor(r ^ color.r, g ^ color.g, b ^ color.b, a ^ color.a);
}

GP2DColor GP2DColor::brighter() const {
    GP2DColor newone = *this;
    // be sure to clamp the maximum color value to 0xFF positive.
    newone.r = ((newone.r + 0x10) > 0xFF ? 0xFF : newone.r + 0x10);
    newone.g = ((newone.g + 0x10) > 0xFF ? 0xFF : newone.g + 0x10);
    newone.b = ((newone.b + 0x10) > 0xFF ? 0xFF : newone.b + 0x10);

    return newone;
}

GP2DColor GP2DColor::darker() const {
    GP2DColor newone = *this;
    // be sure to clamp the maximum color value to 0xFF positive.
    newone.r = ((newone.r - 0x10) < 0x00 ? 0x00 : newone.r - 0x10);
    newone.g = ((newone.g - 0x10) > 0x00 ? 0x00 : newone.g - 0x10);
    newone.b = ((newone.b - 0x10) > 0x00 ? 0x00 : newone.b - 0x10);

    return newone;
}


const GP2DColor GP2DColor::GP2D_COLOR_WHITE   = GP2DColor(                );
const GP2DColor GP2DColor::GP2D_COLOR_BLACK   = GP2DColor(0x00, 0x00, 0x00);
const GP2DColor GP2DColor::GP2D_COLOR_RED     = GP2DColor(0xFF, 0x00, 0x00);
const GP2DColor GP2DColor::GP2D_COLOR_GREEN   = GP2DColor(0x00, 0xFF, 0x00);
const GP2DColor GP2DColor::GP2D_COLOR_BLUE    = GP2DColor(0x00, 0x00, 0xFF);


//==============================================================================

/**
 * GP2DObject constructor.
 */
GP2DObject::GP2DObject() {
    m_x = 0.0f; // initialize the coordinates and all that to 0.0f.
    m_y = 0.0f;
    m_z = 0.0f;

    init();
}

GP2DObject::GP2DObject(float x, float y) {
    m_x = x;
    m_y = y;
    m_z = 0.0f;

    init();
}

GP2DObject::GP2DObject(float x, float y, float z) {
    m_x = x;
    m_y = y;
    m_z = z;

    init();
}

/**
 * Destroy the object. Virtual destructor.
 */
GP2DObject::~GP2DObject() {
    clearBoundingBoxes();
}

/**
 * Do some initializing here of local class members.
 */
void GP2DObject::init() {
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

float GP2DObject::getX() const {
    return m_x;
}
float GP2DObject::getY() const {
    return m_y;
}
float GP2DObject::getZ() const {
    return m_z;
}
float GP2DObject::getWidth() const {
    return m_width;
}
float GP2DObject::getHeight() const {
    return m_height;
}
float GP2DObject::getVelocity_X() const {
    return m_x_velocity;
}
float GP2DObject::getVelocity_Y() const {
    return m_y_velocity;
}
float GP2DObject::getRotation_X() const {
    return m_angle_X;
}
float GP2DObject::getRotation_Y() const {
    return m_angle_Y;
}
float GP2DObject::getRotation_Z() const {
    return m_angle_Z;
}
float GP2DObject::getRotCenter_X() const {
    return m_RotCenter_X;
}
float GP2DObject::getRotCenter_Y() const {
    return m_RotCenter_Y;
}
float GP2DObject::getRotCenter_Z() const {
    return m_RotCenter_Z;
}

/*
 * Shitload of setter methods right here.
 */

void GP2DObject::setX(float x) {
    m_x = x;
}
void GP2DObject::setY(float y) {
    m_y = y;
}
void GP2DObject::setZ(float z) {
    m_z = z;
}
void GP2DObject::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
}
void GP2DObject::setWidth(float w) {
    m_width = w;
}
void GP2DObject::setHeight(float h) {
    m_height = h;
}
void GP2DObject::setSize(float w, float h) {
    m_width = w;
    m_height = h;
}

void GP2DObject::setVelocity_X(float xvel) {
    m_x_velocity = xvel;
}
void GP2DObject::setVelocity_Y(float yvel) {
    m_y_velocity = yvel;
}
void GP2DObject::setRotation_X(float angle) {
    m_angle_X = angle;
}
void GP2DObject::setRotation_Y(float angle) {
    m_angle_Y = angle;
}
void GP2DObject::setRotation_Z(float angle) {
    m_angle_Z = angle;
}
void GP2DObject::setRotCenter_X(float a_X) {
    m_RotCenter_X = a_X;
}
void GP2DObject::setRotCenter_Y(float a_Y) {
    m_RotCenter_Y = a_Y;
}
void GP2DObject::setRotCenter_Z(float a_Z) {
    m_RotCenter_Z = a_Z;
}
void GP2DObject::setRotCenter(float a_x,float a_y,float a_z) {
    m_RotCenter_X = a_x;
    m_RotCenter_Y = a_y;
    m_RotCenter_Z = a_z;
}
vector<GP2DRect>& GP2DObject::getBoundingBoxes() {
    return m_boundingBoxes;
}
void GP2DObject::clearBoundingBoxes() {
    m_boundingBoxes.clear();
}
void GP2DObject::addBoundingBox(GP2DRect rect) {
    m_boundingBoxes.push_back(rect);
}

//==============================================================================

GP2DSprite::GP2DSprite() :
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

GP2DSprite::GP2DSprite(GP2DTexture* texture) :
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

int GP2DSprite::addTexture(GP2DTexture* texture) {
    m_textures.push_back(texture);
    m_texture = m_textures[m_textures.size()-1];

    setWidth(m_texture->getWidth());
    setHeight(m_texture->getHeight());

    // Just to have the rotation be around the center of the image by default
    // (TODO: will need to be adapted for spritesheets)
    this->setRotCenter(m_texture->getWidth() / 2.0, -m_texture->getHeight() / 2.0, 0);
    return m_textures.size()-1;
}

void GP2DSprite::useTexture(unsigned int value) {
    if(value >= 0 && value <= m_textures.size() - 1) {
        m_texture = m_textures[value];
    }
}

GP2DSprite::~GP2DSprite() {
    // not much to delete here by default, especially not the
    // GP2DTexture instance, because it can be used by other sprites.
}

GP2DTexture* GP2DSprite::getTexture() const {
    return m_texture;
}

gp2dInt32 GP2DSprite::createAnim(gp2dInt32 framesWidth, gp2dInt32 framesHeight, gp2dInt32 orgx, gp2dInt32 orgy, gp2dInt32 width, gp2dInt32 height) {
    for(int fy = 0; fy <= framesHeight; fy++) {
        for(int fx = 0; fx <= framesWidth; fx++) {
            GP2DRect rect;
            rect.x = static_cast<gp2dFloat>(orgx + (fx * width)) / m_texture->getSurface()->w;
            rect.y = static_cast<gp2dFloat>(orgy + (fy * height)) / m_texture->getSurface()->h;
            rect.w = (static_cast<gp2dFloat>(orgx + (fx * width)) + static_cast<gp2dFloat>(width)) / m_texture->getSurface()->w;
            rect.h = (static_cast<gp2dFloat>(orgy + (fy * height)) + static_cast<gp2dFloat>(height)) / m_texture->getSurface()->h;

            m_animRects.push_back(rect);
        }
    }

    m_anim_frames = m_animRects.size()-1;
    m_anim_frameEnd = m_anim_frames;

    return m_anim_frameEnd;
}

gp2dInt32 GP2DSprite::createAnimFrame(gp2dInt32 x, gp2dInt32 y, gp2dInt32 width, gp2dInt32 height) {
    GP2DRect rect;
    rect.x = static_cast<gp2dFloat>(x / m_texture->getSurface()->w);
    rect.y = static_cast<gp2dFloat>(y / m_texture->getSurface()->h);
    rect.w = static_cast<gp2dFloat>((x + static_cast<gp2dFloat>(width)) / m_texture->getSurface()->w);
    rect.h = static_cast<gp2dFloat>((y + static_cast<gp2dFloat>(height)) / m_texture->getSurface()->h);

    m_animRects.push_back(rect);
    m_anim_frames = m_animRects.size()-1;
    m_anim_frameEnd = m_anim_frames;

    return m_anim_frameEnd;

}

gp2dInt32 GP2DSprite::getFrame() {
    return m_anim_frame;
}

gp2dInt32 GP2DSprite::getFrames() {
    return m_animRects.size() -1 ;
}

void GP2DSprite::setAnimRange(gp2dInt32 start, gp2dInt32 end) {
    m_anim_frameStart = start;
    m_anim_frameEnd   = end;

    if(m_anim_frame > m_anim_frameEnd) {
        m_anim_frame = m_anim_frameEnd;
    }

    if(m_anim_frame < m_anim_frameStart) {
        m_anim_frame = m_anim_frameStart;
    }
}

void GP2DSprite::setAnimBackwards(gp2dBool val){
    m_anim_backwards = true;
}

void GP2DSprite::setAnimFrame(gp2dInt32 frame) {
    if (frame<0){ frame=0; }
    m_anim_frame = frame;
}

void GP2DSprite::setAnimNextFrame() {
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

void GP2DSprite::setAnimLoop(gp2dBool val) {
    m_anim_loop = val;
}

void GP2DSprite::draw() {

    GP2DWindow* window = GP2DWindow::getInstance();
    if(window->getRenderMode() == GP2DWindow::GP2D_SDL){

        setX(getX() + getVelocity_X());
        setY(getY() + getVelocity_Y());

        /* FIXME: azzkikr: I commented this because I changed the camera stuff.
         * Please somebody check out this later (DARKGuy?) to fix this back. The
         * reason I commented this out, is because I changed the way the camera
         * functions. I made GP2DCamera a virtual base class, and created two other
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
        gp2dBool isPowerOfTwo = getTexture()->isPowerOfTwo();
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

        // set the x and y positions based on the current velocity.
        setX(getX() + getVelocity_X());
        setY(getY() - getVelocity_Y());

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

            glTexCoord2f(x1, y1); glVertex3f(0, 0, getZ());
            glTexCoord2f(x1, y2); glVertex3f(0, 0 - getHeight(), getZ());
            glTexCoord2f(x2, y2); glVertex3f(0 + getWidth(), 0 - getHeight(), getZ());
            glTexCoord2f(x2, y1); glVertex3f(0 + getWidth(), 0, getZ());

        glEnd();

        glDisable(textureMode); // either GL_TEXTURE_2D or GL_TEXTURE_RECTANGLE_NV
        glDisable(GL_BLEND);

    }
}


void GP2DSprite::setAlpha(GLfloat alpha) {
    m_alpha = alpha;
}

GLfloat GP2DSprite::getAlpha() const {
    return m_alpha;
}

Uint8 GP2DSprite::getSurfaceAlpha(SDL_Surface* surface, int x, int y) const {
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

void GP2DSprite::computeEdges() {
    GP2DTexture* tex = m_texture;
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
                    GP2DRect rect(x, -y, 1, 1);
                    addBoundingBox(rect);
                }
            }
        }
    }

    // ... and unlock it when we are done with it!
    SDL_UnlockSurface(surface);
}

//==============================================================================

GP2DCursor::GP2DCursor() {
}

GP2DCursor::GP2DCursor(GP2DTexture* tex) {
    addTexture(tex);
}

GP2DCursor::~GP2DCursor() {

}

gp2dBool GP2DCursor::isDefPointerVisible() {
    return SDL_ShowCursor(-1);
}

void GP2DCursor::setDefPointerVisible(gp2dBool enabled) {
    SDL_ShowCursor(enabled);
}

void GP2DCursor::updatePosition() throw (GP2DException) {
    GP2DWindow* window = GP2DWindow::getInstance();
    if(window == NULL) {
        throw GP2DException("GP2DWindow instance was NULL");
    } else {
        if(!window->isCreated()) {
            throw GP2DException("GP2DWindow is not created!");
        } else {
            // Make use of the static functions GP2DInputHandler
            // provides, to just get the mouse position without
            // the need of registering an event with the input
            // handler, just to get the mouse position.
            gp2dFloat x, y;
            x = GP2DInputHandler::getMousePosition().x;
            y = GP2DInputHandler::getMousePosition().y;
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
        //if(a>0) exit(102);
        return ( true );
    }

} // namespace gp2d

