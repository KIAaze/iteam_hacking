#ifndef _GP_GRAPHICS_H_
#define _GP_GRAPHICS_H_

#include <GL/gl.h>
#include <GL/glext.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <algorithm>
#include <string>
#include "core.h"

namespace gp {

// Forward declarations.
class GPTexture;
class GPCamera;
class GPRect;
class GPColor;

/**
 * This class is basically what has properties to set up and build a window
 * to draw things on.
 *
 * @author krpors
 * @author DARKGuy
 */
class GPWindow {
protected:
    /// The only instance pointer, for singleton purposes.
    static GPWindow* m_instance;

public:
    /**
     * Gets the one and only instance of the GPWindow.
     *
     * @return A pointer to a GPWindow which is guaranteed to be the only
     *   instance.
     */
    static GPWindow* getInstance();

    /**
     * The rendering types. Basically there are two of them only, SDL rendering
     * and OpenGL rendering.
     */
    enum GPRenderMode {
        GP_SDL,
        GP_OPENGL
    };

    /**
     * Destroys the GPWindow.
     */
    ~GPWindow(void);

    /**
     * Gets the width of the window, as set by createWindow(int, int, int).
     *
     * @return The width of the window as an integer.
     */
    int getWidth() const;

    /**
     * Gets the height of the window, as set by createWindow(int, int, int).
     *
     * @return The height of the window as an integer.
     */
    int getHeight() const;

    /**
     * Gets the screen surface, used only by the SDL drawing routines.
     *
     * @return The SDL screen surface as a pointer.
     */
    SDL_Surface* getSurface();

    /**
     * Gets the background surface, used only by the SDL drawing routines for
     * clearing the back buffer with.
     *
     * @return The SDL background surface as a pointer.
     */
    SDL_Surface* getBackground();

    /**
     * Sets the background color when clearing the screen (the color buffer bit
     * in OpenGL speek).
     *
     * @param color The background color.
     */
    void setBackgroundColor(GPColor* color);

    /**
     * Sets whether the window should grab the input. That means the mouse and
     * keyboard presses will only occur in the context of the window. That also
     * means the mouse can not leave the window.
     *
     * @param enabled true if the window should grab the input, false if
     *   otherwise.
     */
    void setInputGrabEnabled(bool enabled);

    /**
     * Sets the title of the window.
     *
     * @param title The new window title.
     */
    void setWindowTitle(std::string title);

    /**
     * Sets the basic graphic defaults (OpenGL enablings and such).
     */
    void setGraphicsDefaults();

    /**
     * Sets an internal flag which disables a surrounding window manager frame.
     *
     * This is a pre-set flag which must be set BEFORE calling the function
     * createWindow(int, int, int).
     */
    void setFlagNoFrame();

    /**
     * Sets an internal flag which sets the window to enable resizing, manually
     * by the user. Meaning dragging the window 'edge' to make the window bigger,
     * or smaller.
     *
     * This is a pre-set flag which must be set BEFORE calling the function
     * createWindow(int, int, int).
     */
    void setFlagResizable();

    /**
     * Toggles the window to fullscreen, or not fullscreen.
     *
     * @throws GPException when the fullscreen could not be toggle, because
     *   the screen surface was not initialized by invoking
     *   GPWindow::createWindow(int, int, int).
     */
    void toggleFullScreen() throw (GPException);

    /**
     * Clears the screen with the clearing color.
     */
    void clearScreen();
    // void clearScreen(GPColor& color);

    /**
     * Synchronizes buffers, i.e. swaps the buffers.
     */
    void sync();


    void setRenderMode(const GPRenderMode mode);

    /**
     * Gets the current video API to use.
     */
    GPRenderMode getRenderMode() const;

    /**
     * If the window is created using GPWindow::createWindow(int, int, int),
     * then a surface from the underlying SDL API is created. A check is made
     * whether it is NULL. If NULL, false will be returned. Otherwise, true
     * will be returned, indicating that the user of the API has created a
     * window already.
     *
     * @return true when the window is created, false if otherwise.
     */
    bool isCreated();

    /**
     * Actually creates the window, provided the GPEngine is initialized
     * fully. If the video engine is not initialized, it will throw a
     * GPException. Therefore, you need to call GPEngine::initVideo() or
     * GPEngine::initAll() before calling this function.
     *
     * @param width The preferred width.
     * @param height The preferred height.
     * @param bpp The amount of bits per pixel (2, 8, 16, 24, 32)
     * @throws GPException when the GPEngine video subsystem was not
     *   initialized. Can also be thrown when the video mode was tried to be
     *   opened, but not supported (like 64 bits per pixel).
     */
    void createWindow(int width, int height, int bpp) throw (GPException);

    /**
     * Creates a new camera for the current window. Each window can have a
     * (hopefully) infinite number of cameras. Be aware, that this will set
     * the new camera as the current one (by changing m_currentCamera) for the
     * next concurrent engine operations unless a setCamera() is used afterwards
	 * TODO: Write implementation.
     */
    void createNewCamera();

    /**
     * Returns a pointer to the current camera, by default it returns the
     * pointer of the newest camera created.
     *
     * @return a GPCamera pointer to the current camera.
	 * TODO: Write implementation.
     */
    GPCamera* getCamera() throw(GPException);

    /**
     * Returns a pointer to a specific camera, in relation to the window's
     * camera vector.
     *
     * @param num camera number in relation to the window's camera vector.
     * @return a GPCamera pointer to the specified camera.
	 * TODO: Write implementation.
     */
    GPCamera* getCamera(int num);

    /**
     * Sets the current camera to do various engine operations with. The
     * getCamera() function will use the value that we set here (instead of
     * the newest camera created).
	 * TODO: Write implementation.
     */
    void setCamera(int num);

    /// The vector with the loaded textures.
    std::vector<GPTexture*> m_textures;
	
	void addTexture(GPTexture* tex);

private:

    /// Boolean indicating whether fullscreen was toggled.
    bool m_fullScreen;

    /// The screen's width.
    int m_screenWidth;

    /// The screen's height.
    int m_screenHeight;

    /// The bitdepth of the window.
    int m_screenDepth;

    GPColor* m_bgColor;

    /// The SDL surface which is the screen.
    SDL_Surface* m_surfaceScreen;

    /// The SDL surface which is the background for clearing the back buffer
    /// with.
    SDL_Surface* m_surfaceBackground;

    /// Video flags, which are manipulated by setFlag...() functions.
    unsigned int m_videoFlags;

    /// Video API to use.
    GPRenderMode m_videoAPI;

    /**
     * Creates the GPWindow.
     */
    GPWindow(void);
};

//==============================================================================

/**
 * The GPCamera actually provides the usage of a viewport. It can be moved to
 * a different position, and can be 'zoomed' in and out by adjusting the range
 * of the camera.
 *
 * @author krpors
 */
class GPCamera {
protected:
    /// The x position of the camera.
    gpFloat m_posX;

    /// The y position of the camera.
    gpFloat m_posY;

    /// The range the camera should attend to.
    gpDouble m_range;

public:
    /**
     * Constructs a GPCamera.
     */
    GPCamera();

    /**
     * Destructor for the camera.
     */
    virtual ~GPCamera();

    /**
     * Updates the camera using the given range and position and all other
     * configurable options.
     *
     * @throws GPException when the parent window is not yet created.
     */
    virtual void updateCamera() throw(GPException);

    /**
     * Gets the camera range.
     *
     * @return The camera range.
     */
    gpDouble getRange() const;

    /**
     * Sets the range of the camera. To make things final after this, call
     * updateCamera().
     *
     * @param range The new range of the camera.
     */
    void setRange(gpDouble range);

    /**
     * Sets the x and y position of the camera.
     */
    void setPosition(gpFloat x, gpFloat y);

    /**
     * Gets camera x position.
     *
     * @return Position as a float.
     */
    gpFloat getX() const;

    /**
     * Gets camera y position.
     *
     * @return Position as a float.
     */
    gpFloat getY() const;
};

//==============================================================================

/**
 * The GPGameCamera is a derivative from the GPCamera. This subclass has the
 * basic logic for being used as a game camera (for the actual in-game display
 * of sprites) using an acceptable orthographic projection.
 *
 * Using the updateCamera() function, it selects the projection matrix to set up
 * a viewport and a orthographic projection. Using translation, the projection is
 * centered on the given x and y position, enabling to 'follow' a trail, path or
 * a certain point given by the user using the setX() and setY() functions.
 *
 * @author krpors
 */
class GPGameCamera : public GPCamera {
public:
    /**
     * Creates a game camera.
     *
     * @param range The range of the orthographic projection. Default value is
     * set to -1. This will cause the camera to use the GPWindow's height divided
     * by 2 as a range.
     *
     * @throws GPException When the GPWindow can not be allocated (because it
     * was probably not created).
     */
    GPGameCamera(gpDouble range = -1) throw (GPException);

    /**
     * Updates the camera positions using the necessary functions. It will for
     * instance set the viewport, orthographic project, and the x and y positions
     * of the camera.
     *
     * @throws GPException When the GPWindow can not be allocated (because it
     * was probably not created).
     */
    virtual void updateCamera() throw (GPException);
};

//==============================================================================

/**
 * The GPGuiCamera is a derivative of the GPCamera. This class has the basic
 * logic to set up an orthographic projection in such a way that it can be easily
 * used to 'project' user interface objects onto it. For instance, one can create
 * a GUI camera using good ranges (left, right, bottom and top - which will probably
 * be [0, window width, 0, window height] respectively) so you can draw a user
 * interface object within positive ranges.
 *
 * This class is different from the GPGameCamera because:
 *  - GPGuiCamera to be able to specify custom ranges in all four directions
 *  - It does not need to move around.
 */
class GPGuiCamera : public GPCamera {
private:
    gpDouble m_rangeLeft;
    gpDouble m_rangeRight;
    gpDouble m_rangeTop;
    gpDouble m_rangeBottom;

public:
    /**
     * Constructs the gui camera.
     *
     * @throws GPException When the GPWindow can not be allocated (because it
     * was probably not created).
     */
    GPGuiCamera() throw (GPException);

    /**
     * Updates the camera using the necessary functions. In contrast of the
     * GPGameCam, it does not translate the camera x,y position, only the
     * viewport and the orthographic project using the private member variables
     * for the ranges.
     *
     * @throws GPException When the GPWindow can not be allocated (because it
     * was probably not created).
     */
    virtual void updateCamera() throw (GPException);

    /**
     * Sets default camera dimensions using the GPWindow boundaries.
     *
     * @throw GPException When the GPWindow can not be allocated (because it
     * was probably not created).
     */
    void setDefaults() throw (GPException);
};

//==============================================================================

/**
 * The GPDirector is the class which handles the switching between the two
 * camera's: game and gui camera. Basically what it does is taking care of the
 * glPushMatrix and glPopMatrix, so the orthographic projections do not interfere
 * with each other.
 */
class GPDirector {
private:

    /// The game camera.
    GPCamera* m_gamecam;

    /// The gui camera.
    GPCamera* m_guicam;

    /// Flag to indicate which camera is used currently.
    gpBool m_flag;

public:
    /**
     * Creates the director using the given camera's.
     *
     * @param gamecam The camera used for the in-game view.
     * @param guicam The camera for the user interface objects.
     */
    GPDirector(GPCamera* gamecam, GPCamera* guicam);

    /**
     * Destructor.
     */
    ~GPDirector();

    /**
     * Sets the game camera as currently 'active', by popping the projection
     * matrix. The game camera is updated afterwards (through updateCamera()).
     */
    void useGameCamera();

    /**
     * Sets the GUI camera as currently 'active', by pushing the projection
     * matrix. The gui camera is updated afterwards (through updateCamera()).
     */
    void useGuiCamera();
};

//==============================================================================

/**
 * Simple point class.
 */
class GPPoint {
public:
    gpFloat x;
    gpFloat y;
};

//==============================================================================

/**
 * A simple rectangle, with values for an (x, y) coordinate and a width, height.
 * The members are declared public for simplicity.
 *
 *
 */
class GPRect {
public:
    gpFloat x;
    gpFloat y;
    gpFloat w;
    gpFloat h;

    /**
     * Creates a rectangle, (x,y)-(w,h).
     *
     * @param x The x coord.
     * @param y The y coord.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     */
    GPRect(gpFloat x = 0, gpFloat y = 0, gpFloat w = 1, gpFloat h = 1);

    /**
     * Destructor, doesn't do anything yet.
     */
    ~GPRect();

    /**
     * TODO: comment this later on today.
     */
    GPRect operator*(const gpFloat& f);
};

//==============================================================================

/**
 * The GPColor class is a simple encapsulation mechanism for r,g,b and alpha
 * coloring. The member vars are public read/write for convenience.
 */
class GPColor {
public:

    /// Red component, ranging from 0 - 255 (0x00 - 0xFF)
    gpByte r;

    /// Green component, ranging from 0 - 255 (0x00 - 0xFF)
    gpByte g;

    /// Blue component, ranging from 0 - 255 (0x00 - 0xFF)
    gpByte b;

    /// Alpha component, ranging from 0 - 255 (0x00 - 0xFF)
    gpByte a;

    /**
     * Creates a GPColor instance. Default values are r = g = b = a = 0xFF.
     * Thus, default is fully white, opaque.
     *
     * @param red The red component, 0 - 255.
     * @param green The green component, 0 - 255.
     * @param blue The blue component, 0 - 255.
     * @param alpha The alpha component, 0 - 255.
     */
    GPColor(gpByte red = 0xFF, gpByte green = 0xFF, gpByte blue = 0xFF, gpByte alpha = 0xFF);

    GPColor(const GPColor& color);

    GPColor operator+(const GPColor& color);
    GPColor operator-(const GPColor& color);
    GPColor operator^(const GPColor& color);

    /**
     * Creates a darker version of the current specified color. This is done by simply
     * subtracting 0x10 from every red, green and blue component. If one of these components
     * has already reached 0x00, nothing happens to that component.
     *
     * @return The new GPColor object, but a darker version of the current one.
     */
    GPColor darker() const;

    /**
     * Creates a brighter version of the current specified color. This is done by simply
     * adding 0x10 to every red, green and blue component. If one of these components
     * has already reached 0xFF, nothing happens to that component.
     *
     * @return The new GPColor object, but a brighter version of the current one.
     */
    GPColor brighter() const;

    /// The color white (0xFF, 0xFF, 0xFF, 0xFF).
    const static GPColor GP_COLOR_WHITE;

    /// The color black (0x00, 0x00, 0x00, 0xFF).
    const static GPColor GP_COLOR_BLACK;

    /// The color black (0xFF, 0x00, 0x00, 0xFF).
    const static GPColor GP_COLOR_RED;

    /// The color black (0x00, 0xFF, 0x00, 0xFF).
    const static GPColor GP_COLOR_GREEN;

    /// The color black (0x00, 0x00, 0xFF, 0xFF).
    const static GPColor GP_COLOR_BLUE;
};



//==============================================================================

/**
 * A GPTexture is a class responsible for loading a texture (a graphic) into
 * memory. It has the necessary functions to create texture from file, and
 * getting properties from it. Internally in the class, an SDL_Surface pointer
 * is kept which is the original 'source' of the raw pixel data.
 *
 * This pixel data can then be used to get pixel values, for instance to detect
 * collision.
 *
 * Generally, for each image you will want to load as a texture, you create only
 * one GPTexture object. For instance, you want to load a texture called
 * 'terrain.png', you will only need to make one GPTexture corresponding to
 * that texture file. If you don't do this, OpenGL will load the texture file
 * twice, consuming memory.
 *
 * TODO: In the future, something like a texture factory, or some kind of map
 * that holds all the generated textures so a choice can be made from it?
 *
 * @author krpors
 */
class GPTexture {
private:
    /// The texture ID. Internally used for OpenGL.
    unsigned int m_texID;

    /// The texture name. Might come in handy to name textures.
    std::string m_texName;

    /// The SDL surface.
    SDL_Surface* m_surface;

    /// Width of the texture.
    float m_width;

    /// Height of the texture.
    float m_height;

    /// Raw pixel data.
    void* m_pixels;

    /// XXX: I don't really think so if you have never seen OGL textures before :-)
    /// Pretty self explanatory
    GLfloat m_textureRepeatX;

    /// Pretty self explanatory
    GLfloat m_textureRepeatY;

    /// Pretty self explanatory
    GLfloat m_textureOffsetX;

    /// Pretty self explanatory
    GLfloat m_textureOffsetY;

    /// Boolean indicating whether the texture is power-of-two tex, or not.
    gpBool m_isPowerOfTwo;

public:
    /**
     * Creates an 'empty' GPTexture. A 256 x 256 surface will be created where
     * the content of the texture is based upon.
     *
     * @throws GPException if the texture cannot be created.
     */
    GPTexture() throw(GPException);

    /**
     * Creates a GPTexture off a filename. An exception is thrown if the file
     * cannot be loaded or some other reason SDL sees fit to.
     *
     * @param file The filename to load a texture for.
     * @throws GPException when the file cannot be loaded or something.
     */
    GPTexture(std::string file) throw(GPException);

    /**
     * Deletes the texture form memory, and the created SDL surface with it,
     * using SDL_FreeSurface().
     */
    ~GPTexture();
	
	void Generate();

    /**
     * Gets the ID of the texture, which is just an unsigned integer. The ID
     * is mapped by OpenGL.
     *
     * @return the texture id.
     */
    unsigned int getId() const;

    /**
     * Gets the texture's name. May be blank.
     *
     * @return the texture name.
     */
    std::string getName() const;

    /**
     * Returns the width of the texture.
     *
     * @return The width of the texture :)
     */
    float getWidth() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    float getHeight() const;
    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    GLfloat getTextureRepeatX() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    GLfloat getTextureRepeatY() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    void setTextureRepeatX(GLfloat value);

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    void setTextureRepeatY(GLfloat value);

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    GLfloat getTextureOffsetX() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    GLfloat getTextureOffsetY() const;

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    void setTextureOffsetX(GLfloat value);

    /**
     * Returns the height of the texture.
     *
     * @return The height, of course.
     */
    void setTextureOffsetY(GLfloat value);

    /**
     * Gets raw pixel data.
     * XXX: do not return a void* pointer, but something specialized (Uint32, Uint24, Uint16)...?
     */
    void* getPixels();

    /**
     * Changes the texture's surface, based on a new SDL_Surface pointer. This will
     * delete/free the previously set SDL_Surface* m_surface, and change it to the
     * given SDL_Surface pointer.
     *
     * If the surface is NULL, no operations will be invoked and the function will
     * simply return.
     *
     * TODO: set an assertion here?
     *
     * @param surface The new surface.
     */
    void setSurface(SDL_Surface* surface);

    /**
     * Gets the surface for direct access.
     */
    SDL_Surface* getSurface();

    /**
     * Returns either true or false if the texture is a Power-of-Two texture.
     *
     * @return true when the texture is a Power-of-Two texture, false if
     * otherwise.
     */
    gpBool isPowerOfTwo();

};

//==============================================================================

/**
 * Simply put, the GPObject is the base class to hold coordinatal data. You
 * could see it as the base of every sprite and all that in GP. It has a few
 * variables to indicate position: x, y, z, w, and h.
 *
 * Besides these variables, it has one interesting function, the virtual void
 * function GPObject::draw(). This function needs to be overridden by derived
 * classes so it knows how to draw itself.
 *
 * @author krpors
 */
class GPObject {
private:
    /// X position of the object.
    gpFloat m_x;

    /// Y position of the object.
    gpFloat m_y;

    /// Z position of the object.
    gpFloat m_z;

    /// The width of the object.
    gpFloat m_width;

    /// The height of the object.
    gpFloat m_height;

    /// The scale of the object on the X axis.
    gpFloat m_x_scale;

    /// The scale of the object on the Y axis.
    gpFloat m_y_scale;

    /// The scale of the object on the Z axis.
    gpFloat m_z_scale;

    /// The x position velocity.
    gpFloat m_x_velocity;

    /// The y position velocity.
    gpFloat m_y_velocity;

    /// Rotation around the X-axis.
    gpFloat m_angle_X;

    /// Rotation around the Y-axis.
    gpFloat m_angle_Y;

    /// Rotation around the Z-axis.
    gpFloat m_angle_Z;

    /// Rotation center X position.
    gpFloat m_RotCenter_X;

    /// Rotation center Y position.
    gpFloat m_RotCenter_Y;

    /// Rotation center Z position.
    gpFloat m_RotCenter_Z;

    /// The vector with the bounding boxes.
    std::vector<GPRect> m_boundingBoxes;

    /**
     * Basic initialization code for variables. Since there are 3 constructors,
     * repeating the same code is a bit tedious. The initialization of the local
     * class variables are initialized here.
     */
    void init();


public:
    /**
     * Creates a GPObject, will initialize the variables to 0.0f.
     */
    GPObject();

    /**
     * Creates a GPObject. This will initialiaze the x and y variables.
     *
     * @param x The x coord.
     * @param y The y coord.
     */
    GPObject(gpFloat x, gpFloat y);

    /**
     * Creates a GPObject, which will initialize the x, y and z variables.
     *
     * @param x The x coord.
     * @param y The y coord.
     * @param z The z coord.
     */
    GPObject(gpFloat x, gpFloat y, gpFloat z);

    /**
     * The virtual destructor.
     */
    virtual ~GPObject();

    /**
     * Gets the x position of the GPObject.
     * @return The x position. Negative goes to the left, positive goes to
     *   the right.
     */
    gpFloat getX() const;

    /**
     * Gets the x position of the GPObject.
     * @return The y position. Negative goes to the bottom, positive goes to
     *   up.
     */
    gpFloat getY() const;

    /**
     * Gets the z(depth) position of the GPObject.
     * @return The z position. Negative goes farther way back? Positive goes to
     *   farther way up front?
     */
    gpFloat getZ() const;

    /**
     * Gets the height of this object.
     * @return The height.
     */
    gpFloat getHeight() const;

    /**
     * Gets the width of this object.
     * @return The width.
     */
    gpFloat getWidth() const;

    /**
     * Gets the X scale of this object.
     * @return The X scale.
     */
    gpFloat getScale_X() const;

    /**
     * Gets the Y scale of this object.
     * @return The Y scale.
     */
    gpFloat getScale_Y() const;

    /**
     * Gets the Z scale of this object.
     * @return The Z scale.
     */
    gpFloat getScale_Z() const;

    /**
     * Gets the XYZ scales of this object.
     */
    void getScale(gpFloat& X, gpFloat& Y, gpFloat& Z) const;

    /**
     * Gets the x coordinate velocity of the object. When 0, it is static. When
     * negative, move the left, positive to the right.
     *
     * @return The horizontal movement (x velocity).
     */
    gpFloat getVelocity_X() const;

    /**
     * Gets the y coordinate velocity of the object. When 0, it is static. When
     * negative, move down, positive move up.
     *
     * @return The vertical movement (y velocity).
     */
    gpFloat getVelocity_Y() const;

    /**
     * Gets the rotation angle around the X axis.
     *
     * @return The rotation angle of the GPObject around the X axis.
     */
    gpFloat getRotation_X() const;

    /**
     * Gets the rotation angle around the Y axis.
     *
     * @return The rotation angle of the GPObject around the Y axis.
     */
    gpFloat getRotation_Y() const;

    /**
     * Gets the rotation angle around the Z axis.
     *
     * @return The rotation angle of the GPObject around the Z axis.
     */
    gpFloat getRotation_Z() const;

    /**
     * Gets the rotation center X position.
     *
     * @return The rotation center X position.
     */
    gpFloat getRotCenter_X() const;

    /**
     * Gets the rotation center Y position.
     *
     * @return The rotation center Y position.
     */
    gpFloat getRotCenter_Y() const;

    /**
     * Gets the rotation center Z position.
     *
     * @return The rotation center Z position.
     */
    gpFloat getRotCenter_Z() const;

    /**
     * Set the x coordinate.
     * @param x The x coord. Negative to go to the left, positive to go to the
     *  right.
     */
    void setX(gpFloat x);

    /**
     * Set the y coordinate.
     * @param y The y coord. Negative to go to down, positive to go up.
     */
    void setY(gpFloat y);

    /**
     * Set the z coordinate.
     * @param z The z coord. Negative to go to the back, positive to go to the
     *  front.
     */
    void setZ(gpFloat z);

    /**
     * Shorthand function for setting x and y positions of the GPObject.
     * @param x The x position.
     * @param y The y position.
     */
    void setPosition(gpFloat x, gpFloat y);

    /**
     * Set the width.
     * @param w The width of the object.
     */
    void setWidth(gpFloat w);

    /**
     * Set the height.
     * @param h The height of the object0r.
     */
    void setHeight(gpFloat h);

    /**
     * Set the X scale.
     * @param s The X scale.
     */
    void setScale_X(gpFloat s);

    /**
     * Set the Y scale.
     * @param s The Y scale.
     */
    void setScale_Y(gpFloat s);

    /**
     * Set the Z scale.
     * @param s The Z scale.
     */
    void setScale_Z(gpFloat s);

    /**
     * Set the XYZ scales.
     * @param sX The X scale.
     */
    void setScale(gpFloat sX, gpFloat sY, gpFloat sZ);

    /**
     * Set the width and height.
     * @param w The height of the object0r.
     * @param h The height of the object0r.
     */
    void setSize(gpFloat w, gpFloat h);

    /**
     * Sets the x coordinate velocity of the object. When 0, it is static. When
     * negative, move the left, positive to the right.
     *
     * @param xvel The velocity, horizontally.
     */
    void setVelocity_X(gpFloat xvel);

    /**
     * Sets the y coordinate velocity of the object. When 0, it is static. When
     * negative, move to the bottom, positive move upwards.
     *
     * @param yvel The velocity, vertically.
     */
    void setVelocity_Y(gpFloat yvel);

    /**
     * Sets the rotation angle of the GPObject around the X axis.
     *
     * @param angle The rotation angle.
     */
    void setRotation_X(gpFloat angle);

    /**
     * Sets the rotation angle of the GPObject around the Y axis.
     *
     * @param angle The rotation angle.
     */
    void setRotation_Y(gpFloat angle);

    /**
     * Sets the rotation angle of the GPObject around the Z axis.
     *
     * @param angle The rotation angle.
     */
    void setRotation_Z(gpFloat angle);

    /**
     * Sets the rotation center X position.
     *
     * @param angle The rotation center X position.
     */
    void setRotCenter_X(gpFloat a_X);

    /**
     * Sets the rotation center Y position.
     *
     * @param angle The rotation center Y position.
     */
    void setRotCenter_Y(gpFloat a_Y);

    /**
     * Sets the rotation center Z position.
     *
     * @param angle The rotation center Z position.
     */
    void setRotCenter_Z(gpFloat a_Z);

    /**
     * Sets the rotation center for all rotations
     *
     * @param a_x The rotation center X position
     * @param a_y The rotation center Y position
     * @param a_z The rotation center Z position
     */
    void setRotCenter(gpFloat a_x,gpFloat a_y,gpFloat a_z);

    /**
     * Adds a bounding box (a GPRect) to the GPObject.
     *
     * @param rect A copy of the rect object to add.
     */
    void addBoundingBox(GPRect rect);

    /**
     * Clear up the vector holding the bounding boxes. This creates
     * a delegate call to m_boundingBoxes.clear().
     */
    void clearBoundingBoxes();

    std::vector<GPRect>& getBoundingBoxes();

    /**
     * The function draw() needs to be overridden by subclasses to implement
     * their own drawing behaviour.
     */
    virtual void draw() = 0;

};

//==============================================================================

/**
 * The GPSprite is a basic class which derives from the GPObject. It can
 * build itself up by the usage of a texture.
 *
 * TODO: rename it to GPTexturedSprite?
 *
 * @author krpors
 */
class GPSprite : public GPObject {
private:

    /// Sprite alpha
    gpFloat m_alpha;

    /// Vector of GPRects (x,y,w,h) to hold coordinates for each animation frame
    std::vector<GPRect> m_animRects;

    /// Current frame to render
    int  m_anim_frame;

    /// Total frames
    int  m_anim_frames;

    /// Loop animation? true/false
    bool m_anim_loop;

    /// Frame number to start animation. It's always 0 as default.
    int  m_anim_frameStart;

    /**
     * Frame number where to stop the animation. It's always the highest frame
     * number available, unless you set it up manually. It must be greater or
     * equal than m_anim_frameStart.
     */
    int  m_anim_frameEnd;

    /// Play the animation backwards? true/false
    bool m_anim_backwards;

    /// Vector of textures to use for animations
    std::vector <GPTexture*> m_textures;

    /// The pointer to the used texture.
    GPTexture* m_texture;

public:

    /**
     * A null constructor.
     */
    GPSprite();

    /**
     * Creates a new GPSprite from a texture and sets it as the active one.
     *
     * @param texture The pointer to an existing texture.
     */
    GPSprite(GPTexture* texture);

    /**
     * Destructor of the sprite. Note that this does not delete the texture
     * associated with this class.
     */
    ~GPSprite();

    /**
     * Adds a texture into GPSprite and sets it as the active texture.
     * It returns the texture number inside the textures array, so we know what
     * number corresponds to that texture and use it in useTexture()
     *
     * @param texture The pointer to an existing texture.
     */
    int addTexture(GPTexture* texture);

    /**
     * Sets the texture to use for the animations, or sprite itself. It just
     * makes the sprite use another texture instead, and it updates in realtime.
     */
    void useTexture(unsigned int value);

    /**
     * Gets the associated texture.
     */
    GPTexture* getTexture() const;

    /**
     * Creates an animation out of the current texture in the sprite.
     *
     * The idea is, you give it how many frames to create in width and height
     * across the whole texture, set the starting point in x & y and the size
     * of each frame in pixels. That will create the coordinates automatically
     * in this way.
     *
     * For example, for a createAnim(3,3, 0,0,64,64) in a 256x256 texture for example, the animation
     * would end up like this:
     *  <pre>
     *  _______________
     * |_0_|_1_|_2_|_3_|
     * |_4_|_5_|_6_|_7_|
     * |_8_|_9_|_10|_11|
     * |_12|_13|_14|_15|
     *  </pre>
     *
     * The numbers represent the frame numbers that the animation will use.
     * Each square being of 64x64 pixels size, starting at 0,0
     *
     * @param framesWidth Number of frames across the texture horizontally
     * @param framesHeight Number of frames across the texture vertically
     * @param orgx X coordinate of origin where to start the automatic process (in pixels)
     * @param orgy Y coordinate of origin where to start the automatic process (in pixels)
     * @param width Width size of each animation frame (in pixels)
     * @param height Height size of each animation frame (in pixels)
     *
     * @return The current maximum number of frames in the sprite
     */
    int createAnim(gpInt32 framesWidth, gpInt32 framesHeight, gpInt32 orgx, gpInt32 orgy, gpInt32 width, gpInt32 height);

    /**
     * Sets the current frame
     *
     * @param frame Frame number
     */
    void setAnimFrame(gpInt32 frame);

    /**
     * "Plays" the animation if used in a loop. It just increases the current
     * frame.
     */
    void setAnimNextFrame();

    /**
     * Sets the limits of the animation in frame numbers. From lowest frame number
     * to highest.
     *
     * NOTE: If the current frame is higher than "end" or it's lower than "start",
     * the frame will be set to either the lowest or highest value possible to fit
     * within the frame limits.
     *
     * @param start Lowest frame number to use in the current animation
     * @param end Highest frame number to use in the current animation
     */
    void setAnimRange(gpInt32 start, gpInt32 end);

    /**
     * Sets a flag whether to play the animation backwards or not.
     *
     * @param val True/false
     */
    void setAnimBackwards(gpBool val);

    /**
     * Sets a flag whether to loop the animation forever. It could be a good
     * idea to add support for a number of looped plays instead of just forever.
     *
     * @param val True/false
     */
    void setAnimLoop(gpBool val);
    /**
     * This creates an animation frame.
     *
     * @param x X top-left coordinate of origin where to begin the frame (in pixels)
     * @param y Y top-left coordinate of origin where to begin the frame (in pixels)
     * @param width Width size of the animation frame (in pixels)
     * @param height Height size of the animation frame (in pixels)
     *
     * @return The current maximum number of frames in the sprite
     */
    gpInt32 createAnimFrame(gpInt32 x, gpInt32 y, gpInt32 width, gpInt32 height);

    /**
     * Returns the current frame number.
     *
     * @return The current frame number in the animation.
     */
    gpInt32 getFrame();

    /**
     * Returns the maximum number of frames available in the sprite.
     *
     * @return The maximum number of frames available.
     */
    gpInt32 getFrames();

    /**
     * Implementation of the draw method from GPObject.
     */
    virtual void draw();

    /**
     * computeEdges() uses the texture in this sprite to calculate where the edges
     * are. An `edge' definition in this case is the intersection between a full
     * transparent pixel and where a non-transparent pixel. The calculation is done
     * as follows:
     *
     * First, over every pixel in the texture (actually the SDL_Surface from which the
     * OpenGL texture was created) is being iterated. For each pixel, try to get the
     * pixels in its surroundings:
     *  <pre>
     *  ___________
     * |___|___|___|  [0 0], [0 1], [0 2]
     * |___|***|___|  [1 0], [1 1], [1 2]
     * |___|___|___|  [2 0], [2 1], [2 2]
     *  </pre>
     *
     * Every `square' in this ASCII denotes a pixel. The square [1 1], or [***] is
     * the current pixel being tested. The surrounding pixels (the other squares
     * around the [***] are being tested if it transparent (i.e. fully alpha, 0x00).
     * If any pixel around the [***] is opaque in any way (alpha > 0x00), it is denoted
     * as an edge. A bounding box will be added to this sprite on the place of the
     * current tested pixel.
     *
     * Note: this function is pretty much a very expensive function, and it is very,
     * very unwise to use this on very large sprited textures with lots and lots of possible
     * `edges' or else the performance may drop during collision tests (because of a large
     * amount of collision boxes generated).
     */
    void computeEdges();

    /**
     * TODO: Uhh... this function shouldn't actually be here... is there a
     * workaround for computeEdges to have it somewhere else?
     */
    Uint8 getSurfaceAlpha(SDL_Surface* surface, int x, int y) const;

    /**
     * Sets the sprite's alpha.
     *
     * XXX (azzkikr): please do not make use of GLfloat, but a possible gpFloat ???
     *
     * @param alpha From 0.0f to 1.0f
     */
    void setAlpha(gpFloat alpha);

    /**
     * Gets the sprite's alpha.
     */
    gpFloat getAlpha() const;

};

//==============================================================================

/**
 * A GPCursor is a subclass of the GPSprite, mainly to function as a
 * representation of a cursor within the bounds of the GPWindow. The cursor is
 * drawn according to a given pointer to a GPTexture.
 *
 * It is a subclass of GPSprite because the drawing routine is the same as
 * a normal sprite, and it can be animated. Basically it provides only a few
 * additional functions, i.e.  to set and query the default pointer
 * (the OS 'arrow').
 *
 * Note that the displaying of a cursor sprite (the GPCursor) should only be
 * done when the current camera mode is in GUI mode, or else you will get flaky
 * results because the orthographic project is different in GAME mode.
 *
 * @author krpors
 */
class GPCursor : public GPSprite {
public:

    /**
     * Creates a GPCursor instance.
     */
    GPCursor();

    /**
     * Creates a GPCursor instance based on a texture.
     *
     * @param tex A texture pointer.
     */
    GPCursor(GPTexture* tex);

    /**
     * Invokes delete operations on the GPCursor instance.
     */
    ~GPCursor();

    /**
     * This static function returns a bool true when the default Window Manager
     * pointer should be rendered when the mouse is positioned over the created
     * window. When returning false, the default pointer is not visible.
     *
     * @return true or false, dependent if the visibility of the default mouse
     *  pointer has been set to true or false using setDefPointerVisible(gpBool).
     */
    static gpBool isDefPointerVisible();

    /**
     * This static function sets the visibility of the default pointer enabled
     * or disabled. When the 'enabled' parameter is set to true, the default
     * pointer of the WM is set visible. When set to false, the default pointer
     * will not be made visible when hovering inside the window instance.
     *
     * @param enabled When true, render the default pointer. When false,
     *  disable rendering of the default pointer.
     */
    static void setDefPointerVisible(gpBool enabled);

    /**
     * Sets the position based on the current window bounds. This is just a
     * convenience method for invoking setPosition(x, window->getHeight() - y),
     * nothing fancy. It just makes positioning the mouse cursor easier.
     *
     * @throws GPException when the GPWindow instance was not yet created.
     */
    void updatePosition() throw (GPException);

};

//==============================================================================


/**
 * TODO: Uhh... these functions shouldn't actually be here... possible fix?
 */
/**
 * Draw a rectangle from (x1,y1) to (x2,y2) at Z=z.
 */
void drawRectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z);
/**
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
Uint32 GetPixel ( SDL_Surface *surface, Uint32 x, Uint32 y );
/**
 * Get the RGBA color values of the pixel at (x, y)
 * Returns true if the coordinates (x,y) are inside the SDL_Surface, false otherwise.
 * NOTE: The surface must be locked before calling this!
 */
bool GetPixelRGBA ( SDL_Surface* surf, Uint32 x, Uint32 y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a );
/**
 * Get the R color value of the pixel at (x, y)
 * Returns true if the coordinates (x,y) are inside the SDL_Surface, false otherwise.
 * NOTE: The surface must be locked before calling this!
 */
Uint8 GetPixelR ( SDL_Surface* surf, Uint32 x, Uint32 y );
/**
 * Get the G color value of the pixel at (x, y)
 * Returns true if the coordinates (x,y) are inside the SDL_Surface, false otherwise.
 * NOTE: The surface must be locked before calling this!
 */
Uint8 GetPixelG ( SDL_Surface* surf, Uint32 x, Uint32 y );
/**
 * Get the B color value of the pixel at (x, y)
 * Returns true if the coordinates (x,y) are inside the SDL_Surface, false otherwise.
 * NOTE: The surface must be locked before calling this!
 */
Uint8 GetPixelB ( SDL_Surface* surf, Uint32 x, Uint32 y );
/**
 * Get the A color value of the pixel at (x, y)
 * Returns true if the coordinates (x,y) are inside the SDL_Surface, false otherwise.
 * NOTE: The surface must be locked before calling this!
 */
Uint8 GetPixelA ( SDL_Surface* surf, Uint32 x, Uint32 y );
}

#endif /* GRAPHICS_H_ */
