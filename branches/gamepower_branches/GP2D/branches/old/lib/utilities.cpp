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

UTILITIES
By KIAaze

MODIFICATIONS BY:
No one at the moment.
===================================================================================
*/

#include "gp2d.h"
namespace gp2d {
//------------------------------------------
//Coordinate conversion utilities
	vec3 cam2universe ( Camera* a_Cam, vec3 a_P )
	{
		vec3 l_C(a_Cam->GetX(),a_Cam->GetY(),0);
		return(l_C+a_P);
	}
	
	//TODO: Make sure wether it's SCREEN_* or VIEWPORT_*
	//TODO: It would be nice if it weren't necessary to pass the Camera as argument
	vec3 screen2universe ( Camera* a_Cam, vec3 a_P )
	{
		vec3 l_S(a_Cam->GetX()-SCREEN_WIDTH/2.,a_Cam->GetY()-SCREEN_HEIGHT/2.,0);
		return(l_S+a_P);
	}
	
	vec3 surface2universe ( Sprite* a_surf, vec3 a_P )
	{
		vec3 l_S(a_surf->GetX()-a_surf->GetWidth()/2.,a_surf->GetY()-a_surf->GetHeight()/2.,0);
		return(l_S+a_P);	
	}
//------------------------------------------
}
