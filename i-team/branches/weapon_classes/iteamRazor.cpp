//
// C++ Implementation: iteamRazor
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "iteamRazor.h"
#include <iostream>
using namespace std;

namespace iteam {

iteamRazor::iteamRazor()
 : Weapon()
{
	this->setAnimationSpeed ( 16.0f );
	animationTimer.Start();
	this->DefineTextures();
}

int iteamRazor::DefineTextures()
{
	this->Load(Weapon_Texture[5],6,1);
	return(0);
}

int iteamRazor::DoBehaviour () {
	this->setNextFrame();//necessary for animation
	// explode on impact with terrain
	//to explode on impact with sprites, we'll need a loop, maybe create a any_collision function. Careful with player collision at start... ^^
	if ( collision ) {
		BlastObjects(supermap);
		DestroyTerrain();
		return(1);
	}
	return(0);
}

int iteamRazor::Render(gp2d::Camera Cam)
{
	Cam.Begin();
	this->DrawFrame();
	Cam.End();
	return(0);
}

}
