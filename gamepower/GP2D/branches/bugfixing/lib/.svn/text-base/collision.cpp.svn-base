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

#include "gp2d.h"
#include "collision.h"

namespace gp2d {

	short int CollisionSimple ( gp2d::Sprite * object1, gp2d::Sprite * object2, int imgid1, int imgid2 ) {
		GLfloat left1, left2;// Upper-left corner X of obj1 & obj2's bounding box.
		GLfloat top1, top2;// Upper-left corner Y of obj1 & obj2's bounding box.
		GLfloat right1, right2;// Bottom-right corner X of obj1 & obj2's bounding box.
		GLfloat bottom1, bottom2;// Bottom-right corner Y of obj1 & obj2's bounding box.

// Calculate the bounding box of each sprite's chosen image.

		left1 = object1->x- ( object1->width[imgid1]/2 );// Obj1's top-left X minus (Obj1's width / 2)
		top1 = object1->y- ( object1->height[imgid1]/2 );// Obj1's top-left Y minus (Obj1's height / 2)
		right1 = object1->x + object1->width[imgid1]- ( object1->width[imgid1]/2 );// Obj1's bottom-right X plus Obj1's width minus (Obj1's width / 2)
		bottom1 = object1->y + object1->height[imgid1]- ( object1->height[imgid1]/2 );// Obj1's bottom-right Y plys Obj1's height minus (Obj1's height / 2)

		left2 = object2->x- ( object2->width[imgid2]/2 );// Obj2's top-left X minus (Obj2's width / 2)
		top2 = object2->y- ( object2->height[imgid2]/2 );// Obj2's top-left Y minus (Obj2's height / 2)
		right2 = object2->x + object2->width[imgid2]- ( object2->width[imgid2]/2 );// Obj2's bottom-right X plus Obj2's width minus (Obj2's width / 2)
		bottom2 = object2->y + object2->height[imgid2]- ( object2->height[imgid2]/2 );// Obj2's bottom-right Y plys Obj2's height minus (Obj2's height / 2)

		/*
		DEBUG INFO: Remove this comment and recompile the library for showing a red rectangle
		            around each sprite's bounding box.

		gp2d::DisableTexturing();
		gp2d::BeginLines();
			SetColor3(1,1,1);
			gp2d::DrawRectangle(left1,top1,right1,bottom1);
			gp2d::DrawRectangle(left2,top2,right2,bottom2);
		gp2d::EndLines();
		gp2d::EnableTexturing();
		*/

// Out-of-boundaries check. This is faster than checking for every inside-boundary.
		if ( bottom1 < top2 ) return ( 0 );
		if ( top1 > bottom2 ) return ( 0 );

		if ( right1 < left2 ) return ( 0 );
		if ( left1 > right2 ) return ( 0 );

// None of those checks passed, means there was a collision!
		return ( 1 );
	}

	short int CollisionAdv ( gp2d::Sprite * object1, gp2d::Sprite * object2, int img1, int img2 ) {
		GLfloat left1, left2;
		GLfloat right1, right2;
		GLfloat top1, top2;
		GLfloat bottom1, bottom2;

// Calculate the collision region for each sprite, taking in account the collision bounding box.

		left1 =  object1->x- ( object1->width[img1]/2 ) + object1->col_x[img1];// Obj1's top-left X minus (Obj1's width / 2) plus Collision Rectangle's top-left X corner.
		top1 =  object1->y- ( object1->height[img1]/2 ) + object1->col_y[img1];// Obj1's top-left Y minus (Obj1's height / 2) plus Collision Rectangle's top-left Y corner.
		right1 = object1->x- ( object1->width[img1]/2 ) + ( object1->col_x[img1] + object1->col_width[img1] );// Obj1's bottom-right X minus (Obj1's width / 2) plus (Collision Rectangle's bottom-right X corner plus Collision Rectangle's width).
		bottom1 = object1->y- ( object1->height[img1]/2 ) + ( object1->col_y[img1] + object1->col_height[img1] );// Obj1's bottom-right Y minus (Obj1's height / 2) plus (Collision Rectangle's bottom-right Y corner plus Collision Rectangle's height).

		left2 =  object2->x- ( object2->width[img2]/2 ) + object2->col_x[img2];// Obj2's top-left X minus (Obj2's width / 2) plus Collision Rectangle's top-left X corner.
		top2 =  object2->y- ( object2->height[img2]/2 ) + object2->col_y[img2];// Obj2's top-left Y minus (Obj2's height / 2) plus Collision Rectangle's top-left Y corner.
		right2 = object2->x- ( object2->width[img2]/2 ) + ( object2->col_x[img2] + object2->col_width[img2] );// Obj2's bottom-right X minus (Obj2's width / 2) plus (Collision Rectangle's bottom-right X corner plus Collision Rectangle's width).
		bottom2 = object2->y- ( object2->height[img2]/2 ) + ( object2->col_y[img2] + object2->col_height[img2] );// Obj2's bottom-right Y minus (Obj2's height / 2) plus (Collision Rectangle's bottom-right Y corner plus Collision Rectangle's height).

		/*
		DEBUG INFO: Remove this comment and recompile the library for showing a red rectangle
		            around each sprite's bounding box.

		gp2d::DisableTexturing();
		gp2d::BeginLines();
			SetColor3(1,1,1);
			gp2d::DrawRectangle(left1,top1,right1,bottom1);
			gp2d::DrawRectangle(left2,top2,right2,bottom2);
		gp2d::EndLines();
		gp2d::EnableTexturing();
		*/

// Same as the simple function.
		if ( bottom1 < top2 ) return ( 0 );
		if ( top1 > bottom2 ) return ( 0 );

		if ( right1 < left2 ) return ( 0 );
		if ( left1 > right2 ) return ( 0 );

		return ( 1 );
	}

	short int CollisionPixel ( gp2d::Sprite * object1, gp2d::Sprite * object2, int img1, int img2 ) {
		GLfloat left1, left2, over_left;
		GLfloat right1, right2, over_right;
		GLfloat top1, top2, over_top;
		GLfloat bottom1, bottom2, over_bottom;
// GLfloat over_width, over_height;
		GLfloat top_off, left_off, right_off, bottom_off;
		Uint32 px, py;
		Uint8  pr, pg, pb, pa2;

		SDL_Surface *surface1, *surface2;
		surface1 = object1->animationSheet[img1].spriteTexture->imgF;
		surface2 = object2->animationSheet[img2].spriteTexture->imgF;

// Alright... this is tricky. First, calculate the collision region just like in the function above.

		left1 =  object1->x- ( object1->width[img1]/2 ) + object1->col_x[img1];// Obj1's top-left X minus (Obj1's width / 2) plus Collision Rectangle's top-left X corner.
		left2 =  object2->x- ( object2->width[img2]/2 ) + object2->col_x[img2];// Obj2's top-left X minus (Obj2's width / 2) plus Collision Rectangle's top-left X corner.
		right1 = object1->x- ( object1->width[img1]/2 ) + ( object1->col_x[img1] + object1->col_width[img1] );// Obj1's bottom-right X minus (Obj1's width / 2) plus (Collision Rectangle's bottom-right X corner plus Collision Rectangle's width).
		right2 = object2->x- ( object2->width[img2]/2 ) + ( object2->col_x[img2] + object2->col_width[img2] );// Obj2's bottom-right X minus (Obj2's width / 2) plus (Collision Rectangle's bottom-right X corner plus Collision Rectangle's width).

		top1 =  object1->y- ( object1->height[img1]/2 ) + object1->col_y[img1];// Obj1's top-left Y minus (Obj1's height / 2) plus Collision Rectangle's top-left Y corner.
		top2 =  object2->y- ( object2->height[img2]/2 ) + object2->col_y[img2];// Obj2's top-left Y minus (Obj2's height / 2) plus Collision Rectangle's top-left Y corner.
		bottom1 = object1->y- ( object1->height[img1]/2 ) + ( object1->col_y[img1] + object1->col_height[img1] );// Obj1's bottom-right Y minus (Obj1's height / 2) plus (Collision Rectangle's bottom-right Y corner plus Collision Rectangle's height).
		bottom2 = object2->y- ( object2->height[img2]/2 ) + ( object2->col_y[img2] + object2->col_height[img2] );// Obj2's bottom-right Y minus (Obj2's height / 2) plus (Collision Rectangle's bottom-right Y corner plus Collision Rectangle's height).

		/*
		DEBUG INFO: Remove this comment and recompile the library for showing a red rectangle
		            around each sprite's bounding box.

		gp2d::DisableTexturing();
		gp2d::BeginLines();
			SetColor3(1,1,1);
			gp2d::DrawRectangle(left1,top1,right1,bottom1);
			gp2d::DrawRectangle(left2,top2,right2,bottom2);
		gp2d::EndLines();
		gp2d::EnableTexturing();
		*/

// Check for basic bounding box collision.
		if ( bottom1 < top2 ) return ( 0 );
		if ( top1 > bottom2 ) return ( 0 );

		if ( right1 < left2 ) return ( 0 );
		if ( left1 > right2 ) return ( 0 );

// We're colliding since no function has returned zero yet, so, calculate the overlapping rectangle
// we'll use for checking the pixels from each image.

		if ( bottom1 > bottom2 ) over_bottom = bottom2;
		else over_bottom = bottom1;

		if ( top1 < top2 ) over_top = top2;
		else over_top = top1;

		if ( right1 > right2 ) over_right = right2;
		else over_right = right1;

		if ( left1 < left2 ) over_left = left2;
		else over_left = left1;

		/*
		DEBUG INFO: Remove this comment and recompile the library for showing a blue rectangle
		            around each sprite's overlapping rectangle relative to the sprite and
		            screen coordinates.

		gp2d::DisableTexturing();
		gp2d::BeginLines();
			SetColor3(0,0,1);
			gp2d::DrawRectangle(over_left,over_top,over_right,over_bottom);
		gp2d::EndLines();
		gp2d::EnableTexturing();
		*/

// Now, get the coordinates from each image, relative to their dimensions and not
// the sprite's position on the screen.

		right_off  = ( over_right - ( object2->x- ( object2->width[img2]/2 ) ) );
		top_off    = ( over_top - ( object2->y- ( object2->height[img2]/2 ) ) );
		left_off   = ( over_left - ( object2->x- ( object2->width[img2]/2 ) ) );
		bottom_off = ( over_bottom - ( object2->y- ( object2->height[img2]/2 ) ) );

		if ( right_off  > object2->width[img2] ) { right_off  = object2->width[img2];  }
		if ( top_off > object2->height[img2] ) { top_off = object2->height[img2]; }
		if ( left_off  < 0 ) { left_off = 0; }
		if ( bottom_off   < 0 ) { bottom_off = 0; }
		/*
				DEBUG INFO: Remove this comment and recompile the library for showing a blue rectangle
				            around each sprite's overlapping rectangle relative to each sprite's image
				            coordinates.
				gp2d::DisableTexturing();
				gp2d::BeginLines();
					SetColor3(0,0,1);
					gp2d::DrawRectangle(left_off,top_off,right_off,bottom_off);
				gp2d::EndLines();
				gp2d::EnableTexturing();
		*/

// We got the rectangle for both images, so, let's check for them now.
// Gotta lock the surfaces first - it's an SDL requirement.
		SDL_LockSurface ( surface1 );
		SDL_LockSurface ( surface2 );
		for ( px = ( Uint32 ) left_off; px <= ( Uint32 ) right_off;  px++ ) {
			for ( py = ( Uint32 ) top_off;  py <= ( Uint32 ) bottom_off; py++ ) {

// For every pixel in the region...
				GetPixelRGBA(surface2,px,py,pr,pg,pb,pa2);// Get the pixel's alpha from the second image.

				/*
					DEBUG INFO: Remove this comment and recompile the library for showing a red area marking
							the collision area found in the destination sprite.
					gp2d::DisableTexturing();
					gp2d::SetPointSize(1.0f);
					gp2d::BeginPoints();
						if(pa2>1){ SetColor3(1,0,0); gp2d::DrawPixel(px,py); }
					gp2d::EndPoints();
					gp2d::EnableTexturing();
				*/

// If there's collision in the destination image (alpha is not zero) unlock the surfaces and return a true value.
// if(pa2>1){ SDL_UnlockSurface(surface1); SDL_UnlockSurface(surface2); return(1); }
				if ( pa2>0 ) { SDL_UnlockSurface ( surface1 ); SDL_UnlockSurface ( surface2 ); return ( 1 ); }
			}
		}

// No collision in the region, unlock the surfaces and return false.

		SDL_UnlockSurface ( surface1 );
		SDL_UnlockSurface ( surface2 );

		return ( 0 );

	}

//added by KIAaze
	short int CollisionPixel_2 ( gp2d::Sprite * object1, gp2d::Sprite * object2, int img1, int img2, GLfloat &Nx, GLfloat &Ny, GLfloat &Tx, GLfloat &Ty, bool bounding, bool overlap, bool relative_overlap, bool pixels, bool force, bool slope ) {

		Nx=0;//default values
		bool collision=false;

		GLfloat left1, left2, over_left;
		GLfloat right1, right2, over_right;
		GLfloat top1, top2, over_top;
		GLfloat bottom1, bottom2, over_bottom;
// GLfloat over_width, over_height;
		GLfloat top_off, left_off, right_off, bottom_off;
		Uint32 px, py;
		Uint8  pr, pg, pb, pa2;

		SDL_Surface *surface1, *surface2;
		surface1 = object1->animationSheet[img1].spriteTexture->imgF;
		surface2 = object2->animationSheet[img2].spriteTexture->imgF;

// Alright... this is tricky. First, calculate the collision region just like in the function above.
		left1 =  object1->x- ( object1->width[img1]/2 ) + object1->col_x[img1];
		left2 =  object2->x- ( object2->width[img2]/2 ) + object2->col_x[img2];
		right1 = object1->x- ( object1->width[img1]/2 ) + ( object1->col_x[img1] + object1->col_width[img1] );
		right2 = object2->x- ( object2->width[img2]/2 ) + ( object2->col_x[img2] + object2->col_width[img2] );

		top1 =  object1->y- ( object1->height[img1]/2 ) + object1->col_y[img1];
		top2 =  object2->y- ( object2->height[img2]/2 ) + object2->col_y[img2];
		bottom1 = object1->y- ( object1->height[img1]/2 ) + ( object1->col_y[img1] + object1->col_height[img1] );
		bottom2 = object2->y- ( object2->height[img2]/2 ) + ( object2->col_y[img2] + object2->col_height[img2] );

// DEBUG INFO: Remove this comment and recompile the library for showing a white rectangle around each sprite's bounding box.
		if ( bounding ) {
			gp2d::DisableTexturing();
			gp2d::BeginLines();
			SetColor3 ( 1,1,1 );
			gp2d::DrawRectangle ( left1,top1,right1,bottom1 );
			gp2d::DrawRectangle ( left2,top2,right2,bottom2 );
			gp2d::EndLines();
			gp2d::EnableTexturing();
		}

// Check for basic bounding box collision.
		if ( bottom1 < top2 ) return ( 0 );
		if ( top1 > bottom2 ) return ( 0 );
		if ( right1 < left2 ) return ( 0 );
		if ( left1 > right2 ) return ( 0 );

// We're colliding since no function has returned zero yet, so, calculate the overlapping rectangle we'll use for checking the pixels from each image.
		if ( bottom1 > bottom2 ) over_bottom = bottom2;
		else over_bottom = bottom1;
		if ( top1 < top2 ) over_top = top2;
		else over_top = top1;
		if ( right1 > right2 ) over_right = right2;
		else over_right = right1;
		if ( left1 < left2 ) over_left = left2;
		else over_left = left1;

// DEBUG INFO: Remove this comment and recompile the library for showing a green rectangle around each sprite's overlapping rectangle relative to the sprite and screen coordinates.
		if ( overlap ) {
			gp2d::DisableTexturing();
			gp2d::BeginLines();
			SetColor3 ( 0,1,0 );
			gp2d::DrawRectangle ( over_left,over_top,over_right,over_bottom );
			gp2d::EndLines();
			gp2d::EnableTexturing();
		}

// Now, get the coordinates from each image, relative to their dimensions and not the sprite's position on the screen.
		right_off  = ( over_right - ( object2->x- ( object2->width[img2]/2 ) ) );
		top_off    = ( over_top - ( object2->y- ( object2->height[img2]/2 ) ) );
		left_off   = ( over_left - ( object2->x- ( object2->width[img2]/2 ) ) );
		bottom_off = ( over_bottom - ( object2->y- ( object2->height[img2]/2 ) ) );

		if ( right_off  > object2->width[img2] ) { right_off  = object2->width[img2];  }
		if ( top_off > object2->height[img2] ) { top_off = object2->height[img2]; }
		if ( left_off  < 0 ) { left_off = 0; }
		if ( bottom_off   < 0 ) { bottom_off = 0; }

		/* DEBUG INFO: Remove this comment and recompile the library for showing a blue rectangle around each sprite's overlapping rectangle relative to each sprite's image coordinates.*/
		if ( relative_overlap ) {
			gp2d::DisableTexturing();
			gp2d::BeginLines();
			SetColor3 ( 0,0,1 );
			gp2d::DrawRectangle ( left_off,top_off,right_off,bottom_off );
			gp2d::EndLines();
			gp2d::EnableTexturing();
		}

// We got the rectangle for both images, so, let's check for them now.
// Gotta lock the surfaces first - it's an SDL requirement.
		SDL_LockSurface ( surface1 );
		SDL_LockSurface ( surface2 );

		for ( px = ( Uint32 ) left_off; px <= ( Uint32 ) right_off;  px++ ) {
			for ( py = ( Uint32 ) top_off;  py <= ( Uint32 ) bottom_off; py++ ) {

				GetPixelRGBA(surface2,px,py,pr,pg,pb,pa2);// Get the pixel's alpha from the second image.

				/* DEBUG INFO: Remove this comment and recompile the library for showing a red area marking the collision area found in the destination sprite.*/
				if ( pixels ) {
					gp2d::DisableTexturing();
					gp2d::SetPointSize ( 1.0f );
					gp2d::BeginPoints();
					if ( pa2>0 ) {SetColor3 ( 1,0,0 ); gp2d::DrawPixel ( px,py );}
					gp2d::EndPoints();
					gp2d::EnableTexturing();
				}


// If there's collision in the destination image (alpha is not zero), set collision to true.
				if ( pa2>0 ) {collision=true; break;}
			}
			if ( collision ) break;
		}

//We have a collision, now let's get the force and slope. :)
		if ( collision ) {
//border 1
			int top_force=0;
			if ( over_top == top1 ) { //if top1 border intersects with sprite 2
				py= ( Uint32 ) top_off;
				for ( px = ( Uint32 ) left_off; px <= ( Uint32 ) right_off;  px++ ) {
					GetPixelRGBA(surface2,px,py,pr,pg,pb,pa2);
					if ( pa2>0 ) top_force++;
				}
			}

//border 2
			int bottom_force=0;
			if ( over_bottom == bottom1 ) { //if bottom1 border intersects with sprite 2
				py= ( Uint32 ) bottom_off;
				for ( px = ( Uint32 ) left_off; px <= ( Uint32 ) right_off;  px++ ) {
					GetPixelRGBA(surface2,px,py,pr,pg,pb,pa2);
					if ( pa2>0 ) bottom_force++;
				}
			}

//border 3
			int right_force=0;
			if ( over_right == right1 ) { //if right1 border intersects with sprite 2
				px= ( Uint32 ) right_off;
				for ( py = ( Uint32 ) top_off;  py <= ( Uint32 ) bottom_off; py++ ) {
					GetPixelRGBA(surface2,px,py,pr,pg,pb,pa2);
					if ( pa2>0 ) right_force++;
				}
			}

//border 4
			int left_force=0;
			if ( over_left == left1 ) { //if left1 border intersects with sprite 2
				px= ( Uint32 ) left_off;
				for ( py = ( Uint32 ) top_off;  py <= ( Uint32 ) bottom_off; py++ ) {
					GetPixelRGBA(surface2,px,py,pr,pg,pb,pa2);
					if ( pa2>0 ) left_force++;
				}
			}

//calculate force (normal to the tangent => Nx,Ny)
			Nx=left_force-right_force;
			Ny=top_force-bottom_force;
//calculate slope
			Tx=-Ny;
			Ty=Nx;

			/* DEBUG INFO: Remove this comment and recompile the library for showing the force and slope of the collision.*/
			if ( force ) {
//display force
				gp2d::DisableTexturing();
				gp2d::BeginLines();
				SetColor3 ( 0,1,0 );
				gp2d::DrawLine ( 100,100,100+Nx,100+Ny );
				gp2d::EndLines();
				gp2d::EnableTexturing();
			}

			if ( slope ) {
//display tangent/slope
				gp2d::DisableTexturing();
				gp2d::BeginLines();
				SetColor3 ( 1,0,0 );
				gp2d::DrawLine ( 100,100,100+Tx,100+Ty );
				gp2d::EndLines();
				gp2d::EnableTexturing();
			}

//return true
			SDL_UnlockSurface ( surface1 ); SDL_UnlockSurface ( surface2 ); return ( 1 );
		}

// No collision in the region, unlock the surfaces and return false.
		SDL_UnlockSurface ( surface1 );
		SDL_UnlockSurface ( surface2 );
		return ( 0 );
	}
//----------------------------------------------
}
