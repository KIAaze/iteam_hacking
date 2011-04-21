#ifndef COLLISION_H_
#define COLLISION_H_

#include "core.h"
#include "graphics.h"
#include "collision.h"

namespace gp2d {

//==============================================================================
// Collision type of classes and all that start from here.
//==============================================================================

/*
 * Pretty funky. To prevent cyclic dependencies, we do NOT, I repeat NOT include
 * the "graphics.h" header file on top of this header file. Instead, we forward
 * declare every class or something that we need to use.
 */
class GP2DObject;
class GP2DSprite;


/*
 * XXX: I've been using & and * throughout the code. Most of the time, we need
 * pointers to existing classes in the code, and I am not sure whether using
 * pointers or references is better in this case. Actual websites mention that
 * "use references where possible, use pointer if necessary". So ... think about
 * this in the future for optimization purposes and/or code enhancements.
 *
 * - Azzkikr
 */

/**
 * Base class/interface for every collision type in GP2D. It actually defines
 * a virtual function isColliding(GP2DObject, GP2DObject) which all subclasses
 * must implement explicitly (due to the '= 0').
 *
 * @author krpors/azzkikr
 */
class GP2DCollision {
private:
    /// The first object..
    GP2DObject* m_obj_first;

    // ... to which the second object must collide with.
    GP2DObject* m_obj_secnd;

    /// The first object..
    GP2DSprite* m_sprite_first;

    // ... to which the second object must collide with.
    GP2DSprite* m_sprite_secnd;
protected:
    /**
     * Sets the first object. Actually only need to be used by subclasses of
     * this class.
     *
     * @param object The object to set for the first one.
     */
    void setObject1(GP2DObject& object);

    /**
     * Sets the second object. Actually only need to be used by subclasses of
     * this class.
     *
     * @param object The object to set for the second one.
     */
    void setObject2(GP2DObject& object);

    /**
     * Sets the first object. Actually only need to be used by subclasses of
     * this class.
     *
     * @param object The object to set for the first one.
     */
    void setSprite1(GP2DSprite& sprite);

    /**
     * Sets the second object. Actually only need to be used by subclasses of
     * this class.
     *
     * @param object The object to set for the second one.
     */
    void setSprite2(GP2DSprite& sprite);
public:
    /**
     * A no-no constructor. Basically does nothing.
     */
    GP2DCollision();

    /**
     * Necessary virtual destructor. Not that this does NOT and must NOT delete
     * the private object pointers in this class.
     */
    virtual ~GP2DCollision();

    /**
     * This method should return true when the object one collided with object
     * two. It is a pure virtual function, so subclasses of this class must
     * implement their own isColliding() function.
     *
     * @return true When object one collides with two, and false if otherwise.
     */
    virtual bool isColliding();

    /**
     * Returns a constant GP2DObject pointer, which is the first object.
     *
     * @return A constant GP2DObject pointer. This is the first object set.
     */
    GP2DObject* getObject1();

    /**
     * Returns a constant GP2DObject pointer, which is the second object.
     *
     * @return A constant GP2DObject pointer. This is the second object set.
     */
    GP2DObject* getObject2();

    /**
     * Returns a constant GP2DObject pointer, which is the first object.
     *
     * @return A constant GP2DObject pointer. This is the first object set.
     */
    GP2DSprite* getSprite1();

    /**
     * Returns a constant GP2DObject pointer, which is the second object.
     *
     * @return A constant GP2DObject pointer. This is the second object set.
     */
    GP2DSprite* getSprite2();
};

/**
 * This default implementation of GP2DCollision does basic bounds checking of
 * two objects. Nothing more, and nothing less. Very easy, but impractical most
 * of the time. Good for testing purposes and what not.
 *
 * @author krpors/azzkikr
 */
class GP2DBoundsCollision : public GP2DCollision {
public:

    /**
     * Creates a bounds collision checker.
     *
     * @param one The first object which is tested for collision with the second
     * @param two The second object which is tested for collision with the first
     */
    GP2DBoundsCollision(GP2DObject& one, GP2DObject& two);

    /**
     * Destructor.
     */
    ~GP2DBoundsCollision();

    /**
     * @see GP2DCollision.isColliding().
     */
    virtual bool isColliding();
};

/**
 * This GP2DPixelCollision class defines basic behaviour of pixel collision.
 * This type of pixel collision only works (currently) with GP2DSprites only,
 * mainly because GP2DSprite objects are the objects which have textures
 * assigned to them. The 2D sprites' textures collide with other textures,
 * making them an excellent example for pixel collisions.
 *
 * @author krpors
 */
class GP2DPixelCollision : public GP2DCollision {
private:
    /// The first SPRITE (not object).
    GP2DSprite* m_sprite_first;

    /// The second SPRITE (not object).
    GP2DSprite* m_sprite_second;
public:

    /**
     * Constructor to create a pixel collision check between two GP2DSprites.
     *
     * @param one The first object which is tested for collision with the second
     * @param two The second object which is tested for collision with the first
     */
    GP2DPixelCollision(GP2DSprite& one, GP2DSprite& two);

    /**
     * Destructor.
     */
    ~GP2DPixelCollision();

    /**
     * @see GP2DCollision.isColliding().
     */
    virtual bool isColliding();
};


/**
 * This class is actually a 'listener' for any collisions. It is used in
 * conjunction witht the GP2DCollisionManager. One may register events like
 * these there. If a collision is happening, the virtual void function
 * `collided` will be invoked.
 *
 * This class is meant to be subclassed. The actual function `collided()` does
 * not do anything. The subclass must implement the `collided` function, then
 * register that class with the GP2DCollisionManager to get notified of any
 * collision-events.
 *
 * TODO: rename the collision event to something like CollisionListener? It's
 * maybe a better description of the purpose of the class.
 */
class GP2DCollisionEvent {
public:
    /**
     * No-no constructor.
     */
    GP2DCollisionEvent();

    /**
     * Virtual destructor.
     */
    virtual ~GP2DCollisionEvent();

    /**
     * This method is actually the callback method for every class which
     * subclasses this class (how many times can you write class in one
     * sentence? :P). When a collision occured, this function will be invoked,
     * with the argument given which holds the actual collided information.
     *
     * @param collisionType The collision data.
     */
    virtual void collided(GP2DCollision& collisionType) = 0;
};

/**
 * The class GP2DCollisionManager is capable of managing a group of collision
 * types. One may 'register' a collision callback with a collision type. It
 * provides similarly to the input handler a processing function, which can
 * check if a collision has occured within the list of registered collisions.
 *
 * If a collision has occured, the callback function `collided()` from
 * GP2DCollisionEvent is executed.
 *
 * @author krpors
 */
class GP2DCollisionManager {
private:

    /// Collisions list.
    std::vector<GP2DCollision*> m_collisions;

    /// Iterator. Not sure if this is really necessary, but wth.
    std::vector<GP2DCollision*>::iterator m_iter;

    /// The one registered callback even.  TODO: make a list?
    GP2DCollisionEvent* m_event;

public:
    /**
     * Creates a collision manager.
     */
    GP2DCollisionManager();

    /**
     * I really don't know what a destructor does.
     */
    ~GP2DCollisionManager();

    /**
     * Adds a collision to the list of to-check.
     *
     * @param collision The collision check to add to this manager.
     */
    void addCollision(GP2DCollision* collision);

    /**
     * Registers a callback event with this manager. Whenever a collision is
     * being found by the handleCollision() function, the GP2DCollisionEvent
     * reigsteren by this function is being 'called back'.
     *
     * @param event The collision event notifier object.
     */
    void registerEvent(GP2DCollisionEvent* event);

    /**
     * Handles the collisions. Within this function, an iteration is done over
     * all the added collisions (see addCollision(GP2DCollision)). Every object
     * is tested whether it is collided, and then the callback event is
     * dispatched.
     */
    void handleCollisions();
};


}  // namespace gp2d

#endif /*COLLISION_H_*/
