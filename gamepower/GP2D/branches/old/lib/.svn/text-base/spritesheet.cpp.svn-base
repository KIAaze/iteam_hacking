#include "gp2d.h"

namespace gp2d {

	int spriteSheet::globalSheetID = 0;

	//The big two
	//default constructor
	spriteSheet::spriteSheet() {
		PrintDebug ( "spriteSheet: default constructor called" );

		framesPerWidth = 1;
		framesPerHeight = 1;
		spriteTotalFrames = 1;
		spriteCurrentFrame = 0;
		Backwards=false;

		spriteCurrentTextCoords.Width = 1;
		spriteCurrentTextCoords.Height = 1;
		spriteCurrentTextCoords.X = 0;
		spriteCurrentTextCoords.Y = 0;

		bLoaded = false;

		localSheetID = globalSheetID;
		globalSheetID+=1;
		spriteTexture=new Texture();
		PrintDebug ( "SPRITE: Adding SpriteSheet ID = %i", localSheetID );
		PrintDebug ( "SPRITE: globalSheetID= %i", globalSheetID );
	}
	//special constructor
	spriteSheet::spriteSheet ( const char fileName[], int width, int height ) {
		PrintDebug ( "spriteSheet: special constructor called" );

		framesPerWidth = 1;
		framesPerHeight = 1;
		spriteTotalFrames = 1;
		spriteCurrentFrame = 0;
		Backwards=false;

		spriteCurrentTextCoords.Width = 1;
		spriteCurrentTextCoords.Height = 1;
		spriteCurrentTextCoords.X = 0;
		spriteCurrentTextCoords.Y = 0;

		bLoaded = false;

		localSheetID = globalSheetID;
		globalSheetID+=1;
		spriteTexture=new Texture();
		PrintDebug ( "spriteSheet: Adding SpriteSheet ID = %i", localSheetID );
		PrintDebug ( "spriteSheet: globalSheetID= %i", globalSheetID );

		this->loadSheet ( fileName, width, height );
	}

	//special constructor
	spriteSheet::spriteSheet ( Texture* tex, int width, int height ) {
		PrintDebug ( "[spriteSheet::spriteSheet ( Texture* tex, int width, int height )] called" );

		if ( tex==NULL ) {printf ( "[spriteSheet::spriteSheet]FATAL ERROR: tex is NULL.\n" );exit ( 47 );}
		if ( !glIsTexture ( tex->id ) ) {printf ( "[spriteSheet::spriteSheet]FATAL ERROR: tex is not a texture.\n" );exit ( 47 );}

		spriteTexture = tex;

		framesPerWidth = 1;
		framesPerHeight = 1;
		spriteTotalFrames = 1;
		spriteCurrentFrame = 0;
		Backwards=false;

		spriteCurrentTextCoords.Width = 1;
		spriteCurrentTextCoords.Height = 1;
		spriteCurrentTextCoords.X = 0;
		spriteCurrentTextCoords.Y = 0;

		bLoaded = false;

		localSheetID = globalSheetID;
		globalSheetID+=1;
		PrintDebug ( "spriteSheet: Adding SpriteSheet ID = %i", localSheetID );
		PrintDebug ( "spriteSheet: globalSheetID= %i", globalSheetID );

//		this->loadSheet ( fileName, width, height );

//		spriteTexture->Load ( fileName );
		framesPerWidth = width;
		framesPerHeight = height;

		// Work out how many frames we have
		spriteWidth = ( int ) ( spriteTexture->OriginalWidth / framesPerWidth );
		spriteHeight = ( int ) ( spriteTexture->OriginalHeight / framesPerHeight );
		spriteTotalFrames = ( int ) framesPerWidth * framesPerHeight;

		// calculate text coord system
		spriteCurrentTextCoords.Width = spriteWidth / ( GLfloat ) spriteTexture->width;
		spriteCurrentTextCoords.Height = spriteHeight / ( GLfloat ) spriteTexture->height;
		spriteCurrentTextCoords.X= ( spriteCurrentFrame%framesPerWidth ) *spriteCurrentTextCoords.Width;
		spriteCurrentTextCoords.Y= ( spriteCurrentFrame/framesPerHeight ) *spriteCurrentTextCoords.Height;

		bLoaded = true;
	}

	int spriteSheet::getSpriteWidth() {
		return spriteWidth;
	}
	int spriteSheet::getSpriteHeight() {
		return spriteHeight;
	}

	bool spriteSheet::LoopFinished() {
		if ( !Backwards )
			return ( spriteCurrentFrame == 0 );
		else
			return ( spriteCurrentFrame == spriteTotalFrames-1 );
	}

	bool spriteSheet::isLoaded() {
		return bLoaded;
	}

	// Loads a new sheet associated with a sprite class
	bool spriteSheet::loadSheet ( const char fileName[], int spWidth, int spHeight ) {
		PrintDebug ( "[spriteSheet::loadSheet] called" );

		spriteTexture->Load ( fileName );
		framesPerWidth = spWidth;
		framesPerHeight = spHeight;

		// Work out how many frames we have
		spriteWidth = ( int ) ( spriteTexture->OriginalWidth / framesPerWidth );
		spriteHeight = ( int ) ( spriteTexture->OriginalHeight / framesPerHeight );
		spriteTotalFrames = ( int ) framesPerWidth * framesPerHeight;

		// calculate text coord system
		spriteCurrentTextCoords.Width = spriteWidth / ( GLfloat ) spriteTexture->width;
		spriteCurrentTextCoords.Height = spriteHeight / ( GLfloat ) spriteTexture->height;
		spriteCurrentTextCoords.X= ( spriteCurrentFrame%framesPerWidth ) *spriteCurrentTextCoords.Width;
		spriteCurrentTextCoords.Y= ( spriteCurrentFrame/framesPerHeight ) *spriteCurrentTextCoords.Height;

		bLoaded = true;
		return true;
	}

	int spriteSheet::setFrame ( int frame ) {
		if ( frame > spriteTotalFrames ) {
			frame = 0;
		}

		spriteCurrentFrame = frame;

		// Moves the window to the correct location on the texture
		spriteCurrentTextCoords.X= ( spriteCurrentFrame%framesPerWidth ) *spriteCurrentTextCoords.Width;
		spriteCurrentTextCoords.Y= ( spriteCurrentFrame/framesPerHeight ) *spriteCurrentTextCoords.Height;

		return spriteCurrentFrame;
	}

	int spriteSheet::setNextFrame ( void ) {
		if ( !Backwards ) {
			if ( ++spriteCurrentFrame >= spriteTotalFrames ) {
				spriteCurrentFrame = 0;
			}
		} else {
			if ( --spriteCurrentFrame <= 0 ) {
				spriteCurrentFrame = spriteTotalFrames-1;
			}
		}
		// Moves the window to the correct location on the texture
		spriteCurrentTextCoords.X= ( spriteCurrentFrame%framesPerWidth ) *spriteCurrentTextCoords.Width;
		spriteCurrentTextCoords.Y= ( spriteCurrentFrame/framesPerHeight ) *spriteCurrentTextCoords.Height;

		return spriteCurrentFrame;
	}

	struct SpriteTextCoords *spriteSheet::getFrameCoord() {
		return &spriteCurrentTextCoords;
	}

};
