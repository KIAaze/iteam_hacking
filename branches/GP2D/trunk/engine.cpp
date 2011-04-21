#include "engine.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

using namespace std;

namespace gp {

GPEngine::GPEngine() {
    /// If we're on Windows, we need a console and redirect stdout/stderr to
    /// the console window so we can have a linux-style console to see
    /// stdout/stderr. Windows bug I guess.
    #ifdef _WIN32
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    #endif
}

GPEngine::~GPEngine() {
    shutdown();
}

/**
 * Basically initializes everything
 */
void GPEngine::initialize(void) throw(GPException) {

    int status = SDL_Init(SDL_INIT_EVERYTHING);
    if(status != 0) {
        throw GPException("Failed to initialize the GamePower engine", SDL_GetError());
    }

    if(TTF_Init() == -1) {
        throw GPException("Failed to initialize the text/font subsystem", TTF_GetError());
    }
}

void GPEngine::shutdown(void) {
    /**
     * TODO: There's something like a bug in SDL_TTF that when SDL quits, it
     * doesn't free the fonts from memory, thus causing a memory leak randomly
     * when running the game again. I'm too sleepy to add this, but all it is
     * needed to be done is to use an iterator for each created GPFont() object
     * (there can be only one, but I didn't add any singleton stuff for it
     * (like Azzkikr did to GPFramerate) and use TTF_CloseFont() on each one of
     * them.
     *
     * So in short, add singleton stuff to GPFont so its pointer can be reached
     * here so we can get access to m_fonts[] and use TTF_CloseFont on each of
     * its elements which are TTF_Font pointers. The iteration must be done
     * before the TTF_WasInit() check. Even if the bug doesn't really exist
     * and/or was already fixed, we should still close the fonts one by one,
     * since not even SDL handles TTF on its own, from what I could see since it
     * doesn't run TTF_Init() in its SDL_INIT_EVERYTHING flag.
     *
     * I know zero French, except "Au Revoir", but since it's very similar to
     * Spanish, I could kinda figure this info out. Thread is here:
     *
     * http://www.developpez.net/forums/showthread.php?t=330960
     *
     * -DARKGuy
     */

    if(TTF_WasInit() == 1){
        TTF_Quit();
    }
    SDL_Quit();
}

void GPEngine::wait(int milliseconds) {
    SDL_Delay(milliseconds);
}

}
