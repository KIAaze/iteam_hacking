//
// C++ Interface: iteamRazor
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ITEAMITEAMRAZOR_H
#define ITEAMITEAMRAZOR_H

#include <Weapon.h>

namespace iteam {

/**
	@author 
*/
class iteamRazor : public Weapon
{
public:
    iteamRazor();
	int DefineTextures();
	int DoBehaviour();
	int Render(gp2d::Camera Cam);
};

}

#endif
