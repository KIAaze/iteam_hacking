#ifndef _GP_WINDOW_H_
#define _GP_WINDOW_H_

#include "core.hpp"
#include "exception.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "texture.hpp"

#include <string>
#include <vector>
#include <map>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace gp {

/**
 * This class is basically what has properties to set up and build a window
 * to draw things on.
 *
 * @author krpors
 * @author DARKGuy
 */
class GPCamera;
class GPGameCamera;
class GPGuiCamera;
class GPDirector;
class GPTexture;

class GPWindow {
private:

    /// Boolean indicating whether fullscreen was toggled.
    gpBool m_fullScreen;

    /// The screen's width.
    gpInt32 m_screenWidth;

    /// The screen's height.
    gpInt32 m_screenHeight;

    /// The bitdepth of the window.
    gpInt32 m_screenDepth;

	/// The window's background color
    GPColor* m_bgColor;

    /// The SDL surface which is the screen.
    SDL_Surface* m_surfaceScreen;

    /// The SDL surface which is the background for clearing the back buffer
    /// with.
    SDL_Surface* m_surfaceBackground;

    /// Video flags, which are manipulated by setFlag...() functions.
    gpUint32 m_videoFlags;

    /// Game camera
    GPGameCamera* m_gameCamera;

    /// GUI camera
    GPGuiCamera* m_guiCamera;

    /// Camera director
    GPDirector* m_cameraDirector;

public:
    /**
     * GPWindow constructor
     */
    GPWindow();

    /**
     * Destroys the GPWindow.
     */
    ~GPWindow();

    /// The vector with the loaded textures.
    /// TODO: Make it private and create getter?
    std::map<std::string, GPTexture*> m_textures;

	void addTexture(std::string name, GPTexture* tex);
    void addTexture(std::string name, std::string filename);
    GPTexture* getTexture(std::string name);

    /**
     * Gets the width of the window, as set by createWindow(int, int, int).
     *
     * @return The width of the window as an integer.
     */
    gpInt32 getWidth() const;

    /**
     * Gets the height of the window, as set by createWindow(int, int, int).
     *
     * @return The height of the window as an integer.
     */
    gpInt32 getHeight() const;

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
    void setTitle(std::string title);

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
    void clear();

    /**
     * Synchronizes buffers, i.e. swaps the buffers.
     */
    void render();

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
     * GPException. Therefore, you need to call GPEngine::initialize() before
     * calling this function.
     *
     * @param width The preferred width.
     * @param height The preferred height.
     * @param bpp The amount of bits per pixel (2, 8, 16, 24, 32)
     * @throws GPException when the GPEngine video subsystem was not
     *   initialized. Can also be thrown when the video mode was tried to be
     *   opened, but not supported (like 64 bits per pixel).
     */
    void create(int width, int height, int bpp, std::string title) throw (GPException);

    void setDirector(GPDirector* director);

    GPDirector* getDirector();

};

}

#endif
