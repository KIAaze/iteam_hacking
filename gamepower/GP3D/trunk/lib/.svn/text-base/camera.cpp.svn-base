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

CAMERA FUNCTIONS FILE (version 0.0.3)
BY DARKGUY AND WYBIRAL

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the camera functions file.
===================================================================================
CHANGELOG:

0.0.3:
-> Full code rewrite. Too many changes to list, but everything was moved to
	a namespace, there are new functions and some variables were taken out and others
	were added.

0.0.1:
-> First code release, camera handling.
===================================================================================
*/

#include "gp3d.h"
#include "camera.h"

namespace gp {

	// ==============================================================================
	// This will set a Perspective or Orthogonal view
	// ==============================================================================
	void Camera::SetView(int CamView,float minRange, float maxRange) {
		if(CamView == VIEW_PERSPECTIVE){
			GLfloat ratio;
			glClearDepth( 1.0f );
			glShadeModel( GL_SMOOTH );
			glEnable( GL_DEPTH_TEST );
			glDepthFunc( GL_LEQUAL );
			glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

			if ( Screen->h <= 0 ) { Screen->h = 1; }
			if ( Screen->w <= 0 ) { Screen->w = 1; }
			if ( minRange <= 0 ) { minRange = 1.0f; }
			if ( maxRange <= 0 ) { maxRange = 1.0f; }
			CameraMinRange = minRange;
			CameraMaxRange = maxRange;
			CameraType = CamView;
			ratio = ( GLfloat )Screen->w / ( GLfloat )Screen->h;

			glViewport( 0, 0, ( GLsizei )Screen->w, ( GLsizei )Screen->h );
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity();
			gluPerspective( CameraFov, ratio, CameraMinRange, CameraMaxRange );
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();

		}
		if(CamView == VIEW_ORTHO){
			CameraType = CamView;
			glEnable(GL_DEPTH_TEST);
			glMatrixMode(GL_MODELVIEW);
			glOrtho(-4,4, -4,4, 1, 10);
		}
	}

	// ==============================================================================
	// This will change the camera's Field of View
	// ==============================================================================
	void Camera::SetFov(float Fov) {
		if(CameraType == VIEW_PERSPECTIVE){
			GLfloat ratio;
			if ( Screen->h <= 0 ) { Screen->h = 1; }
			if ( Screen->w <= 0 ) { Screen->w = 1; }
			ratio = ( GLfloat )Screen->w / ( GLfloat )Screen->h;
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity( );
			gluPerspective( Fov, ratio, CameraMinRange, CameraMaxRange );
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity( );
		}
	}

	// ==============================================================================
	// This will change the camera's Field of View
	// ==============================================================================
	void Camera::SetRange(float Min, float Max) {
		if(CameraType == VIEW_PERSPECTIVE){
			GLfloat ratio;
			if ( Screen->h <= 0 ) { Screen->h = 1; }
			if ( Screen->w <= 0 ) { Screen->w = 1; }
			if ( Min <= 0 ) { Min = 1.0f; }
			if ( Max <= 0 ) { Max = 1.0f; }
			CameraMinRange = Min;
			CameraMaxRange = Max;
			ratio = ( GLfloat )Screen->w / ( GLfloat )Screen->h;
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity( );
			gluPerspective( CameraFov, ratio, CameraMinRange, CameraMaxRange );
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity( );
		}
	}

	// ==============================================================================
	// This will "create" the camera and set some initial default values
	// ==============================================================================
	void Camera::Create() {
		Pos.v[0]=0; Rot.v[0]=0; Vel.v[0]=0;
		Pos.v[1]=0; Rot.v[1]=0; Vel.v[1]=0;
		Pos.v[2]=0; Rot.v[2]=0; Vel.v[2]=0;
		Pos.v[3]=0; Rot.v[3]=0; Vel.v[3]=0;

		//TODO: Check if it's okay to use these values and set up a view within the Create function.

		CameraMinRange = 1.0f;
		CameraMaxRange = 100.0f;
		CameraFov = 45.0f;
		SetView(VIEW_PERSPECTIVE,CameraMinRange,CameraMaxRange);
	}

	// ==============================================================================
	// This must be called before drawing anything else in this camera. Updates
	// its position before drawing anything
	// ==============================================================================
	void Camera::Begin() {
		glLoadIdentity();
		glRotatef(-Rot.v[0], 1, 0, 0);
		glRotatef(-Rot.v[1], 0, 1, 0);
		glRotatef(-Rot.v[2], 0, 0, 1);
		glTranslatef(-Pos.v[0],-Pos.v[1],-Pos.v[2]);
	}

	// ==============================================================================
	// This must be called after drawing anything in this camera. Updates the
	// camera's rotation and resets the velocity vector
	// ==============================================================================
	void Camera::End() {
		Pos = Pos+(MatrixRotateY(Rot.v[1])*MatrixRotateX(Rot.v[0]))*Vel;
		Vel = vec3();
	}

	// ==============================================================================
	// This will move the camera to the specified position
	// ==============================================================================
	void Camera::Move(float x, float y, float z) {
		Pos.v[0]=x;
		Pos.v[1]=y;
		Pos.v[2]=z;
	}

	// ==============================================================================
	// Pretty self-explanatory these functions below
	// ==============================================================================
	void Camera::MoveForward(float dist) { Vel.v[2]-=dist; }
	void Camera::MoveBackwards(float dist) { Vel.v[2]+=dist; }
	void Camera::MoveLeft(float dist) { Vel.v[0]-=dist; }
	void Camera::MoveRight(float dist) { Vel.v[0]+=dist; }
	void Camera::MoveUp(float dist) { Vel.v[1]+=dist; }
	void Camera::MoveDown(float dist) { Vel.v[1]-=dist; }

	void Camera::Rotate(float ax, float ay, float az) {
		Rot.v[0]+=ax;
		Rot.v[1]+=ay;
		Rot.v[2]+=az;
	}
	void Camera::RotateX(float amount) { Rot.v[0]+=amount; }
	void Camera::RotateY(float amount) { Rot.v[1]+=amount; }
	void Camera::RotateZ(float amount) { Rot.v[2]+=amount; }

}
