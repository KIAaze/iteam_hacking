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
#include "gp2d.h"

namespace gp2d {

	Sprite::Sprite() {
		iterateSheets = false;
		currentSheet = 0;
		animationSpeed = 12.0f;	//By default we will do 12 fps
		vx = 0.0f;
		vy = 0.0f;
	}
	
	Sprite::~Sprite() {
		//Need to get rid of all the animationSheets
		if (!animationSheet.empty()) {
			for (int idx; idx < animationSheet.size(); idx++)
			{
				delete animationSheet[idx];
			}
		}
	}
	
	
	void Sprite::selectSheet(int sheet) {
		currentSheet = sheet;
	}
	
	int Sprite::selectNextSheet(void) {
		
		currentSheet++;
		if (currentSheet >= animationSheet.size()) {
			currentSheet = 0;
		}
		animationSheet[currentSheet]->setFrame(0);
		
		return currentSheet;
	}
	
	// Set the next frame on the current sprite sheet
	// this automatically overlaps to the beginning frame
	bool Sprite::setNextFrame() {
		
		GLfloat animDiff;
		
		animDiff = getMovementFactor(this->animationSpeed, animationTimer.getTicks());
		if (animDiff > 1) {
			animationTimer.start();			
			if (animationSheet[currentSheet]->setNextFrame() == 0) {
				// We have performed a full loop
				if (iterateSheets == true)
				{
					// Have we looped back round to sheet 0
					if (selectNextSheet() == 0) {
						return false;
					}
				}
			}
		}
		return true;
	}

	// Set the window onto the texture based on texture coords 0->1	
	void Sprite::SetWindowing(GLfloat x, GLfloat y, GLfloat w, GLfloat h) {
		animationSheet[currentSheet]->spriteCurrentTextCoords.X = x;
		animationSheet[currentSheet]->spriteCurrentTextCoords.Y = y;
		animationSheet[currentSheet]->spriteCurrentTextCoords.Width = w;
		animationSheet[currentSheet]->spriteCurrentTextCoords.Height = h;
	}
	
	void Sprite::DrawFrame(void) {
		
		struct SpriteTextCoords *tempCoord;		
			
		glTranslatef(x,y,z);		// Move to the sprite's coordinate.
		glRotatef(180,0,0,1);	// Rotate 180º in Z

		if(Mirror==true){ glRotatef(180,0,1,0); }	// We're mirrored? rotate 180º in Y
		if(Flip==true){ glRotatef(180,1,0,0); }	// We're flipped? rotate 180º in X

		glRotatef(angle,0,0,1);										// Rotate in the sprite's angle
		EnableTexturing();											// Enable texturing, just in case
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Set blending parameters, for PNGs
		glEnable(GL_BLEND);											// Enable blending.

		
		// TODO: Not sure about this
		if(!animationSheet.empty()) {
			glBindTexture(GL_TEXTURE_2D, animationSheet[currentSheet]->spriteTexture.id);
		}	// If the img vector is not
																							// empty (eg: We've loaded
																							// a texture) then bind it
																							// to the chosen img_id.
		
		tempCoord = animationSheet[currentSheet]->getFrameCoord();
		
		glBegin(GL_QUADS);
			glColor4f(1,1,1,alpha[currentSheet]);														// Set the sprite's alpha
			glTexCoord2f(tempCoord->X + tempCoord->Width, tempCoord->Y + tempCoord->Height);
				glVertex3f(-width[currentSheet]/2, -height[currentSheet]/2, 0);		
			glTexCoord2f(tempCoord->X + tempCoord->Width, tempCoord->Y); 
				glVertex3f(-width[currentSheet]/2,  height[currentSheet]/2, 0);
			glTexCoord2f(tempCoord->X, tempCoord->Y);
				glVertex3f( width[currentSheet]/2,  height[currentSheet]/2, 0);
			glTexCoord2f(tempCoord->X, tempCoord->Y + tempCoord->Height);
				glVertex3f( width[currentSheet]/2, -height[currentSheet]/2, 0);
		
		glEnd(); 

		/*
		   Sprite is drawn in this order:

		          0,0 	     1,0

			         3 ----- 2
			                  
			         |       |
			                  
			         4 ----- 1

                0,1       1,1
		*/
	}
	
	void Sprite::Draw(void) {
		glTranslatef(x,y,z);		// Move to the sprite's coordinate.
		glRotatef(180,0,0,1);	// Rotate 180º in Z

		if(Mirror==true){ glRotatef(180,0,1,0); }	// We're mirrored? rotate 180º in Y
		if(Flip==true){ glRotatef(180,1,0,0); }	// We're flipped? rotate 180º in X

		glRotatef(angle,0,0,1);										// Rotate in the sprite's angle
		EnableTexturing();											// Enable texturing, just in case
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Set blending parameters, for PNGs
		glEnable(GL_BLEND);											// Enable blending.

		// TODO: Not sure about this
		if(!animationSheet.empty()) {
			glBindTexture(GL_TEXTURE_2D, animationSheet[currentSheet]->spriteTexture.id);
		}	// If the img vector is not
																							// empty (eg: We've loaded
																							// a texture) then bind it
																							// to the chosen img_id.
		
		glBegin(GL_QUADS);
			glColor4f(1,1,1,alpha[currentSheet]);														// Set the sprite's alpha
			glTexCoord2f(1, 1); glVertex3f(-width[currentSheet]/2, -height[currentSheet]/2, 0);		
			glTexCoord2f(1, 0); glVertex3f(-width[currentSheet]/2,  height[currentSheet]/2, 0);
			glTexCoord2f(0, 0); glVertex3f( width[currentSheet]/2,  height[currentSheet]/2, 0);
			glTexCoord2f(0, 1); glVertex3f( width[currentSheet]/2, -height[currentSheet]/2, 0);
		
		glEnd(); 

		/*
		   Sprite is drawn in this order:

		          0,0 	     1,0

			         3 ----- 2
			                  
			         |       |
			                  
			         4 ----- 1

                0,1       1,1
		*/
	}

	int Sprite::Load(const char texfilename[], int numSpritesWide, int numSpritesHigh) {	// Load a texture as a sprite image...
		
		int img_index;
				
		animationSheet.push_back(new spriteSheet());
		img_index = this->animationSheet.size()-1;
		animationSheet[img_index]->loadSheet(texfilename, numSpritesWide, numSpritesHigh);
	
		// Set the current image widths and height for the sprite
		width.push_back(this->animationSheet[img_index]->getSpriteWidth());
		height.push_back(this->animationSheet[img_index]->getSpriteHeight());
		
		alpha.push_back(1.0f);			// Set a default alpha of 1.0f (fully opaque).
		// ---
		col_x.push_back(0);					// Set a default collision top-left corner X to zero.
		col_y.push_back(0);					// Set a default collision top-left corner Y to zero.
		col_width.push_back(width[img_index]);	// Set a default collision bottom-right corner X to the image's width.
		col_height.push_back(height[img_index]);	// Set a default collision bottom-right corner Y to the image's height.
		// ---
		angle=0;					// Default angle: 0 (facing right).
		Mirror=false;			// Don't mirror.
		Flip=false;				// Don't flip.
		x=0;y=0;z=0;			// Default coordinates.
		return img_index;	// Return its position value in the img vector.
	}

	void Sprite::Move(GLfloat x2, GLfloat y2) { // Move the sprite.
		x=x2; y=y2;
	}


	void Sprite::Scale(GLfloat factor) {	// Scale the sprite by a given factor
		for(int x=0; x<animationSheet.size(); x++) 			// For each sprite image...
    	{
			width[x]=width[x]*factor;				// Scale width,
			height[x]=height[x]*factor;			// height,
			col_width[x]=col_width[x]*factor;	// collision box's width
			col_height[x]=col_height[x]*factor;	// and height.
		}
	}

	void Sprite::Scale(GLfloat factor, int img_id) {	// Same as above, but with a specified sprite's image id.
		width[img_id]=width[img_id]*factor;
		height[img_id]=height[img_id]*factor;
		col_width[img_id]=col_width[img_id]*factor;
		col_height[img_id]=col_height[img_id]*factor;
	}
/*
	void Sprite::Advance(GLfloat steps) {
		x+=(cosf((angle-90.0f)*CONST_DEG2RAD))*steps;	// Calculate and set new X
		y+=(sinf((angle-90.0f)*CONST_DEG2RAD))*steps;	// Calculate and set new Y
	}
*/


	void Sprite::ResizePropW(GLfloat new_width) {
		GLfloat nw,nh;
		nw = new_width;
		for(int x=0; x<animationSheet.size(); x++) 			// For each sprite image...
    	{
			nh = (height[x] / 100) * (100 / width[x] * new_width);
			width[x] = nw;
			height[x]= nh;
		}
	}

	void Sprite::ResizePropW(int img_id, GLfloat new_width) {
		GLfloat nw,nh;
		nw = new_width;
		nh = (height[img_id] / 100) * (100 / width[img_id] * new_width);
		width[img_id] = nw;
		height[img_id]= nh;
	}

}
