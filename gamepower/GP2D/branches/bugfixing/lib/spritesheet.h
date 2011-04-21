#ifndef GP2D_SPRITESHEET_H
#define GP2D_SPRITESHEET_H

#include "gp2d.h"

namespace gp2d {

	struct SpriteTextCoords {
		GLfloat X;// Convert the width into Texture coords
		GLfloat Y;// Convert the width into Texture coords
		GLfloat Width;// Convert the width into Texture coords
		GLfloat Height;// Convert the width into Texture coords
	};

	// Class spriteSheet
	// This is used to store a manipulate all the animation or stills that
	// are related to a particular sprite.
	class spriteSheet {

			//attributes
		private:
			bool bLoaded;
			int spriteTotalFrames;
			int framesPerWidth;
			int framesPerHeight;
			int spriteCurrentFrame;
			int spriteWidth;
			int spriteHeight;
		public:
			bool Backwards;
		public:
			static int globalSheetID;
			int localSheetID;
		public:
			Texture* spriteTexture;
		public:
			struct SpriteTextCoords spriteCurrentTextCoords;

			//methods
		public:
			bool isLoaded();
			bool loadSheet ( const char fileName[], int width, int height );// Loads in the sheet and sets the width etc
			int setFrame ( int );// Sets the current frameNumber
			int setNextFrame ( void );// Sets the current frameNumber
			struct  SpriteTextCoords *getFrameCoord();
			int getSpriteWidth();
			int getSpriteHeight();
			int getspriteTotalFrames() {return ( spriteTotalFrames );};
			bool LoopFinished();

			//The big two
		public:
			spriteSheet();//default constructor
			spriteSheet ( const char fileName[], int width=1, int height=1 );//special constructor
			spriteSheet ( Texture* tex, int width=1, int height=1 );//special constructor

	};
}
#endif /* _SPRITESHEET_H */
