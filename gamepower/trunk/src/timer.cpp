#include "timer.h"

namespace gp {

    GPTimer::GPTimer() {
        startTicks = 0;
        pausedTicks = 0;
        paused = false;
        started = false;
    }

    void GPTimer::start ( void ) {
        started = true;// Start the timer
        paused = false;// Make sure we are not paused
        this->startTicks = SDL_GetTicks();// Grab the current tick count
    }

    void GPTimer::stop ( void ) {
        started = false;// Stop the timer
        paused =false;// Make sure we are not paused
    }

    void GPTimer::pause ( void ) {
        if ((!paused) && (started)) {
            paused = true;
            pausedTicks = SDL_GetTicks() - startTicks;
        }
    }

    void GPTimer::reset() {
        startTicks = SDL_GetTicks();// Grab the current tick count
        pausedTicks = 0;
    }

    void GPTimer::unpause ( void ) {
        if ( paused == true ) {
            paused = false;
            startTicks = SDL_GetTicks() - pausedTicks;
        }
    }

    int GPTimer::getTicks ( void ) {
        if ( started) {
            if (paused) {
                return pausedTicks;
            } else {
                return SDL_GetTicks() - startTicks;
            }
        }
        return 0;
    }

    bool GPTimer::isStarted() {
        return started;
    }

    bool GPTimer::isPaused() {
        return paused;
    }

}
