/*****
 *
 *  GamePower 3D (GP3D) and GamePower 2D (GP2D) are a portable OpenGL/SDL 
 *  wrapper using C/C++ designed specifically for professional game making
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

#ifndef _GP2D_OBJECT_H
#define _GP2D_OBJECT_H

#include "gp2d.h"

namespace gp2d {

    class Texture {
    };

    class Object {
        public:
            Object();
            ~Object();

            GLfloat x,y,z;  /// Position
            GLfloat vx,vy;  /// Velocity/Speed
            GLfloat angle;  /// Angle
            GLfloat accel;  /// Acceleration towards angle (this modifies x,y,vx & vy)

            // TODO: This should be changed by spritesheets
            std::vector <SDL_Surface*> graph;
            std::vector <Texture>      tex;

            void newGraph();
            void newGraph(SDL_Surface *graphic);
            void draw();
    };

}

#endif

