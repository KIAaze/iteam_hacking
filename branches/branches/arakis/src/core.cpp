#include "core.h"
#include "graphics.h"
#include "framerate.h"

#include <sstream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glext.h>

using namespace std;

namespace gp2d {

//==============================================================================
// Exception classes:
//==============================================================================

GP2DException::GP2DException(const string what) {
    m_what = what;
}

GP2DException::GP2DException(const string what, const string detail) {
    m_what = what;
    m_what = what;
}

GP2DException::~GP2DException() throw() {
}

const std::string GP2DException::getDetail() const throw() {
    return m_what;
}

const char* GP2DException::what() const throw() {
    return m_what.c_str();
}

//==============================================================================
// Engine class:
//==============================================================================

GP2DEngine* GP2DEngine::m_instance = NULL;

GP2DEngine::GP2DEngine() {
}

GP2DEngine::~GP2DEngine() {
    // when the engine is destroyed... shut it all down.
    shutdownAll();
}

// return the m_obj_first and only instance here.
GP2DEngine* GP2DEngine::getInstance(void) {
    // if the instance pointer is null (not inited)
    if(m_instance == NULL) {
        // create the new instance
        m_instance = new GP2DEngine();

		#ifdef _WIN32
			// We need a console and redirect stdout/stderr to it, to have a
			// linux-style console to see stdout/stderr. Windows bug heh.
			AllocConsole();
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
		#endif

    }

    // and return it.
    return m_instance;
}

/**
 * Basically initializes everything
 */
void GP2DEngine::initAll(void) throw(GP2DException) {
    int status = SDL_Init(SDL_INIT_EVERYTHING);
    if(status != 0) {
        throw GP2DException("Failed to initialize the complete engine", SDL_GetError());
    }

    try {
        initText();
    } catch (GP2DException& ex) {
        throw; // re throw it.
    }
}

void GP2DEngine::initTimer(void) throw(GP2DException) {
    int status = SDL_InitSubSystem(SDL_INIT_TIMER);
    if(status != 0) {
        throw GP2DException("Failed to initialize Timer subsystem", SDL_GetError());
    }
}

void GP2DEngine::initAudio(void) throw(GP2DException){
    // XXX: use OpenAL here instead of SDL_AUDIO??
    int status = SDL_InitSubSystem(SDL_INIT_AUDIO);
    if(status != 0) {
        throw GP2DException("Failed to initialize Audio subsystem", SDL_GetError());
    }
}

void GP2DEngine::initVideo(void) throw(GP2DException){
    int status = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if(status != 0) {
        throw GP2DException("Failed to initialize Video subsystem", SDL_GetError());
    }
}

void GP2DEngine::initCDRom(void) throw(GP2DException) {
    int status = SDL_InitSubSystem(SDL_INIT_CDROM);
    if(status != 0) {
        throw GP2DException("Failed to initialize CD-ROM subsystem", SDL_GetError());
    }
}

void GP2DEngine::initJoystick(void) throw(GP2DException) {
    int status = SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    if(status != 0) {
        throw GP2DException("Failed to initialize Joystick subsystem", SDL_GetError());
    }
}

void GP2DEngine::initNoParachute(void) throw(GP2DException) {
    int status = SDL_InitSubSystem(SDL_INIT_NOPARACHUTE);
    if(status != 0) {
        throw GP2DException("Failed to initialize Parachute subsystem", SDL_GetError());
    }
}

void GP2DEngine::initEventThread(void) throw(GP2DException) {
    int status = SDL_InitSubSystem(SDL_INIT_EVENTTHREAD);
    if(status != 0) {
        throw GP2DException("Failed to initialize Event Thread subsystem", SDL_GetError());
    }
}

void GP2DEngine::initText(void) throw(GP2DException) {
    if(TTF_Init() == -1) {
        throw GP2DException("Failed to initialize Text/Font subsystem", TTF_GetError());
    }
}

void GP2DEngine::shutdownAll(void) {
   // TODO: There's something like a bug in SDL_TTF that when SDL quits, it doesn't
   // free the fonts from memory, thus causing a memory leak randomly when running
   // the game again. I'm too sleepy to add this, but all it is needed to be done
   // is to use an iterator for each created GP2DFont() object (there can be only
   // one, but I didn't add any singleton stuff for it (like Azzkikr did to
   // GP2DFramerate) and use TTF_CloseFont() on each one of them.
   //
   // So in short, add singleton stuff to GP2DFont so its pointer can be reached
   // here so we can get access to m_fonts[] and use TTF_CloseFont on each of
   // its elements which are TTF_Font pointers. The iteration must be done before
   // the TTF_WasInit() check. Even if the bug doesn't really exist and/or was
   // already fixed, we should still close the fonts one by one, since not even
   // SDL handles TTF on its own, from what I could see since it doesn't run
   // TTF_Init() in its SDL_INIT_EVERYTHING flag.
   //
   // I know zero French, except "Au Revoir", but since it's very similar to
   // Spanish, I could kinda figure this info out. Thread is here:
   //
   // http://www.developpez.net/forums/showthread.php?t=330960
   //
   // -DARKGuy
    if(TTF_WasInit() == 1){
        TTF_Quit();
    }
    SDL_Quit();
}

//==============================================================================

GP2DWordFilter::GP2DWordFilter() {
}

GP2DWordFilter::~GP2DWordFilter() {
}

void GP2DWordFilter::addWord(string word) {
    m_wordList.insert(word);
}

void GP2DWordFilter::loadWordList(string location) throw (GP2DException) {
    std::string temp;

    ifstream file;
    file.open(location.c_str(), std::ifstream::in);

    if(file.good()) {
        while(!file.eof()) {
            getline(file, temp); // read line by line.
            m_wordList.insert(temp);
        }

        file.close(); // always close the file.
    } else {
        file.close(); // close before throwing the exception
        stringstream s; // stringstream is used to concatenate strings.
        s << "File `" << location << "' could not be opened";
        throw GP2DException(s.str());
    }
}

string GP2DWordFilter::applyFilter(string target) {
    return applyFilter(target, '*');
}

string GP2DWordFilter::applyFilter(string target, char repl) {
    string asteriskFiller;

    set<string>::iterator it;
    int currentPosition = 0; // always starting from 0.
    for(it = m_wordList.begin(); it != m_wordList.end(); it++) {
        string currWord = *it;
        int len = currWord.size();

        bool stillFound = true;
        while(stillFound) {
            size_t findPosition = target.find(currWord, currentPosition);
            if(findPosition != target.npos) { // did we find a bad word?
                asteriskFiller.resize(len, repl); // grow an amount of characters for the word.
                target.replace(findPosition, len, asteriskFiller);
            } else {
                // nah, forget looking. The finding did not return something
                // viable, so stop looking for this word.
                stillFound = false;
            }
        }
    }

    return target;
}


string GP2DWordFilter::applyFilter(string target, string repl) {
    set<string>::iterator it;
    int currentPosition = 0; // always starting from 0.
    for(it = m_wordList.begin(); it != m_wordList.end(); it++) {
        string currWord = *it;
        int len = currWord.size();

        bool stillFound = true;
        while(stillFound) {
            size_t findPosition = target.find(currWord, currentPosition);
            if(findPosition != target.npos) { // did we find a bad word?
                target.replace(findPosition, len, repl);
            } else {
                // nah, forget looking. The finding did not return something
                // viable, so stop looking for this word.
                stillFound = false;
            }
        }
    }

    return target;
}

//==============================================================================

/**
 * Checks to see if a file exists.
 */
bool fileExists(const string filename) {
    std::ifstream input;
    input.open(filename.c_str(), std::ifstream::in);
    input.close();

    return input.fail();
}

int rround(double x) {
    return (int)(x + 0.5);
}

int nextpoweroftwo(int x) {
//    clog << "Calcuing " << x  <<  endl;
    double logbase2 = log(x) / log(2);
//    clog << "logbase2: " << logbase2 << endl;
//    clog << "rround:   " <<  rround(pow(2,ceil(logbase2))) << endl;
    return rround(pow(2,ceil(logbase2)));
}

} // namespace gp2d
