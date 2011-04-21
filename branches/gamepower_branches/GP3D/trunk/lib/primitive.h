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

PRIMITIVES HEADER FILE (version 0.0.3)
BY DARKGUY

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the primitives header file.
===================================================================================
CHANGELOG:

0.0.3:
-> Full code rewrite, only cosmetic changes, and moved the color variables to an
	array.

0.0.1:
-> First code release.
===================================================================================
*/

#ifndef _GP3D_PRIMITIVE_H
#define _GP3D_PRIMITIVE_H

namespace gp {
	class Primitive {
		public:
			float size;									// Size
			float Pos;									// Position
			float Normal;								// Normals flipped or not?
			float color[2];							// Color
			GLfloat Angle[2];							// Angle
			int type;									// Primitive's type

			void RotateX(float);						// Sets rotation values
			void RotateY(float);
			void RotateZ(float);
			void Xrot(float);							// Applies the rotation values
			void Yrot(float);
			void Zrot(float);
			void SetColor(float,float,float);	// Sets the primitive's color
			void Create(int,float);					// "Creates" the primitive (just sets some
															// default initial values).
			void Draw();								// Draw the primitive with a color
			void DrawTextured(int);					// Draw the primitive with a texture
	};
}

#endif
