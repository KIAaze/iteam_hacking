/*! \file iteam-ai.cpp
\brief AI functions

Contains functions essential for the AI.
*/

#include "iteam-ai.h"
#include "iteam_maths.h"
#include "globals.h"
#include "WeaponsList.h"
#include "players.h"
#include "physics.h"
#include "library_h/gp2d.h"


#ifdef _WIN32
#include "../../gamepower/GP2D/trunk/lib/gp2d.h"
#else
#include "library_h/gp2d.h"
#endif


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

// #define LOG( str ) if (debugOn) fprintf( stderr, str );
// #define DEBUGCODE if (debugOn)
// #define DOUT(x) if (debugOn) fprintf(stderr, "%s = %d\n", #x, x);

using std::cout;
using std::cerr;
using std::endl;

/*
    This AI player is concidered ready for use when it can:

    Functionality checklist

    1) Pick a target                        (X)
    2) compensate for obstacles             (X)
    3) select a weapon                      ( )
    4) configure variables for weapon       ( )
    5) get in correct position for firing   ( )
    6) fire                                 (X)


*/

namespace iteam {
	// ======================================================================================
	// ======================================================================================
	//
	// CalculateVelocity
	//
	// calculates velocity+flighttime for a given angle
	// returns true if shot possible, else false
	// Can also return negative speeds when necessary. ;)
	// Also works with negative gravity :D
	// ======================================================================================
    AIPlayerObj::AIPlayerObj()
    {
        int l_Seconds = 3;

        m_TargetAquired = false;
        m_WeaponChosen = false;
        m_ThinkingTime = l_Seconds * 1000;
        m_MaxHeightCalculated = false;
        m_InPosition = false;
        m_ObstacleHeight = 0;
        m_DistanceToEnemy = 0;
        m_HumanPlayer = false;
    }

	bool AIPlayerObj::CalculateVelocity(
		double angle_deg
	, 	GLfloat &StartVelocity
	, 	GLfloat &time
	, 	double gravity
	, 	double player_x
	, 	double player_y
	, 	double target_x
	, 	double target_y
	)
	// ======================================================================================
	{
		//default values that will be returned if shot impossible
		StartVelocity=0;
		time=0;

		double angle_rad = deg2rad(angle_deg);
		double dX = target_x - player_x;
		double dY = target_y - player_y;
		double angle_cos = cos(angle_rad);

		double denom = angle_cos * angle_cos * (dX * tan(angle_rad) + dY);//It's "+Y" because Y goes down instead of up. ;)
		if(denom == 0)
		{
			cerr<<"impossible shot: denom==0"<<endl;
			return(false);
		}
		double VelocitySquared = 0.5 * gravity * dX * dX / denom;
		if(VelocitySquared < 0)
		{
			cerr<<"impossible shot: Vsquared<0"<<endl;
			return(false);
		}
		if(dX/angle_cos > 0)
			StartVelocity = sqrt(VelocitySquared);
		else
			StartVelocity = -sqrt(VelocitySquared);         //Yes, negative speeds are possible :p
		time = dX / (StartVelocity * angle_cos);
		return( true );
	}

	// ======================================================================================
	// ======================================================================================
	//
	// CalculateAngle
	//
	// calculates angle+flighttime for a given velocity
	// returns true if shot possible, else false
	// There are 2 possible (angle,time) pairs for a given speed
	// works with negative speeds too
	// ======================================================================================
	// ======================================================================================
	bool AIPlayerObj::CalculateAngle(
	  double StartVelocity
	, GLfloat &angle_deg1
	, GLfloat &time1
	, GLfloat &angle_deg2
	, GLfloat &time2
	, double gravity
	, double player_x
	, double player_y
	, double target_x
	, double target_y
	)
	// ======================================================================================
	{
		//default values that will be returned if shot impossible
		angle_deg1=0;
		time1=0;
		angle_deg2=0;
		time2=0;

		double dX = target_x - player_x;
		double dY = target_y - player_y;

		double StartVelocitySquared = StartVelocity * StartVelocity;
		double StartVelocityQuad = StartVelocitySquared * StartVelocitySquared;
		double delta = StartVelocityQuad - gravity * dX * dX - 2 * dY * StartVelocitySquared;

		if(delta<0)
		{
			cerr<<"impossible shot: delta<0"<<endl;
			return(false);
		}

		double num1 = StartVelocitySquared + sqrt(delta);
		double num2 = StartVelocitySquared - sqrt(delta);
		double denom = gravity * dX;
		double angle_rad1 = atan2(num1,denom);
		double angle_rad2 = atan2(num2,denom);

		//special add-on for negative speeds
		if(StartVelocity < 0)
		{
			angle_rad1 += M_PI;
			angle_rad2 += M_PI;
		}

		double V0x1=StartVelocity * cos(angle_rad1);
		double V0x2=StartVelocity * cos(angle_rad2);

		if(V0x1 == 0)
		{
			cerr<<"impossible shot: V0x1==0"<<endl;
			return(false);
		}
		time1 = dX / V0x1;

		if(V0x2 == 0)
		{
			cerr<<"impossible shot: V0x2==0"<<endl;
			return(false);
		}
		time2 = dX / V0x2;

		angle_deg1 = limit_angle( rad2deg(angle_rad1) );
		angle_deg2 = limit_angle( rad2deg(angle_rad2) );
		//cout<<"a_deg1="<<a_deg1<<endl;
		//cout<<"a_deg2="<<a_deg2<<endl;
		return(true);
	}

	// ======================================================================================
	// ======================================================================================
	//
	// CalculateVector
	//
	// calculates velocity+angle for a given flighttime (useful for bombs)
	// returns true if shot possible, else false
	// works with negative flighttimes too because it is equivalent to -vector(v0)
	// ======================================================================================
	bool AIPlayerObj::CalculateVector(
	  double time
	, GLfloat &angle_deg
	, GLfloat &StartVelocity
	, double gravity
	, double player_x
	, double player_y
	, double target_x
	, double target_y
	)
	// ======================================================================================
	{
		//default values that will be returned if shot impossible
		StartVelocity = 0;
		angle_deg = 0;


		double dX = target_x - player_x;
		double dY = target_y - player_y;

		double TimeSquared = time*time;
		double Ypart = dY - 0.5 * gravity * TimeSquared;

		if(TimeSquared == 0)
		{
			cerr<<"impossible shot: TimeSquared==0"<<endl;
			return(false);
		}
		StartVelocity = sqrt((dX * dX + Ypart * Ypart)/TimeSquared);
		double angle_rad = atan2( -Ypart, dX); //-Ypart because the V0y=-V0*sin(a)
		angle_deg = limit_angle( rad2deg(angle_rad) );
		return(true);
	}
	// ======================================================================================
	// ======================================================================================
	//
	// GetMaxHeightOfObstacle
	//
	// ======================================================================================
	GLfloat AIPlayerObj::GetMaxHeightOfObstacle()
	// ======================================================================================
	{

        SDL_Surface *l_Surf = AccessLevelData();
		int l_Width, l_Height;
		Uint8  pr, pg, pb, pa2;
		GLfloat l_MaxHeight = 0;

		if(GetX() < m_EnemyPlayer->GetX())	{
			l_Width = (int) m_EnemyPlayer->GetX() -  GetX();
		} else {
			l_Width = (int) GetX() -  m_EnemyPlayer->GetX();
		}

		l_Height = l_Surf->h;
		// search for the highest pixel between the two points x1 & x2
		for(int i=0; i < l_Height; i++)	{
			for(int j=0; j < l_Width; j++)	{
				SDL_GetRGBA(
                  GetPixel(l_Surf, GetX() + j, i)
                , l_Surf->format
                , &pr
                , &pg
                , &pb
                , &pa2
                );	// Get the pixel's alpha from the second image.
				if( pa2  >  0 )	{
					l_MaxHeight = (GLfloat) i;
				}
			}
		}
		return l_MaxHeight;
	}

	unsigned int EstimateTime(GLfloat x1, GLfloat x2)	{
		unsigned int time;
		time=(unsigned int)(fabs(x2 - x1) / 10.);//absolute value ;)
		return (time);
	}

	// ===================================== AI logic ====================================================================

	int AIPlayerObj::TakeTurn()	{
        // is the target aquired
		if(m_TargetAquired)    {
		    // has the maximum obstancle height been found?
            if(m_MaxHeightCalculated)   {
                // Has a suitable weapon been chosen?
                if(m_WeaponChosen)  {
                    // Is the player in position to use the weapon?
                    if(m_InPosition)   {
                        Fire();
                    } else {
                        EstablistBestPosition();
                        MovePlayer();
                    }
                } else {
                    m_WeaponChosen = ChooseWeapon();

                }
            } else {
                m_ObstacleHeight = GetMaxHeightOfObstacle();
                m_MaxHeightCalculated = true;
            }
        } else {
            m_TargetAquired = FindNearestEnemy();
        }


		// function never actually gets here, it exits throught the switch(case)
		return IT_AI_OK;
	}

	bool AIPlayerObj::FindNearestEnemy()	{
		/*

		Ideally this should make a list of all enemies in order of how near they are
		that way if one show if definatley not possible the AI could pick a new enemy to
		attack.

		*/
		bool ReturnVal = false;
		GLfloat l_Nearest = 50000; // any number thats sufficiantly large with do

        for(int i = 0; i < m_PlayerList->size(); i++)   {
            PlayerObj* l_Player = (*m_PlayerList)[i];
            if(l_Player != this) {
                m_DistanceToEnemy = DistanceToPlayer(l_Player);
                if(m_DistanceToEnemy < l_Nearest)    {
                    l_Nearest = m_DistanceToEnemy;
                    m_EnemyPlayer = l_Player;
                    ReturnVal = true;
                }
            }
		}

		return ReturnVal;
	}

    void AIPlayerObj::EstablistBestPosition()
    {

    }

	void AIPlayerObj::MovePlayer()	{
		// basically move the player left or right until they reach the destination
		// NOTE: this does not account for obstacles YET
        Movement.walkingLeft = false;
		Movement.walkingRight = false;

		if(GetX() > m_DestinationX)	{	// move left towards goal
			Movement.walkingLeft = true;
			Movement.walkingRight = false;

		}
		if(GetX() < m_DestinationX)	{	// move right towards goal
			Movement.walkingLeft = false;
			Movement.walkingRight = true;
		}
		if(m_WallEncountered)   {
		    // jump over the wall if possible
            SetVY( -JumpPower );
		}

	}

	bool AIPlayerObj::ChooseWeapon()
	{
		/*
		This function should also be able to tell if any Weapon is able to hit
		the target as well as selecting a Weapon based on availablility and
		ease of use or successfulness - that being said dont expect it to do that
		right from the start lol!
		*/
		bool ReturnVal = true;

		// have three tries at targeting the enemy

		m_PlayerWeapon = m_WeaponsList->AccessWeapon(0);

        if(m_PlayerWeapon->IsThrowable())   {
            SetupThrowingValues();
        }


		return ReturnVal;
	}

    void AIPlayerObj::DoBehaviours()
    {

        if(TimeToTakeMyTurn())  {
            TakeTurn();
        } else {
            PlayerObj::DoBehaviours();
        }
    }

    GLfloat AIPlayerObj::DistanceToPlayer(PlayerObj* a_Player)
    {
        GLfloat ReturnVal = DistanceBetween(
                                  GetX()
                                , GetY()
                                , a_Player->GetX()
                                , a_Player->GetY()
                                );

        return ReturnVal;
    }

    GLfloat AIPlayerObj::CalculateFirePowerX()
    {
        GLfloat l_Wind = m_PhysicsSystem->GetWindInPixels();
        return -(GetX() - 0.5 * l_Wind * pow(m_WeaponETA, 2) - m_EnemyPlayer->GetX()) / m_WeaponETA;
    }

    GLfloat AIPlayerObj::CalculateFirePowerY()
    {
        GLfloat l_Gravity = m_PhysicsSystem->GetGravityInPixels();
        return -(GetY() - 0.5 * l_Gravity * pow(m_WeaponETA, 2) - m_EnemyPlayer->GetY()) / m_WeaponETA;
    }

    void AIPlayerObj::CalculateFireTime()
    {
        m_WeaponETA = m_ObstacleHeight / m_PhysicsSystem->GetGravityInPixels() * 2;

    }

    void AIPlayerObj::SetupThrowingValues()
    {
        CalculateFireTime();
        GLfloat l_FirePowerX = CalculateFirePowerX();
        GLfloat l_FirePowerY = CalculateFirePowerY();

        m_FirePower = sqrt((l_FirePowerX * l_FirePowerX) + (l_FirePowerY * l_FirePowerY));
        m_FireAngle = rad2deg( atan2( l_FirePowerY, l_FirePowerX) );
    }

    void AddAIPlayer(int PlayerID, GLfloat x, GLfloat y, bool Mirror2, GLfloat Scaling)
	{
	    AIPlayerObj *l_tmpPlayer = new AIPlayerObj;

		if(PlayerID == IT_PLAYER_SUSI) {
			l_tmpPlayer->iterateSheets = true;
			l_tmpPlayer->setAnimationSpeed(0.0f);
			l_tmpPlayer->animationTimer.Start();
			strcpy(l_tmpPlayer->Name,"AI Player");
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
        l_tmpPlayer->UsePlayerList(&Player);
        l_tmpPlayer->UsePhysicsSystem(iteamPhysics);
        l_tmpPlayer->UseWeaponsList(iteamWeapons);
        l_tmpPlayer->SetLevel(Level[0]);
        l_tmpPlayer->SetNotTimeToTakeMyTurn();
        Player.push_back(l_tmpPlayer);
	}
}
