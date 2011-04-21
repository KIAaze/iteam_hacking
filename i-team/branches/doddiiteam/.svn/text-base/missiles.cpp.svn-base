#include "missiles.h"

using namespace gp2d;

namespace iteam {

	int gameMissiles::numOfMissiles = 0;
	
	gameMissiles::gameMissiles() {
	}
			
	gameMissiles::~gameMissiles() {
	}
					
	// This function is used to assign all sprites, backgrounds etc
	// into the relevant map arrays used in a scene class
	void gameMissiles::CreateMissile(GLfloat xpos, GLfloat ypos) {
		missiles.push_back(new gp2d::Sprite());
		missiles[missiles.size()-1]->Load("data/objects/bomb_small.png");
		missiles[missiles.size()-1]->Move(xpos,ypos);
		
		missiles[missiles.size()-1]->vx = 300.0f;
		missiles[missiles.size()-1]->vy = -100.0f;		
		
		numOfMissiles++;
	}
			
	bool gameMissiles::DeleteMissile(int index) {
		
		vector<gp2d::Sprite*>::iterator iter = missiles.begin();
		delete missiles[index];		// Recover any memory
		missiles.erase(missiles.begin() + index);			// Remove from the list
		
		numOfMissiles--;
	}
			
	void gameMissiles::UpdateObjects(gp2d::Sprite *blocker) {
		
		GLfloat explodeX, explodeY;
		GLfloat tempX, tempY;
		GLfloat xMovement, yMovement;
		SDL_Surface *surface2;
		
		for (int idx=0; idx<missiles.size(); idx++) {
			
			// If any x movement needed this frame - this is what it will be		
			xMovement += gp2d::getMovementFactor(missiles[idx]->vx, myGameTimer.getTicks());	
			
			// Add the effect of gravity onto the object
			missiles[idx]->vy += gp2d::getMovementFactor(GRAVITY, myGameTimer.getTicks());				
			// Now update the new position based on velocity
			yMovement = gp2d::getMovementFactor(missiles[idx]->vy, myGameTimer.getTicks());			
			
			missiles[idx]->x += xMovement;
			missiles[idx]->y += yMovement;			
			// Add the free fall acceleration to the velocity based on loop time GRAVITY!!!
			//this->vY += gp2d::getMovementFactor(GRAVITY, myGameTimer.getTicks());		
	
			if (CollisionPixel(missiles[idx],blocker,0,0))
			{
				// made a collision -> stop moving downwards
				// reverse the last movement and find at what pixel 
				// the collision happened.
				missiles[idx]->y -= 1;
		
				while(!CollisionPixel(missiles[idx],blocker,0,0)) { // as long as there isnt a collision
					missiles[idx]->y += 1.0f; // move the player downwards 1 pixel
				}
	
				surface2 = blocker->animationSheet[0]->spriteTexture.imgF;
				
				// Find position relative to the image we want to change
				tempX = (blocker->width[0]/2)-(VIEWPORT_WIDTH/2) + missiles[idx]->x;
				tempY = missiles[idx]->y -  (VIEWPORT_HEIGHT - blocker->height[0]);
				
				// Add negative offset for blast radius
				tempX -= missiles[idx]->width[0];
				tempY -= missiles[idx]->height[0];
				
				// Make the explosion surrounding the bombs.
				for (explodeX=tempX; explodeX <=(tempX+(missiles[idx]->width[0]*2)); explodeX++) {
					for (explodeY=tempY; explodeY <=(tempY+(missiles[idx]->height[0]*2)); explodeY++) {						
						gp2d::SetPixelAlpha(surface2, (Uint32)explodeX, (Uint32)explodeY);
					}
				}			
				blocker->animationSheet[0]->spriteTexture.Modify(surface2);
				DeleteMissile(idx);
				
			}					
		}				
	}				
			
	void gameMissiles::DrawObjects(void) {
		
		for (int idx=0; idx<missiles.size(); idx++) {			
			missiles[idx]->Draw();	
		}
	}
}
