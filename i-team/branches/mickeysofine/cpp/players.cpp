/*! \file players.cpp
\brief PlayerObj class

Player class.
*/

#include "globals.h"
#include "players.h"
#include "Weapon.h"
#include "iteam_maths.h"
#include "physics.h"
#include <iostream>

#define KEY_JUMP	SDLK_UP
#define KEY_LEFT	SDLK_LEFT
#define KEY_RIGHT	SDLK_RIGHT

namespace iteam {

	PlayerObj::PlayerObj()
	{
        strcpy(Name,"Susi");
        strcpy(Team,"Neutral");
        SetVX(0.0f);
		SetVY(0.0f);
		Health = 100;
		JumpPower = 0;
		m_FireAngle = 45;
		m_FirePower = 3; // meters per second
		IsPhysical=true;
		Elasticity=0.3;
		accel_x=0;
		accel_y=0;
		obj_accel_x=0;
		obj_accel_y=0;
		LastTicks = iteam::Timer[0].GetTicks(); // used for frame rate limiting the physics code
		CanMove=false;
		CanJump=false;//by default, the player cannot jump
        acceleration = 0;
		Movement.walkingLeft = false;
		Movement.walkingRight = false;
		Movement.jumping = false;
		m_TriggerTime = 3.0;
		HasFired = false;
        m_HumanPlayer = true;
	}

	PlayerObj::~PlayerObj()
	{
	}

	void PlayerObj::DrawMe()
	{
		//I use 2 ifs because if Angle=90 or Angle=270, I want to avoid moonwalking.
		//...but moonwalking could be fun... :D
		if(90< m_FireAngle && m_FireAngle<270) Mirror=true; // Player looks to the left
		if(270< m_FireAngle || m_FireAngle<90) Mirror=false; // Player looks to the right


		DrawFrame();
		setNextFrame();
		Tank_base.Flip=true;
		//Tank_base.Mirror=!(this->Mirror);
		Tank_base.Draw();
		Tank_canon.angle=-m_FireAngle;
		Tank_canon.Mirror=!this->Mirror;
		GLfloat CAx,CAy;
		if(Tank_canon.Mirror)
		{
			CAx=128*cos(deg2rad(-Tank_canon.angle));
			CAy=128*sin(deg2rad(-Tank_canon.angle));
		}
		else
		{
			CAx=128*cos(deg2rad(Tank_canon.angle+180));
			CAy=128*sin(deg2rad(Tank_canon.angle+180));
		}
		Tank_canon.Move(CAx,CAy);
		//cout<<"Angle="<<Tank_canon.angle<<" CAx="<<CAx<<" CAy="<<CAy<<endl;
		Tank_canon.Draw();
	}

	void PlayerObj::DrawName()
	{
		char str[256];
		sprintf(str,"%s <%d%>",Name,Health);
		Text(iteam::Font[2],(GetX()+(VIEWPORT_WIDTH/2)-Cam.GetX())-18, (GetY()+(VIEWPORT_HEIGHT/2)-Cam.GetY())-48, 0,1,1,1, 0.1,0.1,0.1, str);
		Text(iteam::Font[2],(GetX()+(VIEWPORT_WIDTH/2)-Cam.GetX())-20, (GetY()+(VIEWPORT_HEIGHT/2)-Cam.GetY())-50, 0,1,1,1,   1,  1,  1, str);
	}

	void PlayerObj::Fire()
	{
        m_PlayerWeapon->Fire(
          this
        , x
        , y
        , m_FireAngle
        , m_FirePower
        , m_TriggerTime
        );
	}

	void PlayerObj::FlipFireAngle(int direction)	{
		//make sure both variables are the same to avoid moonwalking when continuing in the same direction after having changed direction by changing the m_FireAngle ;)
		FacingRight=Mirror;

		if(direction == SDLK_RIGHT)	{
			if(!FacingRight)	{
				if(m_FireAngle > 90 && m_FireAngle <= 180)	{
					m_FireAngle -= (m_FireAngle - 90) * 2 ;
				}
				if(m_FireAngle > 180 && m_FireAngle < 270)	{
					m_FireAngle += (270 - m_FireAngle) * 2;
				}
				FacingRight = true;
			}
		} else {
			if(FacingRight)	{
				if(m_FireAngle > 270)	{
					m_FireAngle -= (m_FireAngle - 270) * 2;
				}
				if(m_FireAngle < 90)	{
					m_FireAngle += (90 - m_FireAngle) * 2;
				}
				FacingRight = false;
			}
		}
	}

	void PlayerObj::AddAcceleration(GLfloat new_accel, GLfloat new_angle)	{
		// apply a force for to the accelleration of the

	/*	GLfloat wrap_test;
		// newTicks =  iTimer.GetTicks() - LastTicks;
		acceleration = GetDelta(new_accel, newTicks);

		accel_x += acceleration * (GLfloat) cos(new_angle*M_PI/180);
		accel_y += acceleration * (GLfloat) sin(new_angle*M_PI/180);
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
	void AddPlayer(int PlayerID, GLfloat x, GLfloat y, bool Mirror2, GLfloat Scaling)
	{
	    PlayerObj *l_tmpPlayer = new PlayerObj;

		if(PlayerID == IT_PLAYER_SUSI) {
			l_tmpPlayer->iterateSheets = true;
			l_tmpPlayer->setAnimationSpeed(0.0f);
			l_tmpPlayer->animationTimer.Start();
			strcpy(l_tmpPlayer->Name,"Susi");
			l_tmpPlayer->Load("data/chars/susi_film_1of2.png", 8, 1);
			l_tmpPlayer->Load("data/chars/susi_film_2of2.png", 4, 1);
		}
		l_tmpPlayer->Move(x,y);
		l_tmpPlayer->Mirror=Mirror2;
		l_tmpPlayer->Scale(Scaling);
		l_tmpPlayer->CanMove=false;
		l_tmpPlayer->CanJump=false;
		l_tmpPlayer->m_FireAngle=iRand(0,360);
		l_tmpPlayer->col_x[0]=(64/2)-10;
		l_tmpPlayer->col_y[0]=8;
		l_tmpPlayer->col_width[0]=20;
		l_tmpPlayer->col_height[0]=60-8;
		l_tmpPlayer->CurrentWeapon = 0;
		l_tmpPlayer->Elasticity = 0.3;
		l_tmpPlayer->SetNotTimeToTakeMyTurn();

        Player.push_back(l_tmpPlayer);
	}

//==============================================================
//PHYSICS ENGINE
//==============================================================

void PlayerObj::SetBeginPosition(GLfloat nx, GLfloat ny )	{
	SetX(nx);
	SetY(ny);
	accel_x = 0;
	accel_y = 0;
	//m_FireAngle = new_angle;
	//cout << "[WEAPONS COORDS] x = " << x << " y = " << y << " m_FireAngle = " << m_FireAngle << "\n";
}

void PlayerObj::SetVelocity(GLfloat new_vel, GLfloat new_angle)
{
	velocity = new_vel;
	SetVX(velocity * (GLfloat) cos(new_angle*M_PI/180));
	SetVY(velocity * (GLfloat) sin(new_angle*M_PI/180) * -1);
}

//will eventually be used for missiles, friction, etc
void PlayerObj::SetAcceleration(GLfloat new_accel, GLfloat new_angle)	{
	obj_accel_x = new_accel * (GLfloat) cos(new_angle*M_PI/180);
	obj_accel_y = new_accel * (GLfloat) sin(new_angle*M_PI/180) * -1;
}

void PlayerObj::CaclulateVelocity(void)	{
		//cout<<"before: Player[0].vx="<<Player[0].vx<<endl;
		//cout<<"accel_x="<<accel_x<<endl;
//cout<<"delta_time="<<delta_time<<endl;
    GLfloat l_Vx, l_Vy;
    l_Vx = GetVX();
    l_Vy = GetVY();
	l_Vx += GetDelta(accel_x, delta_time);
    l_Vy += GetDelta(accel_y, delta_time);
    SetVX(l_Vx);
    SetVY(l_Vy);
		//cout<<"after: Player[0].vx="<<Player[0].vx<<endl;

}

//to calculate things like friction (IT_FRICTION)
void PlayerObj::CaclulateAcceleration(void)
{
	//cout<<"[CaclulateAcceleration]: Player[0].obj_accel_x="<<Player[0].obj_accel_x<<endl;
	//cout<<"[CaclulateAcceleration]: Player[0].accel_x="<<Player[0].accel_x<<endl;
	accel_x=obj_accel_x;
	// accel_y=obj_accel_y+ Gravity;
}

void PlayerObj::DoBehaviours()
{

    if(Movement.walkingLeft) {

        setAnimationSpeed(24.0f);
        WalkLeft();

    } else {
        setAnimationSpeed(0.0f);
    }

    if(Movement.walkingRight) {
        setAnimationSpeed(24.0f);
        WalkRight();
    } else {
        setAnimationSpeed(0.0f);
    }



}

void PlayerObj::WalkLeft()
{
    Mirror=true; // Player looks to the left
    MovementAngle = 180.00;
    FlipFireAngle(SDLK_LEFT);
    // vx=0;//temporary (we will need some friction ;) )
    GLfloat l_X, l_Y;
    l_X = GetX();
    l_Y = GetY();
    l_X -= 2.0f;
    SetX(l_X);

    m_WallEncountered = false;
    int i = 0;
    while(CollisionPixel(this,Level[0],0,0)) { // If there is a collision
        l_Y -= 1.0f;
        SetY(l_Y); // Move player 1 pixel up
        //cout<<"moving up"<<endl;
        if (++i >= 4) { // If we moved the player already 4 pixels up
            l_Y += 4.0f; // Encountered wall, set character back
            SetY(l_Y);
            l_X += 2.0f;
            SetX(l_X);
            m_WallEncountered = true;
            break;
        }
    }
    setNextFrame();
}

void PlayerObj::WalkRight()
{
    GLfloat l_X, l_Y;
    l_X = GetX();
    l_Y = GetY();
    Mirror=false; // Player looks to the right
    MovementAngle = 0;
    FlipFireAngle(SDLK_RIGHT);
    // vx=0;//temporary (we will need some friction ;) )
    l_X += 2.0f;
    SetX(l_X);

    m_WallEncountered = false;
    int i = 0;
    while(CollisionPixel(this,Level[0],0,0)) { // If there is a collision
        l_Y -= 1.0f; // Move player 1 pixel up
        SetY(l_Y);
        //cout<<"moving up"<<endl;
        if (++i >= 4) { // If we moved the player already 4 pixels up
            l_Y += 4.0f; // Encountered wall, set character back
            SetY(l_Y);
            l_X -= 2.0f;
            SetX(l_X);
            m_WallEncountered = true;
            break;
        }
    }
    setNextFrame();
}

/*	int PlayerObj::MoveMe()	{
		int tempTicks;
		GLfloat advance_x, advance_y, step_x, step_y, distance_between;
		tempTicks = iTimer.GetTicks();
		newTicks = tempTicks - LastTicks;
		LastTicks =  tempTicks;
		CaclulateVelocity();
		advance_x = GetDelta(vx, newTicks);
		advance_y = GetDelta(vy, newTicks);
		//cout << "Adv_x = " << advance_x << "\n";
		//cout << "Adv_y = " << advance_y << "\n";
		//cout << "Ticks are " << newTicks << "\n";


		//cout << "x1 = " << GetX() << " y1 = " <<  GetY() << " x2 = " <<  GetX() + advance_x << " y2 = " << GetY() + advance_y << "\n";
		distance_between = DistanceBetween(GetX(), GetY(), GetX() + advance_x, GetY() + advance_y);

		step_x = advance_x / distance_between;
		step_y = advance_y / distance_between;
		// cout << "Distance = " << distance_between << "\n";
		GetX() += advance_x;
		GetY() += advance_y;
		if (CollisionPixel(this,&Terrain,0,0)) {
				GetX() -= advance_x;
				GetY() -= advance_y;



		} else {
				return(0);
		}
		do {
			GetY() += step_y;

			if (CollisionPixel(this,&Terrain,0,0)) {
				GetY() -= step_y;



			}
			GetX() += step_x;
			if (CollisionPixel(this,&Terrain,0,0)) {
				GetX() -= step_x;


			}
			distance_between -= 1;
		} while(distance_between > 0);
		return(0);
	}
*/
} // namespace iteam closed
