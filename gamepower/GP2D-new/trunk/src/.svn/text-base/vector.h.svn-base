#ifndef VECTOR_H_
#define VECTOR_H_

#include "gp2d.h"
using namespace std;

namespace gp {

/**
 * A simple 3D vector class.
 * It can be used for 1D and 2D easily since the constructor uses default values.
 */
class GPVector {
public:

    /**
     * @name Constructors, Assignment operator and Destructor
     * Constructors, Assignment operator and Destructor
     */
    //@{

    /**
     * Constructor from x, y, and z values.
     *
     * @param x The x coord.
     * @param y The y coord.
     * @param z the z coord.
     */
    GPVector(gpFloat x = 0.0f, gpFloat y = 0.0f, gpFloat z = 0.0f);


    /**
     * Constructor from a gpFloat array.
     *
     * @param arr The float array.
     */
    GPVector(const gpFloat arr[]);

    /**
     * The copy constructor.
     *
     * @param vec The other GPVector instance.
     */
    GPVector(const GPVector& vec);

    /**
     * Assignment operator for GPVector.
     *
     * @param vec The GPVector instance.
     */
    GPVector& operator=(const GPVector& vec);

    /**
     * (Virtual??) destructor of the GPVector.
     */
    virtual ~GPVector();
    //@}

    /**
     * @name Accessors
     * Accessors for the components in the cartesian coordinate system.
     */
    //@{

    /**
     * Gets the x component of the vector.
     *
     * @return the x component (coordinate) of this GPVector.
     */
    gpFloat getX()  const;

    /*
     * Gets the y component of the vector.
     *
     * @return the y component (coordinate) of this GPVector.
     */
    gpFloat getY()  const;

    /**
     * Gets the z component of the vector.
     *
     * @return the z component (coordinate) of this GPVector.
     */
    gpFloat getZ()  const;

    /**
     * Get the components into an array. Not checked!
     *
     * @param carray The array pointer to fill.
     */
    void getXYZ(gpFloat carray[]) const;

    /**
     * Get parameters by index? Why?
     */
    gpFloat operator()(int) const;

    /**
     * Address parameters by index.
     */
    gpFloat operator [] (int) const;
    //@}

    /**
     * @name Setters
     * Setter functions.
     */
    //@{

    /**
     * Sets the x component.
     *
     * @param x The x coord.
     */
    void setX(gpFloat x);

    /**
     * Sets the y component.
     *
     * @param y The y coord.
     */
    void setY(gpFloat y);

    /**
     * Sets the z component.
     *
     * @param z The z coord.
     */
    void setZ(gpFloat z);

    /**
     * Sets the x, y and z component.
     *
     * @param x The x component.
     * @param y The y component.
     * @param z The z component.
     */
    void setXYZ(gpFloat x, gpFloat y, gpFloat z);

    /**
     * Sets components by index.
     */
    gpFloat& operator()(int);

    /**
     * Sets components by index.
     */
    gpFloat& operator[](int);
    //@}

    /**
     * Reflect the vector on a surface with normal n, and returns the 
     * reflected vector. n does not need to be normalized.
     *
     * @param n The normal vector n.
     * @return The reflected vector.
     */
    GPVector NReflectVector(GPVector n);

    /**
     * Reflect the vector on a surface with tangent t. Returns the reflected 
     * vector. t does not need to be normalized.
     *
     * @param t The vector t.
     * @return The reflected vector.
     */
    GPVector TReflectVector(GPVector t);

    /**
     * Setter with mag? theta? and phi?
     *
     * @param mag The magnitude?
     * @param theta Theta component?
     * @param phi The phi.
     */
    void setMagThetaPhi(gpFloat mag, gpFloat theta, gpFloat phi);

    /**
     * Sets the transverse component, theta and phi.
     *
     * @param pt The transverse component
     * @param theta the theta meh.
     * @param phi The phi part.
     */
    void setPtThetaPhi(gpFloat pt, gpFloat theta, gpFloat phi);

    /**
     * The azimuth angle.
     *
     * @return The azimuth angle, ranging from -PI to PI.
     */
    gpFloat phi() const;

    /**
     * Returns the polar angle.
     *
     * @return the polar angle.
     */
    gpFloat theta() const;

    /**
     * Returns the cosine of the polar angle.
     *
     * @return the cosine of the polar angle.
     */
    gpFloat cosTheta() const;

    /**
     * Returns the magnitude squared (rho to the power of 2 in a spherical
     * coordinate system).
     *
     * @return the magnitude squared.
     */
    gpFloat mag2() const;

    /**
     * The magnitude (rho in spherical coordinate system).
     *
     * @return the magnitude.
     */
    gpFloat mag() const;

    /**
     * Set phi keeping mag and theta constant.
     *
     * @param  phi The phi.
     */
    void setPhi(gpFloat phi);

    /**
     * Set theta keeping mag and phi constant.
     * @param theta
     */
    void setTheta(gpFloat theta);

    /**
     * Set magnitude keeping theta and phi constant.
     *
     * @param mag The magnitude.
     */
    void setMag(gpFloat mag);

    /**
     * The transverse component squared (R^2 in cylindrical coordinate system).
     *
     * @return the transerver componanet squared.
     */
    gpFloat perp2() const;

    /**
     * The transverse component (R in cylindrical coordinate system).
     *
     * @return the transverse component.
     */
    gpFloat pt() const;

    /**
     * The transverse component (R in cylindrical coordinate system).
     * 
     * @return the transverse component in the cylindrical coordinate system.
     */
    gpFloat perp() const;

    /**
     * Set the transverse component keeping phi and z constant.
     *
     * @param p The transverse component.
     */
    void setPerp(gpFloat p);

    /**
     * The transverse component w.r.t. given axis squared.
     *
     * @param other The other GPVector reference.
     */
    gpFloat perp2(const GPVector& other) const;

    /**
     * The transverse component w.r.t. given axis.
     *
     * @param other The other.
     * @return something
     */
    gpFloat pt(const GPVector& other) const;

    /**
     * The transverse component w.r.t. given axis.
     *
     * @param o The other vector?
     */
    gpFloat perp(const GPVector& o) const;

    /**
     * @name Operators
     * Operator overloadings, to make certain operations easier.
     */
     //@{
    
    /**
     * Equality.
     */
    bool operator==(const GPVector&) const;

    /**
     * Difference.
     */
    bool operator!=(const GPVector&) const;

    /**
     * Addition.
     */
    GPVector& operator+=(const GPVector&);

    /**
     * Subtraction.
     */
    GPVector& operator-=(const GPVector&);

    /**
     * Unary minus.
     */
    GPVector operator-() const;

    /**
     * Scaling with real numbers.
     */
    GPVector& operator*=(gpFloat);

    /**
     * Addition of three vectors.
     */
    GPVector operator+(const GPVector&);

    /**
     * Subtraction of three vectors.
     */
    GPVector operator-(const GPVector &);

    /**
     * Scalar product of three vectors.
     */
    gpFloat operator*(const GPVector &);

    /**
     * Scaling of 3-vectors with a real number.
     */
    GPVector operator*(gpFloat a);
    //@}

    /**
     * Unit vector parallel to this.
     */
    GPVector unit() const;

    /**
     * Vector orthogonal to this.
     */
    GPVector orthogonal() const;

    /**
     * Scalar product.
     */
    gpFloat dot(const GPVector &) const;

    /**
     * Cross product.
     */
    GPVector cross(const GPVector &) const;

    /**
     * The angle w.r.t. another 3-vector. 
     */
    gpFloat angle(const GPVector &) const;

    /**
     * Rotates the vector around the x-axis.
     */
    void rotateX(gpFloat);

    /**
     * Rotates the vector around the y-axis.
     */
    void rotateY(gpFloat);

    /**
     * Rotates the vector around the z-axis.
     */
    void rotateZ(gpFloat);

    /**
     * Rotates reference frame from Uz to newUz (unit vector).
     */
    void rotateUz(const GPVector&);

    /**
     * Rotates around the axis specified by another vector.
     */
    void rotate(gpFloat, const GPVector &);

    /**
     * Print vector parameters.
     */
    void print() const;

    friend ostream &operator<<(ostream &stream, const GPVector &V);
    friend GPVector operator * (gpFloat a, const GPVector &);

    bool operator < (const GPVector& rhs) const
    {
        return m_x < rhs.getX();
    }

private:
    /**
     * @name Components
     * The components.
     */
    //@{

    /// X component
    gpFloat m_x;

    /// Y component
    gpFloat m_y;

    /// Z component
    gpFloat m_z;

    //@}
};

///ostream utility function
ostream &operator<<(ostream &str, const GPVector &V);

/// Scaling of 3-vectors with a real number
GPVector operator * (gpFloat a, const GPVector &);

} // namespace gp

#endif // VECTOR_H_
