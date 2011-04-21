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

#include "gp2d.h"

namespace gp2d {

    Object::Object()
    {
        printDebug("New object created");
        x=0;y=0;z=0;
    }

    Object::~Object()
    {
        printDebug("Object destroyed");
    }

    void Object::newGraph()
    {
        SDL_Surface *s = NULL;
        graph.push_back(s);
    }
    
    void Object::newGraph(SDL_Surface *graphic)
    {
        graph.push_back(graphic);
    }

    void Object::draw()
    {
        if(g_VideoAPI==GP2D_SDL){
            SDL_Rect rcPosition;
            SDL_Rect rcSource;

            rcPosition.x = (int)x;
            rcPosition.y = (int)y;
            rcPosition.w = graph[0]->w;
            rcPosition.h = graph[0]->h;
            rcSource.x = 0;
            rcSource.y = 0;
            rcSource.w = graph[0]->w;
            rcSource.h = graph[0]->h;

        	SDL_BlitSurface(graph[0], &rcSource, g_SDLScreen, &rcPosition );
        }
    }
    
}

