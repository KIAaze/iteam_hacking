#include "timer.h"

namespace gp2d {

    GP2DTimer::GP2DTimer() {
        startTicks = 0;
        pausedTicks = 0;
        paused = false;
        started = false;
    }

    void GP2DTimer::start ( void ) {
        started = true;// Start the timer
        paused = false;// Make sure we are not paused
        this->startTicks = SDL_GetTicks();// Grab the current tick count
    }

    void GP2DTimer::stop ( void ) {
        started = false;// Stop the timer
        paused =false;// Make sure we are not paused
    }

    void GP2DTimer::pause ( void ) {
        if ((!paused) && (started)) {
            paused = true;
            pausedTicks = SDL_GetTicks() - startTicks;
        }
    }

    void GP2DTimer::reset() {
        startTicks = 0;
        pausedTicks = 0;
    }

    void GP2DTimer::unpause ( void ) {
        if ( paused == true ) {
            paused = false;
            startTicks = SDL_GetTicks() - pausedTicks;
        }
    }

    int GP2DTimer::getTicks ( void ) {
        if ( started) {
            if (paused) {
                return pausedTicks;
            } else {
                return SDL_GetTicks() - startTicks;
            }
        }
        return 0;
    }

    bool GP2DTimer::isStarted() {
        return started;
    }

    bool GP2DTimer::isPaused() {
        return paused;
    }

}
