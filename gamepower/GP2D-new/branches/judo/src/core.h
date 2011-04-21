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
