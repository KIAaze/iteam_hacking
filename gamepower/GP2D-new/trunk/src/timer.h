#ifndef _GP_TIMER_H
#define _GP_TIMER_H
#include "gp2d.h"

namespace gp {

class GPTimer {
private:
    bool started;
    bool paused;
    unsigned int startTicks;
    unsigned int pausedTicks;
public:
    GPTimer();
    void start ( void );
    void stop ( void );
    void reset ();
    void pause ( void );
    void unpause ( void );
    int getTicks ( void );
    bool isStarted();
    bool isPaused();
};

}

#endif
