//
// C++ Implementation: iteamMedipack
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "iteamMedipack.h"
#include "globals.h"
#include "SpriteMap.h"
#include <iostream>
using namespace std;

#define IT_WT_BANDAID_HEAL_FACTOR     42.0

namespace iteam {

iteamMedipack::iteamMedipack()
 : Weapon()
{
	this->DefineTextures();
}

int iteamMedipack::DefineTextures()
{
	this->Load(Weapon_Texture[6],1,1);
	return(0);
}

int iteamMedipack::DoBehaviour()
{
	if(!CheckKey(supermap,m_target))
	{
		cout<<"FATAL ERROR: Target not found!"<<endl;
		return(1);
	}
	supermap[m_target]->m_integrity+=IT_WT_BANDAID_HEAL_FACTOR;
	if ( supermap[m_target]->m_integrity>100 ) supermap[m_target]->m_integrity=100;
	return(1);//return 1 to destroy it right away (or later, once the healing animation is finished)
}

int iteamMedipack::Render(gp2d::Camera Cam)
{
	//Empty because we don't won't to render anything. (yet ;) )
	return(0);
}

}
