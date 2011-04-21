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

	/*!
	    This is the Sprite class.

		The Sprite texture is placed relative to the Sprite position. The Sprite itself is positioned relative to the Universe.

		\image html SpriteSystem.gif

		See also utilities.h for more info on the coordinate systems.
	*/
	class Sprite {

		//attributes
		//non-dynamic
		protected:
			GLfloat x,y,z;/**< Sprite's position */
			/// @todo a sprite doesn't need vx,vy. Create a derived class for physical objects!
			GLfloat vx,vy;/**< Velocity of the sprite */
			GLfloat m_accel_x; /**< X acceleration */
			GLfloat m_accel_y; /**< Y acceleration. */

			GLfloat animationSpeed;/**< This is measured in fps */
			bool PhysicalObject;
		public:
			int m_integrity;
			unsigned long collision_type;
			bool IsStatic;
			char spriteName[256];
			GLfloat xrot,yrot,zrot;/**< Sprite's position */

			GLfloat angle;/**< Sprite's angle. */
			/// @todo Why do we need two angles? Fix this insane mirror/flip/angle/TiltAngle system!!!
			GLfloat SpriteTiltAngle; /**< Sprite's orientation angle (for terrain tilting). */

			GLfloat acceleration;/**< how fast is the sprite accelerating in the angle direction? */
			bool iterateSheets;/**< Do you want to iterate through sheets automatically? */
			signed int currentSheet;//This MUST be a signed int because sometimes, it becomes -1. DO NOT CHANGE!
			bool collision;
			GLfloat Elasticity; /**< how much movement does this weapon keep when it  bounces? */
			Timer animationTimer;/**< Sprites have there own built in timer for animation */
			bool Mirror;/**< Mirror the sprite? (Horizontally). */
			bool Flip;/**< Flip the sprite? (Vertically). */
			bool Backwards;/**< Go backwards through sheets? */
			//potentially dynamic
		public:
			Texture* m_texture;
		public:
			vector <GLfloat> width;/**< Sprite's width. */
			vector <GLfloat> height;/**< Sprite's height. */
			vector <GLfloat> alpha;/**< Sprite's alpha. */
			vector <GLfloat> col_x;/**< Collision rectangle top-left X */
			vector <GLfloat> col_y;/**< Collision rectangle top-left Y */
			vector <GLfloat> col_width;/**< Collision rectangle width (minus X) */
			vector <GLfloat> col_height;/**< Collision rectangle height (minus Y) */
			vector <spriteSheet> animationSheet;
		//Constructors
		public:
			Sprite();/**< default constructor */
			Sprite ( const char texture[], int w=1, int h=1 );/**< special constructor */
			Sprite ( Texture* tex, int numSpritesWide=1, int numSpritesHigh=1 );
		//accessors
		public:
			const GLfloat GetX() { return x; }
			const GLfloat GetY() { return y; }
			const GLfloat GetZ() { return z; }
			const GLfloat GetVX() { return vx; }
			const GLfloat GetVY() { return vy; }
			GLfloat getAnimationSpeed ( void ) { return this->animationSpeed; } /**< on the current sheet selected */
			bool IsPhysical() { return PhysicalObject; }
			//TODO: Make sure this is correct:
			GLfloat GetHeight() { return(height[currentSheet]); }
			GLfloat GetWidth() { return(width[currentSheet]); }
		//modifiers
		public:
			void SetX(const GLfloat a_x) { x = a_x; }
			void SetY(const GLfloat a_y) { y = a_y; }
			void SetZ(const GLfloat a_z) { z = a_z; }
			void SetVX(const GLfloat a_vx) { vx = a_vx; }
			void SetVY(const GLfloat a_vy) { vy = a_vy; }
			void SetAcceleration ( GLfloat a_new_accel, GLfloat a_new_angle );

			void setAnimationSpeed ( GLfloat const speed ) { this->animationSpeed = speed; }
			void SetPhysicalObject ( bool Physical ) { PhysicalObject = Physical; }
		//other methods
		public:
			int Load ();
			int Load ( const char texture[], int w=1, int h=1 );/**< Load a texture for the sprite to use. */
			int  Load ( Texture* tex, int w=1, int h=1 );
			int  UnLoad ();/**< unload stuff (clear vectors) */
			int Loop_Load ( const char base_path[], int N );
			int DeleteTextures();
			void Draw();/**< Draw the whole texture */
			void DrawCube();
			void Draw_loadingbar();
			void DrawFrame();/**< Draw the sprite animation frame */
			void selectSheet ( int sheet );/**< Select sheet by number*/
			int selectNextSheet ( void );/**< Select next sheet*/
			bool setNextFrame ( void );/**< Sets the next frame overall. Result depends on Sprite::iterateSheets, Sprite::Backwards and spriteSheet::Backwards */
			void SetWindowing ( GLfloat const x, GLfloat const y, GLfloat const w, GLfloat const h );
			void Move ( GLfloat , GLfloat );/**< Move the sprite to x,y. */
			void Scale ( GLfloat );/**< Scale the sprite. */
			void Scale ( GLfloat , int );/**< Scale a specified sprite's image. */
			void ScaleXY ( GLfloat, GLfloat );/**< Scale the sprite. */
			void ScaleXY ( GLfloat, GLfloat , int );/**< Scale a specified sprite's image. */
			void Advance ( GLfloat );/**< Advance the position of the sprite's in its current angle in GLfloat steps. */
			void ResizePropW ( GLfloat const );/**< Resize all of the sprite images proportionally by width in pixels */
			void ResizePropW ( int,GLfloat const );/**< Resize a sprite image proportionally by width in pixels */
			bool LoopFinished();/**< Returns true if we've reached the last frame of the animation.  Result depends on Sprite::iterateSheets, Sprite::Backwards and spriteSheet::Backwards */

			virtual int DoBehaviour();
			virtual int Update();
			virtual int Render(gp2d::Camera Cam);
	};
}

#endif
