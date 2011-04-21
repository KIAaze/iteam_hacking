//
// C++ Implementation: iteamMultirazor
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "iteamMultirazor.h"
#include "iteamRazor.h"
#include "globals.h"
#include "SpriteMap.h"
#include "iteam_maths.h"

namespace iteam {

iteamMultirazor::iteamMultirazor()
 : Weapon()
{
	this->setAnimationSpeed ( 16.0f );
	animationTimer.Start();
	this->DefineTextures();
}

int iteamMultirazor::DefineTextures()
{
	this->Load(Weapon_Texture[5],6,1);
	return(0);
}

int iteamMultirazor::DoBehaviour () {
	this->setNextFrame();//necessary for animation
	if ( vy>=0 ) { // max height reached! separate into 3 leaves!
		//activate baby components
		double V=sqrt ( vx*vx+vy*vy );
		double ang1 = atan2 ( vy,vx );
		double ang2 = ang1+deg2rad ( 45 );
		double ang3 = ang1-deg2rad ( 45 );
		Weapon *W1,*W2,*W3;
		W1=new iteamRazor();
		W2=new iteamRazor();
		W3=new iteamRazor();
		W1->Fire(GetX(), GetY(), rad2deg(ang1), V );
		W2->Fire(GetX(), GetY(), rad2deg(ang2), V );
		W3->Fire(GetX(), GetY(), rad2deg(ang3), V );
		Add(supermap,W1);
		Add(supermap,W2);
		Add(supermap,W3);
		return(1);
	}
	return(0);
}

int iteamMultirazor::Render(gp2d::Camera Cam)
{
	Cam.Begin();
	this->DrawFrame();
	Cam.End();
	return(0);
}

}
