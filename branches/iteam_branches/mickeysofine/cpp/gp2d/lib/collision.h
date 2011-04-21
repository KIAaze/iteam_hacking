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

COLLISION FUNCTIONS (version 0.0.1)
By DARKGuy

MODIFICATIONS BY:
No one at the moment.
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

#ifndef _GP2D_COLLISION_H
#define _GP2D_COLLISION_H

namespace gp2d {

	short int CollisionSimple(gp2d::Sprite*,gp2d::Sprite*,int,int);	// Simple, bounding box collision.
	short int CollisionPixel (gp2d::Sprite*,gp2d::Sprite*,int,int);	// Same as above, with an user-definable collision rectangle.
	short int CollisionAdv   (gp2d::Sprite*,gp2d::Sprite*,int,int);	// Pixel-perfect collision

	//added by KIAaze
	short int CollisionPixel_2(
          gp2d::Sprite * object1
        , gp2d::Sprite * object2
        , int img1
        , int img2
        , GLfloat &Nx
        , GLfloat &Ny
        , GLfloat &Tx
        , GLfloat &Ty
        , bool bounding = false
        , bool overlap = false
        , bool relative_overlap = false
        , bool pixels = true
        , bool force = false
        , bool slope = false
    );
    // Pixel-perfect collision which also returns a force (Nx,Ny) and slope (Tx,Ty) on which to bounce off.
	//---------------------------------------------------
}

#endif
