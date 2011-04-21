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

PRIMITIVE FUNCTIONS FILE (version 0.0.3)
BY DARKGUY

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the primitive functions file.
===================================================================================
CHANGELOG:

0.0.3:
-> Full code rewrite, only cosmetic changes, and moved the color variables to an
	array.

0.0.1:
-> First code release.
===================================================================================
*/

#include "gp3d.h"
#include "primitive.h"

namespace gp {
	// ==============================================================================
	// These will set the rotation values.
 	// Also, these might be removed and/or merged into a generic function class?
	// ==============================================================================
	void Primitive::RotateX(float value) { Angle[0] += value; }
	void Primitive::RotateY(float value) { Angle[1] += value; }
	void Primitive::RotateZ(float value) { Angle[2] += value; }
	// ==============================================================================
	// These will apply the rotation values set with the functions defined above.
 	// Also, these might be removed and/or merged into a generic function class?
	// ==============================================================================
	void Primitive::Xrot(float direction) { glRotatef(Angle[0],direction,0.0f,0.0f); }
	void Primitive::Yrot(float direction) { glRotatef(Angle[1],0.0f,direction,0.0f); }
	void Primitive::Zrot(float direction) { glRotatef(Angle[2],0.0f,0.0f,direction); }

	// ==============================================================================
	// "Creates" the primitive (it just sets some default values)
	// ==============================================================================
	void Primitive::Create(int theType, float theSize) {
		type = theType;
		size = theSize;
		color[0]=1.0f;
		color[1]=1.0f;
		color[2]=1.0f;
		Normal = 1.0f;
	}

	// ==============================================================================
	// Sets primitive's color
	// ==============================================================================
	void Primitive::SetColor(float cr, float cg, float cb) { color[0]=cr; color[1]=cg; color[2]=cb; }

	// ==============================================================================
	// Draws the primitive
	// ==============================================================================
	void Primitive::Draw() {
		if(type == PRIM_CUBE){
			glBegin(GL_QUADS);
				glColor3f(color[0], color[1], color[2]);
				glNormal3f( 0.0f, 0.0f, Normal);
				glVertex3f(-size, -size,  size);
				glVertex3f( size, -size,  size);
				glVertex3f( size,  size,  size);
				glVertex3f(-size,  size,  size);

				glNormal3f( 0.0f, 0.0f,-Normal);
				glVertex3f( size, -size, -size);
				glVertex3f(-size, -size, -size);
				glVertex3f(-size,  size, -size);
				glVertex3f( size,  size, -size);

				glNormal3f( -Normal, 0.0f,0.0f);
				glVertex3f(-size,-size, -size);
				glVertex3f(-size,-size,  size);
				glVertex3f(-size, size,  size);
				glVertex3f(-size, size, -size);


				glNormal3f( Normal, 0.0f,0.0f);
				glVertex3f(size, -size,  size);
				glVertex3f(size, -size, -size);
				glVertex3f(size,  size, -size);
				glVertex3f(size,  size,  size);

				glNormal3f( 0.0f, Normal,0.0f);
				glVertex3f(-size, size,  size);
				glVertex3f( size, size,  size);
				glVertex3f( size, size, -size);
				glVertex3f(-size, size, -size);

				glNormal3f( 0.0f, -Normal,0.0f);
				glVertex3f( size,-size, -size);
				glVertex3f( size,-size,  size);
				glVertex3f(-size,-size,  size);
				glVertex3f(-size,-size, -size);
			glEnd();
		}
		if(type == PRIM_PYRAMID) {
			glBegin( GL_TRIANGLES );
				glColor3f(color[0], color[1], color[2]);
				glVertex3f(  0.0f,  size,  0.0f );
				glVertex3f( -size, -size,  size );
				glVertex3f(  size, -size,  size );

				glVertex3f(  0.0f,  size,  0.0f );
				glVertex3f(  size, -size,  size );
				glVertex3f(  size, -size, -size );

				glVertex3f(  0.0f,  size,  0.0f );
				glVertex3f(  size, -size, -size );
				glVertex3f( -size, -size, -size );


				glVertex3f(  0.0f,  size,  0.0f );
				glVertex3f( -size, -size, -size );
				glVertex3f( -size, -size,  size );
			glEnd();
		}
	}

	// ==============================================================================
	// Draws the primitive, with a texture
	// ==============================================================================
	void Primitive::DrawTextured(int tex) {
		if(type == PRIM_CUBE){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, tex);
			glBegin(GL_QUADS);
				glNormal3f( 0.0f, 0.0f, Normal);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size,  size);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size,  size);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size,  size);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size,  size);

				glNormal3f( 0.0f, 0.0f,-Normal);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size, -size);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size, -size);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size, -size);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size, -size);

				glNormal3f( 0.0f, Normal, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-size,  size,  size);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size,  size);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);

				glNormal3f( 0.0f,-Normal, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size, -size);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( size, -size, -size);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);

				glNormal3f( Normal, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size, -size);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size, -size);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size,  size);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size,  size);

				glNormal3f(-Normal, 0.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size,  size);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size,  size);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size, -size);
			glEnd();
		}
	}
}
