//
// C++ Implementation: iteamMissile
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "iteamMissile.h"

#define IT_WT_MISSILE_ACCEL 200.0

namespace iteam {

iteamMissile::iteamMissile()
 : Weapon()
{
	this->DefineTextures();
}

int iteamMissile::DefineTextures()
{
	this->Load(Weapon_Texture[1],1,1);
	return(0);
}

int iteamMissile::Fire (GLfloat nx, GLfloat ny, GLfloat new_angle, GLfloat new_vel) {
	SetX ( nx );
	SetY ( ny );
	SetVelocity ( new_vel, new_angle ); // Set the initial speed and direcion
	this->orientate();
	return(0);
}

int iteamMissile::DoBehaviour()
{
	// orientate missile according to its direction
	this->orientate();
	//apply acceleration from the missile engine
	this->SetAcceleration ( IT_WT_MISSILE_ACCEL,-angle );

	// explode on impact with terrain
	//to explode on impact with sprites, we'll need a loop, maybe create a any_collision function. Careful with player collision at start... ^^
	if ( collision ) {
		BlastObjects(supermap);
		DestroyTerrain();
		return(1);
	}
	return(0);
}

int iteamMissile::Render(gp2d::Camera Cam)
{
	Cam.Begin();
	this->DrawFrame();
	Cam.End();
	return(0);
}

}
