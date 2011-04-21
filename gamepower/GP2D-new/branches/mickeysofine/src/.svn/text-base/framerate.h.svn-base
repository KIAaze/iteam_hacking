/*****
 *
 *  GamePower 3D (GP3D) and GamePower 2D (GP2D) are a portable OpenGL/SDL 
 *  wrapper using C/C++ designedspecifically for professional game making
 *  in various platforms such as Windows, Linux and Macintosh by
 *  exploiting the portable capabilities of OpenGL and SDL.
 *  Copyright (C) 2007 Gamepower development team
 *
 *  This file is part of GamePower.
 *
 *  GamePower is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  GamePower is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GamePower.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****/

#ifndef _GP2D_FRAMERATE_H
#define _GP2D_FRAMERATE_H

#include "gp2d.h"

namespace gp2d {

class GP2DFramerate {
protected:
    /// The only instance pointer, for singleton purposes.
    static GP2DFramerate* m_instance;
    
public:
    /**
     * Gets the one and only instance of the GP2DFramerate.
     * 
     * @return A pointer to a GP2DFramerate which is guaranteed to be the only
     *   instance.
     */
    static GP2DFramerate* getInstance();

    /**
     * Destroys the GP2DFramerate.
     */
    ~GP2DFramerate(void);

    /**
    * getDelta(), for lack lack of a better name, returns the amount of pixels
    * that a sprite should move considering a possible lag.  Basically, if a
    * computer were to have a low framerate, moving the sprite the normal
    * distance would be jerky.  This function can be used to slow that so it
    * appears smooth. (I'll eventually write a guide about this on the wiki.
    * -Judo)
    *
    * @param velocitiy The velocity in pixels/frame (?) that a sprite travels.
    *   The GP2DSprite class has methods that return the x and y velocity.
    *   If you're reading this, I'm going to assume you know of the pythagorean
    *   theorem and how to use it here.
    *
    * @param deltaTicks The change in ticks. (SDL_GetTicks() - oldTicks)
    *   This parameter may be removed as it might not be necessary.
    *
    * @return Uh.... I don't know.  DARKGuy, wanna finish this up for me?
    */
	GLfloat getDelta (GLfloat velocity, unsigned int deltaTicks);

    /**
    * setFPS() is used to limit the framrate.
    *
    * @param rate The highest framerate at which the application will run.
    */
	void setFPS (int rate);

    /**
    * FPSDelay() waits for the required time to achieve the desired FPS
    */
	void FPSDelay();// Waits for the required time for archieving the FPS desired.

    void incrementFrame();

    /**
      ==========================================================================
      ==========================================================================
      == SETTERS AND GETTERS                                                  ==
      ==========================================================================
      ==========================================================================
    **/

    int   getFPSmax()      const;
    int   getFPSmin()      const;
    int   getFPSframes()   const;
    int   getFPSrate()     const;
    float getFPSticks()    const;
    int   getFPSoldTicks() const;

    void setFPSmax(int fps);
    void setFPSmin(int fps);
    void setFPSframes(int frames);
    void setFPSrate(int rate);
    void setFPSticks(float ticks);
    void setFPSoldTicks(int oldTicks);

private:      
    
    int   m_FPSmax;
    int   m_FPSmin;
    int   m_FPSframes;
    int   m_FPSrate;
    float m_FPSticks;
    int   m_FPSoldTicks;

    /**
     * Creates the GP2DFramerate.
     */
    GP2DFramerate(void);
    
};

}

#endif
