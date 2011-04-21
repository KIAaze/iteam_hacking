//
// C++ Implementation: iteamClusterbomb
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "iteamClusterbomb.h"
#include "iteamGrenade.h"
#include "iteam_maths.h"
#include "globals.h"
#include "SpriteMap.h"

namespace iteam {

iteamClusterbomb::iteamClusterbomb()
 : Weapon()
{
	m_TriggerTime = 4000;
	sprintf ( Name, "%d", m_TriggerTime/1000 );
	this->DefineTextures();
}

int iteamClusterbomb::DefineTextures()
{
	this->Load(Weapon_Texture[2],1,1);
	return(0);
}

int iteamClusterbomb::DoBehaviour () {
		int l_Ticks = GameTimer[0].GetTicks() - StartTicks;
		// is it time to explode yet?
		if ( l_Ticks > m_TriggerTime )
		{
			sprintf ( Name, "%d", 0 );
			//activate baby components
			Weapon* W;
			for ( int i=1;i<9;i++ )
			{
				double ang = deg2rad ( rand_uniform ( 0,360 ) );
				double dist = 0.5*BlastRadius;
				W=new iteamGrenade();
				W->Scale(0.5);
				W->Fire(GetX()+dist*cos(ang), GetY()+dist*sin(ang), 0, 0 );
				Add(supermap,W);
			}
			// Blast all objects, including the new babies :)
			BlastObjects(supermap);
			DestroyTerrain();
			return(1);
		}
		else
		{
			// Nope so update seconds counter above Weapon
			sprintf ( Name, "%d", 1 + ( m_TriggerTime - l_Ticks ) / 1000 );
			return(0);
		}
}

}
