#ifndef _GP2D_CORE_H_
#define _GP2D_CORE_H_

#include <SDL/SDL.h>

#include <string>
#include <set>
#include <exception>
#include <vector>
#include <iostream>
#include <fstream>

#ifdef _WIN32

#include "windows.h"

#endif

namespace gp2d {

/**
 * Type definitions: a few type definitions for the GP2D.
 */

/// Signed character to denote a byte in the range of (0  255).
typedef unsigned char gp2dByte;

/// A signed short.
typedef signed short gp2dShort;

/// A signed 32 bit integer.
typedef signed int gp2dInt32;

/// An unsigned short.
typedef unsigned short gp2dUshort;

/// And unsigned 32 bit integer.
typedef unsigned int gp2dUint32;

/// A float type.
typedef float gp2dFloat;

/// A double type.
typedef double gp2dDouble;

// Boolean value.
typedef bool gp2dBool;

/**
 * The GP2DException is the base class for every exception within the GP2D
 * framework. It extends the std::exception class (as recommended by various
 * sites and people from IRC on ##c++ on Freenode).
 *
 * Feel free to extend this class within the GP2D framework to make custom
 * exceptions.
 *
 * TODO: make use of char* to adhere to the standard of std::exception (IRC logs)
 *
 * @author krpors
 */
class GP2DException : public std::exception {
private:

    /// The description of the GP2DException.
    std::string m_what;

    /// Detail of the exception.
    std::string m_detail;

    /// Used to concatenate what and detail.
    std::string m_concat;

public:
    /**
     * Creates the GP2DException provided with a descriptive string.
     *
     * @param description The string used to describe what the exception
     *   actually is.
     * @param detail A detail message. Default is "" (an empty string).
     */
    explicit GP2DException(std::string description, std::string detail = "");

    /**
     * Destructor of the GP2DException.
     */
    virtual ~GP2DException() throw();

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
     * Initializes the audio subsystem. TODO: OpenAL?
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
     * @param target The sentence or phrase, or whatever, that needs to
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

/**
 * The GP2DThread class enables you to create a thread within the GP2D framework.
 * The 'backbone' of this GP2DThread relies on functions supplied by SDL. To use
 * threads, you simply subclass this class, and override the pure virtual
 * function run(). The code within run() will be the threaded code.
 *
 * Because the run() function is pure virtual, this class cannot be used without
 * being subclassed.
 *
 * @author krpors
 */
class GP2DThread {
private:

    /// The name of the thread. May be empty.
    std::string m_name;

    /// The SDL_Thread struct pointer.
    SDL_Thread* m_thread;

    /// Indication whether the thread is started and has not yet finished execution.
    gp2dBool m_running;

    /**
     * This static function is actually the 'callback' function used as the first
     * parameter in the SDL_CreateThread() function:
     *
     * SDL_CreateThread(int (void*)(), void* parameters);
     *
     * The first parameter used there is actually a pointer to this static function!
     * The parameter `threadPtr' is _always_ a pointer to the GP2DThread which is
     * started.
     *
     * @param threadPtr The pointer to the GP2DThread which is being started.
     */
    static gp2dInt32 registerThread(void* threadPtr);


public:

    /**
     * Constructor for the GP2DThread.
     */
    GP2DThread();

    /**
     * Creates a thread with a name attached to it (for identification purposes).
     *
     * @param name The name of the thread.
     */
    GP2DThread(std::string name);

    /**
     * Virtual destructor. When this object is deleted, it will forcefully stop
     * the current running thread. In SDL terms: SDL_KillThread().
     *
     * @see stop()
     */
    virtual ~GP2DThread();

    /**
     * Creates and starts the thread. This will implicitly invoke the pure
     * virtual run() function in subclasses.
     */
    void start() throw (GP2DException);

    /**
     * Forcefully kill the thread, if running.
     */
    void stop();

    /**
     * Waits for a thread to finish.
     */
    void waitForFinish();

    /**
     * Gets the current thread ID as a signed 32 bit integer. If no thread was
     * running, return -1.
     *
     * @return The thread ID when running, or -1 when not running.
     */
    gp2dUint32 getID() const;

    /**
     * Returns whether the thread is running.
     *
     * @return true if running, false if otherwise.
     */
    gp2dBool isRunning() const;

    /**
     * Sets the name of the thread.
     *
     * @param name The name to identify this thread.
     */
    void setName(std::string name);

    /**
     * Gets the name of the thread.
     *
     * @return The name identifying this thread.
     */
    std::string getName() const;

    /**
     * This pure virtual function is the thread worker. When subclassed, override
     * this function to implement functionality for the thread.
     */
    virtual void run() = 0;
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
