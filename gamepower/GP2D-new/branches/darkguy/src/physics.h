/*! \file physics.h
\brief Physics engine

Used to process movement of physical objects.
*/

#ifndef IT_PHYSICS_H
#define IT_PHYSICS_H

#include <map>

#include "gp2d.h"
#include "framerate.h"

namespace gp2d {
    
    class GP2DFramerate; // to correct compiling problems

    class GP2DVector; // defined later on as this is only used internally

    enum GP2DPhysShape {
        CIRCLE,
        CONVEX_POLYGON//,
        //CONCAVE_POLYGON
    };

    typedef enum {
        GAS // gravity is not applied, attempts to achieve  equilibrium
    } GP2DParticleType;
    
    // Okay, I know these structs are identical, but don't question my decisions :D
    
    /*typedef struct {
        GP2DVector tr; // top right quadrant
        GP2DVector tl; // top left quadrant
        GP2DVector bl; // bottom left quadrant
        GP2DVector br; // bottom right quadrant
    } GP2DPhysAABB; // Axis-align bounding box*/
    
    struct GP2DPhysAABB {
        GLfloat x; // top left coordinate of the box
        GLfloat y;
        GLfloat height;
        GLfloat width;
    }; // axis-aligned bounding box
     
    class GP2DPhysSolidObject : public GP2DSprite {

    public:

        /// general functions
		GP2DPhysSolidObject(void); /* required void constructor */
        GP2DPhysSolidObject(GLfloat width, GLfloat height,
                        GLfloat mass, GP2DPhysShape shape, GP2DTexture* texture); /* Constructor */
        virtual ~GP2DPhysSolidObject(void); /* Descrutor */

        // setters and getters
        virtual GP2DPhysShape getShape(void); /* Shapes are defined in the enum above */   
        virtual void setMass(GLfloat newMass); /* Mass of this object is dynamic, but do be careful */
        virtual GLfloat getMass(void); /* Returns the current mass of the object */
        virtual void setGravity(GLfloat gravityConstant); /* Set the acceleration due to gravity, should be negative */
        virtual GLfloat getGravity(void); /* Returns the current gravity constant */
        virtual void setSpeed(GLfloat rate); /* setSpeed(0.5) is slow-mo, setSpeed(1.5) is.... fast-mo? */
        virtual GLfloat getSpeed(void); /* Returns the current rate of speed */
        virtual void setAccelerationX(GLfloat newAcceleration); /* X acceleration, positive = right */
        virtual GLfloat getAccelerationX(void); /* Returns the X acceleration */
        virtual void setAccelerationY(GLfloat newAcceleration); /* Y acceleration, positive = up */
        virtual GLfloat getAccelerationY(void); /* Returns the Y acceleration */
        virtual void setVelocityX(GLfloat newVelocity); /* X velocity, negative = left */
        virtual GLfloat getVelocityX(void); /* Returns the X velocity */
        virtual void setVelocityY(GLfloat newVelocity); /* Y velocity, negative = down */
        virtual GLfloat getVelocityY(void); /* Returns the Y velocity */
        virtual void setCoordX(GLfloat x); /* Set the X coordinate */
        virtual GLfloat getCoordX(void); /* Returns the instantaneous X coordinate */
        virtual void setCoordY(GLfloat y); /* Set the Y coordinate */
        virtual GLfloat getCoordY(void); /* Returns the instantaneous Y coordinate */
        virtual void setPhysWidth(GLfloat width); /* Set the non-graphical/physical width */
        virtual GLfloat getPhysWidth(void); /* Returns the non-graphical/physical width */
        virtual void setPhysHeight(GLfloat height); /* Set the non-graphical/physical height */
        virtual GLfloat getPhysHeight(void); /* Returns the non-graphical/physical height */
        virtual GP2DVector getCenter(void); /* Returns the coordinate of the instantaenous center of mass */
        virtual bool movingRight(void);
        virtual bool movingLeft(void);
        virtual bool movingUp(void);
        virtual bool movingDown(void);
        virtual void addPoint(GLfloat x, GLfloat y); /* be sure to add points in order */
        virtual void buildEdges(void); /* When all desired points are added, call on this to build the edge vectors */

        // physics methods
        virtual void step(GLfloat deltaTicks); /* Processes changes over time */

        /// Polygon attributes
        std::map<unsigned short int, GP2DVector*> Points;
        std::map<unsigned short int, GP2DVector*> Edges;

        GP2DPhysAABB m_AABB;

    protected:
    
        virtual void createAABB(void);
        virtual void calculateArea(void);

        // attributes
        GP2DPhysShape m_shape;
        GLfloat m_area;
        GLfloat m_mass;
        GLfloat m_width;
        GLfloat m_height;

        // instantaneous values
        GLfloat m_gravityConstant;
        GLfloat m_accelerationX;
        GLfloat m_accelerationY;
        GLfloat m_velocityX;
        GLfloat m_velocityY;
        GLfloat m_x;
        GLfloat m_y;
        GLfloat m_speed;
        bool    m_movingRight;
        bool    m_movingLeft;
        bool    m_movingUp;
        bool    m_movingDown;

        // Stuff for drawing the object
        GP2DFramerate* m_framerate;
    };

    class GP2DPhysWorld {

    public:

        /*
         * Constructor determining the size of the world.  The size can be
         * changed.  The center of the world will be (0, 0), so the greatest x
         * coordinate will be width / 2.
         *
         * @param width The width of the world.
         * @param height The height of the world.
         */
        GP2DPhysWorld(GLfloat width, GLfloat height);
        
        /*
         * Basic destructor
         */
        ~GP2DPhysWorld(void);

        /*
         * The step method is the control of time.  Given the change in time, or
         * ticks, it processes physics accordingly of all objects in this world.
         * 
         * @param deltaTicks The change in ticks since the previous loop.
         *     Handing 0.0f to this method essentially pauses physics.
         */
        virtual void step(GLfloat deltaTicks);

        /*
         * Add a physical, non-soft object to the world
         *
         * @param width The width of the object.  If a circle, this is the
         *     diameter.
         * @param height The height of the object.  If a circle, this is the
         *     diameter.
         * @param mass The mass of the object.  This determines the force of
         *     a collision and acceleration from impulses.
         * @param shape The shape of the object given by the GP2DPhysShape enum.
         *
         * @return The id of the newly created object.
         */
        virtual int addObject(GLfloat width, GLfloat height, GLfloat mass, 
            GP2DPhysShape shape, GP2DTexture* texture, GLfloat x, GLfloat y);

        /*
         * Remove an object from the world.
         *
         * @param id The id of the object to be removed.
         */
        virtual void removeObject(int id);

        /*
         * This is a generic and automatic collision detection method.
         *
         * @param object1 The id of the first object we're checking.
         * @param object2 The id of the second object we're checking.
         *
         * @return True if the two objects are overlapping.
         */
        virtual bool isColliding(GP2DPhysSolidObject* object1, 
            GP2DPhysSolidObject* object2);
            
        /*
         * A wrapper to isColliding that predicts if two objects will
         * collide in the next loop by applying the current velocities.
         * 
         * @param object1 The id of the first object we're checking.
         * @param object2 The id of the second object we're checking.
         * 
         * @return True if the two objects will collide.
         */
        virtual bool willCollide(GP2DPhysSolidObject* object1, 
            GP2DPhysSolidObject* object2);

        std::map<unsigned short int, GP2DPhysSolidObject*> Objects;

    protected:

        int m_objectCount;
        GLfloat m_width;
        GLfloat m_height;

        // collision routines called by isColliding()
        virtual bool AABBtoAABB(GP2DPhysAABB& box1,
            GP2DPhysAABB& box2);
        virtual bool rectangleToCircle(GP2DPhysSolidObject* object1,
            GP2DPhysSolidObject* object2);
        virtual bool circleToCircle(GP2DPhysSolidObject* object1,
            GP2DPhysSolidObject* object2);
        virtual bool convexPolygonToPolygon(GP2DPhysSolidObject* object1,
            GP2DPhysSolidObject* object2);
            
        virtual void project(GP2DVector* axis,
            GP2DPhysSolidObject* toProject, GLfloat& min, GLfloat& max); // projects toProject onto axis

    };

    class GP2DParticle : public GP2DSprite {

    public:
        
        GP2DParticle(void);
        GP2DParticle(GP2DParticleType type, float x, float y);
        ~GP2DParticle(void);
        virtual void setX(GLfloat newX);
        virtual GLfloat getX(void);
        virtual void setY(GLfloat newY);
        virtual GLfloat getY(void);
        virtual void setVelocityX(GLfloat newVelocity);
        virtual GLfloat getVelocityX(void);
        virtual void setVelocityY(GLfloat newVelocity);
        virtual GLfloat getVelocityY(void);
        
        virtual void step(GLfloat deltaTicks);

    protected:

        GP2DParticleType m_type;
        GLfloat m_oldTicks;
        GLfloat m_ticks;
        
        GLfloat m_x;
        GLfloat m_y;
        GLfloat m_velocityX;
        GLfloat m_velocityY;

    };

    class GP2DParticleSystem {

    public:
        
        GP2DParticleSystem(void);
        ~GP2DParticleSystem(void);
        virtual void addParticles(int numberOfParticles);
        virtual void step(GLfloat deltaTicks);
        virtual bool isColliding(GP2DParticle* particle1,
            GP2DParticle* particle2);

    protected:

        std::map<unsigned short int, GP2DParticle*> m_particles;

    };
    
    class GP2DVector {
        
    public:
        
        GP2DVector(void);
        GP2DVector(GLfloat x, GLfloat y);
        ~GP2DVector(void);
        GLfloat magnitude(void);
        GP2DVector* normalize(void);
        GLfloat dotProduct(GP2DVector& other);
        
        // operators
        /*GP2DVector operator = (const GP2DVector& other1,
            const GP2DVector& other2) const;
        GP2DVector operator + (const GP2DVector& other1,
            const GP2DVector& other2) const;
        GP2DVector operator - (const GP2DVector& other1,
            const GP2DVector& other2) const;
        GP2DVector operator * (const GP2DVector& other1,
            const GP2DVector& other2) const;
        GP2DVector operator / (const GP2DVector& other1,
            const GP2DVector& other2) const;*/
        void operator += (const GP2DVector& other);
        void operator -= (const GP2DVector& other);
        void operator *= (const GP2DVector& other);
        void operator /= (const GP2DVector& other);
        bool operator == (const GP2DVector& other) const;
        bool operator != (const GP2DVector& other) const;
        
        GLfloat x;
        GLfloat y;
    
    };

} // namespace gp2d

#endif


/*
 * THINGS TO ADD
 * - Axis-aligned bounding boxes -- DONE
 * - circle to circle collisions -- DONE
 * - circle to polygon collisions
 * - polygon to polygon collisions
 * - collision responses in GP2DPhysWorld
 *   - bouncing
 *   - friction
 * - GP2DParticle -- DONE
 * - GP2DParticleSystem
 *   - some systems may require collision detection, but this can be
 *     done with if (x1 == x2 && y1 == y2) -- DONE
 * - willCollide methods, applying velocity to predict collisions -- DONE
 * - method to add Points and edges for polygons -- DONE
 * - rotations
 * - center of mass calculations -- DONE
 *   - polygons will require area for this, so implement an area-
 *     calculating method, too -- DONE
 * - wind
 * - object to world collisions
 */
