#ifndef _GP_CAMERA_H_
#define _GP_CAMERA_H_

#include "core.hpp"
#include "exception.hpp"
#include "window.hpp"

namespace gp {

/**
 * The GPCamera actually provides the usage of a viewport. It can be moved to
 * a different position, and can be 'zoomed' in and out by adjusting the range
 * of the camera.
 *
 * @author krpors
 */

/// Forward GPWindow declaration. I don't know why the compiler whines about not
/// finding the GPWindow type if I don't declare it here first.
class GPWindow;

class GPCamera {
protected:
    /// The x position of the camera.
    gpFloat m_posX;

    /// The y position of the camera.
    gpFloat m_posY;

    /// The range the camera should attend to.
    gpDouble m_range;

    /// The associated window instance
    GPWindow* m_window;

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
     * Sets the window associated to the camera
     */
    void setWindow(GPWindow* window);

    /**
     * Gets the window associated to the camera
     */
    GPWindow* getWindow();

    /**
     * Updates the camera using the given range and position and all other
     * configurable options.
     *
     * @throws GPException when the parent window is not yet created.
     */
    virtual void updateCamera() = 0;

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
     * was probably not created or set using setWindow()).
     */
    GPGameCamera();

    /**
     * Updates the camera positions using the necessary functions. It will for
     * instance set the viewport, orthographic project, and the x and y positions
     * of the camera.
     *
     * @throws GPException When the GPWindow can not be allocated (because it
     * was probably not created or set using setWindow()).
     */
    virtual void updateCamera();
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
 *  - Coordinates are in screen-space and not world-space
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
     * was probably not created or set using setWindow()).
     */
    GPGuiCamera() throw (GPException);

    /**
     * Updates the camera using the necessary functions. In contrast of the
     * GPGameCam, it does not translate the camera x,y position, only the
     * viewport and the orthographic project using the private member variables
     * for the ranges.
     *
     * @throws GPException When the GPWindow can not be allocated (because it
     * was probably not created or set using setWindow()).
     */
    virtual void updateCamera();

    /**
     * Sets default camera dimensions using the GPWindow boundaries.
     *
     * @throw GPException When the GPWindow can not be allocated (because it
     * was probably not created or set using setWindow()).
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
    GPGameCamera* m_gamecam;

    /// The gui camera.
    GPGuiCamera* m_guicam;

    /**
     * Flag to indicate which camera is used currently.
     * False = Game Camera
     * True  = GUI Camera
     */
    gpBool m_flag;

public:
    /**
     * Creates the director using the given camera's.
     *
     * @param gamecam The camera used for the in-game view.
     * @param guicam The camera for the user interface objects.
     */
    GPDirector(GPGameCamera* gamecam, GPGuiCamera* guicam);

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

    /**
     * Returns the game camera object
     */
    GPGameCamera* getGameCamera();

    /**
     * Returns the GUI camera object
     */
    GPGuiCamera* getGuiCamera();
};

}

#endif
