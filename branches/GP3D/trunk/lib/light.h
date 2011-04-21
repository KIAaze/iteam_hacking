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

LIGHTS HEADER FILE (version 0.0.3)
BY DARKGUY

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the lights header file.
===================================================================================
CHANGELOG:

0.0.3:
-> Full code rewrite.

0.0.1:
-> First code release.
===================================================================================
*/

#ifndef _GP3D_LIGHT_H
#define _GP3D_LIGHT_H

namespace gp {
	class Light {
		public:
			GLuint ID;														// Light's ID (for OpenGL)
			GLfloat LightDiffuse[3];									// Diffuse color
			GLfloat LightAmbient[3];									// Ambient color
			GLfloat LightPosition[3];									// Light position
			void SetAmbient(GLfloat,GLfloat,GLfloat,GLfloat);	// Sets the ambient color
			void SetDiffuse(GLfloat,GLfloat,GLfloat,GLfloat);	// Sets the diffuse color
			void SetPosition(GLfloat,GLfloat,GLfloat,GLfloat);	// Sets the light's position
			void Update();													// Updates the changes
			void Enable();													// Enables the light
			void Disable();												// Disables the light
	};
}

#endif
