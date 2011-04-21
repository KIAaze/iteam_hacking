/*! \file physics.cpp
\brief Physics engine

Used to process movement of physical objects.
*/

#include "physics.h"
#include "globals.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include "iteam_maths.h"

namespace iteam {

//=================================
// Physics processing new version
//=================================
//TODO: Improves physics engine by adding collision pair functions and collision callbacks, mass, inertia, friction, etc. Try to implement Chipmunks eventually.
	PhysicsSystem* iteamPhysics;

	PhysicsSystem::PhysicsSystem() {
		if ( iteam::GameTimer.size() ==0 ) { printf ( "[PhysicsSystem::PhysicsSystem]FATAL ERROR: iteam::GameTimer is empty.\n" ); exit ( 42 );}

		GLfloat l_Multiplier = 1;

		m_ImpulseCount=0;
		m_LastTicks=iteam::GameTimer[0].GetTicks();
		m_DeltaTime=0;
		m_OneMeterInPixels=10 * l_Multiplier;
		m_Wind=0;
		m_WindInPixels=0;
		m_Gravity=9.81 * l_Multiplier;
		m_GravityInPixels=m_Gravity * m_OneMeterInPixels;
		m_Friction=0;
		m_NumObjectsInSystem=0;
// 		m_PhysicalObjects=NULL;
// 		m_EnvironmentalForces=NULL;

		SetWind ( 0.0 );
	}

	int PhysicsSystem::Reset() {
		m_LastTicks = iteam::GameTimer[0].GetTicks();
		return(m_LastTicks);
	}

	int PhysicsSystem::Step() {
		int l_NowTicks = iteam::GameTimer[0].GetTicks();
		m_DeltaTime = l_NowTicks - m_LastTicks;
		m_LastTicks = l_NowTicks;
		return(m_DeltaTime);
	}

	//called from iteam.cpp
	void PhysicsSystem::ProcessAllPhysicalObjects ( void ) {
		GLfloat l_AdvanceX, l_AdvanceY;
		GLfloat l_Nx, l_Ny;
		GLfloat l_Tx, l_Ty;
		GLfloat l_AccelX, l_AccelY;
		GLfloat l_EnviroAccelerationX, l_EnviroAccelerationY;

		// set the length of the current iteration
		int l_NowTicks = iteam::GameTimer[0].GetTicks();
		int l_DeltaTime = l_NowTicks - m_LastTicks;
		// update for next time around
		m_LastTicks = l_NowTicks;

		// calculate the enviromental accelerations for all objects in the system
		// like gravity and crosswinds etc
		l_EnviroAccelerationX = CalulateEnvironmentXAcceleration();
		l_EnviroAccelerationY = CalulateEnvironmentYAcceleration();

		gp2d::Sprite* l_CurrSpr = 0;
		//l_DeltaTime=1;
		//cout<<"l_DeltaTime="<<l_DeltaTime<<endl;

		for ( map<int,gp2d::Sprite*>::iterator ii=m_PhysicalObjects.begin(); ii!=m_PhysicalObjects.end(); ii++ ) {
			//cout<<"i="<<i<<" m_NumObjectsInSystem="<<m_NumObjectsInSystem<<endl;
			// set enviromental accelerations
			l_AccelX = GetDelta ( l_EnviroAccelerationX, l_DeltaTime );
			l_AccelY = GetDelta ( l_EnviroAccelerationY, l_DeltaTime );
			//cout<<"l_AccelY="<<l_AccelY<<endl;

			l_CurrSpr = ( *ii ).second;

			GLfloat l_X, l_Y;
			GLfloat l_XNew, l_YNew;
			l_X = l_CurrSpr->GetX();
			l_Y = l_CurrSpr->GetY();
			GLfloat l_Vx, l_Vy;
			l_Vx = l_CurrSpr->GetVX();
			l_Vy = l_CurrSpr->GetVY();

			// now add any sprite accelerations
			l_Vx += l_AccelX;
			l_CurrSpr->SetVX ( l_Vx );

			l_Vy += l_AccelY;
			l_CurrSpr->SetVY ( l_Vy );

			// work out how much the current frames will step our sprite in game space
			l_AdvanceX = GetDelta ( l_CurrSpr->GetVX(), l_DeltaTime );
			l_AdvanceY = GetDelta ( l_CurrSpr->GetVY(), l_DeltaTime );
			// add the step amounts
			l_XNew = l_X + l_AdvanceX;
			l_CurrSpr->SetX ( l_XNew );

			l_YNew = l_Y + l_AdvanceY;
			l_CurrSpr->SetY ( l_YNew );

			//cout<<"l_AdvanceY="<<l_AdvanceY<<endl;

			// did we hit anything when we stepped?
			if ( CollisionPixel_2 ( l_CurrSpr, & ( Level[0] ), 0, 0, l_Nx, l_Ny, l_Tx, l_Ty ) ) {
				l_CurrSpr->SpriteTiltAngle=rad2deg ( atan2 ( l_Ty,l_Tx ) );

				l_CurrSpr->SetX ( l_X );
				l_CurrSpr->SetY ( l_Y );
				NormalReflectVector ( l_Nx, l_Ny, l_CurrSpr );
				// remove some of the bounce - commonly know as restitution coefficient I think XD
				l_Vx = l_CurrSpr->GetVX();
				l_Vy = l_CurrSpr->GetVY();
				l_CurrSpr->SetVX ( l_Vx * l_CurrSpr->Elasticity );
				l_CurrSpr->SetVY ( l_Vy * l_CurrSpr->Elasticity );
				l_CurrSpr->collision = true;
			}
		}//end of loop through m_PhysicalObjects
	}//end of PhysicsSystem::ProcessAllPhysicalObjects ( void )

	int PhysicsSystem::UpdateObject(Sprite* a_obj)
	{
		GLfloat l_AdvanceX, l_AdvanceY;
		GLfloat l_Nx, l_Ny;
		GLfloat l_Tx, l_Ty;
		GLfloat l_AccelX, l_AccelY;
		GLfloat l_EnviroAccelerationX, l_EnviroAccelerationY;

		// set the length of the current iteration
// 		int l_NowTicks = iteam::GameTimer[0].GetTicks();
// 		int m_DeltaTime = l_NowTicks - m_LastTicks;
		// update for next time around
// 		m_LastTicks = l_NowTicks;

		// calculate the enviromental accelerations for all objects in the system
		// like gravity and crosswinds etc
		l_EnviroAccelerationX = CalulateEnvironmentXAcceleration();
		l_EnviroAccelerationY = CalulateEnvironmentYAcceleration();

		//cout<<"i="<<i<<" m_NumObjectsInSystem="<<m_NumObjectsInSystem<<endl;
		// set enviromental accelerations
		l_AccelX = GetDelta ( l_EnviroAccelerationX, m_DeltaTime );
		l_AccelY = GetDelta ( l_EnviroAccelerationY, m_DeltaTime );
		//cout<<"l_AccelY="<<l_AccelY<<endl;

		GLfloat l_X, l_Y;
		GLfloat l_XNew, l_YNew;
		l_X = a_obj->GetX();
		l_Y = a_obj->GetY();
		GLfloat l_Vx, l_Vy;
		l_Vx = a_obj->GetVX();
		l_Vy = a_obj->GetVY();

		// now add any sprite accelerations
		l_Vx += l_AccelX;
		a_obj->SetVX ( l_Vx );

		l_Vy += l_AccelY;
		a_obj->SetVY ( l_Vy );

		// work out how much the current frames will step our sprite in game space
		l_AdvanceX = GetDelta ( a_obj->GetVX(), m_DeltaTime );
		l_AdvanceY = GetDelta ( a_obj->GetVY(), m_DeltaTime );
		// add the step amounts
		l_XNew = l_X + l_AdvanceX;
		a_obj->SetX ( l_XNew );

		l_YNew = l_Y + l_AdvanceY;
		a_obj->SetY ( l_YNew );

		//cout<<"l_AdvanceY="<<l_AdvanceY<<endl;

		// did we hit anything when we stepped?
		if ( CollisionPixel_2 ( a_obj, & ( Level[0] ), 0, 0, l_Nx, l_Ny, l_Tx, l_Ty ) ) {
			a_obj->SpriteTiltAngle=rad2deg ( atan2 ( l_Ty,l_Tx ) );

			a_obj->SetX ( l_X );
			a_obj->SetY ( l_Y );
			NormalReflectVector ( l_Nx, l_Ny, a_obj );
			// remove some of the bounce - commonly know as restitution coefficient I think XD
			l_Vx = a_obj->GetVX();
			l_Vy = a_obj->GetVY();
			a_obj->SetVX ( l_Vx * a_obj->Elasticity );
			a_obj->SetVY ( l_Vy * a_obj->Elasticity );
			a_obj->collision = true;
			return(1);
		}
		return(0);
	}

	// factor in any impulses added into the system for x direction
	const GLfloat PhysicsSystem::CalulateEnvironmentXAcceleration() {
		return 0.0;
		//return -m_GravityInPixels;//0.0;
	}

	// factor in any impulses added into the system for x direction
	const GLfloat PhysicsSystem::CalulateEnvironmentYAcceleration() {
		return m_GravityInPixels;
	}

	/// @warning This function usually gets classes derived from Sprite instead of Sprites. This seems to give some problems... -> correction: It seems the problem is rather in change of Player address when doing push_back. cf AddPlayer()
	int PhysicsSystem::AddObject ( gp2d::Sprite* a_Sprite ) {
// 		m_PhysicalObjects[ m_NumObjectsInSystem ] = a_Sprite;

		int N;
		if ( m_PhysicalObjects.empty() ) N=0;
		else N= ( m_PhysicalObjects.rbegin() )->first+1;
		m_PhysicalObjects[N]=a_Sprite;

		m_NumObjectsInSystem++;
		cout<<"[PhysicsSystem::AddObject]m_NumObjectsInSystem="<<m_NumObjectsInSystem<<endl;
		return(N);
	}

	//FIXME: I don't think it will work like this...
	void PhysicsSystem::RemoveObject( int id ) {
		m_PhysicalObjects.erase(id);
		m_NumObjectsInSystem--;
		cout<<"[PhysicsSystem::RemoveObject]m_NumObjectsInSystem="<<m_NumObjectsInSystem<<endl;
	}

	void PhysicsSystem::AddImpulse (
	    PhysicalImpulse* a_Impulse
	) {
		if ( m_ImpulseCount < PHYSIC_MAX_OBJECTS ) {
			m_EnvironmentalForces[ m_ImpulseCount ] = a_Impulse;
			m_ImpulseCount++;
		}
	}

}//end of namespace iteam
