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
#include <sstream>

namespace gp2d {

	//The big two
	//default constructor
	Sprite::Sprite() {
		PrintDebug ( "Sprite: default constructor called" );
		strcpy(spriteName,"Default");
		collision_type=1;
		IsStatic=false;

		animationSpeed = 0.0f;//By default we don't animate
		PhysicalObject=true;
		x=y=z=0;
		xrot=yrot=zrot=0;
		vx=vy=0.0f;
		angle=0;
		SpriteTiltAngle=0;
		acceleration=0;
		iterateSheets = false;
		currentSheet = 0;
		collision=false;
		Elasticity=0;
		Mirror=false;
		Flip=false;
		Backwards=false;
		m_texture=NULL;
		m_integrity=100;
	}
	//special constructor
	Sprite::Sprite ( const char texture[], int w, int h ) {
		PrintDebug ( "Sprite: special constructor called" );
		strcpy(spriteName,"Special 1");

		collision_type=1;
		IsStatic=false;

		animationSpeed = 0.0f;//By default we will don't animate
		PhysicalObject=true;
		x=y=z=0;
		xrot=yrot=zrot=0;
		vx=vy=0.0f;
		angle=0;
		SpriteTiltAngle=0;
		acceleration=0;
		iterateSheets = false;
		currentSheet = 0;
		collision=false;
		Elasticity=0;
		Mirror=false;
		Flip=false;
		Backwards=false;
		m_texture=NULL;
		this->Load ( texture,w,h );
		m_integrity=100;
	}

	//special constructor
	Sprite::Sprite ( Texture* tex, int numSpritesWide, int numSpritesHigh ) {
		PrintDebug ( "[Sprite::Sprite ( Texture* tex )] called" );
		strcpy(spriteName,"Special 2");

		collision_type=1;
		IsStatic=false;

		animationSpeed = 0.0f;//By default we will don't animate
		PhysicalObject=true;
		x=y=z=0;
		xrot=yrot=zrot=0;
		vx=vy=0.0f;
		angle=0;
		SpriteTiltAngle=0;
		acceleration=0;
		iterateSheets = false;
		currentSheet = 0;
		collision=false;
		Elasticity=0;
		Mirror=false;
		Flip=false;
		Backwards=false;
		m_texture = tex;

		animationSheet.push_back ( spriteSheet ( tex, numSpritesWide, numSpritesHigh ) );
		int img_index = this->animationSheet.size()-1;

		width.push_back ( this->animationSheet[img_index].getSpriteWidth() );
		height.push_back ( this->animationSheet[img_index].getSpriteHeight() );
		alpha.push_back ( 1.0f );
		col_x.push_back ( 0 );
		col_y.push_back ( 0 );
		col_width.push_back ( width[img_index] );
		col_height.push_back ( height[img_index] );
		m_integrity=100;
	}

	int Sprite::DoBehaviour()
	{
		if(m_integrity<=0) return(1);
		return(!(this->setNextFrame()));
	}

	int Sprite::Update()
	{
		return(0);
	}
	int Sprite::Render(gp2d::Camera Cam)
	{
		Cam.Begin();
		this->DrawFrame();
		Cam.End();
		return(0);
	}

	void Sprite::selectSheet ( int sheet ) {
		currentSheet = sheet;
	}

	int Sprite::selectNextSheet ( void ) {

		if ( !Backwards ) {
			currentSheet++;
			if ( currentSheet >= (signed int) animationSheet.size() ) {
				currentSheet = 0;
			}
		} else {
			currentSheet--;
			if ( currentSheet <= (signed int) 0 ) {
				currentSheet = animationSheet.size()-1;
			}
		}

		if ( !animationSheet[currentSheet].Backwards ) {
			animationSheet[currentSheet].setFrame ( 0 );
		} else {
			animationSheet[currentSheet].setFrame ( animationSheet[currentSheet].getspriteTotalFrames()-1 );
		}

		return currentSheet;
	}

	// Set the next frame on the current sprite sheet
	// this automatically overlaps to the beginning frame
	// returns false when it has reached the end of the animation
	bool Sprite::setNextFrame ( void ) {
		GLfloat animDiff;
		animDiff = GetDelta ( this->animationSpeed, animationTimer.GetTicks() );
		if ( animDiff > 1 ) {
			animationTimer.Start();
			animationSheet[currentSheet].setNextFrame();
			if ( animationSheet[currentSheet].LoopFinished() ) {
				if ( iterateSheets == true ) {
					selectNextSheet();
					if ( LoopFinished() ) {
						return false;
					}
				} else return false;
			}
		}
		return true;
	}

	// Set the window onto the texture based on texture coords 0->1
	//currently unused
	void Sprite::SetWindowing ( GLfloat const x, GLfloat const y, GLfloat const w, GLfloat const h ) {
		animationSheet[currentSheet].spriteCurrentTextCoords.X = x;
		animationSheet[currentSheet].spriteCurrentTextCoords.Y = y;
		animationSheet[currentSheet].spriteCurrentTextCoords.Width = w;
		animationSheet[currentSheet].spriteCurrentTextCoords.Height = h;
	}

	void Sprite::DrawFrame() {
		if ( animationSheet.empty() ) {
			PrintDebug ( "[Sprite::DrawFrame] FATAL ERROR: animationSheet is empty! spriteName=%s",spriteName );
			exit ( 253 );
		}
		if ( !glIsTexture ( animationSheet[currentSheet].spriteTexture->id ) ) {
			PrintDebug ( "[Sprite::DrawFrame] FATAL ERROR: Oh shit! No texture! spriteName=%s",spriteName );
			exit ( 254 );
		}

		glTranslatef ( x,y,z );// Move to the sprite's coordinate.
		glRotatef ( 180,0,0,1 );// Rotate 180Â° in Z

		if ( Mirror==true ) { glRotatef ( 180,0,1,0 ); }// We're mirrored? rotate 180Â° in Y
		if ( Flip==true ) { glRotatef ( 180,1,0,0 ); }// We're flipped? rotate 180Â° in X

		glRotatef ( angle,0,0,1 );// Rotate in the sprite's angle
		EnableTexturing();// Enable texturing, just in case
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );// Set blending parameters, for PNGs
		glEnable ( GL_BLEND );// Enable blending.

		// TODO: Not sure about this
		if ( !animationSheet.empty() ) {
			// If the img vector is not
			// empty (eg: We've loaded
			// a texture) then bind it
			// to the chosen img_id.
			glBindTexture ( GL_TEXTURE_2D, animationSheet[currentSheet].spriteTexture->id );
		}

		struct SpriteTextCoords *tempCoord;
		tempCoord = animationSheet[currentSheet].getFrameCoord();

		glBegin ( GL_QUADS );
		glColor4f ( 1,1,1,alpha[currentSheet] );// Set the sprite's alpha
		glTexCoord2f ( tempCoord->X + tempCoord->Width, tempCoord->Y + tempCoord->Height );
		glVertex3f ( -width[currentSheet]/2, -height[currentSheet]/2, 0 );
		glTexCoord2f ( tempCoord->X + tempCoord->Width, tempCoord->Y );
		glVertex3f ( -width[currentSheet]/2,  height[currentSheet]/2, 0 );
		glTexCoord2f ( tempCoord->X, tempCoord->Y );
		glVertex3f ( width[currentSheet]/2,  height[currentSheet]/2, 0 );
		glTexCoord2f ( tempCoord->X, tempCoord->Y + tempCoord->Height );
		glVertex3f ( width[currentSheet]/2, -height[currentSheet]/2, 0 );

		glEnd();
		/*
		   Sprite is drawn in this order:

				0,0	1,0
			         3 ----- 2
			       
			         |       |
			       
			         4 ----- 1
				0,1	1,1
		*/
	}

	void Sprite::Draw() {
//		if(
//PrintDebug("Drawing %s",animationSheet[currentSheet].spriteTexture.TextureName);//)

		if ( !glIsTexture ( animationSheet[currentSheet].spriteTexture->id ) ) {
			PrintDebug ( "[Sprite::Draw] FATAL ERROR: Oh shit! No texture!" );
			exit ( -2 );
		}

		glTranslatef ( x,y,z );// Move to the sprite's coordinate.
		glRotatef ( 180,0,0,1 );// Rotate 180ÃÂÃÂº in Z

		if ( Mirror==true ) { glRotatef ( 180,0,1,0 ); }// We're mirrored? rotate 180ÃÂÃÂº in Y
		if ( Flip==true ) { glRotatef ( 180,1,0,0 ); }// We're flipped? rotate 180ÃÂÃÂº in X

		glRotatef ( angle,0,0,1 );// Rotate in the sprite's angle

		EnableTexturing();// Enable texturing, just in case
		glEnable ( GL_BLEND );// Enable blending.

		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );// Set blending parameters, for PNGs

		// TODO: Not sure about this
		if ( !animationSheet.empty() ) {
			// If the img vector is not
			// empty (eg: We've loaded
			// a texture) then bind it
			// to the chosen img_id.
			glBindTexture ( GL_TEXTURE_2D, animationSheet[currentSheet].spriteTexture->id );
		}

		struct SpriteTextCoords *tempCoord;
		tempCoord = animationSheet[currentSheet].getFrameCoord();

		glBegin ( GL_QUADS );
		glColor4f ( 1,1,1,alpha[currentSheet] );// Set the sprite's alpha
		glTexCoord2f ( tempCoord->X + tempCoord->Width, tempCoord->Y + tempCoord->Height );
		glVertex3f ( -width[currentSheet]/2, -height[currentSheet]/2, 0 );
		glTexCoord2f ( tempCoord->X + tempCoord->Width, tempCoord->Y );
		glVertex3f ( -width[currentSheet]/2,  height[currentSheet]/2, 0 );
		glTexCoord2f ( tempCoord->X, tempCoord->Y );
		glVertex3f ( width[currentSheet]/2,  height[currentSheet]/2, 0 );
		glTexCoord2f ( tempCoord->X, tempCoord->Y + tempCoord->Height );
		glVertex3f ( width[currentSheet]/2, -height[currentSheet]/2, 0 );

		glEnd();

// 		glBegin ( GL_QUADS );
// 		glColor4f ( 1,1,1,alpha[currentSheet] );// Set the sprite's alpha
// 		glTexCoord2f ( 1, 1 ); glVertex3f ( -width[currentSheet]/2, -height[currentSheet]/2, 0 );
// 		glTexCoord2f ( 1, 0 ); glVertex3f ( -width[currentSheet]/2,  height[currentSheet]/2, 0 );
// 		glTexCoord2f ( 0, 0 ); glVertex3f ( width[currentSheet]/2,  height[currentSheet]/2, 0 );
// 		glTexCoord2f ( 0, 1 ); glVertex3f ( width[currentSheet]/2, -height[currentSheet]/2, 0 );
// 		glEnd();

		DisableTexturing();
		glDisable ( GL_BLEND );


		/*
		   Sprite is drawn in this order:

				0,0	1,0
			         3 ----- 2
			       
			         |       |
			       
			         4 ----- 1
				0,1	1,1
		*/
	}

	// Loads nothing as sprite image... Used for non-textured sprites
	int Sprite::Load () {
		width.push_back ( 0 );
		height.push_back ( 0 );
		alpha.push_back ( 0 );
		col_x.push_back ( 0 );
		col_y.push_back ( 0 );
		col_width.push_back ( 0 );
		col_height.push_back ( 0 );
		animationSheet.push_back ( spriteSheet() );
		return ( 0 );
	}

	// Load a texture as a sprite image...
	int Sprite::Load ( const char filename_branch[], int numSpritesWide, int numSpritesHigh ) {
		PrintDebug ( "[Sprite::Load]Sprite::Load called" );

		char texfilename[256];
		sprintf ( texfilename,"%s/%s",DATA_DIR,filename_branch );
		PrintDebug ( "[Sprite::Load]------------->Sprite:%s\n",texfilename );

		sprintf ( spriteName,"%s/%s",DATA_DIR,filename_branch );

		int img_index;
		img_index = this->animationSheet.size()-1;
		PrintDebug ( "[Sprite::Load]before push_back: img_index=%d\n",img_index );

		animationSheet.push_back ( spriteSheet ( texfilename, numSpritesWide, numSpritesHigh ) );
		img_index = this->animationSheet.size()-1;
		PrintDebug ( "[Sprite::Load]after push_back: img_index=%d\n",img_index );
//		animationSheet[img_index].loadSheet();

// Set the current image width and height for the sprite
		width.push_back ( this->animationSheet[img_index].getSpriteWidth() );
		height.push_back ( this->animationSheet[img_index].getSpriteHeight() );

		alpha.push_back ( 1.0f );// Set a default alpha of 1.0f (fully opaque).
// ---
		col_x.push_back ( 0 );// Set a default collision top-left corner X to zero.
		col_y.push_back ( 0 );// Set a default collision top-left corner Y to zero.
		col_width.push_back ( width[img_index] );// Set a default collision bottom-right corner X to the image's width.
		col_height.push_back ( height[img_index] );// Set a default collision bottom-right corner Y to the image's height.
// ---

		angle=0;// Default angle: 0 (facing right).
		Mirror=false;// Don't mirror.
		Flip=false;// Don't flip.
		x=0;y=0;z=0;// Default coordinates.
		return img_index;// Return its position value in the img vector.
	}

	// Load a texture as a sprite image...
	int Sprite::Load ( Texture *tex, int numSpritesWide, int numSpritesHigh ) {
		PrintDebug ( "[Sprite::Load ( Texture *tex, int numSpritesWide, int numSpritesHigh )] called" );

		strcpy(spriteName,tex->TextureName);

		int img_index;
		img_index = this->animationSheet.size()-1;
		PrintDebug ( "[Sprite::Load]before push_back: img_index=%d\n",img_index );

		animationSheet.push_back ( spriteSheet ( tex, numSpritesWide, numSpritesHigh ) );
		img_index = this->animationSheet.size()-1;
		PrintDebug ( "[Sprite::Load]after push_back: img_index=%d\n",img_index );
//		animationSheet[img_index].loadSheet();

// Set the current image width and height for the sprite
		width.push_back ( this->animationSheet[img_index].getSpriteWidth() );
		height.push_back ( this->animationSheet[img_index].getSpriteHeight() );

		alpha.push_back ( 1.0f );// Set a default alpha of 1.0f (fully opaque).
// ---
		col_x.push_back ( 0 );// Set a default collision top-left corner X to zero.
		col_y.push_back ( 0 );// Set a default collision top-left corner Y to zero.
		col_width.push_back ( width[img_index] );// Set a default collision bottom-right corner X to the image's width.
		col_height.push_back ( height[img_index] );// Set a default collision bottom-right corner Y to the image's height.
// ---

		angle=0;// Default angle: 0 (facing right).
		Mirror=false;// Don't mirror.
		Flip=false;// Don't flip.
		x=0;y=0;z=0;// Default coordinates.
		return img_index;// Return its position value in the img vector.
	}

	//unload stuff (clear vectors)
	int  Sprite::UnLoad () {
		m_texture=NULL;
		width.clear();
		height.clear();
		alpha.clear();
		col_x.clear();
		col_y.clear();
		col_width.clear();
		col_height.clear();
		animationSheet.clear();
		return ( 0 );
	}

	//load numbered images
	int Sprite::Loop_Load ( const char base_path[], int N ) {
		string file;
		for ( int i=0;i<=N;i++ ) {
			stringstream temp;
			file = base_path;
			if ( i<10 ) file+= "000";
			if ( ( i>=10 ) && ( i<100 ) ) file+= "00";
			if ( ( i>=100 ) && ( i<1000 ) ) file+= "0";
			temp << i;
			file+= temp.str();
			file+= ".png";
			this->Load ( file.c_str() );
		};
		return ( 0 );
	}

	int Sprite::DeleteTextures() {
		for ( unsigned int i=0;i<animationSheet.size();i++ ) {
			delete animationSheet[i].spriteTexture;
		}
		this->UnLoad();//clear vectors too.
		return ( 0 );
	}

	void Sprite::Move ( GLfloat const x2, GLfloat const y2 ) { // Move the sprite.
		x=x2; y=y2;
	}

	void Sprite::Scale ( GLfloat const factor ) {// Scale the sprite by a given factor
		for ( unsigned int x=0; x<animationSheet.size(); x++ ) { // For each sprite image...
			width[x]=width[x]*factor;// Scale width,
			height[x]=height[x]*factor;// height,
			col_width[x]=col_width[x]*factor;// collision box's width
			col_height[x]=col_height[x]*factor;// and height.
		}
	}

	void Sprite::Scale ( GLfloat const factor, int img_id ) {// Same as above, but with a specified sprite's image id.
		width[img_id]=width[img_id]*factor;
		height[img_id]=height[img_id]*factor;
		col_width[img_id]=col_width[img_id]*factor;
		col_height[img_id]=col_height[img_id]*factor;
	}

	void Sprite::ScaleXY ( GLfloat const factorX, GLfloat const factorY ) {// Scale the sprite by a given factor
		for ( unsigned int x=0; x<animationSheet.size(); x++ ) { // For each sprite image...
			width[x]=width[x]*factorX;// Scale width,
			height[x]=height[x]*factorY;// height,
			col_width[x]=col_width[x]*factorX;// collision box's width
			col_height[x]=col_height[x]*factorY;// and height.
		}
	}

	void Sprite::ScaleXY ( GLfloat const factorX, GLfloat const factorY, int img_id ) {// Same as above, but with a specified sprite's image id.
		width[img_id]=width[img_id]*factorX;
		height[img_id]=height[img_id]*factorY;
		col_width[img_id]=col_width[img_id]*factorX;
		col_height[img_id]=col_height[img_id]*factorY;
	}

	void Sprite::Advance ( GLfloat const steps ) {
		x+= ( cosf ( ( angle-90.0f ) *CONST_DEG2RAD ) ) *steps;// Calculate and set new X
		y+= ( sinf ( ( angle-90.0f ) *CONST_DEG2RAD ) ) *steps;// Calculate and set new Y
	}

	void Sprite::ResizePropW ( GLfloat const new_width ) {
		GLfloat nw,nh;
		nw = new_width;
		for ( unsigned int x=0; x<animationSheet.size(); x++ ) { // For each sprite image...
			nh = ( height[x] / 100 ) * ( 100 / width[x] * new_width );
			width[x] = nw;
			height[x]= nh;
		}
	}

	void Sprite::ResizePropW ( int img_id, GLfloat const new_width ) {
		GLfloat nw,nh;
		nw = new_width;
		nh = ( height[img_id] / 100 ) * ( 100 / width[img_id] * new_width );
		width[img_id] = nw;
		height[img_id]= nh;
	}

	bool Sprite::LoopFinished() {
		if ( !Backwards )
			return ( currentSheet == (signed int) 0 );
		else
			return ( currentSheet == (signed int) animationSheet.size()-1 );
	}

	/* To draw 3D objects (cubes) (not working yet)*/
	void Sprite::DrawCube() {

		glTranslatef ( x,y,z );// Move to the sprite's coordinate.
		glRotatef ( xrot,1.0f,0.0f,0.0f );
		glRotatef ( yrot,0.0f,1.0f,0.0f );
		glRotatef ( zrot,0.0f,0.0f,1.0f );

		GLfloat A=width[currentSheet]/2.;
		GLfloat B=height[currentSheet]/2.;
		GLfloat C=A;

		DisableTexturing();
		glDisable ( GL_BLEND );

		//glColor4f ( 1,0,0,alpha[currentSheet] );// Set the sprite's alpha

		glBegin ( GL_QUADS );

		glColor3ub ( 255, 000, 000 ); glVertex3f ( -A,  B, C );
		glColor3ub ( 000, 255, 000 ); glVertex3f ( A,  B, C );
		glColor3ub ( 000, 000, 255 ); glVertex3f ( A, -B, C );
		glColor3ub ( 255, 255, 000 ); glVertex3f ( -A, -B, C );

		glColor3ub ( 255, 000, 000 ); glVertex3f ( -A,  B, -C );
		glColor3ub ( 000, 255, 000 ); glVertex3f ( A,  B, -C );
		glColor3ub ( 000, 000, 255 ); glVertex3f ( A, -B, -C );
		glColor3ub ( 255, 255, 000 ); glVertex3f ( -A, -B, -C );

		glColor3ub ( 255, 000, 000 ); glVertex3f ( A, -B,  C );
		glColor3ub ( 000, 255, 000 ); glVertex3f ( A,  B,  C );
		glColor3ub ( 000, 000, 255 ); glVertex3f ( A,  B, -C );
		glColor3ub ( 255, 255, 000 ); glVertex3f ( A, -B, -C );

		glColor3ub ( 255, 000, 000 ); glVertex3f ( -A, -B,  C );
		glColor3ub ( 000, 255, 000 ); glVertex3f ( -A,  B,  C );
		glColor3ub ( 000, 000, 255 ); glVertex3f ( -A,  B, -C );
		glColor3ub ( 255, 255, 000 ); glVertex3f ( -A, -B, -C );

		glColor3ub ( 255, 000, 000 ); glVertex3f ( -A,  B,  C );
		glColor3ub ( 000, 255, 000 ); glVertex3f ( A,  B,  C );
		glColor3ub ( 000, 000, 255 ); glVertex3f ( A,  B, -C );
		glColor3ub ( 255, 255, 000 ); glVertex3f ( -A,  B, -C );

		glColor3ub ( 255, 000, 000 ); glVertex3f ( -A, -B,  C );
		glColor3ub ( 000, 255, 000 ); glVertex3f ( A, -B,  C );
		glColor3ub ( 000, 000, 255 ); glVertex3f ( A, -B, -C );
		glColor3ub ( 255, 255, 000 ); glVertex3f ( -A, -B, -C );

		glEnd();

		EnableTexturing();
		glEnable ( GL_BLEND );
	}

	void Sprite::Draw_loadingbar() {

		glTranslatef ( x,y,z );// Move to the sprite's coordinate.

		DisableTexturing();
//		glDisable ( GL_BLEND );

// 		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );// Set blending parameters, for PNGs
		glEnable ( GL_BLEND );// Enable blending.

		glBegin ( GL_QUADS );

		//glColor3ub ( 255, 0, 0 );
		glColor4f ( 1,0,0,alpha[currentSheet] );// Set the sprite's alpha

		glVertex3f ( -width[currentSheet]/2, -height[currentSheet]/2, 0 );
		glVertex3f ( -width[currentSheet]/2,  height[currentSheet]/2, 0 );

		glColor4f ( 0,0,1,alpha[currentSheet] );// Set the sprite's alpha
		glVertex3f ( width[currentSheet]/2,  height[currentSheet]/2, 0 );
		glVertex3f ( width[currentSheet]/2, -height[currentSheet]/2, 0 );

		glEnd();

		EnableTexturing();// Enable texturing, just in case
		glEnable ( GL_BLEND );

	}

	void Sprite::SetAcceleration ( GLfloat a_new_accel, GLfloat a_new_angle )	{
		m_accel_x = a_new_accel * ( GLfloat ) cos ( a_new_angle*M_PI/180 );
		m_accel_y = a_new_accel * ( GLfloat ) sin ( a_new_angle*M_PI/180 ) * -1;
	}

}
