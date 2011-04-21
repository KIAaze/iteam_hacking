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

SPRITE CLASS (version 0.0.1)
By DARKGuy

MODIFICATIONS BY:
No one at the moment.
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

#ifndef _GP2D_SPRITE_H
#define _GP2D_SPRITE_H

#include "gp2d.h"

namespace gp2d {

	using namespace std;
	
	class Sprite {
		public:
			Sprite();
			~Sprite();
			
			GLfloat x,y,z;							// Sprite's position
			GLfloat vx, vy;							// Velocity of the sprite
			GLfloat angle;							// Sprite's angle.
			vector <GLfloat> width;				// Sprite's width.
			vector <GLfloat> height;			// Sprite's height.
			// vector <GLuint>  img;				// Sprite's OpenGL texture ID.
			vector <GLfloat> alpha;				// Sprite's alpha.
			
			vector<spriteSheet *>			animationSheet;
			bool iterateSheets;
			int currentSheet;

			Timer	animationTimer;	// Sprites have there own built in timer for animation
			
			vector <GLfloat> col_x;			// Collision rectangle top-left X
			vector <GLfloat> col_y;			// Collision rectangle top-left Y
			vector <GLfloat> col_width;	// Collision rectangle width (minus X)
			vector <GLfloat> col_height;	// Collision rectangle height (minus Y)

			bool Mirror;	// Mirror the sprite? (Horizontally).
			bool Flip;		// Flip the sprite? (Vertically).

			int  Load(const char texture[], int w=1, int h=1); // Load a texture for the sprite to use.
			
			void Draw();								// Draw the whole texture
			void DrawFrame();					// Draw the sprite animation frame
			
			void selectSheet(int sheet);				// Selects the next sheet to be drawn
			int selectNextSheet(void);		// on the current sheet selected
			bool setNextFrame(void);				// Sets the next frame to be drawn based
																	// on the current sheet selected
			void SetWindowing(GLfloat x, GLfloat y, GLfloat w, GLfloat h);

			void Move(GLfloat, GLfloat);		// Move the sprite to x,y.
			void Scale(GLfloat);					// Scale the sprite.
			void Scale(GLfloat, int);			// Scale a specified sprite's image.
			void Advance(GLfloat);				// Advance the position of the sprite's in its current angle in GLfloat steps.

			void ResizePropW(GLfloat);			// Resize all of the sprite images proportionally by width in pixels
			void ResizePropW(int,GLfloat);	// Resize a sprite image proportionally by width in pixels

		private:
			GLfloat animationSpeed;				// This is measured in fps
	};
}

#endif
