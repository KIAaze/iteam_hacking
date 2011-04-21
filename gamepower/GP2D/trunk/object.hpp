#ifndef _GP_OBJECT_H_
#define _GP_OBJECT_H_

#include "core.hpp"
#include "exception.hpp"

namespace gp {

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
     * Set the XYZ scales in one shot
     * @param sX The scale for all coordinates
     */
    void setScale(gpFloat sX);

    /**
     * Set the XYZ scales
     * @param sX The X scale
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
     * The function draw() needs to be overridden by subclasses to implement
     * their own drawing behaviour.
     */
    virtual void draw() = 0;

};

}

#endif
