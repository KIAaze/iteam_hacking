//
// C++ Implementation: iteamDynamite
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "iteamDynamite.h"
#define IT_WT_DYNAMITE_BLAST_RADIUS             240.0
#define IT_WT_DYNAMITE_BLAST_FACTOR             100.
#define IT_WT_DYNAMITE_BLAST_DAMAGE             10.

namespace iteam {

iteamDynamite::iteamDynamite()
 : Weapon()
{
	m_TriggerTime = 10000;
	BlastRadius=IT_WT_DYNAMITE_BLAST_RADIUS;
	BlastFactor=IT_WT_DYNAMITE_BLAST_FACTOR;
	BlastDamage=IT_WT_DYNAMITE_BLAST_DAMAGE;
	sprintf ( Name, "%d", m_TriggerTime/1000 );
	this->DefineTextures();
}

int iteamDynamite::DefineTextures()
{
	this->Load(Weapon_Texture[3],1,1);
	return(0);
}

}
