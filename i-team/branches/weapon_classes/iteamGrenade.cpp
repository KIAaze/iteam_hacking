//
// C++ Implementation: iteamGrenade
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "iteamGrenade.h"

namespace iteam {

iteamGrenade::iteamGrenade()
 : Weapon()
{
	m_TriggerTime = 3000;
	sprintf ( Name, "%d", m_TriggerTime/1000 );
	this->DefineTextures();
}

int iteamGrenade::DefineTextures()
{
	this->Load(Weapon_Texture[0],1,1);
	return(0);
}

}
