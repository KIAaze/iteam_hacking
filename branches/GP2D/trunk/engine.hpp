#ifndef _GP_ENGINE_H_
#define _GP_ENGINE_H_

#include "exception.hpp"

namespace gp {

/**
 * GPEngine can be seen as a class which contains functions useful for
 * initializing and shutting down the Simple Directmedia Layer and the OpenAL
 * audio implementation. 
 */
class GPEngine {

public:
    /**
     * Constructor to create the GPEngine object.
     */
    GPEngine();
    
    /**
     * Destructor of the GPEngine. Must be public or implementations will
     * suffer from it.
     */
    ~GPEngine();

    /**
     * Initializes everything, i.e. every subsystem available. The easiest one
     * to use, and pretty much the one which you'll always want.
     *
     * @throw GPException when all of the subsystems could not be
     *   initialized.
     */
    void initialize() throw(GPException);

    /**
     * Simply just shuts down all of the subsystems. This function should be
     * executed at all times after an application is finished using GP. It
     * does a delegate call to the SDL API (SDL_Quit()) so it is killed
     * gracefully, without leaking memory occupied by SDL.
     */
    void shutdown();
    
    /**
     * 
     */ 
    void wait(int);
};

}

#endif
