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
#include "gp2d.h"
#include "camera.h"

namespace gp2d {

	void Camera::Create() {
		Pos.v[0]=0; Rot.v[0]=0; Vel.v[0]=0;
		Pos.v[1]=0; Rot.v[1]=0; Vel.v[1]=0;
		Pos.v[2]=0; Rot.v[2]=0; Vel.v[2]=0;
		Pos.v[3]=0; Rot.v[3]=0; Vel.v[3]=0;
		Move ( VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT/2 );
	}

	void Camera::Begin ( GLfloat Width, GLfloat Height ) {
		glMatrixMode ( GL_PROJECTION );

// 		glEnable( GL_DEPTH_TEST );
// 	gluPerspective( 45, (float)VIEWPORT_WIDTH/VIEWPORT_HEIGHT, 0.1, 100 );

		glLoadIdentity();
		glOrtho ( 0, Width, Height, 0, -1, 1 );
		glMatrixMode ( GL_MODELVIEW );
		glLoadIdentity();

		glLoadIdentity();
		glRotatef ( -Rot.v[0], 1, 0, 0 );
		glRotatef ( -Rot.v[1], 0, 1, 0 );
		glRotatef ( -Rot.v[2], 0, 0, 1 );
		glTranslatef ( -Pos.v[0],-Pos.v[1],-Pos.v[2] );
		glLoadIdentity();
	}

	void Camera::Begin() {
		glMatrixMode ( GL_PROJECTION );

// 		glEnable( GL_DEPTH_TEST );
// 	gluPerspective( 45, (float)VIEWPORT_WIDTH/VIEWPORT_HEIGHT, 0.1, 100 );

		glLoadIdentity();
		glOrtho ( 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT, 0, -1, 1 );
		glMatrixMode ( GL_MODELVIEW );
		glLoadIdentity();

		glLoadIdentity();
		glRotatef ( -Rot.v[0], 1, 0, 0 );
		glRotatef ( -Rot.v[1], 0, 1, 0 );
		glRotatef ( -Rot.v[2], 0, 0, 1 );
		glTranslatef ( - ( Pos.v[0]-VIEWPORT_WIDTH/2 ),- ( Pos.v[1]-VIEWPORT_HEIGHT/2 ),-Pos.v[2] );
	}

	void Camera::End() {
		Pos = Pos+ ( MatrixRotateY ( Rot.v[1] ) *MatrixRotateX ( Rot.v[0] ) ) *Vel;
		Vel = vec3();
	}

	void Camera::Move ( GLfloat x, GLfloat y ) {
		Pos.v[0]=x;
		Pos.v[1]=y;
		Pos.v[2]=0;
	}

	void Camera::Rotate ( GLfloat ax, GLfloat ay, GLfloat az ) {
		Rot.v[0]+=ax;
		Rot.v[1]+=ay;
		Rot.v[2]+=az;
	}
	void Camera::RotateX ( GLfloat amount ) { Rot.v[0]+=amount; }
	void Camera::RotateY ( GLfloat amount ) { Rot.v[1]+=amount; }
	void Camera::RotateZ ( GLfloat amount ) { Rot.v[2]+=amount; }

	GLfloat Camera::GetX() { return Pos.v[0]; }
	GLfloat Camera::GetY() { return Pos.v[1]; }

}
