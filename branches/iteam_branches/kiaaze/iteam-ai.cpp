/*! \file iteam-ai.cpp
\brief AI functions

Contains functions essential for the AI.
*/

#include "iteam-ai.h"
#include "iteam_maths.h"
#include "globals.h"
#include "weapons.h"
#include "library_h/gp2d.h"
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
	bool calc_velocity(double a_deg, GLfloat &v0, GLfloat &time, double g, double x0, double y0, double x, double y)
	{
		//default values that will be returned if shot impossible
		v0=0;
		time=0;

		double a_rad=deg2rad(a_deg);
		double X=x-x0;
		double Y=y-y0;
		double c_a = cos(a_rad);

		double denom = c_a*c_a * (X * tan(a_rad) + Y);//It's "+Y" because Y goes down instead of up. ;)
		if(denom==0)
		{
			cerr<<"impossible shot: denom==0"<<endl;
			return(false);
		}
		double Vsquared= 0.5*g*X*X/denom;
		if(Vsquared<0)
		{
			cerr<<"impossible shot: Vsquared<0"<<endl;
			return(false);
		}
		if(X/c_a>0)
			v0=sqrt(Vsquared);
		else
			v0=-sqrt(Vsquared);//Yes, negative speeds are possible :p
		time=X/(v0*c_a);
		return( true );
	}
	
	//calculates angle+flighttime for a given velocity
	//returns true if shot possible, else false
	//There are 2 possible (angle,time) pairs for a given speed
	//works with negative speeds too
	bool calc_angle(double v0, GLfloat &a_deg1, GLfloat &time1, GLfloat &a_deg2, GLfloat &time2, double g, double x0, double y0, double x, double y)
	{
		//default values that will be returned if shot impossible
		a_deg1=0;
		time1=0;
		a_deg2=0;
		time2=0;

		double X=x-x0;
		double Y=y-y0;

		double V0squared=v0*v0;
		double V0quad=V0squared*V0squared;
		double delta=V0quad-g*(g*X*X-2*Y*V0squared);

		if(delta<0)
		{
			cerr<<"impossible shot: delta<0"<<endl;
			return(false);
		}

		double num1=V0squared+sqrt(delta);
		double num2=V0squared-sqrt(delta);
		double denom=g*X;
		double a_rad1=atan2(num1,denom);
		double a_rad2=atan2(num2,denom);

		//special add-on for negative speeds
		if(v0<0)
		{
			a_rad1+=M_PI;
			a_rad2+=M_PI;
		}

		double V0x1=v0*cos(a_rad1);
		double V0x2=v0*cos(a_rad2);

		if(V0x1==0)
		{
			cerr<<"impossible shot: V0x1==0"<<endl;
			return(false);
		}
		time1=X/V0x1;
		
		if(V0x2==0)
		{
			cerr<<"impossible shot: V0x2==0"<<endl;
			return(false);
		}
		time2=X/V0x2;

		a_deg1=limit_angle(rad2deg(a_rad1));
		a_deg2=limit_angle(rad2deg(a_rad2));
		cout<<"a_deg1="<<a_deg1<<endl;
		cout<<"a_deg2="<<a_deg2<<endl;
		return(true);
	}
	
	//calculates velocity+angle for a given flighttime (useful for bombs)
	//returns true if shot possible, else false
	//works with negative flighttimes too because it is equivalent to -vector(v0)
	bool calc_vector(double time, GLfloat &a_deg, GLfloat &v0, double g, double x0, double y0, double x, double y)
	{
		//default values that will be returned if shot impossible
		v0=0;
		a_deg=0;

		double X=x-x0;
		double Y=y-y0;
		
		double TimeSquared=time*time;
		double Ypart=Y-0.5*g*TimeSquared;

		if(TimeSquared==0)
		{
			cerr<<"impossible shot: TimeSquared==0"<<endl;
			return(false);
		}
		v0=sqrt((X*X+Ypart*Ypart)/TimeSquared);
		double a_rad=atan2(-Ypart,X); //-Ypart because the V0y=-V0*sin(a)
		a_deg=limit_angle(rad2deg(a_rad));
		return(true);
	}

	void AIMovePlayer()	{
		
	}
	
	Uint32 GetMaxHeightOfObstacle(SDL_Surface *surf, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2)	{
		
	}
	
	void AIFireWeapons(int AIPlayer)	{
		Uint32 ObstacleHieght;
		/*if(AIPlayer == 0)	{
			ObstacleHieght = GetMaxHeightOfObstacle(&Terrain, Players[0].x, Players[0].y, Players[1].x, Players[1].x);
		} else {
			ObstacleHieght = GetMaxHeightOfObstacle(&Terrain, Players[1].x, Players[1].y, Players[0].x, Players[0].x);
		}*/
		
		
	}
	
	unsigned int EstimateTime(GLfloat x1, GLfloat x2)	{
		unsigned int time;
		time=(unsigned int)(fabs(x2 - x1) / 10.);//absolute value ;)
		return (time);
	}
	
	GLfloat GetXVelocity(GLfloat x1, GLfloat x2, unsigned int time )	{
		return( (x2 - x1) / time );
	}
	
	GLfloat GetYVelocity(GLfloat y1, GLfloat y2, GLfloat gravity,  unsigned int time )	{
		return( -( y1 - 0.5 * pow(time, 2.0) - y2 ) / time);
	}

	void AIChooseWeapon()	{
		
	}
	
}
