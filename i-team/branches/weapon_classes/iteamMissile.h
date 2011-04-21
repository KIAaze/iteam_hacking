//
// C++ Interface: iteamMissile
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ITEAMITEAMMISSILE_H
#define ITEAMITEAMMISSILE_H

#include <Weapon.h>

namespace iteam {

/**
	@author 
*/
class iteamMissile : public Weapon
{
public:
    iteamMissile();
	int DefineTextures();
	int Fire (GLfloat nx, GLfloat ny, GLfloat new_angle, GLfloat new_vel);
	int DoBehaviour();
	int Render(gp2d::Camera Cam);
};

}

#endif
