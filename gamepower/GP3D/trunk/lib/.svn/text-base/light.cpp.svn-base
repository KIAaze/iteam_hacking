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

LIGHTS FUNCTIONS FILE (version 0.0.3)
BY DARKGUY

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the lights functions file.
===================================================================================
CHANGELOG:

0.0.3:
-> Full code rewrite.

0.0.1:
-> First code release.
===================================================================================
*/

#include "gp3d.h"
#include "light.h"

namespace gp {
	// ==============================================================================
	// Sets the ambient light color and intensity (or alpha?)
	// ==============================================================================
	void Light::SetAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat i) {
		LightAmbient[0] = r;
		LightAmbient[1] = g;
		LightAmbient[2] = b;
		LightAmbient[3] = i;
	}

	// ==============================================================================
	// Sets the diffuse light color and intensity (or alpha?)
	// ==============================================================================
	void Light::SetDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat i) {
		LightDiffuse[0] = r;
		LightDiffuse[1] = g;
		LightDiffuse[2] = b;
		LightDiffuse[3] = i;
	}

	// ==============================================================================
	// Sets the light's position (and intensity?)
	// ==============================================================================
	void Light::SetPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat i) {
		LightPosition[0] = x;
		LightPosition[1] = y;
		LightPosition[2] = z;
		LightPosition[3] = i;
	}

	// ==============================================================================
	// Applies the changes made to the light
	// ==============================================================================
	void Light::Update () {
		glLightfv(ID, GL_AMBIENT, LightAmbient);
		glLightfv(ID, GL_DIFFUSE, LightDiffuse);
		glLightfv(ID, GL_POSITION,LightPosition);
	}

	// ==============================================================================
	// Enables and Disables the light
	// ==============================================================================
	void Light::Enable () { glEnable(ID); }
	void Light::Disable () { glDisable(ID); }
}
