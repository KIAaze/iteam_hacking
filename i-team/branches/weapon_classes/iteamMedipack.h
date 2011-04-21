//
// C++ Interface: iteamMedipack
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ITEAMITEAMMEDIPACK_H
#define ITEAMITEAMMEDIPACK_H

#include <Weapon.h>

namespace iteam {

/**
	@author 
*/
class iteamMedipack : public Weapon
{
public:
    iteamMedipack();
	int DefineTextures();
	int DoBehaviour();
	int Render(gp2d::Camera Cam);
};

}

#endif
