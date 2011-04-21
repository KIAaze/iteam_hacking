/*! \file iteam-ai.h
\brief AI functions

Contains functions essential for the AI.
*/

#ifndef IT_AI_H
#define IT_AI_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

#ifdef _WIN32
#include "../bugfixing/lib/gp2d.h"
#else
#include "library_h/gp2d.h"
#endif

using std::cout;
using std::endl;

namespace iteam {

	/*! \brief calculates velocity+flighttime for a given angle

	returns true if shot possible, else false
	Can also return negative speeds when necessary. ;)
	Also works with negative gravity :D
	*/
	bool calc_velocity ( double a_deg, GLfloat &v0, GLfloat &time, double g, double x0, double y0, double x, double y );

	/*! \brief calculates angle+flighttime for a given velocity

	returns true if shot possible, else false
	There are 2 possible (angle,time) pairs for a given speed
	works with negative speeds too
	*/
	bool calc_angle ( double v0, GLfloat &a_deg1, GLfloat &time1, GLfloat &a_deg2, GLfloat &time2, double g, double x0, double y0, double x, double y );

	/*! \brief calculates velocity+angle for a given flighttime (useful for bombs)

	returns true if shot possible, else false
	works with negative flighttimes too because it is equivalent to -vector(v0)
	*/
	bool calc_vector ( double time, GLfloat &a_deg, GLfloat &v0, double g, double x0, double y0, double x, double y );

	void AIMovePlayer();
	//Uint32 GetMaxHeightOfObstacle(SDL_Surface *surf, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2);
	void AIFireWeapons();
	void AIChooseWeapon();

	Uint32 GetMaxHeightOfObstacle ( SDL_Surface *surf, Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2 );
}

#endif
