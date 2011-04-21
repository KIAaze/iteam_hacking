/*! \file weapons.cpp
\brief Weapon class
*/

#include "Weapon.h"
#include "globals.h"
// #include "WeaponsList.h"
// #include "players.h"
// #include "iteam_maths.h"
// #include "primitives.h"
// #include "explosions.h"
// #include <iostream>
// #include <stdio.h>

// ====================== GLOBALS =============================

namespace iteam	{

	Weapon::Weapon() {
		NumberOfComponents = 0;
		m_Name = new char[20];
		strcpy ( m_Name, "New Weapon" );
		m_Active = false;
		m_Throwable = true;
	}

	void Weapon::SetName ( char *a_Name ) {
		strcpy ( m_Name, a_Name );
	}

	char * Weapon::GetName() {
		return m_Name;
	}

	Weapon::~Weapon() {
		for ( int i=0; i < NumberOfComponents; i++ )   {
			delete component[i];

		}

	}

	int Weapon::Fire (
	    PlayerObj *a_Player
	    , GLfloat nx
	    , GLfloat ny
	    , GLfloat new_angle
	    , GLfloat new_vel
	    , GLfloat a_TriggerTime
	) {
		//GLfloat l_GravityInPixels = m_PhysicsSystem->GetGravityInPixels();
		m_Player = a_Player;
		WeaponComponent* l_Component = component[0];
		l_Component->Fire (
		    nx
		    , ny
		    , new_angle
		    , new_vel
		    , a_TriggerTime
		);
		m_PhysicsSystem->AddObject ( l_Component );
		m_Active = true;
		return ( 0 );
	}

	void Weapon::IncrementTriggerTime (
	    const GLfloat a_Increment
	) {
		int l_TriggerTime;
		l_TriggerTime = component[0]->GetTriggerTime();
		l_TriggerTime += ( int ) a_Increment * 1000;
		component[0]->SetTriggerTime ( l_TriggerTime );
	}

	void Weapon::DecrementTriggerTime (
	    const GLfloat a_Increment
	) {
		int l_TriggerTime;
		l_TriggerTime = component[0]->GetTriggerTime();
		l_TriggerTime -= ( int ) a_Increment * 1000;
		component[0]->SetTriggerTime ( l_TriggerTime );
	}


	void Weapon::Add (
	    int TypeID
	    , const char texture[]
	    , bool IsPhysical
	    , bool Bounces
	    , GLfloat BlastRadius
	    , GLfloat BlastFactor
	    , GLfloat BlastDamage
	    , GLfloat a_Elasticity
	    , int a_TriggerTime
	    , bool Active
	    , GLfloat scale
	) {
		WeaponComponent* l_TempComponent;

		l_TempComponent = new WeaponComponent ( "New Component", false, true, TypeID, BlastRadius, BlastFactor, BlastDamage, a_TriggerTime * 1000, 0, true, TypeID, true );

		l_TempComponent->Load ( texture );
		l_TempComponent->Scale ( scale );
		l_TempComponent->Elasticity = a_Elasticity;
		l_TempComponent->col_x[0]= ( 32/2 )-4;
		l_TempComponent->col_y[0]=8;
		l_TempComponent->col_width[0]=20;
		l_TempComponent->col_height[0]=32-8;

		// create thumbnail file reference
		if ( NumberOfComponents == 0 ) {
			m_PathToThumbnail = new char[ sizeof ( texture ) ];
			strcpy ( m_PathToThumbnail, texture );
		}
		component.push_back ( l_TempComponent );	// add a new component to the weapons type
		NumberOfComponents++;
	}

	const int Weapon::GetTriggerTime() {
		return component[0]->GetTriggerTime();
	}


	void Weapon::DoBehaviours ( int collision )	{

#if 0
		int newTicks;
		GLfloat distance;
		GLfloat tempX, tempY;
		SDL_Surface * surf;

		switch ( TypeID )	{
				// ==========================================================================================
				// ================================ GRENADES ==================================================
				// ==========================================================================================
			case IT_WT_GRENADE:
				newTicks =  GameTimer[0].GetTicks() - WeaponsList[TypeID].component[0]->StartTicks;
				if ( newTicks > WeaponsList[TypeID].component[0]->TimeTrigger )	{  // time trigger reached! go BOOOOOOM!

					// apply blast to all physical objects
					WeaponsList[TypeID].component[0]->BlastObjects();
					// destroy terrain
					DestroyTerrain ( TypeID, 0 );
					// deactivate Weapon
					WeaponsList[TypeID].Active = false;

				} else {
					sprintf ( str, "%d",1+ ( WeaponsList[TypeID].component[0]->TimeTrigger - newTicks ) / 1000 );
					WeaponsList[TypeID].component[0]->Name = str;
				}
				break;
				// ==========================================================================================
				// ================================   MISSILES  ==================================================
				// ==========================================================================================
			case IT_WT_MISSILE:
				// orientate missile according to its direction
				WeaponsList[TypeID].component[0]->orientate();
				//apply acceleration from the missile engine
				WeaponsList[TypeID].component[0]->SetAcceleration ( IT_WT_MISSILE_ACCEL,WeaponsList[TypeID].component[0]->movement_angle );

				// explode on impact with terrain
				//to explode on impact with sprites, we'll need a loop, maybe create a any_collision function. Careful with player collision at start... ^^
				if ( /*CollisionPixel(&(WeaponsList[TypeID].component[0]),&Terrain,0,0)*/collision ) {

					// apply blast to all physical objects
					WeaponsList[TypeID].component[0]->BlastObjects();
					// destroy terrain
					DestroyTerrain ( TypeID, 0 );
					// deactivate Weapon
					WeaponsList[TypeID].Active = false;
				}
				break;

				// ==========================================================================================
				// ================================ CLUSTER BOMB ===============================================
				// ==========================================================================================
			case IT_WT_CLUSTERBOMB:
				for ( int i=0;i<9;i++ )
					printf ( "%d",WeaponsList[TypeID].component[i].Active );
				printf ( "\n" );
				newTicks =  GameTimer[0].GetTicks() - WeaponsList[TypeID].component[CompID].StartTicks;
				if ( newTicks > WeaponsList[TypeID].component[CompID].TimeTrigger )	{  // time trigger reached! go BOOOOOOM!

					//destroy the terrain
					DestroyTerrain ( TypeID, CompID );
					//activate baby component
					if ( CompID==0 ) {
						for ( int i=1;i<9;i++ ) {
							double ang = deg2rad ( rand_uniform ( 0,360 ) );
							double dist = 0.5*WeaponsList[TypeID].component[0]->BlastRadius;
							FireComponent ( TypeID, i, WeaponsList[TypeID].component[0]->x+dist*cos ( ang ), WeaponsList[TypeID].component[0]->y+dist*sin ( ang ), 0, 0 );
						}
					}
					// apply blast to all physical objects
					WeaponsList[TypeID].component[CompID].BlastObjects();
					//deactivate component
					WeaponsList[TypeID].component[CompID].Active = false;
				} else {
					sprintf ( str, "%d",1+ ( WeaponsList[TypeID].component[CompID].TimeTrigger - newTicks ) / 1000 );
					WeaponsList[TypeID].component[CompID].Name = str;
				}
				break;

				// ==========================================================================================
				// ================================ DYNAMITE ===================================================
				// ==========================================================================================
			case IT_WT_DYNAMITE:
				newTicks =  GameTimer[0].GetTicks() - WeaponsList[TypeID].component[0]->StartTicks;
				if ( newTicks > WeaponsList[TypeID].component[0]->TimeTrigger )	{  // time trigger reached! go BOOOOOOM!

					// apply blast to all physical objects
					WeaponsList[TypeID].component[0]->BlastObjects();
					// destroy terrain
					DestroyTerrain ( TypeID, 0 );
					// deactivate Weapon
					WeaponsList[TypeID].Active = false;

				} else {
					sprintf ( str, "%d",1+ ( WeaponsList[TypeID].component[0]->TimeTrigger - newTicks ) / 1000 );
					WeaponsList[TypeID].component[0]->Name = str;
				}
				break;
		}//end of switch
#endif
	}//end of DoWeaponBehaviours


	//not yet used
	/*
	void UpdateWeaponObjects(void)	{
	    exit(0);
	    // update any active weapons
	    int i,j;
	    // cout << "[Weapon PHYSICS] WeaponsList is " << WeaponsList.size() << " items long\n";
	    for(i=0; i < WeaponsList.size(); i++)	{	// loop through each Weapon in list and test if its active
	        // cout << "[Weapon PHYSICS] Weapon " << i << " searched\n";
	        if(WeaponsList[i].Active == true)	{	// seems to be active so process the componets
	            for(j=0; j < WeaponsList[i].component.size(); j++)	{ // move each component
	                // cout << "[Weapon PHYSICS] Weapon " << i << " is active\n";
	                WeaponsList[i].component[j].CaclulateVelocity();
	                WeaponsList[i].component[j].MoveMe();
	                DoWeaponBehaviours(i,j);
	                Cam.Begin();

	                WeaponsList[i].component[j].Draw();
	                WeaponsList[i].component[j].DrawName();
	                //cout << "[Weapon PHYSICS] x = " << WeaponsList[i].component[j].x << " y = " << WeaponsList[i].component[j].y << "\n";
	            }
	        }
	    }
	    // this may include any players eventually as all moving things
	    // in the scene will be reacting to gravity etc.
	}
	*/

	bool Weapon::ComponentTriggered ( WeaponComponent* a_Component ) {
		bool ReturnVal = false;
		int l_Ticks = GameTimer[0].GetTicks() - a_Component->GetStartTicks();
		if ( a_Component->IsActive() )   {
			if ( l_Ticks > a_Component->GetTriggerTime() )   {
				a_Component->BlastObjects();
				a_Component->DestroyTerrain();
				a_Component->SetInactive();
				m_PhysicsSystem->RemoveOneObject();
				ReturnVal = true;
			}
		}
		return ReturnVal;
	}


}
