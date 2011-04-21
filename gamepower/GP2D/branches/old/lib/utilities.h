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

/*! \file utilities.h 
This file contains useful coordinate conversion functions. Please use them to make the code more readable.
Here's an illustration of the GP2D coordinate systems:
\image html CoordinateSystem.png
*/

#ifndef _GP2D_UTILITIES_H
#define _GP2D_UTILITIES_H

#include "gp2d.h"
namespace gp2d {
	//TODO: Put this elsewhere?
	//------------------------------------------
	//Coordinate conversion utilities
	vec3 cam2universe ( Camera* a_Cam, vec3 a_P );
	vec3 screen2universe ( Camera* a_Cam, vec3 a_P );
	vec3 surface2universe ( Sprite* a_surf, vec3 a_P );
	//------------------------------------------
}
#endif
