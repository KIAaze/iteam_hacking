/*! \file weapons.h
\brief weapon class
*/

#include "globals.h"

#ifndef _ITEAM_WEAPONS_H
#define _ITEAM_WEAPONS_H

#define IT_GRAVITY_DEFAULT 100

#define PI 3.14159265

// ================ PHYSICAL PROPERTIES ================

#define IT_MAX_WEAPON_VELOCITY 1.0
#define IT_BOUNCY_WEAPON 1
#define IT_NONEBOUNCY_WEAPON 0
#define IT_WEAPON_GRAVITY 1
#define IT_NO_WEAPON_GRAVITY 0
#define IT_NB_OF_WEAPONS 5

// ================ WEAPON TYPES =====================

#define IT_WT_GRENADE 				0
#define IT_WT_MISSILE				1
#define IT_WT_CLUSTERBOMB			2
#define IT_WT_DYNAMITE				3
#define IT_WT_PISTOL				4
#define IT_WT_ROCKET				5

// ================ WEAPON COMPONENTS ================

#define IT_WC_GRENADE			0
#define IT_WC_BULLET			1

// ================ WEAPON PROPERTIES ================

#define IT_WT_GRENADE_TIME_DEFAULT	3
#define IT_WT_DYNAMITE_TIME_DEFAULT	10

#define IT_WT_GRENADE_BLAST_RADIUS		60.0
#define IT_WT_CLUSTERBOMB_BLAST_RADIUS		60.0
#define IT_WT_DYNAMITE_BLAST_RADIUS	240.0
#define IT_WT_MISSILE_BLAST_RADIUS	120.0

#define IT_WT_GRENADE_BLAST_FACTOR	100.
#define IT_WT_CLUSTERBOMB_BLAST_FACTOR	100.
#define IT_WT_DYNAMITE_BLAST_FACTOR	100.
#define IT_WT_MISSILE_BLAST_FACTOR	200.0

#define IT_WT_GRENADE_BLAST_DAMAGE	10.
#define IT_WT_CLUSTERBOMB_BLAST_DAMAGE	10.
#define IT_WT_DYNAMITE_BLAST_DAMAGE	10.
#define IT_WT_MISSILE_BLAST_DAMAGE	50.0

#define IT_WT_MISSILE_ACCEL		200.0

// ================  EXPLOSION STUFF ===================
#define EXPLOSION_HALO_WIDTH 		5

namespace iteam {
	// =========== WEAPON IDs ===============
	// NOTE: These are suggested names but can be changed 
	// 		to suite any type of weapon 
	
	#define GRENADE 	0
	#define TRIPLE_GRENADE 	1
	#define ROCKET 		2
	#define MACHINE_GUN	3
	#define PISTOL 		4
	
	class weapon : public gp2d::Sprite	{
		public:
			//==================================
			//VARIABLES
			//==================================

			//general variables
			char* Name;			/**< Weapon's name. */
			bool Active;			/**< Is the weapon active? */

			//special variables
			GLfloat fire_angle;	/**< initial angle at which is was fired */
			GLfloat movement_angle;	/**< direction angle according to iteam standards */
			GLfloat BlastRadius; /**< how big of a boom does it make? */
			GLfloat BlastFactor; /**< how much blast does it apply to objects? */
			GLfloat BlastDamage; /**< how much damage does it make? */

			int TimeTrigger;	/**< how many ticks do we wait to blowup? */
			int StartTicks;		/**< when did we start counting? */
			bool Bounces;		/**< can this weapon bounce of things? */
			int WeaponID;
			bool Visible;

			//physics engine variables
			//general movement
			GLfloat vel_x; /**< X velocity. */
			GLfloat vel_y; /**< Y velocity. */
			GLfloat velocity;	/**< length of velocity vector */
			GLfloat accel_x; /**< X acceleration */
			GLfloat accel_y; /**< Y acceleration. */
			GLfloat acceleration;	/**< length of vector accelrating in angle direction */
			//time
			int LastTicks;		/**< record of last frame ticks */
			int delta_time;	/**< Small time interval used for movement calculation. It is initialized with "delta_time=iTimer.GetTicks() - LastTicks;" in "UpdatePhysicalObjects". */
			//bouncing
			bool IsPhysical;	/**< does this weapon get effects of gravity or bouncing applied? */
			GLfloat Elasticity; /**< how much movement does this weapon keep when it  bounces? */
			//object's own/internal acceleration (jetpack, missile, etc.)
			GLfloat obj_accel_x; /**< object's own X acceleration */
			GLfloat obj_accel_y; /**< object's own Y acceleration. */

			//==================================
			//FUNCTIONS
			//==================================

			//general functions
			weapon();		/**< Constructor. */
			~weapon();		/**< Deconstructor. */
			void DrawMe();		/**< Draws the weapon's sprite. */
			void DrawName();	/**< Draws the weapon's name. */

			//special functions
			int BlastObjects(); /**< Applies blast and damage to all physical objects within the blast radius. Effect is proportional to BlastRadius/distance and can be tweaked with BlastFactor and BlastDamage. */
			double orientate();	/**< Sets sprite angle to movement angle and returns movement angle. */

			//physics engine functions
			void SetBeginPosition(GLfloat nx, GLfloat ny);
			void SetVelocity(GLfloat new_vel, GLfloat new_angle);
			void SetAcceleration(GLfloat new_accel, GLfloat new_angle);/**< Set obj_accel_x and obj_accel_y. */
			void CaclulateVelocity(void);
			void CaclulateAcceleration(void);
			int MoveMe();/**< Execute weapon movement actions. Returns 1 if there was a collision, 0 otherwise.*/
	};
	
	class IT_Weapon : public gp2d::Sprite	{
		public:
			GLfloat offset_x;
			GLfloat offset_y;
			int TypeID;
			bool Active;			/**< Is the weapon active? */
			vector <weapon> components;
			
			
	};
	
	void AddWeaponTypeToWeaponList(GLfloat px, GLfloat py, int TypeID, const char thumb[]);
	void AddComponent(int WeaponID, int TypeID, const char texture[], bool IsPhysical=true, bool Bounces=true, GLfloat BlastRadius=0, GLfloat BlastFactor=0, GLfloat BlastDamage=0, GLfloat Elasticity=0, int TriggerTime=0, bool Active=true, GLfloat scale=1);
	int FireWeapon(int TypeID, GLfloat nx, GLfloat ny, GLfloat new_angle, GLfloat new_accel);/**< Fires a weapon. */
	int FireComponent(int TypeID, int CompID, GLfloat nx, GLfloat ny, GLfloat vel_x, GLfloat vel_y); /**< Fires a component. */
	void Weapons_Init(void);
	void Weapons_Fire(GLfloat angle, GLfloat Speed, int TypeID);
	void UpdateWeaponThumbs(void);
	void UpdateWeaponObjects(void);
	void DoWeaponBehaviours(int TypeID,int CompID,int collision=0);
	void DestroyTerrain(int TypeID, int ComponentID);/**< Destroys the terrain. */
	extern vector <iteam::IT_Weapon> WeaponsList;

	//has been replaced by "void ProcessAllPhysicalObjects(void)" from physics.h
	//void UpdatePhysicalObjects(void);

	extern vector <iteam::IT_Weapon> WeaponsList;
	extern GLfloat WeaponStrength;
	extern GLfloat WeaponAngle;
	
}

#endif
