//
// C++ Interface: iteamMultirazor
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ITEAMITEAMMULTIRAZOR_H
#define ITEAMITEAMMULTIRAZOR_H

#include <Weapon.h>

namespace iteam {

/**
	@author 
*/
class iteamMultirazor : public Weapon
{
public:
    iteamMultirazor();
	int DefineTextures();
	int DoBehaviour();
	int Render(gp2d::Camera Cam);
};

}

#endif
