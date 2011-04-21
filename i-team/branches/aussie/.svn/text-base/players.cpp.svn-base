#include "globals.h"
#include "players.h"

namespace iteam {

	PlayerObj::PlayerObj()
	{
		this->vY = 0.0f;
		this->vX = 0.0f;
	}

	PlayerObj::~PlayerObj()
	{
	}

	void PlayerObj::DrawMe()
	{
		this->Draw();
	}

	void PlayerObj::DrawName()
	{
		Text(FNTNames,(this->x+(VIEWPORT_WIDTH/2)-Cam.GetX())-18, (this->y+(VIEWPORT_HEIGHT/2)-Cam.GetY())-48, 0,1,1,1, 0.1,0.1,0.1, this->Name);
		Text(FNTNames,(this->x+(VIEWPORT_WIDTH/2)-Cam.GetX())-20, (this->y+(VIEWPORT_HEIGHT/2)-Cam.GetY())-50, 0,1,1,1,   1,  1,  1, this->Name);
	}

	void PlayerObj::MoveMe()
	{
		this->vY += 0.2f;
		this->y  += this->vY;
		int i = 0;

		if (CollisionPixel(this,&Terrain,0,0))
		{
			this->y -= this->vY; // touch the ground -> stop moving downwards
			this->vY = 0;
			// it could be that we are now way up in the air, becouse the velocity our dude is traveling can be rather fast
			while(!CollisionPixel(this,&Terrain,0,0)) { // as long as there isnt a collision
				this->y += 1.0f; // move the player downwards 1 pixel
			}

			// Because we do have a collision now, we should move it back up 1 pix
			this->y -= 1.0f;

			if(this->CanMove==true){ // Can we move?
				if(this->CanJump==true){ // Can we jump?
					if (gp2d::KeyPressed(SDLK_UP)) { // We would like to jump
						this->vY = -6.0f;
						this->y += -6.0f;
					}
				}
			}
		}

		if(this->CanMove==true){ // Can we move?

			i=0;
			if(gp2d::KeyPressed(SDLK_LEFT)){
				this->Mirror=true; // Player looks to the left
				this->x -= 2.0f;
				while(CollisionPixel(this,&Terrain,0,0)) { // If there is a collision
					this->y -= 1.0f; // Move player 1 pixel up
					if (++i >= 4) { // If we moved the player already 4 pixels up
						this->y += 4.0f; // Encountered wall, set character back
						this->x+=2.0f;
						break;
					}
				}
			}
			i=0;
			if(gp2d::KeyPressed(SDLK_RIGHT)){
				this->Mirror=false; // Player looks to the left
				this->x += 2.0f;
				while(CollisionPixel(this,&Terrain,0,0)) { // If there is a collision
					this->y -= 1.0f; // Move player 1 pixel up
					if (++i >= 4) { // If we moved the player already 4 pixels up
						this->y += 4.0f;  // Encountered wall, set character back
						this->x-=2.0f;
						break;
					}
				}
			}
		}
	}

	void AddPlayer(int PlayerID, GLfloat x, GLfloat y, bool Mirror2, GLfloat Scaling)
	{
		Player.push_back(PlayerObj());
		if(PlayerID == IT_PLAYER_SUSI){ Player[Player.size()-1].Name="Susi"; Player[Player.size()-1].Load("data/chars/susi.png"); }
		Player[Player.size()-1].Move(x,y);
		Player[Player.size()-1].Mirror=Mirror2;
		Player[Player.size()-1].Scale(Scaling);
		Player[Player.size()-1].CanMove=false;
		Player[Player.size()-1].CanJump=false;
		Player[Player.size()-1].Angle=iRand(0,360);
		Player[Player.size()-1].col_x[0]=(64/2)-10;
		Player[Player.size()-1].col_y[0]=8;
		Player[Player.size()-1].col_width[0]=20;
		Player[Player.size()-1].col_height[0]=60-8;
	}

}
