#include "framerate.h"

#include <iostream>

using namespace std;

namespace gp2d {

// The one and only instance of the GP2DFramerater.
// Firstly initialized to NULL, or else we get some errors :)
GP2DFramerate* GP2DFramerate::m_instance = NULL;

GP2DFramerate* GP2DFramerate::getInstance() {
    if(m_instance == NULL) { // instance not already created?
        // then create it!
        m_instance = new GP2DFramerate();
    }
    // and return it.
    return m_instance;
}

GP2DFramerate::GP2DFramerate() :
        m_max(200),
        m_min(0),
        m_ticks(0),
        m_oldTicks(0) {
}

GP2DFramerate::~GP2DFramerate() {
}

const gp2dUshort GP2DFramerate::getMax() const {
    return m_max;
}

const gp2dUshort  GP2DFramerate::getMin() const {
    return m_min;
}

const gp2dUshort  GP2DFramerate::getRate() const {
    return m_rate;
}


void GP2DFramerate::setMax(gp2dUshort fps) {
    m_max = fps;
}

void GP2DFramerate::setMin(gp2dUshort fps) {
    m_min = fps;
}

void GP2DFramerate::incrementFrame() {
    m_frames++; // Increment frames.
}


gp2dFloat GP2DFramerate::getDelta(gp2dFloat velocity, gp2dUint32 deltaTicks) {
    gp2dFloat secPerFrame = deltaTicks / 1000.0f; // stored in seconds
    return velocity * secPerFrame;
}

// Limits the FPS
void GP2DFramerate::setFps (gp2dUshort rate) {
    if (rate >= m_min && rate <= m_max) { // If the desired framerate is within range...
        m_frames = 0;
        m_rate = rate;
        m_ticks = (1000 / static_cast<gp2dUint32>(rate)); // Get the ticks
    }
}

// Waits for the required time for archieving the FPS desired.
void GP2DFramerate::delay() {
    gp2dUint32 oldticks;// Old time
    gp2dUint32 newticks;// New time

    incrementFrame();

    oldticks = SDL_GetTicks();// Get the old time
    newticks = m_oldTicks + (int) (m_frames * m_ticks);// Get the new time

    if (oldticks <= newticks) {// Too slow, let's wait.
        SDL_Delay(newticks - oldticks);
    } else {// Too fast! keep up :).
        m_frames = 0;
        m_oldTicks = SDL_GetTicks();
    }
}

} // namespace gp2d
