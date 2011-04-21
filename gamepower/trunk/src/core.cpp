#include "core.h"
#include "graphics.h"
#include "framerate.h"

#include <sstream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <cmath>
using namespace std;

namespace gp {

//==============================================================================
// Exception classes:
//==============================================================================

GPException::GPException(string what, string detail) :
        m_what(what),
        m_detail(detail),
        m_concat(m_what + " (Detail: " + m_detail + ")") {
}

GPException::~GPException() throw() {
}

const std::string GPException::getDetail() const throw() {
    return m_detail;
}

const char* GPException::what() const throw() {
    return m_concat.c_str();
}




//==============================================================================
// Engine class:
//==============================================================================

GPEngine* GPEngine::m_instance = NULL;

GPEngine::GPEngine() {
}

GPEngine::~GPEngine() {
    // when the engine is destroyed... shut it all down.
    shutdownAll();
}

// return the m_obj_first and only instance here.
GPEngine* GPEngine::getInstance(void) {
    // if the instance pointer is null (not inited)
    if(m_instance == NULL) {
        // create the new instance
        m_instance = new GPEngine();

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
void GPEngine::initAll(void) throw(GPException) {
    int status = SDL_Init(SDL_INIT_EVERYTHING);
    if(status != 0) {
        throw GPException("Failed to initialize the complete engine", SDL_GetError());
    }

    try {
        initText();
    } catch (GPException& ex) {
        throw; // re throw it.
    }
}

void GPEngine::initTimer(void) throw(GPException) {
    int status = SDL_InitSubSystem(SDL_INIT_TIMER);
    if(status != 0) {
        throw GPException("Failed to initialize Timer subsystem", SDL_GetError());
    }
}

void GPEngine::initAudio(void) throw(GPException){
    // XXX: use OpenAL here instead of SDL_AUDIO??
    int status = SDL_InitSubSystem(SDL_INIT_AUDIO);
    if(status != 0) {
        throw GPException("Failed to initialize Audio subsystem", SDL_GetError());
    }
}

void GPEngine::initVideo(void) throw(GPException){
    int status = SDL_InitSubSystem(SDL_INIT_VIDEO);
    if(status != 0) {
        throw GPException("Failed to initialize Video subsystem", SDL_GetError());
    }
}

void GPEngine::initCDRom(void) throw(GPException) {
    int status = SDL_InitSubSystem(SDL_INIT_CDROM);
    if(status != 0) {
        throw GPException("Failed to initialize CD-ROM subsystem", SDL_GetError());
    }
}

void GPEngine::initJoystick(void) throw(GPException) {
    int status = SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    if(status != 0) {
        throw GPException("Failed to initialize Joystick subsystem", SDL_GetError());
    }
}

void GPEngine::initNoParachute(void) throw(GPException) {
    int status = SDL_InitSubSystem(SDL_INIT_NOPARACHUTE);
    if(status != 0) {
        throw GPException("Failed to initialize Parachute subsystem", SDL_GetError());
    }
}

void GPEngine::initEventThread(void) throw(GPException) {
    int status = SDL_InitSubSystem(SDL_INIT_EVENTTHREAD);
    if(status != 0) {
        throw GPException("Failed to initialize Event Thread subsystem", SDL_GetError());
    }
}

void GPEngine::initText(void) throw(GPException) {
    if(TTF_Init() == -1) {
        throw GPException("Failed to initialize Text/Font subsystem", TTF_GetError());
    }
}

void GPEngine::shutdownAll(void) {
   // TODO: There's something like a bug in SDL_TTF that when SDL quits, it doesn't
   // free the fonts from memory, thus causing a memory leak randomly when running
   // the game again. I'm too sleepy to add this, but all it is needed to be done
   // is to use an iterator for each created GPFont() object (there can be only
   // one, but I didn't add any singleton stuff for it (like Azzkikr did to
   // GPFramerate) and use TTF_CloseFont() on each one of them.
   //
   // So in short, add singleton stuff to GPFont so its pointer can be reached
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

GPWordFilter::GPWordFilter() {
}

GPWordFilter::~GPWordFilter() {
}

void GPWordFilter::addWord(string word) {
    m_wordList.insert(word);
}

void GPWordFilter::loadWordList(string location) throw (GPException) {
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
        throw GPException(s.str());
    }
}

string GPWordFilter::applyFilter(string target) {
    return applyFilter(target, '*');
}

string GPWordFilter::applyFilter(string target, char repl) {
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


string GPWordFilter::applyFilter(string target, string repl) {
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

GPThread::GPThread() :
        m_name(""),
        m_thread(NULL),
        m_running(false) {
    // in the constructor, initialize the basic thread to NULL first to prevent
    // undefined behaviour of the value of m_thread.
}

GPThread::GPThread(string name) :
        m_name(name) {
}

GPThread::~GPThread() {
    // forcefully delete the thread, if not NULL.
    if(m_thread != NULL) {
        stop();
    }
}

gpInt32 GPThread::registerThread(void* threadPtr) {
    GPThread* thread = reinterpret_cast<GPThread*>(threadPtr);
    if(thread == NULL) {
        // Do not throw an exception here.
        cerr << "Thread was not created!" << endl;
        return -1;
    }

    thread->run();

    return 1; // yeah.. what else? Nobody is listening for this value anyway.
}


void GPThread::start() throw (GPException) {
    // basically initializes and starting the thread by creating it using the
    // SDL_CreateThread function.

    // If not already running, start it. We should and must not start a thread
    // twice in a GPThread object instance. To prevent this, check for the
    // boolean m_running and if the m_thread struct is NOT NULL.
    if(!m_running && m_thread == NULL) {
        m_thread = SDL_CreateThread(GPThread::registerThread, this);
        if(m_thread == NULL) {
            string err = "Unable to create thread";
            if(!getName().empty()) {
                err += " `" + getName() + "'"; // append name, if given
            }

            throw GPException(err, SDL_GetError());
        }

        m_running = true;

        clog << "Thread (ID ";
        clog << getID();
        if(!getName().empty()) {
            clog << " - `" << getName() << "'"; // append the name, if given
        }
        clog << ") started" << endl;;

    }
}



void GPThread::stop() {
    if(m_running && m_thread != NULL) {
        clog << "Thread (ID ";
        clog << getID();
        if(!getName().empty()) {
            clog << " - `" << getName() << "'"; // append the name, if given
        }
        clog << ") killed" << endl;

        // FORCEFULLY kill it, without checking for return values... not that
        // we do that, anyway... possible fixing needed?
        SDL_KillThread(m_thread);

        m_running = false; // mark as stopped.
    }
}

void GPThread::waitForFinish() {
    if(m_running && m_thread != NULL) {
        clog << "Waiting for thread (ID " << getID();
        if(!getName().empty()) {
            clog << " - `" << getName() << "'";
        }
        clog << ") to finish" << endl;

        // actually wait for the thread to finish, here
        SDL_WaitThread(m_thread, NULL);

        clog << "Thread (ID " << getID();
        if(!getName().empty()) {
            clog << " - `" << getName() << "'";
        }
        clog << ") finished" << endl;
    }
}

gpBool GPThread::isRunning() const {
    return m_running;
}

gpUint32 GPThread::getID() const {
    if(m_thread != NULL && isRunning()) {
        return SDL_GetThreadID(m_thread);
    } else {
        return 0;
    }
}

void GPThread::setName(string name) {
    m_name = name;
}

string GPThread::getName() const {
    return m_name;
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
    double logbase2 = log(x) / log(2);
    return (pow(2,ceil(logbase2)));
}

int closestpoweroftwo(int x) {
    double logbase2 = log(x) / log(2);
    return (pow(2,rround(logbase2)));
}

double RadToDeg(double a_rad) {
    return a_rad/M_PI*180.;
}

double DegToRad(double a_deg) {
    return a_deg/180.*M_PI;
}

} // namespace gp
