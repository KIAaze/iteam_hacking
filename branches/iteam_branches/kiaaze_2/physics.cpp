/*! \file physics.cpp
\brief Physics engine

Used to process movement of physical objects.
*/

#include "physics.h"
#include "weapons.h"
#include "globals.h"
#include <iostream>

namespace iteam {

	//called from iteam.cpp
	void ProcessAllPhysicalObjects(void)	{
		ProcessPlayers();
		ProcessWeapons();
	}

	void ProcessPlayers(void)	{
cout<<"===================================="<<endl;
cout<<"================= PROCESSPLAYERS ==="<<endl;
	for(int i=0;i<=Player.size()-1;i++){
			//=================================================================
			//Main physics engine
			//=================================================================
			//initialization of delta_time which will be used for movement calculation
		cout<<"iTimer.GetTicks()="<<iTimer.GetTicks()<<endl;
		cout<<"Player["<<i<<"].LastTicks="<<Player[i].LastTicks<<endl;
			Player[i].delta_time = iTimer.GetTicks() - Player[i].LastTicks;
		cout<<"Player["<<i<<"].delta_time="<<Player[i].delta_time<<endl;

			//don't forget to memorize LastTicks for the next passage
			Player[i].LastTicks = iTimer.GetTicks();
			//position=position+vel*delta_time
cout<<"================= MOVEME ==="<<endl;
			Player[i].MoveMe();
			//vel=vel+accel*delta_time
		cout<<"before calcvel: Player["<<i<<"]: "<<Player[i].vX<<","<<Player[i].vY<<endl;
cout<<"================= CALCVEL ==="<<endl;
			Player[i].CaclulateVelocity();
		cout<<"after calcvel: Player["<<i<<"]: "<<Player[i].vX<<","<<Player[i].vY<<endl;
			//accel=accel_external+accel_internal
cout<<"================= CALCACCEL ==="<<endl;
			Player[i].CaclulateAcceleration();
			//=================================================================
			Cam.Begin();
			Player[i].DrawMe();
			Cam.Begin();
			Player[i].DrawName();
		}
	}

	void ProcessWeapons(void)	{
		// update any active weapons
		// cout << "[WEAPON PHYSICS] WeaponList is " << WeaponsList.size() << " items long\n";
		for(int i=0; i < WeaponsList.size(); i++)	{	// loop through each weapon in list and test if its active
			// cout << "[WEAPON PHYSICS] Weapon " << i << " searched\n";
			if(WeaponsList[i].Active == true)	{	// seems to be active so process the components
				bool allinactive=true;//to deactivate clusterbomb
				for(int j=0; j < WeaponsList[i].components.size(); j++)	{ // move each component
				if(WeaponsList[i].components[j].Active == true)	{
					allinactive=false;
					//cout << "[WEAPON PHYSICS] Weapon " << i << " is active\n";

					//=================================================================
					//Main physics engine
					//=================================================================
					//initialization of delta_time which will be used for movement calculation
					WeaponsList[i].components[j].delta_time = iTimer.GetTicks() - WeaponsList[i].components[j].LastTicks;
					//don't forget to memorize LastTicks for the next passage
					WeaponsList[i].components[j].LastTicks = iTimer.GetTicks();
					//position=position+vel*delta_time
					int collision=WeaponsList[i].components[j].MoveMe();
					//vel=vel+accel*delta_time
					WeaponsList[i].components[j].CaclulateVelocity();
					//accel=accel_external+accel_internal
					WeaponsList[i].components[j].CaclulateAcceleration();
					//=================================================================

					DoWeaponBehaviours(i,j,collision);
					Cam.Begin();
					WeaponsList[i].components[j].Draw();
					WeaponsList[i].components[j].DrawName();
					//cout << "[WEAPON PHYSICS] x = " << WeaponsList[i].components[j].x << " y = " << WeaponsList[i].components[j].y << "\n";
				}//end of if component active
				}//end of j loop
				if(allinactive) WeaponsList[i].Active=false;
			}//end of if weapon active
		}//end of i loop
	}//end of ProcessWeapons

}//end of namespace iteam
