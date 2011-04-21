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

#ifndef _GP2D_2DMATH_H
#define _GP2D_2DMATH_H

#include <math.h>

#define CONST_PI 3.1415926535897932384626433832795
#define CONST_E 2.7182818284590452353602874713526
#define CONST_RAD2DEG (180/CONST_PI)
#define CONST_DEG2RAD (CONST_PI/180)

namespace gp2d {

// ==================== Vec3 Class ==================== //
class vec3 {
	public:
	float v[3];
	vec3();
	vec3(float X, float Y, float Z);
	vec3  operator+ (vec3  b);
	vec3  operator- (vec3  b);
	vec3  operator* (float b);
	vec3  operator/ (float b);
	void  operator+=(vec3  b);
	void  operator-=(vec3  b);
	void  operator*=(float b);
	void  operator/=(float b);
	float operator* (vec3  b);
	float length();
};
vec3 operator*(float b, vec3 a);
vec3 operator/(float b, vec3 a);
vec3  normalize(vec3 a);
float dotProduct(vec3 a, vec3 b);
vec3  crossProduct(vec3 a, vec3 b);
// ==================== End Vec3 Class ==================== //

// ==================== Mat4 Class ==================== //
class mat4 {
	public:
	float m[16];
	mat4();
	mat4(
		float A, float B, float C, float D,
		float E, float F, float G, float H,
		float I, float J, float K, float L,
		float M, float N, float O, float P
	);
	void billBoard();
};
mat4 operator* (mat4 a, mat4 b);
void operator*=(mat4 &a, mat4 b);
vec3 VectorTransform(vec3 a, mat4 b);
vec3 operator* (mat4 a, vec3 b);
mat4 MatrixIdentity();
mat4 MatrixTranslate(float x, float y, float z);
mat4 MatrixScale(float x, float y, float z);
mat4 MatrixRotate(float ang, float x, float y, float z);
mat4 MatrixRotateX (float ang);
mat4 MatrixRotateY (float ang);
mat4 MatrixRotateZ (float ang);
// ==================== End Mat4 Class ==================== //

}

#endif
