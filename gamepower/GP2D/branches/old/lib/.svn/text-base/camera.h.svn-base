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

CAMERA FUNCTIONS (version 0.0.1)
By Wybiral

MODIFICATIONS BY:
DARKGuy
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

#ifndef _GP2D_CAMERA_H
#define _GP2D_CAMERA_H
#include "3dmath.h"

namespace gp2d {
	/*!
	    This is the Camera class.

	    The screen is placed relative to the Camera position. The Camera itself is positioned relative to the Universe.

		See also utilities.h for more info on the coordinate systems.
	*/
	class Camera {
		public:
			vec3 Pos;// Position - [0]=x, [1]=y, [2]=z .
			vec3 Rot;// Rotation - Same as above       |- Developers shouldn't have to edit this directly
			vec3 Vel;// Velocity - Same as above       '
			void Create();// Create a camera
			void Begin ( GLfloat, GLfloat );// Start drawing (with a specified viewport resolution)
			void Begin();// Start drawing (default viewport resolution (screen res))
			void End();// Stop drawing

			void Move ( GLfloat,GLfloat );// Move the camera

			void Rotate ( GLfloat,GLfloat,GLfloat );// Rotate
			void RotateX ( GLfloat );// Rotate
			void RotateY ( GLfloat );// Rotate
			void RotateZ ( GLfloat );// Rotate

			GLfloat GetX();// Get the camera's X
			GLfloat GetY();// Get the camera's Y
	};
}

#endif
