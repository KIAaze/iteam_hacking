#include "core.h"
#include "graphics.h"
#include "framerate.h"

#include <sstream>
#include <SDL/SDL_gfxPrimitives.h>
#include <GL/gl.h>
#include <GL/glext.h>

using namespace std;

namespace gp2d {

//==============================================================================
// Exception classes:
//==============================================================================

GP2DException::GP2DException(const string& what) {
    m_what = what;
}

GP2DException::GP2DException(const string& what, const string& detail) {
    m_what = what;
    m_detail = detail;
}

GP2DException::~GP2DException() throw() {
}

const std::string GP2DException::getDetail() const throw() {
    return m_detail;
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
// Base collision class:
//==============================================================================
GP2DCollision::GP2DCollision() {
}

GP2DCollision::~GP2DCollision(){
}

bool GP2DCollision::isColliding() {
    return false;
}

const GP2DObject* GP2DCollision::getObject1() {
    return m_obj_first;
}

const GP2DObject* GP2DCollision::getObject2() {
    return m_obj_secnd;
}

void GP2DCollision::setObject1(GP2DObject& object) {
    m_obj_first = &object;
}

void GP2DCollision::setObject2(GP2DObject& object) {
    m_obj_secnd = &object;
}

//==============================================================================
// Bounds collision class:
//==============================================================================
GP2DBoundsCollision::GP2DBoundsCollision(GP2DObject& first, GP2DObject& second) {
    setObject1(first);
    setObject2(second); 
}

GP2DBoundsCollision::~GP2DBoundsCollision() {
    // do not delete the m_obj_first and second, because they might be used 
    // elsewhere still in the program.
}


bool GP2DBoundsCollision::isColliding() {
    /* 
     * This very simple bounds collision check does collision check based on the
     * bounds of a 2D object. Very simple and clean, but probably not very 
     * practical for use. Anyway, the values used here are the X and Y values,
     * and the width/height of the GP2DObject in question. 
     * 
     * This also means that if the object is rotated or such, that the x and y
     * and width and height remains the same. This might pose a problem when the
     * object is rotated in the viewing space, because essentially, the boundaries
     * for collisions change that way.
     * 
     * TODO: Must find a way to cleanly solve this. Probably somewhere in 
     * GP2DObject, where the two-dimensional bounds must be calculated based on
     * rotation, sizing and all other possible operations.
     */
    const GP2DObject* first = getObject1();
    const GP2DObject* second = getObject2();
    
    float x1 = first->getX();
    float y1 = first->getY();
    float x1w = x1 + first->getWidth();
    float y1h = y1 - first->getHeight();
    
    float x2 = second->getX();
    float y2 = second->getY();
    float x2w = x2 + second->getWidth();
    float y2h = y2 - second->getHeight();
    
    bool collide_left = (x1w >= x2);
    bool collide_right = (x1 <= x2w);
    bool collide_top = (y1h <= y2);
    bool collide_bottom = (y1 >= y2h);
    
    return collide_left && collide_right && collide_top && collide_bottom;
}

//==============================================================================
// Pixel collision class:
//==============================================================================
GP2DPixelCollision::GP2DPixelCollision(GP2DSprite& first, GP2DSprite& second) {
    setObject1(first);
    setObject2(second); 
    m_sprite_first = &first;
    m_sprite_second = &second;
}

GP2DPixelCollision::~GP2DPixelCollision() {
    // do not delete the m_obj_first and second, because they might be used 
    // elsewhere still in the program.
}


bool GP2DPixelCollision::isColliding() {
    /*
     * TODO: DARKGuy, this is where you might want to check things out. As you
     * can see in the constructor, I've assigned two private variables (the 
     * sprites). You can refer to these in this function, and check for 
     * collision with each other.
     */

	GP2DWindow* window = GP2DWindow::getInstance();
    const GP2DObject* first = m_sprite_first;
    const GP2DObject* second = m_sprite_second;

    float x1 = first->getX();
    float y1 = first->getY();
    float x1w = x1 + first->getWidth();
    float y1h = y1 - first->getHeight();
        
    float x2 = second->getX();
    float y2 = second->getY();
    float x2w = x2 + second->getWidth();
    float y2h = y2 - second->getHeight();
         
    bool collide_left = (x1w >= x2);
    bool collide_right = (x1 <= x2w);
    bool collide_top = (y1h <= y2);
    bool collide_bottom = (y1 >= y2h);
    
    bool box_collide = collide_left && collide_right && collide_top && collide_bottom;
    
    // do some calculations based on SDL data.
    if(window->getRenderMode() == GP2DWindow::GP2D_SDL) {
        
        // sanity check. When we are within the bounds, there MIGHT be a possible
        // collision. If not within the bounds, do not even bother checking plzkthx :D
        if(box_collide) {
        
            boxRGBA(window->getSurface(), 0, 0, 16, 16, 255, 0, 0, 255);
        
            float x2lol=0,y2lol=0;
            float x1lol=0,y1lol=0;
            x2lol=x2;
            y2lol=y2;
            x1lol=x1;
            y1lol=y1;
            if(x2<0){ x2lol=0; }
            if(y2<0){ y2lol=0; }
            if(x1<0){ x1lol=0; }
            if(y1<0){ y1lol=0; }
            
            hlineRGBA(window->getSurface(),
                    static_cast<int>(x2lol),
                    static_cast<int>(x2+second->getWidth()),
                    static_cast<int>(y2),
                    255,0,0,255);
            hlineRGBA(window->getSurface(),
            		static_cast<int>(x2lol),
            		static_cast<int>(x2+second->getWidth()),
            		static_cast<int>(y2+second->getHeight()),
            		255,0,0,255);
            vlineRGBA(window->getSurface(),
                    static_cast<int>(x2lol),
                    static_cast<int>(y2),
                    static_cast<int>(y2+second->getHeight()),
                    255,0,0,255);
            vlineRGBA(window->getSurface(),
                    static_cast<int>(x2+second->getWidth()),
                    static_cast<int>(y2),
                    static_cast<int>(y2+second->getHeight()),
                    255,0,0,255);
    
    
            hlineRGBA(window->getSurface(),
                    static_cast<int>(x1lol),
                    static_cast<int>(x1+first->getWidth()),
                    static_cast<int>(y1),
                    0,0,255,255);
            hlineRGBA(window->getSurface(),
                    static_cast<int>(x1lol),
                    static_cast<int>(x1+first->getWidth()),
                    static_cast<int>(y1+first->getHeight()),
                    0,0,255,255);
            vlineRGBA(window->getSurface(),
                    static_cast<int>(x1lol),
                    static_cast<int>(y1),
                    static_cast<int>(y1+first->getHeight()),
                    0,0,255,255);
            vlineRGBA(window->getSurface(),
                    static_cast<int>(x1+first->getWidth()),
                    static_cast<int>(y1),
                    static_cast<int>(y1+first->getHeight()),
                    0,0,255,255);
        }
    }
#ifndef NOGL
    else { // if rendermode != GP2D_SDL, in otherwords.. OGL?
        // The bounding box collides. We can now bother checking 
        if(box_collide) {            
            clog << "Box collision" << endl;
            GP2DTexture* tex = m_sprite_first->getTexture();
            if(tex != NULL) {
//                SDL_Surface* surf = m_sprite_first->getTexture()->getSurface();
            }
        }
    }
#endif
    return false;
}


//==============================================================================
// Collision event. Empty implementation.
//==============================================================================
GP2DCollisionEvent::GP2DCollisionEvent() {
}

GP2DCollisionEvent::~GP2DCollisionEvent() {
}

void GP2DCollisionEvent::collided(GP2DCollision& collision) {
    cout << "GP2DCollisionEvent::collided()" << endl;
}

//==============================================================================
// Collision event. Empty implementation.
//==============================================================================

GP2DCollisionManager::GP2DCollisionManager() {
}

GP2DCollisionManager::~GP2DCollisionManager() {
    m_collisions.clear(); // clear out just to be sure.. probably not necessary,
                          // because the m_collisions goes out of scope anyway.
}

void GP2DCollisionManager::addCollision(GP2DCollision* coll) {
	// re-set the iterator to the first available spot in the vector.
	m_iter = m_collisions.begin();
	// now, add a collision to the vector
    m_collisions.insert(m_iter, coll);
}

void GP2DCollisionManager::registerEvent(GP2DCollisionEvent* event) {
    m_event = event;
}

void GP2DCollisionManager::handleCollisions() {
    vector<GP2DCollision*>::iterator it;
    for (it = m_collisions.begin() ; it < m_collisions.end(); it++) {
        GP2DCollision* coll = *it;
        if(coll->isColliding()) {
            // check if the registered callback event is NOT null
            if(m_event != NULL) {
                // not null? then callback damn it!
                m_event->collided(*coll);
            }
        }
    }
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
    clog << "Calcuing " << x  <<  endl;
    double logbase2 = log(x) / log(2);
    clog << "logbase2: " << logbase2 << endl;
    clog << "rround:   " <<  rround(pow(2,ceil(logbase2))) << endl;
    return rround(pow(2,ceil(logbase2)));
}

} // namespace gp2d

