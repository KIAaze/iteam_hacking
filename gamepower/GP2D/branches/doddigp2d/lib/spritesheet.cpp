#include "gp2d.h"

namespace gp2d {
	
	int spriteSheet::globalSheetID = 0;
	
	spriteSheet::spriteSheet() {
		
		framesPerWidth = 1;
		framesPerHeight = 1;
		spriteTotalFrames = 1;
		spriteCurrentFrame = 0;

		spriteCurrentTextCoords.Width = 1;
		spriteCurrentTextCoords.Height = 1;
		spriteCurrentTextCoords.X = 0;
		spriteCurrentTextCoords.Y = 0;
		
		bLoaded = false;
		
		localSheetID = globalSheetID;
		globalSheetID+=1;		
	}
	spriteSheet::~spriteSheet() {		
		printf("deleting, localID = %i\n", localSheetID);		
	}

	int spriteSheet::getSpriteWidth() {
		return spriteWidth; 
	}
	int spriteSheet::getSpriteHeight() {
		return spriteHeight; 
	}
	
	bool spriteSheet::isLoaded() {
		return bLoaded;
	}

	// Loads a new sheet associated with a sprite class	
	bool spriteSheet::loadSheet(const char fileName[], int spWidth, int spHeight) {
			
		spriteTexture.Load(fileName);		
		framesPerWidth = spWidth;
		framesPerHeight = spHeight;
				
		// Work out how many frames we have
		spriteWidth = (int)(spriteTexture.width / framesPerWidth);
		spriteHeight = (int)(spriteTexture.height / framesPerHeight);
		spriteTotalFrames = (int)framesPerWidth * framesPerHeight;

		// calculate text coord system
		spriteCurrentTextCoords.Width = 1 / (GLfloat)framesPerWidth;
		spriteCurrentTextCoords.Height = 1 / (GLfloat)framesPerHeight;
		spriteCurrentTextCoords.X = (spriteCurrentFrame % framesPerWidth) / (GLfloat)framesPerWidth;
		spriteCurrentTextCoords.Y = (spriteCurrentFrame / framesPerHeight) / (GLfloat)framesPerHeight;
		
		bLoaded = true;
	}

	int spriteSheet::setFrame(int frame) {
		if (frame > spriteTotalFrames) {
			frame = 0;
		}
		
		spriteCurrentFrame = frame;
		
		// Calculate text coord stuff
		spriteCurrentTextCoords.X = (spriteCurrentFrame % framesPerWidth) / (GLfloat)framesPerWidth;
		spriteCurrentTextCoords.Y = (spriteCurrentFrame / framesPerHeight) / (GLfloat)framesPerHeight;
			
		return spriteCurrentFrame;
	}

	int spriteSheet::setNextFrame(void) {
		if (++spriteCurrentFrame >= spriteTotalFrames) {
			spriteCurrentFrame = 0;			
		}

		// Moves the window to the correct location on the texture
		spriteCurrentTextCoords.X = (spriteCurrentFrame % framesPerWidth) / (GLfloat)framesPerWidth;
		spriteCurrentTextCoords.Y = (spriteCurrentFrame / framesPerHeight) / (GLfloat)framesPerHeight;
		
		return spriteCurrentFrame;
	}
	
	struct  SpriteTextCoords *spriteSheet::getFrameCoord() {
		return &spriteCurrentTextCoords;
	}
	
};
