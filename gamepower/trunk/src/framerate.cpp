#include "framerate.h"

#include <iostream>

using namespace std;

namespace gp {

// The one and only instance of the GPFramerater.
// Firstly initialized to NULL, or else we get some errors :)
GPFramerate* GPFramerate::m_instance = NULL;

GPFramerate* GPFramerate::getInstance() {
    if(m_instance == NULL) { // instance not already created?
        // then create it!
        m_instance = new GPFramerate();
    }
    // and return it.
    return m_instance;
}

GPFramerate::GPFramerate() :
        m_max(200),
        m_min(0),
        m_ticks(0),
        m_oldTicks(0) {
}

GPFramerate::~GPFramerate() {
}

const gpUshort GPFramerate::getMax() const {
    return m_max;
}

const gpUshort  GPFramerate::getMin() const {
    return m_min;
}

const gpUshort  GPFramerate::getRate() const {
    return m_rate;
}


void GPFramerate::setMax(gpUshort fps) {
    m_max = fps;
}

void GPFramerate::setMin(gpUshort fps) {
    m_min = fps;
}

void GPFramerate::incrementFrame() {
    m_frames++; // Increment frames.
}


gpFloat GPFramerate::getDelta(gpFloat velocity, gpUint32 deltaTicks) {
    gpFloat secPerFrame = deltaTicks / 1000.0f; // stored in seconds
    return velocity * secPerFrame;
}

// Limits the FPS
void GPFramerate::setFps (gpUshort rate) {
    if (rate >= m_min && rate <= m_max) { // If the desired framerate is within range...
        m_frames = 0;
        m_rate = rate;
        m_ticks = (1000 / static_cast<gpUint32>(rate)); // Get the ticks
    }
}

// Waits for the required time for archieving the FPS desired.
void GPFramerate::delay() {
    gpUint32 oldticks;// Old time
    gpUint32 newticks;// New time

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

} // namespace gp
