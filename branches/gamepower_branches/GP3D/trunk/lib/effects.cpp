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

EFFECTS FUNCTIONS FILE (version 0.0.3)
BY DARKGUY AND WYBIRAL

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the effects functions file.
===================================================================================
CHANGELOG:

0.0.3:
-> First release.

0.0.1:
-> It was not existant to this moment.
===================================================================================
*/

#include "gp3d.h"
#include "effects.h"

namespace gp {
	// ==============================================================================
	// This enables FullScreen AntiAliasing
	// ==============================================================================
	void EnableFSAA(int samples) {
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
		SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, samples );
	}
}
