/*****
 *
 *  GamePower 3D (GP3D) and GamePower 2D (GP) are a portable OpenGL/SDL
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

#ifndef _GP_FRAMERATE_H
#define _GP_FRAMERATE_H

#include "gp2d.h"

namespace gp {

class GPFramerate {
protected:
    /// The only instance pointer, for singleton purposes.
    static GPFramerate* m_instance;

public:
    /**
     * Gets the one and only instance of the GPFramerate.
     *
     * @return A pointer to a GPFramerate which is guaranteed to be the only
     *   instance.
     */
    static GPFramerate* getInstance();

    /**
     * Destroys the GPFramerate.
     */
    ~GPFramerate(void);

    /**
     * getDelta(), for lack lack of a better name, returns the amount of pixels
     * that a sprite should move considering a possible lag.  Basically, if a
     * computer were to have a low framerate, moving the sprite the normal
     * distance would be jerky.  This function can be used to slow that so it
     * appears smooth. (I'll eventually write a guide about this on the wiki.
     * -Judo)
     *
     * @param velocity The velocity in pixels/frame (?) that a sprite travels.
     * The GPSprite class has methods that return the x and y velocity. If
     * you're reading this, I'm going to assume you know of the pythagorean
     * theorem and how to use it here.
     * @param deltaTicks The change in ticks. (SDL_GetTicks() - oldTicks) this
     * parameter may be removed as it might not be necessary.
     *
     * @return Uh.... I don't know.  DARKGuy, wanna finish this up for me?
     */
    gpFloat getDelta(gpFloat velocity, gpUint32 deltaTicks);

    /**
     * setFPS() is used to limit the framrate.
     *
     * @param rate The highest framerate at which the application will run.
     */
    void setFps(gpUshort rate);

    /**
     * Waits for the required time to achieve the desired FPS.
     */
    void delay();

    const gpUshort getMax() const;
    const gpUshort getMin() const;

    /**
     * Gets the fps which was set by setFps().
     *
     * @return The rate of fps which was required.
     */
    const gpUshort getRate() const;

    void setMax(gpUshort fps);
    void setMin(gpUshort fps);

private:

    gpUshort m_max;
    gpUshort m_min;
    gpUint32 m_frames;
    gpUshort m_rate;
    gpUint32 m_ticks;
    gpUint32 m_oldTicks;

    /**
     * Creates the GPFramerate.
     */
    GPFramerate(void);

    void incrementFrame();
};

}

#endif
