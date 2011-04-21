/*! \file physics.cpp
\brief Physics engine

Used to process movement of physical objects.
*/

#include "physics.h"
#include "weapons.h"
#include "Weapon.h"
#include "globals.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include "iteam_maths.h"

namespace iteam {

	//called from iteam.cpp
	void ProcessAllPhysicalObjects ( void ) {
		ProcessPlayers();
		ProcessWeapons();
	}

	void ProcessPlayers ( void ) {
		for ( int i=0;i<=Player.size()-1;i++ ) {
			if ( Player[i].Alive ) {
				if ( Player[i].Health<=0 ) {
					Player[i].selectSheet ( 1 );//select death animation
					Player[i].setAnimationSpeed ( 24.0 );
					Player[i].Dying=true;
					//cout<<"Player["<<i<<"] is dying!"<<endl;
				}
				if ( Player[i].GetY() >TERRAIN_YMAX ) {
					Player[i].Alive=false;
					cout<<"Player["<<i<<"] fell into a black hole!"<<endl;
				}
				//=================================================================
				//Main physics engine
				//=================================================================
				//initialization of delta_time which will be used for movement calculation
#if 0
				cout<<"iTimer.GetTicks()="<<GameTimer[0].GetTicks() <<endl;
				cout<<"Player[i].LastTicks="<<Player[i].LastTicks<<endl;
#endif
				Player[i].delta_time = GameTimer[0].GetTicks() - Player[i].LastTicks;
#if 0
				cout<<"Player[i].delta_time="<<Player[i].delta_time<<endl;
#endif
				//don't forget to memorize LastTicks for the next passage
				Player[i].LastTicks = GameTimer[0].GetTicks();
				//position=position+vel*delta_time
				Player[i].MoveMe();
				//vel=vel+accel*delta_time
#if 0
				cout<<"before calcvel: Player[0].vX="<<Player[0].vX<<endl;
#endif
				Player[i].CalculateVelocity();
#if 0
				cout<<"after calcvel: Player[0].vX="<<Player[0].vX<<endl;
#endif
				//accel=accel_external+accel_internal
				Player[i].CalculateAcceleration();
				//=================================================================
				Cam.Begin();
				Player[i].DrawMe();
				Cam.Begin();
				Player[i].DrawName();
			}//end if Alive
		}//end for loop
	}//end ProcessPlayers

	void ProcessWeapons ( void ) {
		// update any active weapons
		// cout << "[WEAPON PHYSICS] WeaponList is " << g_WeaponsList.size() << " items long\n";
		for ( int i=0; i < g_WeaponsList.size(); i++ ) { 	// loop through each weapon in list and test if its active
			// cout << "[WEAPON PHYSICS] Weapon " << i << " searched\n";
			if ( g_WeaponsList[i].Active == true ) { 	// seems to be active so process the components
				bool allinactive=true;//to deactivate clusterbomb
				for ( int j=0; j < g_WeaponsList[i].components.size(); j++ ) {  // move each component
					if ( g_WeaponsList[i].components[j].Active == true ) {
						allinactive=false;
						//cout << "[WEAPON PHYSICS] Weapon " << i << " is active\n";

						//=================================================================
						//Main physics engine
						//=================================================================
						//initialization of delta_time which will be used for movement calculation
						g_WeaponsList[i].components[j].delta_time = GameTimer[0].GetTicks() - g_WeaponsList[i].components[j].LastTicks;
						//don't forget to memorize LastTicks for the next passage
						g_WeaponsList[i].components[j].LastTicks = GameTimer[0].GetTicks();
						//position=position+vel*delta_time
						int collision=g_WeaponsList[i].components[j].MoveMe();
						//vel=vel+accel*delta_time
						g_WeaponsList[i].components[j].CalculateVelocity();
						//accel=accel_external+accel_internal
						g_WeaponsList[i].components[j].CalculateAcceleration();
						//=================================================================

						DoWeaponBehaviours ( i,j,collision );
						Cam.Begin();
						g_WeaponsList[i].components[j].DrawFrame();
						g_WeaponsList[i].components[j].DrawName();
						g_WeaponsList[i].components[j].setNextFrame();
						//cout << "[WEAPON PHYSICS] x = " << g_WeaponsList[i].components[j].x << " y = " << g_WeaponsList[i].components[j].y << "\n";
					}//end of if component active
				}//end of j loop
				if ( allinactive ) g_WeaponsList[i].Active=false;
			}//end of if weapon active
		}//end of i loop
	}//end of ProcessWeapons

}//end of namespace iteam

namespace iteam {

	PhysicsSystem* iteamPhysics;

	PhysicsSystem::PhysicsSystem() {
		GLfloat l_Multiplier = 1.5;
		m_NumObjectsInSystem = 0;
		m_ImpulseCount = 0;
		m_LastTicks = iteam::GameTimer[0].GetTicks();
		m_Gravity = 9.81 * l_Multiplier; // actual gravity times 2 (its seems faster than normal gravity somehow
		m_OneMeterInPixels = 27 * l_Multiplier; // 27 pixels in this implementation but might be different in other games
		m_GravityInPixels = m_Gravity * m_OneMeterInPixels; // establish the actual game units measurements
		SetWind ( 0.0 );
	}
	//called from iteam.cpp
	void PhysicsSystem::ProcessAllPhysicalObjects ( void ) {
		GLfloat l_AdvanceX, l_AdvanceY;
		GLfloat l_Nx, l_Ny;
		GLfloat l_AccelX, l_AccelY;
		GLfloat l_EnviroAccelerationX, l_EnviroAccelerationY;

		// set the lenght of the current iteration
		int l_NowTicks = iteam::GameTimer[0].GetTicks();
		int l_DeltaTime = l_NowTicks - m_LastTicks;
		// update for next time around
		m_LastTicks = l_NowTicks;

		// calculate the enviromental accelerations for all objects in the system
		// like gravity and crosswinds etc
		l_EnviroAccelerationX = CalulateEnviromentXAcceleration();
		l_EnviroAccelerationY = CalulateEnviromentYAcceleration();

		gp2d::Sprite* l_CurrSpr = 0;

		for ( int i = 0; i < m_NumObjectsInSystem; i++ ) {
			// set enviromental accelerations
			l_AccelX = GetDelta ( l_EnviroAccelerationX, l_DeltaTime );
			l_AccelY = GetDelta ( l_EnviroAccelerationY, l_DeltaTime );
			l_CurrSpr = m_PhysicalObjects[i];
			// now add any sprite accelerations

			GLfloat l_Vx, l_Vy;
			l_Vx = l_CurrSpr->GetVX();
			l_Vx += l_AccelX;
			l_CurrSpr->SetVX ( l_Vx );

			l_Vy = l_CurrSpr->GetVY();
			l_Vy += l_AccelY;
			l_CurrSpr->SetVY ( l_Vy );

			// assert(l_CurrSpr->GetVY() < 50);

			// work out how much the current frames will step our sprite in game space
			l_AdvanceX = GetDelta ( l_CurrSpr->GetVX(), l_DeltaTime );
			l_AdvanceY = GetDelta ( l_CurrSpr->GetVY(), l_DeltaTime );
			// add the step amounts
			GLfloat l_X, l_Y;
			GLfloat l_XNew, l_YNew;
			l_X = l_CurrSpr->GetX();
			l_XNew = l_X + l_AdvanceX;
			l_CurrSpr->SetX ( l_XNew );

			l_Y = l_CurrSpr->GetY();
			l_YNew = l_Y + l_AdvanceY;
			l_CurrSpr->SetY ( l_YNew );

			// did we hit anything when we stepped?
			// if(m_PhysicalObjects[i]->IsPhysical())	{
			if ( CollisionPixel ( l_CurrSpr,&Level[0],0,0 ) ) {
				// yes, so work out how far we can step WITHOUT colliding
				l_CurrSpr->collision = true;
				l_CurrSpr->SetX ( l_X - l_AdvanceX );
				l_CurrSpr->SetY ( l_Y - l_AdvanceY );
				// try to step half way to the collision point without colliding
				// so we can get a nearer proximity for our sprite without touching
				for ( int j=0; j < PS_SUBDEVIDE_VALUE; j++ ) {
					l_AdvanceX = l_AdvanceX / 2;
					l_AdvanceY = l_AdvanceY / 2;

					l_CurrSpr->SetX ( l_X + l_AdvanceX );
					l_CurrSpr->SetY ( l_Y + l_AdvanceY );
					// did we do it withough hitting again?
					if ( CollisionPixel ( l_CurrSpr,&Level[0],0,0 ) ) {

						l_CurrSpr->SetX ( l_X - l_AdvanceX );
						l_CurrSpr->SetY ( l_Y - l_AdvanceY );
					}
				}

				NormalReflectVector (
				    l_Nx
				    , l_Ny
				    , l_CurrSpr
				);
				// is our sprite a w

				// remove some of the bounce - commonly know as restitution coefficient I think XD
				l_Vx = l_CurrSpr->GetVX();
				l_Vy = l_CurrSpr->GetVY();
				l_CurrSpr->SetVX ( l_Vx * l_CurrSpr->Elasticity );
				l_CurrSpr->SetVY ( l_Vy * l_CurrSpr->Elasticity );

			}
			// }
			Cam.Begin();
			l_CurrSpr->DrawFrame();
			Cam.End();
			l_CurrSpr->setNextFrame();

		}
	}

	// factor in any impulses added into the system for x direction
	const GLfloat PhysicsSystem::CalulateEnviromentXAcceleration() {
		return 0.0;
	}

	// factor in any impulses added into the system for x direction
	const GLfloat PhysicsSystem::CalulateEnviromentYAcceleration() {
		return m_GravityInPixels;
	}

	void PhysicsSystem::AddObject (
	    gp2d::Sprite* a_Sprite
	) {
		if ( m_NumObjectsInSystem < PHYSIC_MAX_OBJECTS ) {

			m_PhysicalObjects[ m_NumObjectsInSystem ] = a_Sprite;
			m_NumObjectsInSystem++;
		}
	}

	void PhysicsSystem::RemoveOneObject() {
		m_NumObjectsInSystem--;
	}

	void PhysicsSystem::AddImpulse (
	    PhysicalImpulse* a_Impulse
	) {
		if ( m_ImpulseCount < PHYSIC_MAX_OBJECTS ) {
			m_EnviromentalForces[ m_ImpulseCount ] = a_Impulse;
			m_ImpulseCount++;
		}
	}





#if 0
	void PhysicsSystem::ProcessPlayers ( void ) {
		for ( int i=0;i<=Player.size()-1;i++ ) {
			//=================================================================
			//Main physics engine
			//=================================================================
			//initialization of delta_time which will be used for movement calculation
			cout<<"iTimer.GetTicks()="<<GameTimer[0].GetTicks() <<endl;
			cout<<"Player[i].LastTicks="<<Player[i].LastTicks<<endl;
			Player[i].delta_time = GameTimer[0].GetTicks() - Player[i].LastTicks;
			cout<<"Player[i].delta_time="<<Player[i].delta_time<<endl;
			//don't forget to memorize LastTicks for the next passage
			Player[i].LastTicks = GameTimer[0].GetTicks();
			//position=position+vel*delta_time
			Player[i].MoveMe();
			//vel=vel+accel*delta_time
			cout<<"before calcvel: Player[0].vX="<<Player[0].vX<<endl;
			Player[i].CaclulateVelocity();
			cout<<"after calcvel: Player[0].vX="<<Player[0].vX<<endl;
			//accel=accel_external+accel_internal
			Player[i].CaclulateAcceleration();
			//=================================================================
			Cam.Begin();
			Player[i].DrawMe();
			Cam.Begin();
			Player[i].DrawName();
		}
	}

	void ProcessWeapons ( void ) {
		// update any active weapons
		// cout << "[Weapon PHYSICS] WeaponList is " << g_WeaponsList.size() << " items long\n";
		for ( int i=0; i < g_WeaponsList.SizeCount(); i++ ) { 	// loop through each Weapon in list and test if its active
			// cout << "[Weapon PHYSICS] Weapon " << i << " searched\n";
			if ( g_WeaponsList[i].Active == true ) { 	// seems to be active so process the components
				bool allinactive=true;//to deactivate clusterbomb
				for ( int j=0; j < g_WeaponsList[i].components.size(); j++ ) {  // move each component
					if ( g_WeaponsList[i].components[j].Active == true ) {
						allinactive=false;
						//cout << "[Weapon PHYSICS] Weapon " << i << " is active\n";

						//=================================================================
						//Main physics engine
						//=================================================================
						//initialization of delta_time which will be used for movement calculation
						g_WeaponsList[i].components[j].delta_time = GameTimer[0].GetTicks() - g_WeaponsList[i].components[j].LastTicks;
						//don't forget to memorize LastTicks for the next passage
						g_WeaponsList[i].components[j].LastTicks = GameTimer[0].GetTicks();
						//position=position+vel*delta_time
						int collision=g_WeaponsList[i].components[j].MoveMe();
						//vel=vel+accel*delta_time
						g_WeaponsList[i].components[j].CaclulateVelocity();
						//accel=accel_external+accel_internal
						g_WeaponsList[i].components[j].CaclulateAcceleration();
						//=================================================================

						DoWeaponBehaviours ( i,j,collision );
						Cam.Begin();
						g_WeaponsList[i].components[j].Draw();
						g_WeaponsList[i].components[j].DrawName();
						//cout << "[Weapon PHYSICS] x = " << g_WeaponsList[i].components[j].x << " y = " << g_WeaponsList[i].components[j].y << "\n";
					}//end of if component active
				}//end of j loop
				if ( allinactive ) g_WeaponsList[i].Active=false;
			}//end of if Weapon active
		}//end of i loop
	}//end of ProcessWeapons
#endif

}//end of namespace iteam
