/*

	This file is part of GamePower 2D.

    GamePower 2D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 2D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 2D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 2D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  - libsdl1.2-dev
                          - libsdl-image1.2-dev
                          - libsdl-mixer1.2-dev
                        * FreeType development libraries
                          - libfreetype6-dev

FPS CONTROLLER (version 0.0.1)
By DARKGuy

MODIFICATIONS BY:
Doddi
Judo
DARKGuy
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

#include "framerate.h"

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

GP2DFramerate::GP2DFramerate() {    
	if (getFPSmax() == 0) { 
	    setFPSmax(200); // If no one set the max FPS, set them to 200. 
	}
    if (getFPSmin() == 0) { 
        setFPSmin(0); // Same with min FPS. 
    }
}

GP2DFramerate::~GP2DFramerate() {
}

/**
  ==============================================================================
  ==============================================================================
  == SETTERS AND GETTERS                                                      ==
  ==============================================================================
  ==============================================================================
**/

int GP2DFramerate::getFPSmax() const {
    return m_FPSmax;
}
int GP2DFramerate::getFPSmin() const {
    return m_FPSmin;
}
int GP2DFramerate::getFPSframes() const {
    return m_FPSframes;
}
int GP2DFramerate::getFPSrate() const {
    return m_FPSrate;
}
float GP2DFramerate::getFPSticks() const {
    return m_FPSticks;
}
int GP2DFramerate::getFPSoldTicks() const {
    return m_FPSoldTicks;
}

void GP2DFramerate::setFPSmax(int fps) {
    m_FPSmax = fps;
}

void GP2DFramerate::setFPSmin(int fps) {
    m_FPSmin = fps;
}
void GP2DFramerate::setFPSframes(int frames) {
    m_FPSframes = frames;
}
void GP2DFramerate::setFPSrate(int rate) {
    m_FPSrate = rate;
}
void GP2DFramerate::setFPSticks(float ticks) {
    m_FPSticks = ticks;
}
void GP2DFramerate::setFPSoldTicks(int oldTicks) {
    m_FPSoldTicks = oldTicks;
}

void GP2DFramerate::incrementFrame() {
    m_FPSframes++; // Increment frames.
}

/**
  ==============================================================================
  ==============================================================================
  == ACTUAL CODE                                                              ==
  ==============================================================================
  ==============================================================================
**/

GLfloat GP2DFramerate::getDelta (GLfloat velocity, unsigned int deltaTicks) {
	GLfloat result;

	GLfloat secPerFrame = deltaTicks / 1000.0f;// Stored in seconds
	result = velocity * secPerFrame;

	return result;
}

// Limits the FPS
void GP2DFramerate::setFPS (int rate) {
	if ( rate >= getFPSmin() && rate <= getFPSmax() ) {// If the desired framerate is within range...
		setFPSframes(0);// Set FPS_frames to 0.
        setFPSrate(rate);// Set FPS_rate to .
        setFPSticks(( 1000.0 / (float) rate));// Get the ticks.
	}
}

// Waits for the required time for archieving the FPS desired.
void GP2DFramerate::FPSDelay() {
	int oldticks;// Old time
	int newticks;// New time

	incrementFrame();

	oldticks = SDL_GetTicks();// Get the old time
	newticks = getFPSoldTicks() + (int) ((float) getFPSframes() * getFPSticks());// Get the new time

	if ( oldticks <= newticks ) {// Too slow, let's wait.
		SDL_Delay ( newticks - oldticks );
	} else {// Too fast! keep up :).
		setFPSframes(0);
		setFPSoldTicks(SDL_GetTicks());
	}
}

}
