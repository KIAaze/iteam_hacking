#include "globals.h"
#include "WeaponComponent.h"
#include "primitives.h"
#include "explosions.h"
// #include "Weapon.h"
#include "weapons.h"
#include "iteam_maths.h"
#include <assert.h>

namespace iteam {

	//constructor
	// initialise the weapon
	WeaponComponent::WeaponComponent() {
		m_TriggerTime = 0;
		// Name="";//to avoid segfaulting when drawing name (default behaviour)
		acceleration = 0;
		Elasticity = 0;
		strcpy ( Name, "New Component" );
	}

	WeaponComponent::WeaponComponent (
	    char* a_Name			/**< Weapon's name. */
	    , bool a_Active		/**< Is the weapon active? */
	    , bool a_IsController
	    , int a_TypeID
	    , GLfloat a_BlastRadius /**< how big of a boom does it make? */
	    , GLfloat a_BlastFactor /**< how much blast does it apply to objects? */
	    , GLfloat a_BlastDamage /**< how much damage does it make? */
	    , int a_TriggerTime 	/**< how many ticks do we wait to blowup? */
	    , int a_StartTicks		/**< when did we start counting? */
	    , bool a_Bounces		/**< can this weapon bounce of things? */
	    , int a_WeaponID
	    , bool a_Visible
	) {
		x = 0;
		y = 0;
		vx = 0;
		vy = 0;
		strcpy ( Name, a_Name );		/**< Weapon's name. */
		Active = a_Active;			/**< Is the weapon active? */
		IsController = a_IsController;
		TypeID = a_TypeID;

		//special variables
		BlastRadius = a_BlastRadius; /**< how big of a boom does it make? */
		BlastFactor = a_BlastFactor; /**< how much blast does it apply to objects? */
		BlastDamage = a_BlastDamage; /**< how much damage does it make? */

		m_TriggerTime = a_TriggerTime;	/**< how many ticks do we wait to blowup? */
		StartTicks = a_StartTicks;		/**< when did we start counting? */
		Bounces = a_Bounces;		/**< can this weapon bounce of things? */
		m_WeaponID = a_WeaponID;
		Visible = a_Visible;
	}

	// ...and stolen again from mickey's code ^^
	// stolen from DARKGuys code hehe!
	void WeaponComponent::DrawName() {
		//printf("Name=%s\n",Name);exit(0);
		Text ( iteam::Font[2], ( GetX() + ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-18, ( GetY() + ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-48, 0,1,1,1, 0.1,0.1,0.1, Name );
		Text ( iteam::Font[2], ( GetX() + ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-20, ( GetY() + ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-50, 0,1,1,1,   1,  1,  1, Name );
	}

	double WeaponComponent::orientate() {
		angle=rad2deg ( atan2 ( GetVY(),GetVX() ) );//no need to take the opposite angle here since vx,vy,angle all follow SDL standards
		return ( -angle );
	}

	void WeaponComponent::SetBeginPosition ( GLfloat nx, GLfloat ny ) {
		SetX ( nx );
		SetY ( ny );
	}

	// Set the initial velocity of the projectile (easier and more precise than setting the force=mass*acceleration ;) )
	void WeaponComponent::SetVelocity ( GLfloat new_vel, GLfloat new_angle ) {
		SetVX ( new_vel * ( GLfloat ) cos ( new_angle*M_PI/180 ) );
		SetVY ( new_vel * ( GLfloat ) sin ( new_angle*M_PI/180 ) * -1 );
	}


	int WeaponComponent::BlastObjects() {
		for ( int i=0;i < Player.size();i++ ) {
			GLfloat distance=DistanceBetween ( x,y,Player[i].GetX(),Player[i].GetY() );
			if ( 0<distance && distance<BlastRadius ) { //we avoid division by zero

				Player[i].SetVX ( BlastFactor*BlastRadius/distance* ( Player[i].GetX()-x ) /distance );
				Player[i].SetVY ( BlastFactor*BlastRadius/distance* ( Player[i].GetY()-y ) /distance );
				Player[i].Health-= ( int ) ( BlastDamage*BlastRadius/ ( GLfloat ) distance );
			}
		}
		/* NOTE: this function should really be passing a set of values to a unified physics system and letting
		that system move the object based on its own records */

		return ( 0 );
	}


	void WeaponComponent::DestroyTerrain() {

		GLfloat tempX, tempY;
		SDL_Surface * surf;
		surf = Level[0].animationSheet[0].spriteTexture->imgF;
		assert ( surf != NULL );
		// Find position relative to the image we want to change
		tempX = ( Level[0].width[0]/2 )- ( VIEWPORT_WIDTH/2 ) + x;
		tempY = y - ( VIEWPORT_HEIGHT - Level[0].height[0] );

		DrawCircleFilled ( tempX, tempY, ( int ) BlastRadius, surf, 0x00FFFFFF );
		printf ( "%d\n",EXPLOSION_HALO_WIDTH );
		DrawCircleHalo ( tempX, tempY, ( int ) BlastRadius + EXPLOSION_HALO_WIDTH, surf, 0x00FFFFFF );
		Level[0].animationSheet[0].spriteTexture->Modify ( surf );
		//start explosion animation
		TriggerExplosion ( Explosion_Texture[0], x , y, BlastRadius );
	}

	int WeaponComponent::Fire (
	    GLfloat nx
	    , GLfloat ny
	    , GLfloat new_angle
	    , GLfloat new_vel
	    , GLfloat a_TriggerTime
	) {

		int l_Ticks = GameTimer[0].GetTicks();
		SetX ( nx );
		SetY ( ny );
		// SetBeginPosition( nx, ny); // start by placing the weapon at the players location
		SetVelocity ( new_vel, new_angle ); // Set the initial speed and direcion
		LastTicks = l_Ticks; // used for frame rate limiting the physics code
		StartTicks = l_Ticks; // used for timed explosions
		m_TriggerTime = ( int ) a_TriggerTime * 1000;
		SetActive();//deactivate all component

	}

} // end namespace

