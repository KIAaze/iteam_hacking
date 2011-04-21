#ifndef _GP2D_GRAPHICS_H_
#define _GP2D_GRAPHICS_H_

#include <GL/gl.h>
#include <GL/glext.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <algorithm>
#include <string>
#include "core.h"

namespace gp2d {

// Forward declarations.
class GP2DCamera;
class GP2DRect;
class GP2DColor;

/**
 * This class is basically what has properties to set up and build a window
 * to draw things on.
 *
 * @author krpors
 * @author DARKGuy
 */
class GP2DWindow {
protected:
    /// The only instance pointer, for singleton purposes.
    static GP2DWindow* m_instance;

public:
    /**
     * Gets the one and only instance of the GP2DWindow.
     *
     * @return A pointer to a GP2DWindow which is guaranteed to be the only
     *   instance.
     */
    static GP2DWindow* getInstance();

    /**
     * The rendering types. Basically there are two of them only, SDL rendering
     * and OpenGL rendering.
     */
    enum GP2DRenderMode {
        GP2D_SDL,
        GP2D_OPENGL
    };

    /**
     * Destroys the GP2DWindow.
     */
    ~GP2DWindow(void);

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
     * Sets the background color
     *
     * @param r Red   (0...255)
     * @param g Green (0...255)
     * @param b Blue  (0...255)
     */
    void setBackgroundColor(int r,int g,int b);

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
     * @throws GP2DException when the fullscreen could not be toggle, because
     *   the screen surface was not initialized by invoking
     *   GP2DWindow::createWindow(int, int, int).
     */
    void toggleFullScreen() throw (GP2DException);

    /**
     * Clears the screen with the clearing color.
     */
    void clearScreen();
    // void clearScreen(GP2DColor& color);

    /**
     * Synchronizes buffers, i.e. swaps the buffers.
     */
    void sync();


    void setRenderMode(const GP2DRenderMode mode);

    /**
     * Gets the current video API to use.
     */
    GP2DRenderMode getRenderMode() const;

    /**
     * If the window is created using GP2DWindow::createWindow(int, int, int),
     * then a surface from the underlying SDL API is created. A check is made
     * whether it is NULL. If NULL, false will be returned. Otherwise, true
     * will be returned, indicating that the user of the API has created a
     * window already.
     *
     * @return true when the window is created, false if otherwise.
     */
    bool isCreated();

    /**
     * Actually creates the window, provided the GP2DEngine is initialized
     * fully. If the video engine is not initialized, it will throw a
     * GP2DException. Therefore, you need to call GP2DEngine::initVideo() or
     * GP2DEngine::initAll() before calling this function.
     *
     * @param width The preferred width.
     * @param height The preferred height.
     * @param bpp The amount of bits per pixel (2, 8, 16, 24, 32)
     * @throws GP2DException when the GP2DEngine video subsystem was not
     *   initialized. Can also be thrown when the video mode was tried to be
     *   opened, but not supported (like 64 bits per pixel).
     */
    void createWindow(int width, int height, int bpp) throw (GP2DException);

    /**
     * Creates a new camera for the current window. Each window can have a
     * (hopefully) infinite number of cameras. Be aware, that this will set
     * the new camera as the current one (by changing m_currentCamera) for the
     * next concurrent engine operations unless a setCamera() is used afterwards
     */
    void  createNewCamera();

    /**
     * Returns a pointer to the current camera, by default it returns the
     * pointer of the newest camera created.
     *
     * @return a GP2DCamera pointer to the current camera.
     */
    GP2DCamera* getCamera() throw(GP2DException);

    /**
     * Returns a pointer to a specific camera, in relation to the window's
     * camera vector.
     *
     * @param num camera number in relation to the window's camera vector.
     * @return a GP2DCamera pointer to the specified camera.
     */
    GP2DCamera* getCamera(int num);

    /*
     * Sets the current camera to do various engine operations with. The
     * getCamera() function will use the value that we set here (instead of
     * the newest camera created).
     */
    void setCamera(int num);

private:

    /// Boolean indicating whether fullscreen was toggled.
    bool m_fullScreen;

    /// The screen's width.
    int m_screenWidth;

    /// The screen's height.
    int m_screenHeight;

    /// The bitdepth of the window.
    int m_screenDepth;

    /// The SDL surface which is the screen.
    SDL_Surface* m_surfaceScreen;

    /// The SDL surface which is the background for clearing the back buffer
    /// with.
    SDL_Surface* m_surfaceBackground;

    /// Background color to clear the background with, in SDL mode.
    Uint32 m_backgroundColor;

    /// Background color array, in RGB [0]=R,[1]=G,[2]=B
    int m_backgroundColorArray[3];

    /// Video flags, which are manipulated by setFlag...() functions.
    unsigned int m_videoFlags;

    /// Video API to use.
    GP2DRenderMode m_videoAPI;

    /**
     * Creates the GP2DWindow.
     */
    GP2DWindow(void);

    std::vector <GP2DCamera> m_camera;
    int m_currentCamera;

};

//==============================================================================

/**
 * The GP2DCamera actually provides the usage of a viewport. It can be moved to
 * a different position, and can be 'zoomed' in and out by adjusting the range
 * of the camera.
 *
 * @author krpors
 */
class GP2DCamera {
private:
    /// The x position of the camera.
    float m_posX;

    /// The y position of the camera.
    float m_posY;

    /// The range the camera should attend to.
    int m_range;

    /**
     * Initializes the camera with the specified range.
     *
     * @param range The range of the camera along the x-axis.
     * @throws GP2DException When the window parent is not created yet.
     */
    void initializeCamera(int range) throw(GP2DException);
public:
    /**
     * Constructs a GP2DCamera given the window instance and a specific range.
     *
     * @param range The range of the orthographic projection.
     */
    GP2DCamera(int range);
    /**
     * Constructs a GP2DCamera given the window instance with a default range.
     */
    GP2DCamera();

    /**
     * Destructor for the camera.
     */
    ~GP2DCamera();

    /**
     * Updates the camera using the given range and position.
     *
     * @throws GP2DException when the parent window is not yet created.
     */
    void updateCamera() throw(GP2DException);

    /**
     * Gets the camera range.
     *
     * @return The camera range.
     */
    int getRange() const;

    /**
     * Sets the range of the camera. To make things final after this, call
     * updateCamera().
     *
     * @param range The new range of the camera.
     */
    void setRange(int range);

    /**
     * Sets the x and y position of the camera.
     */
    void setPosition(float x, float y);

    /**
     * Gets camera x position.
     *
     * @return Position as a float.
     */
    float getX() const;

    /**
     * Gets camera y position.
     *
     * @return Position as a float.
     */
    float getY() const;
};

//==============================================================================

/**
 * A simple rectangle, with values for an (x, y) coordinate and a width, height.
 * The members are declared public for simplicity.
 */
class GP2DRect {
public:
    float m_x;
    float m_y;
    float m_w;
    float m_h;

public:
    /**
     * Creates a rectangle, (0,0)-(0,0).
     */
    GP2DRect();

    /**
     * Creates a rectangle, (x,y)-(w,h).
     *
     * @param x The x coord.
     * @param y The y coord.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     */
    GP2DRect(float x, float y, float w, float h);

    GP2DRect operator*(const float& f);

    /**
     * Desstructor, doesn't do anything yet.
     */
    ~GP2DRect();
};

//==============================================================================

/**
 * The GP2DColor class is a simple encapsulation mechanism for r,g,b and alpha
 * coloring. The member vars are public read/write for convenience.
 */
class GP2DColor {
public:

    /// Red component, ranging from 0 - 255 (0x00 - 0xFF)
    unsigned int r;

    /// Green component, ranging from 0 - 255 (0x00 - 0xFF)
    unsigned int g;

    /// Blue component, ranging from 0 - 255 (0x00 - 0xFF)
    unsigned int b;

    /// Alpha component, ranging from 0 - 255 (0x00 - 0xFF)
    unsigned int a;

    GP2DColor();
    GP2DColor(unsigned int red, unsigned int green, unsigned int blue);
    GP2DColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

    GP2DColor operator+(const GP2DColor& color);
    GP2DColor operator-(const GP2DColor& color);
    GP2DColor operator^(const GP2DColor& color);
};


//==============================================================================

/**
 * A GP2DTexture is a class responsible for loading a texture (a graphic) into
 * memory. It has the necessary functions to create texture from file, and
 * getting properties from it. Internally in the class, an SDL_Surface pointer
 * is kept which is the original 'source' of the raw pixel data.
 *
 * This pixel data can then be used to get pixel values, for instance to detect
 * collision.
 *
 * Generally, for each image you will want to load as a texture, you create only
 * one GP2DTexture object. For instance, you want to load a texture called
 * 'terrain.png', you will only need to make one GP2DTexture corresponding to
 * that texture file. If you don't do this, OpenGL will load the texture file
 * twice, consuming memory.
 *
 * TODO: In the future, something like a texture factory, or some kind of map
 * that holds all the generated textures so a choice can be made from it?
 *
 * @author krpors
 */
class GP2DTexture {
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

	 GLfloat m_textureRepeatX;
	 GLfloat m_textureRepeatY;

	 GLfloat m_textureOffsetX;
	 GLfloat m_textureOffsetY;

public:
    /**
     * Creates an 'empty' GP2DTexture. A 256 x 256 surface will be created where
     * the content of the texture is based upon.
     *
     * @throws GP2DException if the texture cannot be created.
     */
    GP2DTexture() throw(GP2DException);

    /**
     * Creates a GP2DTexture off a filename. An exception is thrown if the file
     * cannot be loaded or some other reason SDL sees fit to.
     *
     * @param file The filename to load a texture for.
     * @throws GP2DException when the file cannot be loaded or something.
     */
    GP2DTexture(std::string file) throw(GP2DException);

    /**
     * Deletes the texture form memory, and the created SDL surface with it,
     * using SDL_FreeSurface().
     */
    ~GP2DTexture();

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
};

//==============================================================================

/**
 * Simply put, the GP2DObject is the base class to hold coordinatal data. You
 * could see it as the base of every sprite and all that in GP2D. It has a few
 * variables to indicate position: x, y, z, w, and h.
 *
 * Besides these variables, it has one interesting function, the virtual void
 * function GP2DObject::draw(). This function needs to be overridden by derived
 * classes so it knows how to draw itself.
 *
 * @author krpors
 */
class GP2DObject {
private:
    /// X position of the object.
    float m_x;

    /// Y position of the object.
    float m_y;

    /// Z position of the object.
    float m_z;

    /// The width of the object.
    float m_width;

    /// The height of the object.
    float m_height;

    /// The x position velocity.
    float m_x_velocity;

    /// The y position velocity.
    float m_y_velocity;

    /// Rotation around the X-axis.
    float m_angle_X;

    /// Rotation around the Y-axis.
    float m_angle_Y;

    /// Rotation around the Z-axis.
    float m_angle_Z;

    /// Rotation center X position.
    float m_RotCenter_X;
    /// Rotation center Y position.
    float m_RotCenter_Y;
    /// Rotation center Z position.
    float m_RotCenter_Z;

    std::vector<GP2DRect> m_boundingBoxes;

    /**
     * Basic initialization code for variables. Since there are 3 constructors,
     * repeating the same code is a bit tedious. The initialization of the local
     * class variables are initialized here.
     */
    void init();


public:
    /**
     * Creates a GP2DObject, will initialize the variables to 0.0f.
     */
    GP2DObject();

    /**
     * Creates a GP2DObject. This will initialiaze the x and y variables.
     *
     * @param x The x coord.
     * @param y The y coord.
     */
    GP2DObject(float x, float y);

    /**
     * Creates a GP2DObject, which will initialize the x, y and z variables.
     *
     * @param x The x coord.
     * @param y The y coord.
     * @param z The z coord.
     */
    GP2DObject(float x, float y, float z);

    /**
     * The virtual destructor.
     */
    virtual ~GP2DObject();

    /**
     * Gets the x position of the GP2DObject.
     * @return The x position. Negative goes to the left, positive goes to
     *   the right.
     */
    float getX() const;

    /**
     * Gets the x position of the GP2DObject.
     * @return The y position. Negative goes to the bottom, positive goes to
     *   up.
     */
    float getY() const;

    /**
     * Gets the z(depth) position of the GP2DObject.
     * @return The z position. Negative goes farther way back? Positive goes to
     *   farther way up front?
     */
    float getZ() const;

    /**
     * Gets the height of this object.
     * @return The height.
     */
    float getHeight() const;

    /**
     * Gets the width of this object.
     * @return The width.
     */
    float getWidth() const;

    /**
     * Gets the x coordinate velocity of the object. When 0, it is static. When
     * negative, move the left, positive to the right.
     *
     * @return The horizontal movement (x velocity).
     */
    float getVelocity_X() const;

    /**
     * Gets the y coordinate velocity of the object. When 0, it is static. When
     * negative, move down, positive move up.
     *
     * @return The vertical movement (y velocity).
     */
    float getVelocity_Y() const;

    /**
     * Gets the rotation angle around the X axis.
     *
     * @return The rotation angle of the GP2DObject around the X axis.
     */
    float getRotation_X() const;

    /**
     * Gets the rotation angle around the Y axis.
     *
     * @return The rotation angle of the GP2DObject around the Y axis.
     */
    float getRotation_Y() const;

    /**
     * Gets the rotation angle around the Z axis.
     *
     * @return The rotation angle of the GP2DObject around the Z axis.
     */
    float getRotation_Z() const;

    /**
     * Gets the rotation center X position.
     *
     * @return The rotation center X position.
     */
    float getRotCenter_X() const;

    /**
     * Gets the rotation center Y position.
     *
     * @return The rotation center Y position.
     */
    float getRotCenter_Y() const;

    /**
     * Gets the rotation center Z position.
     *
     * @return The rotation center Z position.
     */
    float getRotCenter_Z() const;

    /**
     * Set the x coordinate.
     * @param x The x coord. Negative to go to the left, positive to go to the
     *  right.
     */
    void setX(float x);

    /**
     * Set the y coordinate.
     * @param y The y coord. Negative to go to down, positive to go up.
     */
    void setY(float y);

    /**
     * Set the z coordinate.
     * @param z The z coord. Negative to go to the back, positive to go to the
     *  front.
     */
    void setZ(float z);

    /**
     * Shorthand function for setting x and y positions of the GP2DObject.
     * @param x The x position.
     * @param y The y position.
     */
    void setPosition(float x, float y);

    /**
     * Set the width.
     * @param w The width of the object.
     */
    void setWidth(float w);

    /**
     * Set the height.
     * @param h The height of the object0r.
     */
    void setHeight(float h);

    /**
     * Set the width and height.
     * @param w The height of the object0r.
     * @param h The height of the object0r.
     */
    void setSize(float w, float h);

    /**
     * Sets the x coordinate velocity of the object. When 0, it is static. When
     * negative, move the left, positive to the right.
     *
     * @param xvel The velocity, horizontally.
     */
    void setVelocity_X(float xvel);

    /**
     * Sets the y coordinate velocity of the object. When 0, it is static. When
     * negative, move to the bottom, positive move upwards.
     *
     * @param yvel The velocity, vertically.
     */
    void setVelocity_Y(float yvel);

    /**
     * Sets the rotation angle of the GP2DObject around the X axis.
     *
     * @param angle The rotation angle.
     */
    void setRotation_X(float angle);

    /**
     * Sets the rotation angle of the GP2DObject around the Y axis.
     *
     * @param angle The rotation angle.
     */
    void setRotation_Y(float angle);

    /**
     * Sets the rotation angle of the GP2DObject around the Z axis.
     *
     * @param angle The rotation angle.
     */
    void setRotation_Z(float angle);

    /**
     * Sets the rotation center X position.
     *
     * @param angle The rotation center X position.
     */
    void setRotCenter_X(float a_X);

    /**
     * Sets the rotation center Y position.
     *
     * @param angle The rotation center Y position.
     */
    void setRotCenter_Y(float a_Y);

    /**
     * Sets the rotation center Z position.
     *
     * @param angle The rotation center Z position.
     */
    void setRotCenter_Z(float a_Z);

    /**
     * Sets the rotation center for all rotations
     *
     * @param a_x The rotation center X position
     * @param a_y The rotation center Y position
     * @param a_z The rotation center Z position
     */
    void setRotCenter(float a_x,float a_y,float a_z);

    /**
     * Adds a bounding box (a GP2DRect) to the GP2DObject.
     *
     * @param rect A copy of the rect object to add.
     */
    void addBoundingBox(GP2DRect rect);

    /**
     * Clear up the vector holding the bounding boxes. This creates
     * a delegate call to m_boundingBoxes.clear().
     */
    void clearBoundingBoxes();

    std::vector<GP2DRect>& getBoundingBoxes();

    /**
     * The function draw() needs to be overridden by subclasses to implement
     * their own drawing behaviour.
     */
    virtual void draw() = 0;

};

//==============================================================================

/**
 * The GP2DSprite is a basic class which derives from the GP2DObject. It can
 * build itself up by the usage of a texture.
 *
 * TODO: rename it to GP2DTexturedSprite?
 *
 * @author krpors
 */
class GP2DSprite : public GP2DObject {
private:
    GLfloat m_alpha;    /// Sprite alpha

    int  m_anim_frame;  /// Current frame to render
    int  m_anim_frames; /// Total frames
    int  m_anim_w;      /// Number of sprites wide
    int  m_anim_h;      /// Number of sprites high
    bool m_anim_loop;   /// Loop animation?
    int  m_anim_frameStart;
    int  m_anim_frameEnd;
    bool m_anim_backwards;

	/**
	 * XXX: Why protected?
	 */
   /// Vector of textures to use for animations
   std::vector <GP2DTexture*> m_textures;

   /// The pointer to the used texture.
	GP2DTexture* m_texture;
public:

    /**
     * A null constructor.
     */
    GP2DSprite();

    /**
     * Creates a new GP2DSprite from a texture and sets it as the active one.
     *
     * @param texture The pointer to an existing texture.
     */
    GP2DSprite(GP2DTexture* texture);

    /**
     * Creates a GP2DSprite with a GP2DTexture off a filename.
     *
     * @param file The filename to load a texture for.
     */
    GP2DSprite(std::string file);

    /**
     * Destructor of the sprite. Note that this does not delete the texture
     * associated with this class.
     */
    ~GP2DSprite();

    /**
     * Adds a texture into GP2DSprite and sets it as the active texture.
     *
     * @param texture The pointer to an existing texture.
     */
    int addTexture(GP2DTexture* texture);

    /**
     * Adds a texture into GP2DSprite and sets it as the active texture.
     *
     * @param file The filename to an existing texture image file.
     */
    int addTexture(std::string file);

    /**
     * XXX (azzkikr): what does useTexture do?
     */
    void useTexture(unsigned int value);

    /**
     * Gets the associated texture.
     */
    GP2DTexture* getTexture() const;

    /**
     * TODO: documentation.
     */
     void createAnim(int width, int height);
	  void setAnimFrame(int frame);
	  void setAnimNextFrame();
	  void setAnimRange(int start, int end);
	  void setAnimBackwards(bool val);
	  void setAnimLoop(bool val);

    /**
     * Implementation of the draw method from GP2DObject.
     */
    virtual void draw();

    /**
     * Computes edges.
     * TODO: documentation.
     */
    void computeEdges();

    /**
     * TODO: Uhh... this function shouldn't actually be here... is there a
     * workaround for computeEdges to have it somewhere else?
     */
	 Uint8 getSurfaceAlpha(SDL_Surface* surface, int x, int y) const;

    /**
     * TODO: documentation.
     * XXX (azzkikr): please do not make use of GLfloat, but a possible gp2dFloat ???
     */
    void setAlpha(GLfloat alpha);
    GLfloat getAlpha() const;

};

/**
 * TODO: Uhh... these functions shouldn't actually be here... possible fix?
 */
void drawRectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z);
Uint32 GetPixel ( SDL_Surface *surface, Uint32 x, Uint32 y );
bool GetPixelRGBA ( SDL_Surface* surf, Uint32 x, Uint32 y, Uint8 &r, Uint8 &g, Uint8 &b, Uint8 &a );

}

#endif /* GRAPHICS_H_ */
