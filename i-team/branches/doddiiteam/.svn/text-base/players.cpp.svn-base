#include "globals.h"
#include "players.h"

namespace iteam {

	#define JUMP_VEL			200.0f
	#define START_JUMP		-30.0f
	#define MOVE_VEL			200.0f
	
	PlayerObj::PlayerObj()
	{
		this->vY = GRAVITY;
		this->vX = 0.0f;							// Only change X velocity when a key is pressed
		
		this->CanJump = false;
		this->CanMove = false;
	}

	PlayerObj::~PlayerObj()
	{
	}

	void PlayerObj::DrawMe()
	{
		this->DrawFrame();
		this->setNextFrame();	
	}
	
	void PlayerObj::MoveMe(gp2d::Sprite *blocker)
	{
		int i = 0;
		GLfloat xMovement;
		GLfloat yMovement;		
		
		// If any x movement needed this frame - this is what it will be		
		xMovement = gp2d::getMovementFactor(MOVE_VEL, myGameTimer.getTicks());	
		
		if (this->CanJump == false)		// Falling / Already Jumping!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
			// Add the free fall acceleration to the velocity based on loop time GRAVITY!!!
			this->vY += gp2d::getMovementFactor(GRAVITY, myGameTimer.getTicks());		
			
			// Calculated the distance to move since last time round the loop
			yMovement = gp2d::getMovementFactor(this->vY, myGameTimer.getTicks());					
			this->y += yMovement;				// Comment out this line if you dont want gravity to take effect
			//this->y += gp2d::getMovementFactor(100.0f, myGameTimer.getTicks()); //Use this line for no gravity
			
			// Test if at any point within the required distance to move if
			// there is a collision with an object. Most of the time this will be true
			if (CollisionPixel(this,blocker,0,0))
			{
				this->CanJump = true;
				// made a collision -> stop moving downwards
				// reverse the last movement and find at what pixel 
				// the collision happened.
				this->y -= this->vY;
				this->vY = 0;
		
				while(!CollisionPixel(this,blocker,0,0)) { // as long as there isnt a collision
					this->y += 1.0f; // move the player downwards 1 pixel
				}
		
				// Because we do have a collision now, we should move it back up 1 pix
				this->y -= 1.0f;
			}
		}
		else
		{
			if (gp2d::KeyPressed(SDLK_UP)) { 	// We would like to jump
				this->CanJump = false;				
				this->vY = -JUMP_VEL;
				this->y += START_JUMP;
			}
		}
		
		if(this->CanMove==true){ // Can we move?

			if( (gp2d::KeyPressed(SDLK_LEFT)) || (gp2d::KeyPressed(SDLK_RIGHT))) {
				setAnimationSpeed(24.0f);
			}
			else {
				setAnimationSpeed(0.0f);				
			}

			i=0;
			if(gp2d::KeyPressed(SDLK_LEFT)){
				this->CanJump = false;
				this->Mirror=true; // Player looks to the left
				this->x -= xMovement;
				while(CollisionPixel(this,blocker,0,0)) { // If there is a collision
					this->y -= 1.0f; // Move player 1 pixel up
					if (++i >= 4) { // If we moved the player already 4 pixels up
						this->y += 4.0f; // Encountered wall, set character back
						this->x+=xMovement;
						break;
					}
				}
			}
			i=0;
			if(gp2d::KeyPressed(SDLK_RIGHT)){
				this->CanJump = false;				
				this->Mirror=false; // Player looks to the left
				this->x += xMovement;
				while(CollisionPixel(this,blocker,0,0)) { // If there is a collision
					this->y -= 1.0f; // Move player 1 pixel up
					if (++i >= 4) { // If we moved the player already 4 pixels up
						this->y += 4.0f;  // Encountered wall, set character back
						this->x-=xMovement;
						break;
					}
				}
			}
		}
	}
}
