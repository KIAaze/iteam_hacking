/*! \file Player.cpp
\brief Player class

Player class.
*/

#include "globals.h"
#include "Player.h"
#include "physics.h"
#include "iteam_maths.h"
#include <iostream>

#define KEY_JUMP	SDLK_UP
#define KEY_LEFT	SDLK_LEFT
#define KEY_RIGHT	SDLK_RIGHT

namespace iteam {

	map <int,iteam::Player> PlayerList;

	Player::Player() : gp2d::Sprite() {
		strcpy ( Name,"Susi" );
		strcpy ( Team,"Neutral" );
		strcpy ( Vehicle,"Neutral" );
		m_FireAngle=0;
		m_FirePower=100;
		JumpPower=125;
		Health=100;
		Alive=true;
		Dying=false;
		CanMove=false;
		CanJump=false;//by default, the player cannot jump
		newTicks=0;
		FacingRight=true;
		TiltAngle=0;
		MovementAngle=0;
		HasFired=false;
		CurrentWeapon=0;
		m_TriggerTime=0;
		PowerMultiplier=1;
		Status=0;
		dest_x=0;
		dest_y=0;
		vX = 0.0f;
		vY = 0.0f;
		velocity=0;
		accel_x=0;
		accel_y=0;
		acceleration=0;
		LastTicks = iteam::GameTimer[0].GetTicks(); // used for frame rate limiting the physics code
		delta_time=0;
		IsPhysical=true;
		Elasticity=0.3;
		obj_accel_x=0;
		obj_accel_y=0;
		Movement.walkingLeft = false;
		Movement.walkingRight = false;
		Movement.jumping = false;
		m_TimeToTakeMyTurn=false;
		m_WallEncountered=false;
		m_HumanPlayer=true;
	}

	Player::Player( const char texture[], int w, int h ) : gp2d::Sprite(texture,w,h) {
		strcpy ( Name,"Susi" );
		strcpy ( Team,"Neutral" );
		strcpy ( Vehicle,"Neutral" );
		m_FireAngle=0;
		m_FirePower=100;
		JumpPower=125;
		Health=100;
		Alive=true;
		Dying=false;
		CanMove=false;
		CanJump=false;//by default, the player cannot jump
		newTicks=0;
		FacingRight=true;
		TiltAngle=0;
		MovementAngle=0;
		HasFired=false;
		CurrentWeapon=0;
		m_TriggerTime=0;
		PowerMultiplier=1;
		Status=0;
		dest_x=0;
		dest_y=0;
		vX = 0.0f;
		vY = 0.0f;
		velocity=0;
		accel_x=0;
		accel_y=0;
		acceleration=0;
		LastTicks = iteam::GameTimer[0].GetTicks(); // used for frame rate limiting the physics code
		delta_time=0;
		IsPhysical=true;
		Elasticity=0.3;
		obj_accel_x=0;
		obj_accel_y=0;
		Movement.walkingLeft = false;
		Movement.walkingRight = false;
		Movement.jumping = false;
		m_TimeToTakeMyTurn=false;
		m_WallEncountered=false;
		m_HumanPlayer=true;
	}

	Player::Player( gp2d::Texture* tex, int numSpritesWide, int numSpritesHigh ): gp2d::Sprite(tex,numSpritesWide,numSpritesHigh){
		strcpy ( Name,"Susi" );
		strcpy ( Team,"Neutral" );
		strcpy ( Vehicle,"Neutral" );
		m_FireAngle=0;
		m_FirePower=100;
		JumpPower=125;
		Health=100;
		Alive=true;
		Dying=false;
		CanMove=false;
		CanJump=false;//by default, the player cannot jump
		newTicks=0;
		FacingRight=true;
		TiltAngle=0;
		MovementAngle=0;
		HasFired=false;
		CurrentWeapon=0;
		m_TriggerTime=0;
		PowerMultiplier=1;
		Status=0;
		dest_x=0;
		dest_y=0;
		vX = 0.0f;
		vY = 0.0f;
		velocity=0;
		accel_x=0;
		accel_y=0;
		acceleration=0;
		LastTicks = iteam::GameTimer[0].GetTicks(); // used for frame rate limiting the physics code
		delta_time=0;
		IsPhysical=true;
		Elasticity=0.3;
		obj_accel_x=0;
		obj_accel_y=0;
		Movement.walkingLeft = false;
		Movement.walkingRight = false;
		Movement.jumping = false;
		m_TimeToTakeMyTurn=false;
		m_WallEncountered=false;
		m_HumanPlayer=true;
	}

	void Player::DrawMe() {
		//I use 2 ifs because if Angle=90 or Angle=270, I want to avoid moonwalking.
		//...but moonwalking could be fun... :D
		if ( 90<this->m_FireAngle && this->m_FireAngle<270 ) {
			this->Mirror=true; // Player looks to the left
			angle=-SpriteTiltAngle;
		}
		if ( 270<this->m_FireAngle || this->m_FireAngle<90 ) {
			this->Mirror=false; // Player looks to the right
			angle=SpriteTiltAngle;
		}
		this->DrawFrame();

		//animate and kill if the dying animation is finished
		if ( this->setNextFrame() ==false && Dying==true ) {
			Alive=false;
			cout<<Name<<" has been killed"<<endl;
		}

		if ( draw_tanks ) {
			Tank_base.Flip=true;
			//Tank_base.Mirror=!(this->Mirror);
			Tank_base.Draw();

			Tank_canon.angle=-this->m_FireAngle;
			Tank_canon.Mirror=!this->Mirror;
			GLfloat CAx,CAy;
			if ( Tank_canon.Mirror ) {
				CAx=Tank_canon.width[0]/2.0*cos ( deg2rad ( -Tank_canon.angle ) );
				CAy=Tank_canon.width[0]/2.0*sin ( deg2rad ( -Tank_canon.angle ) );
			} else {
				CAx=Tank_canon.width[0]/2.0*cos ( deg2rad ( Tank_canon.angle+180 ) );
				CAy=Tank_canon.width[0]/2.0*sin ( deg2rad ( Tank_canon.angle+180 ) );
			}
			Tank_canon.Move ( CAx,CAy );
			//cout<<"Angle="<<Tank_canon.angle<<" CAx="<<CAx<<" CAy="<<CAy<<endl;
			Tank_canon.Draw();
		}
	}

	void Player::DrawName() {
		char str[256];
		sprintf ( str,"%s (%d%%)",Name,Health );
		Text ( iteam::Font[2], ( this->x+ ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-18, ( this->y+ ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-48, 0,1,1,1, 0.1,0.1,0.1, str );
		Text ( iteam::Font[2], ( this->x+ ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-20, ( this->y+ ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-50, 0,1,1,1,   1,  1,  1, str );
	}

	void Player::Fire() {
		/*        m_PlayerWeapon->Fire(
		          this
		        , x
		        , y
		        , m_FireAngle
		        , m_FirePower
		        , m_TriggerTime
		        );*/
	}

	void Player::FlipFireAngle ( int direction )	{
		//make sure both variables are the same to avoid moonwalking when continuing in the same direction after having changed direction by changing the angle ;)
		FacingRight=Mirror;

		if ( direction == SDLK_RIGHT )	{
			if ( !this->FacingRight )	{
				if ( this->m_FireAngle > 90 && this->m_FireAngle <= 180 )	{
					this->m_FireAngle -= ( this->m_FireAngle - 90 ) * 2 ;
				}

				if ( this->m_FireAngle > 180 && this->m_FireAngle < 270 )	{
					this->m_FireAngle += ( 270 - this->m_FireAngle ) * 2;
				}
				this->FacingRight = true;
			}
		} else {
			if ( this->FacingRight )	{
				if ( this->m_FireAngle > 270 )	{
					this->m_FireAngle -= ( this->m_FireAngle - 270 ) * 2;
				}

				if ( this->m_FireAngle < 90 )	{
					this->m_FireAngle += ( 90 - this->m_FireAngle ) * 2;
				}
				this->FacingRight = false;
			}
		}
	}

	void Player::AddAcceleration ( GLfloat new_accel, GLfloat new_angle )	{
		// apply a force for to the accelleration of the

		/*	GLfloat wrap_test;
			// this->newTicks =  iTimer.GetTicks() - this->LastTicks;
			this->acceleration = GetDelta(new_accel, this->newTicks);

			this->accel_x += this->acceleration * (GLfloat) cos(new_angle*M_PI/180);
			this->accel_y += this->acceleration * (GLfloat) sin(new_angle*M_PI/180);
		*/
	}

//==============================================================
//PHYSICS ENGINE
//==============================================================

	void Player::SetBeginPosition ( GLfloat nx, GLfloat ny )	{
		x = nx;
		y = ny;
		accel_x = 0;
		accel_y = 0;
		//angle = new_angle;
		//cout << "[WEAPONS COORDS] x = " << x << " y = " << y << " angle = " << angle << "\n";
	}

	void Player::SetVelocity ( GLfloat new_vel, GLfloat new_angle ) {
		velocity = new_vel;
		vX = velocity * ( GLfloat ) cos ( new_angle*M_PI/180 );
		vY = velocity * ( GLfloat ) sin ( new_angle*M_PI/180 ) * -1;
	}

//will eventually be used for missiles, friction, etc
	void Player::SetAcceleration ( GLfloat new_accel, GLfloat new_angle )	{
		obj_accel_x = new_accel * ( GLfloat ) cos ( new_angle*M_PI/180 );
		obj_accel_y = new_accel * ( GLfloat ) sin ( new_angle*M_PI/180 ) * -1;
	}

	void Player::CalculateVelocity ( void )	{
		//cout<<"before: Player[0]->vX="<<Player[0]->vX<<endl;
		//cout<<"accel_x="<<accel_x<<endl;
//cout<<"delta_time="<<delta_time<<endl;
		vX += GetDelta ( accel_x, delta_time );
		vY += GetDelta ( accel_y, delta_time );
		//cout<<"after: Player[0]->vX="<<Player[0]->vX<<endl;

	}

//to calculate things like friction (IT_FRICTION)
	void Player::CalculateAcceleration ( void ) {
		//cout<<"[CalculateAcceleration]: Player[0]->obj_accel_x="<<Player[0]->obj_accel_x<<endl;
		//cout<<"[CalculateAcceleration]: Player[0]->accel_x="<<Player[0]->accel_x<<endl;
		accel_x=obj_accel_x;
		accel_y=obj_accel_y+Gravity;
	}

	void Player::WalkLeft() {
		Mirror=true; // Player looks to the left
		MovementAngle = 180.00;
		FlipFireAngle ( SDLK_LEFT );
		// vx=0;//temporary (we will need some friction ;) )
		GLfloat l_X, l_Y;
		l_X = GetX();
		l_Y = GetY();
		l_X -= 2.0f;
		SetX ( l_X );

		m_WallEncountered = false;
		int i = 0;
		while ( CollisionPixel ( this,& ( Level[0] ),0,0 ) ) { // If there is a collision
			l_Y -= 1.0f;
			SetY ( l_Y ); // Move player 1 pixel up
			//cout<<"moving up"<<endl;
			if ( ++i >= 4 ) { // If we moved the player already 4 pixels up
				l_Y += 4.0f; // Encountered wall, set character back
				SetY ( l_Y );
				l_X += 2.0f;
				SetX ( l_X );
				m_WallEncountered = true;
				break;
			}
		}
		setNextFrame();
	}

	void Player::WalkRight() {
		GLfloat l_X, l_Y;
		l_X = GetX();
		l_Y = GetY();
		Mirror=false; // Player looks to the right
		MovementAngle = 0;
		FlipFireAngle ( SDLK_RIGHT );
		// vx=0;//temporary (we will need some friction ;) )
		l_X += 2.0f;
		SetX ( l_X );

		m_WallEncountered = false;
		int i = 0;
		while ( CollisionPixel ( this,& ( Level[0] ),0,0 ) ) { // If there is a collision
			l_Y -= 1.0f; // Move player 1 pixel up
			SetY ( l_Y );
			//cout<<"moving up"<<endl;
			if ( ++i >= 4 ) { // If we moved the player already 4 pixels up
				l_Y += 4.0f; // Encountered wall, set character back
				SetY ( l_Y );
				l_X -= 2.0f;
				SetX ( l_X );
				m_WallEncountered = true;
				break;
			}
		}
		setNextFrame();
	}

	//MoveMe
	int Player::MoveMe() {
		exit ( 56 );
		int collision=0;//default return value
		GLfloat advance_x, advance_y;
		advance_x = GetDelta ( vX, delta_time );
		advance_y = GetDelta ( vY, delta_time );
		x += advance_x;
		y += advance_y;

		int i = 0;

		this->CanJump=false;//by default, the player cannot jump
		if ( !Dying ) setAnimationSpeed ( 0.0f );//by default, the player doesn't walk
		//collision test
		GLfloat Nx,Ny,Tx,Ty;
		if ( CollisionPixel_2 ( this,& ( Level[0] ),0,0,Nx,Ny,Tx,Ty ) ) {
			TiltAngle=rad2deg ( atan2 ( Ty,Tx ) );

			collision=1;
			this->CanJump=true;//player is on the ground, therefore can jump
			x -= advance_x;
			y -= advance_y;
			N_reflect_vector ( Nx,Ny,vX,vY,vX,vY );
			if ( IsPhysical )	{
				// remove some of the bounce - commonly know as restitution coefficient I think XD
				vX = vX * Elasticity;
				vY = vY * Elasticity;
			}

		}//end of collision test

		//keyboard input
		if ( this->CanMove==true ) { // Can we move?
			if ( Movement.walkingLeft || Movement.walkingRight ) {
				if ( this->CanJump ) setAnimationSpeed ( 24.0f );
			} else {
				if ( !Dying ) setAnimationSpeed ( 0.0f );
			}

			i=0;
			if ( Movement.walkingLeft ) {
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
			if ( Movement.walkingRight ) {
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

	int Player::DoBehaviour()
	{
		Health=m_integrity;
		if(m_integrity<=0) return(1);
		return(!(this->setNextFrame()));
	}

	int Player::Render(gp2d::Camera Cam)
	{
		Cam.Begin();
		this->DrawFrame();
		this->DrawName();
		Cam.End();
		return(0);
	}

	//TODO: Simplify. Always draw+increment. Erase if necessary.
	void ProccessPlayer ( void ) {
		for ( map<int,iteam::Player>::iterator ii=PlayerList.begin(); ii!=PlayerList.end(); ) {
			if ( ( *ii ).second.Health<=0 ) {
				cout<<"erasing Player "<< ( *ii ).first<<endl;
				PlayerList.erase ( ii++ );//Here we erase ii and then increment it (post-incrementation). ;)
			}
			else {
				if ( ( *ii ).second.Alive ) {
					Cam.Begin();
					( *ii ).second.Draw();
/*					( *ii ).second.DrawFrame();
					( *ii ).second.setNextFrame();*/
					Cam.End();
				}
				++ii;//Here we pre-increment for example.
			}
		}//end of loop through PlayerList
	}//end of ProccessPlayer

	int AddPlayer(SpriteMap &a_map, Texture* tex, GLfloat x, GLfloat y)
	{
		int N=GetUnusedMapNumber(a_map);
		a_map[N]=new Player();
		a_map[N]->Load ( tex, 1, 1 );
		a_map[N]->SetX ( x );
		a_map[N]->SetY ( y );
		return(0);
	}

} // namespace iteam closed
