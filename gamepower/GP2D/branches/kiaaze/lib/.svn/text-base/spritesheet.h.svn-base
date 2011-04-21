#ifndef GP2D_SPRITESHEET_H
#define GP2D_SPRITESHEET_H

#include "gp2d.h"

namespace gp2d {
	
	struct SpriteTextCoords {
		GLfloat X;									// Convert the width into Texture coords
		GLfloat Y;									// Convert the width into Texture coords					
		GLfloat Width;							// Convert the width into Texture coords
		GLfloat Height;						// Convert the width into Texture coords				
	};

	// Class spriteSheet 
	// This is used to store a manipulate all the animatin or stills that
	// are related to a particular sprite.	
	class spriteSheet {
		public:
			spriteSheet();
			~spriteSheet();
			
			static int globalSheetID;
			int localSheetID;
		
			bool isLoaded();
			bool loadSheet(const char fileName[], int width, int height);				// Loads in the sheet and sets the width etc
		
			int setFrame(int);			// Sets the current frameNumber
			int setNextFrame(void);			// Sets the current frameNumber		
			struct  SpriteTextCoords *getFrameCoord();
				
			int getSpriteWidth();
			int getSpriteHeight();
			
			Texture	spriteTexture;
			
		private:
			bool bLoaded;
			int spriteTotalFrames;
			int framesPerWidth;
			int framesPerHeight;
		
			int spriteCurrentFrame;
			int spriteWidth;
			int spriteHeight;
		
		public:
			struct SpriteTextCoords spriteCurrentTextCoords;
	};
}
#endif /* _SPRITESHEET_H */
