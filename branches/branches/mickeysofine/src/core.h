#ifndef _GP2D_CORE_H_
#define _GP2D_CORE_H_

#include <SDL/SDL.h>

#include <string>
#include <set>
#include <exception>
#include <vector>
#include <iostream>
#include <fstream>

namespace gp2d {

/**
 * The GP2DException is the base class for every exception within the GP2D 
 * framework. It extends the std::exception class (as recommended by various
 * sites and people from IRC on ##c++ on Freenode).
 *
 * Feel free to extend this class within the GP2D framework to make custom 
 * exceptions.
 *
 * @author krpors
 */
class GP2DException : public std::exception {
private:

    /// The description of the GP2DException.
    std::string m_what;
    
    /// Detail of the exception.
    std::string m_detail;

public:
    /**
     * Creates the GP2DException provided with a descriptive string.
     *
     * @param description The string used to describe what the exception
     *   actually is.
     */
    GP2DException(const std::string& description);
    
    /**
     * Creates the GP2DException provided with a descriptive string.
     *
     * @param description The string used to describe what the exception
     *   actually is.
     * @param detail A detail message.
     */
    GP2DException(const std::string& description, const std::string& detail);

    /**
     * Destructor of the GP2DException.
     */
    ~GP2DException() throw();
    
    /**
     * Gets the (optional) extra detail of the exception. For instance, if
     * SDL generates an error, this error could be returned by this method.
     * 
     * @return The detail message, optional.
     */
    const std::string getDetail() const throw(); 

    /**
     * Gets the description of the GP2DException. It's an overridden function
     * from the std::exception class.
     *
     * @return The description of the exception.
     */
    const char* what() const throw(); 
};

//==============================================================================

/**
 * GP2DEngine can be seen as a class which contains functions useful for 
 * initializing and shutting down the Simple Directmedia Layer and the OpenAL 
 * audio implementation. It is designed as a singleton, so only one instance 
 * ever is generated.
 * 
 * It has also other functions, like .... TODO: more docs! The engine must do
 * more than only this, I guess??!  
 */ 
class GP2DEngine {
private:
    /**
     * Private constructor to create the GP2DEngine object.
     */
    GP2DEngine();
    
protected:
    /**
     * The static instance to the GP2DEngine pointer.
     */
    static GP2DEngine* m_instance;
    
public:
    /**
     * Destructor of the GP2DEngine. Must be public or implementations will 
     * suffer from it.
     */
    ~GP2DEngine();
    
    /**
     * Gets the instance to the one and only GP2DEngine object.
     */
    static GP2DEngine* getInstance();

    /**
     * Initializes everything, i.e. every subsystem available. The easiest one
     * to use, and pretty much the one which you'll always want.
     * 
     * @throw GP2DException when all of the subsystems could not be 
     *   initialized.
     */
    void initAll() throw(GP2DException);

    /**
     * Initializes the timer from SDL, whatever that may mean.
     * 
     * @throw GP2DException when the SDL timer subsystem could not be initialized.
     */
    void initTimer() throw(GP2DException);

    /**
     * Initializes the audio subsystem. TODO: OpenAL.
     * 
     * @throw GP2DException when the audio subsystem could not be initialized.
     */
    void initAudio() throw(GP2DException);

    /**
     * Initializes the video/graphical subsystem.
     * 
     * @throw GP2DException when the video subsystem failed to initialize.
     */
    void initVideo() throw(GP2DException);

    /**
     * Initializes the CD-Rom subsystem.
     * 
     * @throw GP2DException when the CD-Rom subsystem failed to initialize.
     */
    void initCDRom() throw(GP2DException);
    
    /**
     * Initializes joystick subsystem.
     *
     * @throw GP2DException if the joystick subsystem failed to initialize.
     */
    void initJoystick() throw(GP2DException);

    /**
     * Initializes event parachute or some sorts.
     */
    void initNoParachute() throw(GP2DException);

    /**
     * Initializes event thread, whatever it is.
     */
    void initEventThread() throw(GP2DException);

    /**
     * Initializes text/font rendering subsystem.
     */
    void initText() throw(GP2DException);
    
    /**
     * Simply just shuts down all of the subsystems. This function should be
     * executed at all times after an application is finished using GP2D. It
     * does a delegate call to the SDL API (SDL_Quit()) so it is killed 
     * gracefully, without leaking memory occupied by SDL.
     */
    void shutdownAll();
};


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
    const GP2DObject* getObject1();
    
    /**
     * Returns a constant GP2DObject pointer, which is the second object.
     * 
     * @return A constant GP2DObject pointer. This is the second object set.
     */
    const GP2DObject* getObject2();
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

/**
 * The GP2DWordFilter class is used for filtering out swearwords and the like (usually
 * from text messages sent to players in multiplayer mode). Functions are specified
 * to filter them out using a character or choice or asterisks (*) by default.
 */
class GP2DWordFilter {
public:
    /**
     * Empty constructor, does nothing special.
     */
    GP2DWordFilter();

    /**
    * Dtor.
    */
    ~GP2DWordFilter();

    /**
     * Adds a particular word to the set.
     * 
     * @param word The word to add. Duplicate words are ignored.
     */
    void addWord(std::string word);
    
    /**
     * Opens the configuration file of choice. For clarification, that list should 
     * only contain the words to be removed (or replaced with some other character,
     * such as an asterisk (*)).  The confi file  is used to replace words. This 
     * file essentially updates the list that will be filtered, allowing it to be 
     * updated while the game is running.
     *
     * @param location The file path to the the configuration file.
     * @throws GP2DException when the specified file 'location' can not be found, or
     *   read from.
     */
    void loadWordList(std::string location) throw (GP2DException);

    /**
     * This will replace the words currently in the set m_wordList with asterisks.
     *
     * @param target The sentance or phrase, or whatever, that needs to
     *  be censored.
     * @return An std::string that is simply the input string replaced with
     *  asterisks where required.
     */
    std::string applyFilter(const std::string target);
    
    std::string applyFilter(const std::string target, char repl);
    
    std::string applyFilter(const std::string target, std::string repl);

private:
    
    /// A Set container, for the words (prevents duplicates).
    std::set<std::string> m_wordList;
        
};



//==============================================================================
// Utility functions come here. They are the basic functions one can use without
// instantiating a class or something. For simple practical use I guess.
//==============================================================================

/**
 * Check if the file exists. There may very well be a better way to do
 * this but this works crossplatform, I believe.
 *
 * @author compwiz18
*/
bool fileExists(const std::string filename); 

int rround(double x);

int nextpoweroftwo(int x);

} // namespace gp2d


#endif /*GP2D_H_*/
