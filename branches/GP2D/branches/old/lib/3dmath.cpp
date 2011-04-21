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

3D MATHS (version 0.0.1)
By Wybiral

MODIFICATIONS BY:
No one at the moment.
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/
//#include "gp2d.h"
#include "3dmath.h"

namespace gp2d {

// ==================== Vec3 Class Members ==================== //
	vec3::vec3() {
		v[0]=0;
		v[1]=0;
		v[2]=0;
	}

	vec3::vec3 ( float X, float Y, float Z ) {
		v[0]=X;
		v[1]=Y;
		v[2]=Z;
	}

	vec3 vec3::operator+ ( vec3  b ) {
		return vec3 ( v[0]+b.v[0], v[1]+b.v[1], v[2]+b.v[2] );
	}

	vec3 vec3::operator- ( vec3  b ) {
		return vec3 ( v[0]-b.v[0], v[1]-b.v[1], v[2]-b.v[2] );
	}

	vec3 vec3::operator* ( float b ) {
		return vec3 ( v[0]*b,v[1]*b,v[2]*b );
	}

	vec3 vec3::operator/ ( float b ) {
		float fact = 1.0/b;
		return vec3 ( v[0]*fact, v[1]*fact, v[2]*fact );
	}

	void vec3::operator+= ( vec3  b ) {
		v[0]+=b.v[0]; v[1]+=b.v[1]; v[2]+=b.v[2];
	}

	void vec3::operator-= ( vec3  b ) {
		v[0]-=b.v[0]; v[1]-=b.v[1]; v[2]-=b.v[2];
	}

	void vec3::operator*= ( float b ) {
		v[0]*=b; v[1]*=b; v[2]*=b;
	}

	void vec3::operator/= ( float b ) {
		float fact = 1.0/b;
		v[0]*=fact; v[1]*=fact; v[2]*=fact;
	}

	float vec3::operator* ( vec3  b ) {
		return v[0]*b.v[0] + v[1]*b.v[1] + v[2]*b.v[2];
	}

	float vec3::length() {
		return sqrt ( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
	}
// ==================== End Vec3 Class Members ==================== //

// ==================== Vec3 Supporting Functions ==================== //
	vec3 operator* ( float b, vec3 a ) {
		return vec3 ( a.v[0]*b,a.v[1]*b,a.v[2]*b );
	}

	vec3 operator/ ( float b, vec3 a ) {
		float fact = 1.0/b;
		return vec3 ( a.v[0]*fact, a.v[1]*fact, a.v[2]*fact );
	}

	vec3  normalize ( vec3 a ) {
		return a/a.length();
	}

	float dotProduct ( vec3 a, vec3 b ) {
		return a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2];
	}

	vec3  crossProduct ( vec3 a, vec3 b ) {
		return vec3 ( a.v[1]*b.v[2]-a.v[2]*b.v[1],a.v[2]*b.v[0]-a.v[0]*b.v[2],a.v[0]*b.v[1]-a.v[1]*b.v[0] );
	}
// ==================== End Vec3 Supporting Functions ==================== //

// ==================== Mat4 Class Members ==================== //
	mat4::mat4() {
		m[ 0]=0.0; m[ 1]=0.0; m[ 2]=0.0; m[ 3]=0.0;
		m[ 4]=0.0; m[ 5]=0.0; m[ 6]=0.0; m[ 7]=0.0;
		m[ 8]=0.0; m[ 9]=0.0; m[10]=0.0; m[11]=0.0;
		m[12]=0.0; m[13]=0.0; m[14]=0.0; m[15]=0.0;
	}

	mat4::mat4 (
	    float A, float B, float C, float D,
	    float E, float F, float G, float H,
	    float I, float J, float K, float L,
	    float M, float N, float O, float P ) {
		m[ 0]=A; m[ 1]=B; m[ 2]=C; m[ 3]=D;
		m[ 4]=E; m[ 5]=F; m[ 6]=G; m[ 7]=H;
		m[ 8]=I; m[ 9]=J; m[10]=K; m[11]=L;
		m[12]=M; m[13]=N; m[14]=O; m[15]=P;
	}

	void mat4::billBoard() {
		m[ 0]=1.0; m[ 1]=0.0; m[ 2]=0.0; m[ 3]=0.0;
		m[ 4]=0.0; m[ 5]=1.0; m[ 6]=0.0; m[ 7]=0.0;
		m[ 8]=0.0; m[ 9]=0.0; m[10]=1.0; m[11]=0.0;
	}
// ==================== End Mat4 Class Members ==================== //

// ==================== Mat4 Supporting Functions ==================== //
	vec3 operator* ( mat4 a, vec3 b ) {
		const float x = b.v[0]*a.m[ 0] + b.v[1]*a.m[ 4] + b.v[2]*a.m[ 8]+a.m[12];
		const float y = b.v[0]*a.m[ 1] + b.v[1]*a.m[ 5] + b.v[2]*a.m[ 9]+a.m[13];
		const float z = b.v[0]*a.m[ 2] + b.v[1]*a.m[ 6] + b.v[2]*a.m[10]+a.m[14];
		return vec3 ( x, y, z );
	}

	vec3 VectorTransform ( vec3 a, mat4 b ) {
		return b * a;
	}

	mat4 operator* ( mat4 a, mat4 b ) {
		mat4 temp;
		for ( int x2=0; x2<4; x2++ ) {
			for ( int y1=0; y1<4; y1++ ) {
				for ( int i = 0; i < 4; i++ ) {
					temp.m[x2*4+y1]+=b.m[x2*4+i]*a.m[i*4+y1];
				}
			}
		}
		return temp;
	}

	void operator*= ( mat4 &a, mat4 b ) {
		mat4 temp;
		for ( int x2=0; x2<4; x2++ ) {
			for ( int y1=0; y1<4; y1++ ) {
				for ( int i = 0; i < 4; i++ ) {
					temp.m[x2*4+y1]+=b.m[x2*4+i]*a.m[i*4+y1];
				}
			}
		}
		a = temp;
	}

	mat4 MatrixIdentity( ) {
		return mat4 (
		           1.0, 0.0, 0.0, 0.0,
		           0.0, 1.0, 0.0, 0.0,
		           0.0, 0.0, 1.0, 0.0,
		           0.0, 0.0, 0.0, 1.0
		       );
	}

	mat4 MatrixTranslate ( float x, float y, float z ) {
		return mat4 (
		           1.0, 0.0, 0.0, 0.0,
		           0.0, 1.0, 0.0, 0.0,
		           0.0, 0.0, 1.0, 0.0,
		           x,   y,   z, 1.0
		       );
	}

	mat4 MatrixScale ( float x, float y, float z ) {
		return mat4 (
		           x, 0.0, 0.0, 0.0,
		           0.0,   y, 0.0, 0.0,
		           0.0, 0.0,   z, 0.0,
		           0.0, 0.0, 0.0, 1.0
		       );
	}

	mat4 MatrixRotate ( float ang, float x, float y, float z ) {
		mat4 temp = MatrixIdentity();
		const float cosa = cosf ( ang*CONST_DEG2RAD );
		const float sina = sinf ( ang*CONST_DEG2RAD );
		const float M = 1.0f - cosa;
		float tmp1 = x*y*M;
		float tmp2 = z*sina;
		temp.m[0] = cosa + x*x*M;
		temp.m[5] = cosa + y*y*M;
		temp.m[10]= cosa + z*z*M;
		temp.m[4] = tmp1 + tmp2;
		temp.m[1] = tmp1 - tmp2;
		tmp1 = x*z*M;
		tmp2 = y*sina;
		temp.m[8] = tmp1 - tmp2;
		temp.m[2] = tmp1 + tmp2;
		tmp1 = y*z*M;
		tmp2 = x*sina;
		temp.m[9] = tmp1 + tmp2;
		temp.m[6] = tmp1 - tmp2;
		return temp;
	}

	mat4 MatrixRotateAxis ( float ang, int main, int a1, int a2 ) {
		const float cosa = cosf ( ang * CONST_DEG2RAD );
		const float sina = sinf ( ang * CONST_DEG2RAD );
		mat4 tempMatrix;
		tempMatrix.m[15] = 1.0;
		tempMatrix.m[main*4+main] = 1.0;
		tempMatrix.m[a1+a1*4] =  cosa;
		tempMatrix.m[a1+a2*4] =  sina;
		tempMatrix.m[a2+a1*4] = -sina;
		tempMatrix.m[a2+a2*4] =  cosa;
		return tempMatrix;
	}

	mat4 MatrixRotateX ( float ang ) { return MatrixRotateAxis ( ang, 0, 2, 1 ); }
	mat4 MatrixRotateY ( float ang ) { return MatrixRotateAxis ( ang, 1, 0, 2 ); }
	mat4 MatrixRotateZ ( float ang ) { return MatrixRotateAxis ( ang, 2, 1, 0 ); }
// ==================== End Mat4 Supporting Functions ==================== //

}
