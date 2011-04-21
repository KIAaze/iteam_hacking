#include "globals.h"
#include "Weapon.h"
#include "primitives.h"
#include "Explosion.h"
#include "iteam_maths.h"
#include "physics.h"
#include "SpriteMap.h"
#include <assert.h>
#include <iostream>

#define GRENADETIME 5000

namespace iteam {

	//constructor
	// initialise the weapon
	Weapon::Weapon() : Sprite() {
		//general variables
// 		strcpy ( Name, "New Component" );
		Active=true;
		IsController=true;
		TypeID=0;

		//special variables
		BlastRadius=60;
		BlastFactor=100;
		BlastDamage=10;
		StartTicks=GameTimer[0].GetTicks();
		LastTicks=0;
		Bounces=true;
		m_WeaponID=0;
		Visible=true;
		m_target=0;

		m_TriggerTime = GRENADETIME;
		//acceleration = 0;
		sprintf(Name,"Generic weapon");//to avoid segfaulting when drawing name (default behaviour)
	}

	Weapon::Weapon ( const char texture[], int numSpritesWide, int numSpritesHigh) : Sprite(texture,numSpritesWide,numSpritesHigh) {
		//general variables
// 		strcpy ( Name, "New Component" );
		Active=true;
		IsController=true;
		TypeID=0;

		//special variables
		BlastRadius=60;
		BlastFactor=100;
		BlastDamage=10;
		m_TriggerTime = GRENADETIME;
		StartTicks=GameTimer[0].GetTicks();
		LastTicks=0;
		Bounces=true;
		m_WeaponID=0;
		Visible=true;
		m_target=0;

		sprintf ( Name, "%d", m_TriggerTime/1000 );

		//acceleration = 0;
		// Name="";//to avoid segfaulting when drawing name (default behaviour)
		//Elasticity = 0;
	}

	Weapon::Weapon ( Texture* tex, int numSpritesWide, int numSpritesHigh) : Sprite(tex,numSpritesWide,numSpritesHigh) {
		//general variables
// 		strcpy ( Name, "New Component" );
		Active=true;
		IsController=true;
		TypeID=0;

		//special variables
		BlastRadius=60;
		BlastFactor=100;
		BlastDamage=10;
		m_TriggerTime = GRENADETIME;
		StartTicks=GameTimer[0].GetTicks();
		LastTicks=0;
		Bounces=true;
		m_WeaponID=0;
		Visible=true;
		m_target=0;

		sprintf ( Name, "%d", m_TriggerTime/1000 );

		//acceleration = 0;
		// Name="";//to avoid segfaulting when drawing name (default behaviour)
		//Elasticity = 0;
	}

	// ...and stolen again from mickey's code ^^
	// stolen from DARKGuys code hehe!
	void Weapon::DrawName() {
		//printf("Name=%s\n",Name);exit(0);
		Text ( iteam::Font[2], ( GetX() + ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-18, ( GetY() + ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-48, 0,1,1,1, 0.1,0.1,0.1, Name );
		Text ( iteam::Font[2], ( GetX() + ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-20, ( GetY() + ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-50, 0,1,1,1,   1,  1,  1, Name );
	}

	double Weapon::orientate() {
		angle=rad2deg ( atan2 ( GetVY(),GetVX() ) );//no need to take the opposite angle here since vx,vy,angle all follow SDL standards
		return ( -angle );
	}

	void Weapon::SetBeginPosition ( GLfloat nx, GLfloat ny ) {
		SetX ( nx );
		SetY ( ny );
	}

	// Set the initial velocity of the projectile (easier and more precise than setting the force=mass*acceleration ;) )
	void Weapon::SetVelocity ( GLfloat new_vel, GLfloat new_angle ) {
		SetVX ( new_vel * ( GLfloat ) cos ( new_angle*M_PI/180 ) );
		SetVY ( new_vel * ( GLfloat ) sin ( new_angle*M_PI/180 ) * -1 );
	}

	int Weapon::BlastObjects(SpriteMap &a_map) {
		for ( SpriteMap::iterator it=a_map.begin(); it!=a_map.end(); it++ )
		{
			GLfloat distance=DistanceBetween ( this->GetX(),this->GetY(),(*it).second->GetX(),(*it).second->GetY() );
			if ( 0<distance && distance<BlastRadius ) { //we avoid division by zero

				(*it).second->SetVX(BlastFactor*BlastRadius/distance* ( (*it).second->GetX()-x ) /distance);
				(*it).second->SetVY(BlastFactor*BlastRadius/distance* ( (*it).second->GetY()-y ) /distance);
				(*it).second->m_integrity-= ( int ) ( BlastDamage*BlastRadius/ ( GLfloat ) distance );
			}
		}
		return ( 0 );
	}


	void Weapon::DestroyTerrain() {
		GenericDestroyTerrain(&(Level[0]),this->GetX(),this->GetY(),BlastRadius,5);
		int N=Add( supermap, new Explosion(Explosion_Texture[0], 4, 4 , BlastRadius) );
		supermap[N]->SetX ( this->GetX() );
		supermap[N]->SetY ( this->GetY() );
// 		AddExplosion ( Explosion_Texture[0], this->GetX() , this->GetY(), BlastRadius );
	}

	int Weapon::Fire (GLfloat nx, GLfloat ny, GLfloat new_angle, GLfloat new_vel) {
		int l_Ticks = GameTimer[0].GetTicks();
		SetX ( nx );
		SetY ( ny );
		SetVelocity ( new_vel, new_angle ); // Set the initial speed and direcion
		LastTicks = l_Ticks; // used for frame rate limiting the physics code
		StartTicks = l_Ticks; // used for timed Explosions
		return(0);
	}

	int Weapon::DoBehaviour () {
			this->setNextFrame();//necessary for animation
			int l_Ticks = GameTimer[0].GetTicks() - StartTicks;
			// is it time to explode yet?
			if ( l_Ticks > m_TriggerTime ) {
				sprintf ( Name, "%d", 0 );
				// yes ... Fire in the hole!
				BlastObjects(supermap);
				DestroyTerrain();
// 				SetInactive();
				//m_PhysicsSystem->RemoveObject();
// 				Active = false;
				//m_Player->HasFired = false;
				return(1);
			} else {
				// Nope so update seconds counter above Weapon
				sprintf ( Name, "%d", 1 + ( m_TriggerTime - l_Ticks ) / 1000 );
				return(0);
			}
	}

	int Weapon::Render(gp2d::Camera Cam)
	{
		Cam.Begin();
		this->DrawFrame();
		this->DrawName();
		Cam.End();
		return(0);
	}

} // end namespace

