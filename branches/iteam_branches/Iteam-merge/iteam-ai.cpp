/*! \file iteam-ai.cpp
\brief AI functions

Contains functions essential for the AI.
*/

#include "iteam-ai.h"
#include "iteam_maths.h"
#include "globals.h"
#include "weapons.h"

#include "players.h"

#ifdef _WIN32
#include "../bugfixing/lib/gp2d.h"
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

namespace iteam {

	//calculates velocity+flighttime for a given angle
	//returns true if shot possible, else false
	//Can also return negative speeds when necessary. ;)
	//Also works with negative gravity :D
	bool CalculateVelocity ( double angle_deg, GLfloat &StartVelocity, GLfloat &time, double gravity, double player_x, double player_y, double target_x, double target_y ) {
		//default values that will be returned if shot impossible
		double v0=0;
		time=0;

		double angle_rad = deg2rad ( angle_deg );
		double dX = target_x - player_x;
		double dY = target_y - player_y;
		double angle_cos = cos ( angle_rad );

		double denom = angle_cos * angle_cos * ( dX * tan ( angle_rad ) + dY );//It's "+Y" because Y goes down instead of up. ;)
		if ( denom == 0 ) {
			cerr<<"impossible shot: denom==0"<<endl;
			return ( false );
		}
		double VelocitySquared = 0.5 * gravity * dX * dX / denom;
		if ( VelocitySquared < 0 ) {
			cerr<<"impossible shot: Vsquared<0"<<endl;
			return ( false );
		}
		if ( dX/angle_cos > 0 )
			StartVelocity = sqrt ( VelocitySquared );
		else
			StartVelocity = -sqrt ( VelocitySquared );      //Yes, negative speeds are possible :p
		time = dX / ( StartVelocity * angle_cos );
		return ( true );
	}

	//calculates angle+flighttime for a given velocity
	//returns true if shot possible, else false
	//There are 2 possible (angle,time) pairs for a given speed
	//works with negative speeds too
	bool CalculateAngle ( double StartVelocity, GLfloat &angle_deg1, GLfloat &time1, GLfloat &angle_deg2, GLfloat &time2, double gravity, double player_x, double player_y, double target_x, double target_y )	{
		//default values that will be returned if shot impossible
		angle_deg1=0;
		time1=0;
		angle_deg2=0;
		time2=0;

		double dX = target_x - player_x;
		double dY = target_y - player_y;

		double StartVelocitySquared = StartVelocity * StartVelocity;
		double StartVelocityQuad = StartVelocitySquared * StartVelocitySquared;
		double delta = StartVelocityQuad -gravity* dX * dX - 2 * dY * StartVelocitySquared;

		if ( delta<0 ) {
			cerr<<"impossible shot: delta<0"<<endl;
			return ( false );
		}

		double num1 = StartVelocitySquared + sqrt ( delta );
		double num2 = StartVelocitySquared - sqrt ( delta );
		double denom = gravity * dX;
		double angle_rad1 = atan2 ( num1,denom );
		double angle_rad2 = atan2 ( num2,denom );

		//special add-on for negative speeds
		if ( StartVelocity < 0 ) {
			angle_rad1 += M_PI;
			angle_rad2 += M_PI;
		}

		double V0x1=StartVelocity * cos ( angle_rad1 );
		double V0x2=StartVelocity * cos ( angle_rad2 );

		if ( V0x1 == 0 ) {
			cerr<<"impossible shot: V0x1==0"<<endl;
			return ( false );
		}
		time1 = dX / V0x1;

		if ( V0x2 == 0 ) {
			cerr<<"impossible shot: V0x2==0"<<endl;
			return ( false );
		}
		time2 = dX / V0x2;

		angle_deg1 = limit_angle ( rad2deg ( angle_rad1 ) );
		angle_deg2 = limit_angle ( rad2deg ( angle_rad2 ) );
		//cout<<"a_deg1="<<a_deg1<<endl;
		//cout<<"a_deg2="<<a_deg2<<endl;
		return ( true );
	}

	//calculates velocity+angle for a given flighttime (useful for bombs)
	//returns true if shot possible, else false
	//works with negative flighttimes too because it is equivalent to -vector(v0)
	bool CalculateVector ( double time, GLfloat &angle_deg, GLfloat &StartVelocity, double gravity, double player_x, double player_y, double target_x, double target_y ) {
		//default values that will be returned if shot impossible
		StartVelocity = 0;
		angle_deg = 0;


		double dX = target_x - player_x;
		double dY = target_y - player_y;

		double TimeSquared = time*time;
		double Ypart = dY - 0.5 * gravity * TimeSquared;

		if ( TimeSquared == 0 ) {
			cerr<<"impossible shot: TimeSquared==0"<<endl;
			return ( false );
		}
		StartVelocity = sqrt ( ( dX * dX + Ypart * Ypart ) /TimeSquared );
		double angle_rad = atan2 ( -Ypart,dX ); //-Ypart because the V0y=-V0*sin(a)
		angle_deg = limit_angle ( rad2deg ( angle_rad ) );
		return ( true );
	}

	void AIMovePlayer()	{

	}

	Uint32 GetMaxHeightOfObstacle ( SDL_Surface *surf, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2 )	{

	}

	void AIFireWeapons ( int AIPlayer )	{
		Uint32 ObstacleHieght;
		/*if(AIPlayer == 0)	{
			ObstacleHieght = GetMaxHeightOfObstacle(&Terrain, Players[0].x, Players[0].y, Players[1].x, Players[1].x);
		} else {
			ObstacleHieght = GetMaxHeightOfObstacle(&Terrain, Players[1].x, Players[1].y, Players[0].x, Players[0].x);
		}*/


	}

	unsigned int EstimateTime ( GLfloat x1, GLfloat x2 )	{
		unsigned int time;
		time= ( unsigned int ) ( fabs ( x2 - x1 ) / 10. );//absolute value ;)
		return ( time );
	}

	GLfloat GetXVelocity ( GLfloat x1, GLfloat x2, unsigned int time )	{
		return ( ( x2 - x1 ) / time );
	}

	GLfloat GetYVelocity ( GLfloat y1, GLfloat y2, GLfloat gravity,  unsigned int time )	{
		return ( - ( y1 - 0.5 * pow ( time, 2.0 ) - y2 ) / time );
	}

	void AIChooseWeapon()	{

	}

}
