/*

	This file is part of GamePower 3D.

    GamePower 3D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 3D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 3D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 3D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  (libsdl1.2-dev, libsdl-image1.2-dev)

CAMERA HEADER FILE (version 0.0.3)
BY DARKGUY AND WYBIRAL

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the header for the camera functions.
===================================================================================
CHANGELOG:

0.0.3:
-> Full code rewrite. Too many changes to list, but everything was moved to
	a namespace, there are new functions and some variables were taken out and others
	were added (CameraFov, MinRange & MaxRange were added and merged into this class
	instead of being global variables, so there can be multiple cameras with different
	fov and range).

0.0.1:
-> First code release, camera handling.
===================================================================================
*/

#ifndef _GP3D_CAMERA_H
#define _GP3D_CAMERA_H
#include "3dmath.h"

namespace gp {
	class Camera {
		public:
			GLfloat CameraFov;					// Camera's Field of View
			GLfloat CameraMinRange;				// Minimum view range
			GLfloat CameraMaxRange;				// Maximum view range
			int CameraType;						// Camera view type
			vec3 Pos;								// Position
			vec3 Rot;								// Rotation
			vec3 Vel;								// Velocity
			void SetView(int,float,float);	// Sets the camera's view
			void SetFov(float);					// Sets the camera's FoV
			void SetRange(float,float);		// Sets the camera's Minimum and Maximum range
			void Create();							// Sets the camera's default initial values
			void Begin();							// "Begins rendering" (Basically sets up
														// position, rotation and an entity)
			void End();								// "Stops rendering" (It applies the changes
														// made and resets the velocity vector

			void Move(float,float,float);		// Pretty self-explanatory all of the functions
			void MoveForward(float);			// here below.
			void MoveBackwards(float);
			void MoveLeft(float);
			void MoveRight(float);
			void MoveUp(float);
			void MoveDown(float);

			void Rotate(float,float,float);
			void RotateX(float);
			void RotateY(float);
			void RotateZ(float);
	};
}

#endif
