/*! \file weapons.cpp
\brief weapon class
*/

#include "weapons.h"
#include "globals.h"
#include "players.h"
#include "iteam_maths.h"
#include "primitives.h"
#include "explosions.h"
#include <iostream>
#include <stdio.h>

// ====================== GLOBALS =============================

namespace iteam	{

//==============================================
//copy constructors
//weapon::weapon(const weapon &){}
//weapon & operator = (const weapon &);
//IT_Weapon::IT_Weapon(const IT_Weapon &){}
//IT_Weapon & operator = (const IT_Weapon &);
//==============================================

	IT_Weapon::IT_Weapon() :gp2d::Sprite() {}

// //copy constructor
// IT_Weapon::IT_Weapon(const IT_Weapon& IT_Weapon_)
// {
// }
// //assignment operator
// IT_Weapon& IT_Weapon::operator=(const IT_Weapon& IT_Weapon_)
// {
// 	//IT_Weapon(IT_Weapon_);
// }
// //destructor
// IT_Weapon::~IT_Weapon()
// {
// }

	vector <iteam::IT_Weapon> WeaponsList;

	char str[30];

	GLfloat WeaponStrength = 500.0;
	GLfloat WeaponAngle = 90;
	GLfloat Gravity = IT_GRAVITY_DEFAULT;
	int grenade_time = IT_WT_GRENADE_TIME_DEFAULT;
	int dynamite_time = IT_WT_DYNAMITE_TIME_DEFAULT;

	bool first_move=false;

// ====================== WEAPONS =============================

//constructor
// initialise the weapon
	weapon::weapon()	{
		strcpy ( Name,"" );//to avoid segfaulting when drawing name (default behaviour)
		Active=false;
		fire_angle=0;
		GLfloat movement_angle=0;
		GLfloat BlastRadius=0;
		GLfloat BlastFactor=0;
		GLfloat BlastDamage=0;
		TimeTrigger=0;
		StartTicks=0;
		Bounces=true;
		WeaponID=0;
		Visible=false;
		vel_x=0;
		vel_y=0;
		velocity=0;
		accel_x=0;
		accel_y=0;
		acceleration=0;
		LastTicks=0;
		delta_time=0;
		IsPhysical=false;
		Elasticity=0;
		obj_accel_x=0;
		obj_accel_y=0;
	}

// //destructor
// //free memory
// weapon::~weapon()
// {
// }

// ...and stolen again from mickey's code ^^
// stolen from DARKGuys code hehe!
	void weapon::DrawName() {
		//printf("this->Name=%s\n",this->Name);exit(0);
		Text ( iteam::Font[2], ( this->x+ ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-18, ( this->y+ ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-48, 0,1,1,1, 0.1,0.1,0.1, this->Name );
		Text ( iteam::Font[2], ( this->x+ ( VIEWPORT_WIDTH/2 )-Cam.GetX() )-20, ( this->y+ ( VIEWPORT_HEIGHT/2 )-Cam.GetY() )-50, 0,1,1,1,   1,  1,  1, this->Name );
	}

	double weapon::orientate() {
		angle=rad2deg ( atan2 ( vel_y,vel_x ) );//no need to take the opposite angle here since vel_x,vel_y,angle all follow SDL standards
		movement_angle=-angle;//movement_angle follows iteam standards
		return ( movement_angle );
	}

// ==================== WEAPON CLUSTERS =========================

	void AddWeaponTypeToWeaponList ( GLfloat px, GLfloat py, int TypeID, Texture *thumb )	{
		// add this weapon to the cluster
		WeaponsList.push_back ( IT_Weapon() ); 	// add a new weapon type to the weapons list
		WeaponsList[WeaponsList.size()-1].TypeID = TypeID;
		WeaponsList[WeaponsList.size()-1].Active = false;
		WeaponsList[WeaponsList.size()-1].Load ( thumb );  // load thumbnail for display on the gui
		WeaponsList[WeaponsList.size()-1].offset_x = px;
		WeaponsList[WeaponsList.size()-1].offset_y = py;
		WeaponsList[WeaponsList.size()-1].Move ( Cam.GetX() + px,Cam.GetY() + py );
	}

	void AddComponent ( int WeaponID, int TypeID, Texture *texture, bool IsPhysical, bool Bounces, GLfloat BlastRadius, GLfloat BlastFactor, GLfloat BlastDamage, GLfloat Elasticity, int TriggerTime, bool Active, GLfloat scale )	{

		WeaponsList[TypeID].components.push_back ( weapon() );	// add a new component to the weapons type
		//cout << "[WEAPONS] Adding texture\n";
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Load ( texture );
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Scale ( scale );
		//cout << "[WEAPONS] Added texture " << texture << "\n";
		// set the main values for this conponent
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].WeaponID = WeaponID;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Visible = false;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].IsPhysical = IsPhysical;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].BlastRadius = BlastRadius;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].BlastFactor = BlastFactor;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].BlastDamage = BlastDamage;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Bounces = Bounces;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Elasticity = Elasticity;
		printf ( "TriggerTime=%d\n",TriggerTime );
		//exit(0);
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].TimeTrigger = TriggerTime * 1000; // multiply by 1000 to get time in miliseconds
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].col_x[0]= ( 32/2 )-4;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].col_y[0]=8;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].col_width[0]=20;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].col_height[0]=32-8;
		WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Active=Active;
	}

// ==================== WEAPON FUNCTIONS ========================

	int FireWeapon ( int TypeID, GLfloat nx, GLfloat ny, GLfloat new_angle, GLfloat new_vel )	{
		int i;
		WeaponsList[TypeID].Active = true;
		//cout << "[FIRE WEAPON] TypeID = " << TypeID << "\n";
		//cout << "[WEAPONS] x = " << nx << " y = " << ny << " angle= " << new_angle << " velocity = " << new_vel << "\n";
		for ( i=0; i < WeaponsList[TypeID].components.size(); i++ )	{
			// cout << "[FIRE WEAPON] TypeID = " << TypeID << "\n";
			WeaponsList[TypeID].components[i].SetBeginPosition ( nx, ny ); // start by placing the weapon at the players location
			WeaponsList[TypeID].components[i].SetVelocity ( new_vel, new_angle ); // Set the initial speed and direcion
			WeaponsList[TypeID].components[i].LastTicks = Timer[0].GetTicks(); // used for frame rate limiting the physics code
			WeaponsList[TypeID].components[i].StartTicks = Timer[0].GetTicks(); // used for timed explosions
			WeaponsList[TypeID].components[i].Active=false;//deactivate all components
		}
		WeaponsList[TypeID].components[0].Active=true;//activate first component
		return ( 0 );
	}

	int FireComponent ( int TypeID, int CompID, GLfloat nx, GLfloat ny, GLfloat vel_x, GLfloat vel_y )	{
		WeaponsList[TypeID].components[ CompID ].Active=true;//activate component
		//cout << "[FIRE WEAPON] TypeID = " << TypeID << "\n";
		//cout << "[WEAPONS] x = " << nx << " y = " << ny << " angle= " << new_angle << " velocity = " << new_vel << "\n";
		// cout << "[FIRE WEAPON] TypeID = " << TypeID << "\n";
		WeaponsList[TypeID].components[ CompID ].SetBeginPosition ( nx, ny ); // start by placing the weapon at the players location
		WeaponsList[TypeID].components[ CompID ].vel_x=vel_x;
		WeaponsList[TypeID].components[ CompID ].vel_y=vel_y;
		WeaponsList[TypeID].components[ CompID ].LastTicks = Timer[0].GetTicks(); // used for frame rate limiting the physics code
		WeaponsList[TypeID].components[ CompID ].StartTicks = Timer[0].GetTicks(); // used for timed explosions
		return ( 0 );
	}

// ==================== INITIALIZATION FUNCTIONS ============================

	void Weapons_Init ( void )	{
		// ============================ GRENADES ===========================================
		AddWeaponTypeToWeaponList ( THUMBS_WIDTH + IT_WT_GRENADE*34, 600 - THUMBS_HEIGHT, IT_WT_GRENADE, Weapon_Texture[0] );
		AddComponent ( 0, IT_WT_GRENADE, Weapon_Texture[0], true, true, ( GLfloat ) IT_WT_GRENADE_BLAST_RADIUS,IT_WT_GRENADE_BLAST_FACTOR,IT_WT_GRENADE_BLAST_DAMAGE, ( GLfloat ) 0.0, grenade_time );

		// ============================ MISSILES ============================================
		AddWeaponTypeToWeaponList ( THUMBS_WIDTH + IT_WT_MISSILE*34, 600 - THUMBS_HEIGHT, IT_WT_MISSILE, Weapon_Texture[1] );
		AddComponent ( 0, IT_WT_MISSILE, Weapon_Texture[1], true, true, ( GLfloat ) IT_WT_MISSILE_BLAST_RADIUS,IT_WT_MISSILE_BLAST_FACTOR,IT_WT_MISSILE_BLAST_DAMAGE, ( GLfloat ) 0, 0 );

		// ============================ CLUSTER BOMBS =======================================
		AddWeaponTypeToWeaponList ( THUMBS_WIDTH + IT_WT_CLUSTERBOMB*34, 600 - THUMBS_HEIGHT, IT_WT_CLUSTERBOMB, Weapon_Texture[2] );
		AddComponent ( 0, IT_WT_CLUSTERBOMB, Weapon_Texture[0], true, true, ( GLfloat ) IT_WT_CLUSTERBOMB_BLAST_RADIUS,IT_WT_CLUSTERBOMB_BLAST_FACTOR,IT_WT_CLUSTERBOMB_BLAST_DAMAGE, ( GLfloat ) 0.80, grenade_time, true );//main grenade active at first
		for ( int i=1;i<9;i++ ) { //add baby grenades
			AddComponent ( i, IT_WT_CLUSTERBOMB, Weapon_Texture[0], true, true, ( GLfloat ) IT_WT_CLUSTERBOMB_BLAST_RADIUS,IT_WT_CLUSTERBOMB_BLAST_FACTOR,IT_WT_CLUSTERBOMB_BLAST_DAMAGE, ( GLfloat ) 0.80, grenade_time, false, 0.5 );//inactive at first
		}

		// ============================ DYNAMITE ===========================================
		AddWeaponTypeToWeaponList ( THUMBS_WIDTH + IT_WT_DYNAMITE*34, 600 - THUMBS_HEIGHT, IT_WT_DYNAMITE, Weapon_Texture[3] );
		AddComponent ( 0, IT_WT_DYNAMITE, Weapon_Texture[3], true, true, ( GLfloat ) IT_WT_DYNAMITE_BLAST_RADIUS,IT_WT_DYNAMITE_BLAST_FACTOR,IT_WT_DYNAMITE_BLAST_DAMAGE, ( GLfloat ) 0, dynamite_time );

		// ============================ PISTOL ===========================================
		AddWeaponTypeToWeaponList ( THUMBS_WIDTH + IT_WT_PISTOL*34, 600 - THUMBS_HEIGHT, IT_WT_PISTOL, Weapon_Texture[4] );
	}

	//use of this function unclear
	//FireWeapon might be enough
	void Weapons_Fire ( GLfloat angle, GLfloat Speed, int TypeID )	{
		int retval;
		switch ( TypeID )	{
			case IT_WT_GRENADE:
				// bouncy fun fun fun!
				retval = FireWeapon ( TypeID, Player[CurPlayer].x, Player[CurPlayer].y, angle, Speed );
				break;
			case IT_WT_MISSILE:
				//soon to be heat seeking! (including your own heat :p)
				retval = FireWeapon ( TypeID, Player[CurPlayer].x, Player[CurPlayer].y, angle, 100 );//fixed initial speed needed to avoid shooting into the ground
				break;
			case IT_WT_CLUSTERBOMB:
				// multi bouncy fun fun fun!
				retval = FireWeapon ( TypeID, Player[CurPlayer].x, Player[CurPlayer].y, angle, Speed );
				break;
			case IT_WT_DYNAMITE:
				// just drop this sucker and run!
				retval = FireWeapon ( TypeID, Player[CurPlayer].x, Player[CurPlayer].y, angle, 2 );
				break;
		}
	}

// ====================

	void UpdateWeaponThumbs ( void )	{
		int i;

		for ( i=0; i < WeaponsList.size(); i++ )	{
			Cam.Begin();
			WeaponsList[i].Move ( Cam.GetX() + - ( VIEWPORT_WIDTH/2 ) + WeaponsList[i].offset_x,Cam.GetY() - ( VIEWPORT_HEIGHT/2 ) + WeaponsList[i].offset_y );
			WeaponsList[i].Draw();
		}
	}

	void DoWeaponBehaviours ( int TypeID, int CompID,int collision )	{
		int newTicks;
		GLfloat distance;
		GLfloat tempX, tempY;
		SDL_Surface * surf;

		switch ( TypeID )	{
				// ==========================================================================================
				// ================================ GRENADES ==================================================
				// ==========================================================================================
			case IT_WT_GRENADE:
				newTicks =  Timer[0].GetTicks() - WeaponsList[TypeID].components[0].StartTicks;
				if ( newTicks > WeaponsList[TypeID].components[0].TimeTrigger )	{  // time trigger reached! go BOOOOOOM!

					// apply blast to all physical objects
					WeaponsList[TypeID].components[0].BlastObjects();
					// destroy terrain
					DestroyTerrain ( TypeID, 0 );
					// deactivate weapon
					WeaponsList[TypeID].Active = false;

				}
				else {
					sprintf ( WeaponsList[TypeID].components[0].Name, "%d",1+ ( WeaponsList[TypeID].components[0].TimeTrigger - newTicks ) / 1000 );
				}
				break;
				// ==========================================================================================
				// ================================   MISSILES  ==================================================
				// ==========================================================================================
			case IT_WT_MISSILE:
				// orientate missile according to its direction
				WeaponsList[TypeID].components[0].orientate();
				//apply acceleration from the missile engine
				WeaponsList[TypeID].components[0].SetAcceleration ( IT_WT_MISSILE_ACCEL,WeaponsList[TypeID].components[0].movement_angle );

				// explode on impact with terrain
				//to explode on impact with sprites, we'll need a loop, maybe create a any_collision function. Careful with player collision at start... ^^
				if ( /*CollisionPixel(&(WeaponsList[TypeID].components[0]),&Terrain,0,0)*/collision ) {

					// apply blast to all physical objects
					WeaponsList[TypeID].components[0].BlastObjects();
					// destroy terrain
					DestroyTerrain ( TypeID, 0 );
					// deactivate weapon
					WeaponsList[TypeID].Active = false;
				}
				break;

				// ==========================================================================================
				// ================================ CLUSTER BOMB ===============================================
				// ==========================================================================================
			case IT_WT_CLUSTERBOMB:
				/*				printf("active clusterbombs:");
								for ( int i=0;i<9;i++ )
									printf ( "%d",WeaponsList[TypeID].components[i].Active );
								printf ( "\n" );*/
				newTicks =  Timer[0].GetTicks() - WeaponsList[TypeID].components[CompID].StartTicks;
				if ( newTicks > WeaponsList[TypeID].components[CompID].TimeTrigger )	{  // time trigger reached! go BOOOOOOM!

					//destroy the terrain
					DestroyTerrain ( TypeID, CompID );
					//activate baby components
					if ( CompID==0 ) {
						for ( int i=1;i<9;i++ ) {
							double ang = deg2rad ( rand_uniform ( 0,360 ) );
							double dist = 0.5*WeaponsList[TypeID].components[0].BlastRadius;
							FireComponent ( TypeID, i, WeaponsList[TypeID].components[0].x+dist*cos ( ang ), WeaponsList[TypeID].components[0].y+dist*sin ( ang ), 0, 0 );
						}
					}
					// apply blast to all physical objects
					WeaponsList[TypeID].components[CompID].BlastObjects();
					//deactivate component
					WeaponsList[TypeID].components[CompID].Active = false;
				}
				else {
					sprintf ( WeaponsList[TypeID].components[CompID].Name, "%d",1+ ( WeaponsList[TypeID].components[CompID].TimeTrigger - newTicks ) / 1000 );
				}
				break;

				// ==========================================================================================
				// ================================ DYNAMITE ===================================================
				// ==========================================================================================
			case IT_WT_DYNAMITE:
				newTicks =  Timer[0].GetTicks() - WeaponsList[TypeID].components[0].StartTicks;
				if ( newTicks > WeaponsList[TypeID].components[0].TimeTrigger )	{  // time trigger reached! go BOOOOOOM!

					// apply blast to all physical objects
					WeaponsList[TypeID].components[0].BlastObjects();
					// destroy terrain
					DestroyTerrain ( TypeID, 0 );
					// deactivate weapon
					WeaponsList[TypeID].Active = false;

				}
				else {
					sprintf ( WeaponsList[TypeID].components[0].Name, "%d",1+ ( WeaponsList[TypeID].components[0].TimeTrigger - newTicks ) / 1000 );
				}
				break;
		}//end of switch
	}//end of DoWeaponBehaviours

	int weapon::BlastObjects() {
		for ( int i=0;i<=Player.size()-1;i++ ) {
			GLfloat distance=DistanceBetween ( x,y,Player[i].x,Player[i].y );
			if ( 0<distance && distance<BlastRadius ) { //we avoid division by zero
				cout<<"Player["<<i<<"].vX="<<BlastFactor*BlastRadius/distance* ( Player[i].x-x ) /distance<<endl;
				cout<<"Player["<<i<<"].vY="<<BlastFactor*BlastRadius/distance* ( Player[i].y-y ) /distance<<endl;
				cout<<"Player["<<i<<"].Health-="<< ( int ) ( BlastDamage*BlastRadius/ ( GLfloat ) distance ) <<endl;

				Player[i].vX=BlastFactor*BlastRadius/distance* ( Player[i].x-x ) /distance;
				Player[i].vY=BlastFactor*BlastRadius/distance* ( Player[i].y-y ) /distance;
				Player[i].Health-= ( int ) ( BlastDamage*BlastRadius/ ( GLfloat ) distance );
			}
		}
		for ( int i=0; i < WeaponsList.size(); i++ ) {
			if ( WeaponsList[i].Active == true ) {
				for ( int j=0; j < WeaponsList[i].components.size(); j++ ) {
					GLfloat distance=DistanceBetween ( x,y,WeaponsList[i].components[j].x,WeaponsList[i].components[j].y );
					if ( 0<distance && distance<BlastRadius ) { //we avoid division by zero
						cout<<"weapon["<<i<<"]["<<j<<"].vel_x="<<BlastFactor*BlastRadius/distance* ( WeaponsList[i].components[j].x-x ) /distance<<endl;
						cout<<"weapon["<<i<<"]["<<j<<"].vel_y="<<BlastFactor*BlastRadius/distance* ( WeaponsList[i].components[j].y-y ) /distance<<endl;

						WeaponsList[i].components[j].vel_x=BlastFactor*BlastRadius/distance* ( WeaponsList[i].components[j].x-x ) /distance;
						WeaponsList[i].components[j].vel_y=BlastFactor*BlastRadius/distance* ( WeaponsList[i].components[j].y-y ) /distance;
					}
				}
			}
		}
		return ( 0 );
	}

	void DestroyTerrain ( int TypeID, int ComponentID )	{

		cout<<"===DESTROY TERRAIN==="<<endl;
		GLfloat tempX, tempY;
		SDL_Surface * surf;
		surf = Level[0].animationSheet[0].spriteTexture->imgF;
		// Find position relative to the image we want to change
		tempX = ( Level[0].width[0]/2 )- ( VIEWPORT_WIDTH/2 ) + WeaponsList[TypeID].components[ComponentID].x;
		tempY = WeaponsList[TypeID].components[ComponentID].y - ( VIEWPORT_HEIGHT - Level[0].height[0] );

//		circleColor ( surf,tempX, tempY, ( int ) WeaponsList[TypeID].components[ComponentID].BlastRadius, 0xFFFFFFFF );


		Draw_filledCircleRGBA ( surf,tempX,tempY, ( int ) WeaponsList[TypeID].components[ComponentID].BlastRadius,  0,0,0,0,false,true );
		Draw_filledCircleRGBA ( surf,tempX,tempY, ( int ) WeaponsList[TypeID].components[ComponentID].BlastRadius + EXPLOSION_HALO_WIDTH, 0,0,0,128,true,true );

		Level[0].animationSheet[0].spriteTexture->Modify ( surf );
		SDL_FreeSurface ( surf );//we free this surface because it has already been copied
//		SDL_SaveBMP(Level[0].animationSheet[0].spriteTexture->imgF,"destruction.bmp");

		//start explosion animation
		TriggerExplosion ( Explosion_Texture[0], WeaponsList[TypeID].components[ComponentID].x , WeaponsList[TypeID].components[ComponentID].y, WeaponsList[TypeID].components[ComponentID].BlastRadius );
		cout<<"===DESTROY TERRAIN END==="<<endl;
	}

//not yet used
	void UpdateWeaponObjects ( void )	{
		exit ( 0 );
		// update any active weapons
		int i,j;
		// cout << "[WEAPON PHYSICS] WeaponList is " << WeaponsList.size() << " items long\n";
		for ( i=0; i < WeaponsList.size(); i++ )	{	// loop through each weapon in list and test if its active
			// cout << "[WEAPON PHYSICS] Weapon " << i << " searched\n";
			if ( WeaponsList[i].Active == true )	{	// seems to be active so process the componets
				for ( j=0; j < WeaponsList[i].components.size(); j++ )	{ // move each component
					// cout << "[WEAPON PHYSICS] Weapon " << i << " is active\n";
					WeaponsList[i].components[j].CalculateVelocity();
					WeaponsList[i].components[j].MoveMe();
					DoWeaponBehaviours ( i,j );
					Cam.Begin();

					WeaponsList[i].components[j].Draw();
					WeaponsList[i].components[j].DrawName();
					//cout << "[WEAPON PHYSICS] x = " << WeaponsList[i].components[j].x << " y = " << WeaponsList[i].components[j].y << "\n";
				}
			}
		}
		// this may include any players eventually as all moving things
		// in the scene will be reacting to gravity etc.
	}

//==============================================================
//PHYSICS ENGINE
//==============================================================

	void weapon::SetBeginPosition ( GLfloat nx, GLfloat ny )	{
		x = nx;
		y = ny;
		accel_x = 0;
		accel_y = 0;
		//angle = new_angle;
		//cout << "[WEAPONS COORDS] x = " << x << " y = " << y << " angle = " << angle << "\n";
	}

// Set the initial velocity of the projectile (easier and more precise than setting the force=mass*acceleration ;) )
	void weapon::SetVelocity ( GLfloat new_vel, GLfloat new_angle ) {
		cout<<"SetVelocity: delta_time="<<delta_time<<endl;

		//adapt class members
		velocity = new_vel;
		movement_angle=new_angle;

		vel_x = velocity * ( GLfloat ) cos ( new_angle*M_PI/180 );
		vel_y = velocity * ( GLfloat ) sin ( new_angle*M_PI/180 ) * -1;
	}

// apply a force for the acceleration of the projectile
	void weapon::SetAcceleration ( GLfloat new_accel, GLfloat new_angle )	{
		obj_accel_x = new_accel * ( GLfloat ) cos ( new_angle*M_PI/180 );
		obj_accel_y = new_accel * ( GLfloat ) sin ( new_angle*M_PI/180 ) * -1;
	}

	void weapon::CalculateVelocity ( void )	{
		vel_x += GetDelta ( accel_x, delta_time );
		vel_y += GetDelta ( accel_y, delta_time );
	}

//to calculate things like friction (IT_FRICTION)
	void weapon::CalculateAcceleration ( void ) {
		accel_x=obj_accel_x;
		accel_y=obj_accel_y+Gravity;
		/*		cout<<"after CalculateAcceleration"<<endl;
				cout<<"obj_accel_x="<<obj_accel_x<<endl;
				cout<<"obj_accel_y="<<obj_accel_y<<endl;
				cout<<"accel_x="<<accel_x<<endl;
				cout<<"accel_y="<<accel_y<<endl;*/
	}

	int weapon::MoveMe ( void )	{
		GLfloat advance_x, advance_y;
		if ( first_move ) { //for debugging
			cout<<"vel_x="<<vel_x<<endl;
			cout<<"vel_y="<<vel_y<<endl;
			cout<<"sqrt(vel_x*vel_x+vel_y*vel_y)="<<sqrt ( vel_x*vel_x+vel_y*vel_y ) <<endl;
			first_move=false;
		}

		advance_x = GetDelta ( vel_x, delta_time );
		advance_y = GetDelta ( vel_y, delta_time );
		x += advance_x;
		y += advance_y;

		GLfloat Nx,Ny,Tx,Ty;
		//if (CollisionPixel(this,&Terrain,0,0)) {
		if ( CollisionPixel_2 ( this,& ( Level[0] ),0,0,Nx,Ny,Tx,Ty ) ) {
			x -= advance_x;
			y -= advance_y;
			/*			cout<<"================="<<endl;
						cout<<"before reflection"<<endl;
						cout<<Nx<<","<<Ny<<endl;
						cout<<vel_x<<","<<vel_y<<endl;*/
			N_reflect_vector ( Nx,Ny,vel_x,vel_y,vel_x,vel_y );
			/*			cout<<"after reflection"<<endl;
						cout<<vel_x<<","<<vel_y<<endl;
						cout<<"================="<<endl;*/
			if ( IsPhysical )	{
				// remove some of the bounce - commonly know as restitution coefficient I think XD
				vel_x = vel_x * Elasticity;
				vel_y = vel_y * Elasticity;

			}
			//we need to continue moving forward slowly until we have a collision.
			//It's necessary for missiles and jumping for example.
			//Personnally, I don't like it...
			/*		advance_x = advance_x / fabs(advance_x);//sign of advance_x
					advance_y = advance_y / fabs(advance_y);//sign of advance_y
					while(!CollisionPixel(this,&Terrain,0,0)) { // as long as there isnt a collision
							y += advance_y;
							x += advance_x;
					}*/
			return ( 1 );
		}
		return ( 0 );
	}

} // namespace iteam closed
