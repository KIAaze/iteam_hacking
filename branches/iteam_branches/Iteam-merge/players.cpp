/*! \file players.cpp
\brief PlayerObj class

Player class.
*/

#include "globals.h"
#include "players.h"
#include "weapons.h"
#include "iteam_maths.h"
#include <iostream>

#define KEY_JUMP	SDLK_UP
#define KEY_LEFT	SDLK_LEFT
#define KEY_RIGHT	SDLK_RIGHT

namespace iteam {

	PlayerObj::PlayerObj() {
		strcpy ( Name,"Susi" );
		strcpy ( Team,"Neutral" );
		vX = 0.0f;
		vY = 0.0f;
		Health=100;
		Alive=true;
		Dying=false;
		JumpPower=125;
		Power=100;
		IsPhysical=true;
		Elasticity=0.3;
		accel_x=0;
		accel_y=0;
		obj_accel_x=0;
		obj_accel_y=0;
		LastTicks = iteam::Timer[0].GetTicks(); // used for frame rate limiting the physics code
		CanMove=false;
		CanJump=false;//by default, the player cannot jump

		Movement.walkingLeft = false;
		Movement.walkingRight = false;
		Movement.jumping = false;
	}

// 	PlayerObj::~PlayerObj() {
// 	}

	void PlayerObj::DrawMe() {
		//I use 2 ifs because if Angle=90 or Angle=270, I want to avoid moonwalking.
		//...but moonwalking could be fun... :D
		if ( 90<this->Angle && this->Angle<270 )
		{
			this->Mirror=true; // Player looks to the left
			angle=-TiltAngle;
		}
		if ( 270<this->Angle || this->Angle<90 )
		{
			this->Mirror=false; // Player looks to the right
			angle=TiltAngle;
		}
		this->DrawFrame();
		this->setNextFrame();
		Tank_base.Flip=true;

		//Tank_base.Mirror=!(this->Mirror);
		//Tank_base.Draw();
		Tank_canon.angle=-this->Angle;
		Tank_canon.Mirror=!this->Mirror;
		GLfloat CAx,CAy;
		if ( Tank_canon.Mirror ) {
			CAx=Tank_canon.width[0]/2.0*cos ( deg2rad ( -Tank_canon.angle ) );
			CAy=Tank_canon.width[0]/2.0*sin ( deg2rad ( -Tank_canon.angle ) );
		}
		else {
			CAx=Tank_canon.width[0]/2.0*cos ( deg2rad ( Tank_canon.angle+180 ) );
			CAy=Tank_canon.width[0]/2.0*sin ( deg2rad ( Tank_canon.angle+180 ) );
		}
		Tank_canon.Move ( CAx,CAy );
		//cout<<"Angle="<<Tank_canon.angle<<" CAx="<<CAx<<" CAy="<<CAy<<endl;
		//Tank_canon.Draw();
	}

	void PlayerObj::DrawName() {
		char str[256];
		sprintf ( str,"%s (%d%)",Name,Health );
		Text ( iteam::Font[2], ( this->x+ ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-18, ( this->y+ ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-48, 0,1,1,1, 0.1,0.1,0.1, str );
		Text ( iteam::Font[2], ( this->x+ ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-20, ( this->y+ ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-50, 0,1,1,1,   1,  1,  1, str );
	}

	void PlayerObj::FlipFireAngle ( int direction )	{
		//make sure both variables are the same to avoid moonwalking when continuing in the same direction after having changed direction by changing the angle ;)
		FacingRight=Mirror;

		if ( direction == SDLK_RIGHT )	{
			if ( !this->FacingRight )	{
				if ( this->Angle > 90 && this->Angle <= 180 )	{
					this->Angle -= ( this->Angle - 90 ) * 2 ;
				}

				if ( this->Angle > 180 && this->Angle < 270 )	{
					this->Angle += ( 270 - this->Angle ) * 2;
				}
				this->FacingRight = true;
			}
		}
		else {
			if ( this->FacingRight )	{
				if ( this->Angle > 270 )	{
					this->Angle -= ( this->Angle - 270 ) * 2;
				}

				if ( this->Angle < 90 )	{
					this->Angle += ( 90 - this->Angle ) * 2;
				}
				this->FacingRight = false;
			}
		}
	}

	void PlayerObj::AddAcceleration ( GLfloat new_accel, GLfloat new_angle )	{
		// apply a force for to the accelleration of the

		/*	GLfloat wrap_test;
			// this->newTicks =  iTimer.GetTicks() - this->LastTicks;
			this->acceleration = GetDelta(new_accel, this->newTicks);

			this->accel_x += this->acceleration * (GLfloat) cos(new_angle*M_PI/180);
			this->accel_y += this->acceleration * (GLfloat) sin(new_angle*M_PI/180);
		*/
	}

	/*!
	\brief Adds a player into the game and creates its slot in the Player Vector.

	\param PlayerID This is NOT the player's ID relative to the Player vector, but just a constant to define which player sprite is this one. For example, IT_PLAYER_SUSI (which is 1, as seen in players.h).
	\param x Player's X.
	\param y Player's Y.
	\param Mirror2 Which side is the player facing? you should use IT_PLAYER_FACE_LEFT or _RIGHT as seen in players.h.
	\param Scaling Player's size (in percents). Note: This DOES NOT modify its collision internal bounding box if its defined BEFORE the player's scaling here.
	*/
	void AddPlayer ( int PlayerID, GLfloat x, GLfloat y, bool Mirror2, GLfloat Scaling ) {
		Player.push_back ( PlayerObj() );

		if ( PlayerID == IT_PLAYER_SUSI ) {
			Player[Player.size()-1].iterateSheets = true;
			Player[Player.size()-1].setAnimationSpeed ( 0.0f );
			Player[Player.size()-1].animationTimer.Start();
			strcpy ( Player[Player.size()-1].Name,"Susi" );
			//Player[Player.size()-1].Load("data/chars/susi_film_1of2.png", 8, 1);
			Player[Player.size()-1].Load ( Player_Texture[0], 4, 1 );
		}

		Player[Player.size()-1].Move ( x,y );
		Player[Player.size()-1].Mirror=Mirror2;
		Player[Player.size()-1].Scale ( Scaling );
		Player[Player.size()-1].CanMove=false;
		Player[Player.size()-1].CanJump=false;
		Player[Player.size()-1].Angle=iRand ( 0,360 );
		Player[Player.size()-1].col_x[0]= ( 64/2 )-10;
		Player[Player.size()-1].col_y[0]=8;
		Player[Player.size()-1].col_width[0]=20;
		Player[Player.size()-1].col_height[0]=60-8;
	}

//==============================================================
//PHYSICS ENGINE
//==============================================================

	void PlayerObj::SetBeginPosition ( GLfloat nx, GLfloat ny )	{
		x = nx;
		y = ny;
		accel_x = 0;
		accel_y = 0;
		//angle = new_angle;
		//cout << "[WEAPONS COORDS] x = " << x << " y = " << y << " angle = " << angle << "\n";
	}

	void PlayerObj::SetVelocity ( GLfloat new_vel, GLfloat new_angle ) {
		velocity = new_vel;
		vX = velocity * ( GLfloat ) cos ( new_angle*M_PI/180 );
		vY = velocity * ( GLfloat ) sin ( new_angle*M_PI/180 ) * -1;
	}

//will eventually be used for missiles, friction, etc
	void PlayerObj::SetAcceleration ( GLfloat new_accel, GLfloat new_angle )	{
		obj_accel_x = new_accel * ( GLfloat ) cos ( new_angle*M_PI/180 );
		obj_accel_y = new_accel * ( GLfloat ) sin ( new_angle*M_PI/180 ) * -1;
	}

	void PlayerObj::CalculateVelocity ( void )	{
		//cout<<"before: Player[0].vX="<<Player[0].vX<<endl;
		//cout<<"accel_x="<<accel_x<<endl;
//cout<<"delta_time="<<delta_time<<endl;
		vX += GetDelta ( accel_x, delta_time );
		vY += GetDelta ( accel_y, delta_time );
		//cout<<"after: Player[0].vX="<<Player[0].vX<<endl;

	}

//to calculate things like friction (IT_FRICTION)
	void PlayerObj::CalculateAcceleration ( void ) {
		//cout<<"[CalculateAcceleration]: Player[0].obj_accel_x="<<Player[0].obj_accel_x<<endl;
		//cout<<"[CalculateAcceleration]: Player[0].accel_x="<<Player[0].accel_x<<endl;
		accel_x=obj_accel_x;
		accel_y=obj_accel_y+Gravity;
	}


	//MoveMe
	int PlayerObj::MoveMe() {
		int collision=0;//default return value
		GLfloat advance_x, advance_y;
		advance_x = GetDelta ( vX, delta_time );
		advance_y = GetDelta ( vY, delta_time );
		x += advance_x;
		y += advance_y;

		int i = 0;

		this->CanJump=false;//by default, the player cannot jump
		setAnimationSpeed ( 0.0f );//by default, the player doesn't walk
		//collision test
		GLfloat Nx,Ny,Tx,Ty;
		if ( CollisionPixel_2 ( this,& ( Level[0] ),0,0,Nx,Ny,Tx,Ty ) ) {
			//cout<<"Nx="<<Nx<<endl;
			//cout<<"Ny="<<Ny<<endl;
			//cout<<"Tx="<<Tx<<endl;
			//cout<<"Ty="<<Ty<<endl;
			Cam.Begin();
			DrawLine(x,y,x+100*Tx,y+100*Ty,255,255,255);
			Cam.End();
			TiltAngle=rad2deg(atan2(Ty,Tx));
			//if(!strcmp(Name,"Susi 0")) cout<<"TiltAngle="<<TiltAngle<<endl;

			collision=1;
			this->CanJump=true;//player is on the ground, therefore can jump

			x -= advance_x;
			y -= advance_y;
			//cout<<"vX="<<vX<<endl;
			//cout<<"vY="<<vY<<endl;
			N_reflect_vector ( Nx,Ny,vX,vY,vX,vY );
			//cout<<"vX="<<vX<<endl;
			//cout<<"vY="<<vY<<endl;
			if ( IsPhysical )	{
				// remove some of the bounce - commonly know as restitution coefficient I think XD
				vX = vX * Elasticity;
				vY = vY * Elasticity;

			}
			//we need to continue moving forward slowly until we have a collision.
			//It's necessary for missiles and jumping for example.
			//Personnally, I don't like it...
// 		advance_x = advance_x / fabs(advance_x);//sign of advance_x
// 		advance_y = advance_y / fabs(advance_y);//sign of advance_y
// 		while(!CollisionPixel(this,&Terrain,0,0)) { // as long as there isnt a collision
// 				y += advance_y;
// 				x += advance_x;
// 		}

			// Because we do have a collision now, we should move it back up 1 pixel
			//this->y -= 1.0f;
			/*		if(this->CanMove==true){ // Can we move?
						if (gp2d::KeyPressed(KEY_JUMP)) { // We would like to jump
							Jump.Play();
							this->vY = -JumpPower;
						}
					}*/
		}//end of collision test


		//keyboard input
		if ( this->CanMove==true ) { // Can we move?
#ifndef USE_EVENTCALLBACK
			if ( ( gp2d::KeyPressed ( KEY_LEFT ) ) || ( gp2d::KeyPressed ( KEY_RIGHT ) ) ) {
#else
			if ( Movement.walkingLeft || Movement.walkingRight ) {
#endif
				if ( this->CanJump ) setAnimationSpeed ( 24.0f );
			}
			else {
				setAnimationSpeed ( 0.0f );
			}

			i=0;
#ifndef USE_EVENTCALLBACK
			if ( gp2d::KeyPressed ( KEY_LEFT ) ) {
#else
			if ( Movement.walkingLeft ) {
#endif
				this->Mirror=true; // Player looks to the left
				this->MovementAngle = 180.00;
				this->FlipFireAngle ( SDLK_LEFT );
				vX=0;//temporary (we will need some friction ;) )
				this->x -= 2.0f;
				while ( CollisionPixel ( this,& ( Level[0] ),0,0 ) ) { // If there is a collision
					this->y -= 1.0f; // Move player 1 pixel up
					//cout<<"moving up"<<endl;
					if ( ++i >= 4 ) { // If we moved the player already 4 pixels up
						this->y += 4.0f; // Encountered wall, set character back
						this->x+=2.0f;
						break;
					}
				}
			}
			i=0;
#ifndef USE_EVENTCALLBACK
			if ( gp2d::KeyPressed ( KEY_RIGHT ) ) {
#else
			if ( Movement.walkingRight ) {
#endif
				this->Mirror=false; // Player looks to the left
				this->MovementAngle = 0;
				this->FlipFireAngle ( SDLK_RIGHT );
				vX=0;//temporary (we will need some friction ;) )
				this->x += 2.0f;
				while ( CollisionPixel ( this,& ( Level[0] ),0,0 ) ) { // If there is a collision
					this->y -= 1.0f; // Move player 1 pixel up
					//cout<<"moving up"<<endl;
					if ( ++i >= 4 ) { // If we moved the player already 4 pixels up
						this->y += 4.0f;  // Encountered wall, set character back
						this->x-=2.0f;
						break;
					}
				}
			}
		}//end of keyboard input

		if ( x<TERRAIN_XMIN ) x=TERRAIN_XMIN;
		if ( x>TERRAIN_XMAX ) x=TERRAIN_XMAX;

		return ( collision );
	}

	/*	int PlayerObj::MoveMe()	{
			int tempTicks;
			GLfloat advance_x, advance_y, step_x, step_y, distance_between;
			tempTicks = iTimer.GetTicks();
			this->newTicks = tempTicks - this->LastTicks;
			this->LastTicks =  tempTicks;
			this->CalculateVelocity();
			advance_x = GetDelta(this->vX, this->newTicks);
			advance_y = GetDelta(this->vY, this->newTicks);
			//cout << "Adv_x = " << advance_x << "\n";
			//cout << "Adv_y = " << advance_y << "\n";
			//cout << "Ticks are " << this->newTicks << "\n";


			//cout << "x1 = " << this->x << " y1 = " <<  this->y << " x2 = " <<  this->x + advance_x << " y2 = " << this->y + advance_y << "\n";
			distance_between = DistanceBetween(this->x, this->y, this->x + advance_x, this->y + advance_y);

			step_x = advance_x / distance_between;
			step_y = advance_y / distance_between;
			// cout << "Distance = " << distance_between << "\n";
			this->x += advance_x;
			this->y += advance_y;
			if (CollisionPixel(this,&Terrain,0,0)) {

					this->x -= advance_x;
					this->y -= advance_y;



			} else {
					return(0);
			}
			do {

				this->y += step_y;

				if (CollisionPixel(this,&Terrain,0,0)) {

					this->y -= step_y;



				}

				this->x += step_x;
				if (CollisionPixel(this,&Terrain,0,0)) {
					this->x -= step_x;


				}
				distance_between -= 1;
			} while(distance_between > 0);
			return(0);
		}
	*/
} // namespace iteam closed
