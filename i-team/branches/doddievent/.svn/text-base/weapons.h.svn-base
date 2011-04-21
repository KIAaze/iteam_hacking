#include "globals.h"

#ifndef _ITEAM_WEAPONS_H
#define _ITEAM_WEAPONS_H

#define IT_GRAVITY 5
#define IT_FRICTION 0.001

#define PI 3.14159265

// ================ PHYSICAL PROPERTIES ================

#define IT_MAX_WEAPON_VELOCITY 1.0
#define IT_BOUNCY_WEAPON 1
#define IT_NONEBOUNCY_WEAPON 0
#define IT_WEAPON_GRAVITY 1
#define IT_NO_WEAPON_GRAVITY 0

// ================ WEAPON TYPES =====================

#define IT_WT_GRENADE 				0
#define IT_WT_ROCKET				1
#define IT_WT_PISTOL				2

// ================ WEAPON COMPONENTS ================

#define IT_WC_GRENADE			0
#define IT_WC_BULLET			1

namespace iteam {
	// =========== WEAPON IDs ===============
	// NOTE: These are suggested names but can be changed 
	// 		to suite any type of weapon 
	
	#define GRENADE 			0
	#define TRIPLE_GRENADE 	1
	#define ROCKET			2
	#define MACHINE_GUN		3
	#define PISTOL 			4
	
	class weapon : public gp2d::Sprite	{
		public:
			GLfloat accel_x;
			GLfloat accel_y;
			GLfloat vel_x;
			GLfloat vel_y;
			GLfloat fire_angle;			// direction angle
			GLfloat acceleration;	// lenght of vector accelrating in angle direction
			GLfloat velocity;		// lenght ofvelocity vector
			GLfloat BlastRadius;		// how big of a boom does it make?
			GLfloat Elasticity; 		// how much movement does this qweapon keep when it bounces?
			int LastTicks;			// record of last frame ticks
			bool Bounces;		// can this weapon bounce of things?
			bool IsPhysical;			// does this weapon get effects of gravity applied?
			int WeaponID;
			bool Visible;
		
			weapon();
			void CaclulateVelocity(void);
			void MoveMe();
			void SetBeginPosition(GLfloat nx, GLfloat ny);
			void SetAcceleration(GLfloat new_accel, GLfloat new_angle);
	};
	
	class IT_Weapon	{
		public:
			int TypeID;
			bool Active;
			vector <weapon> components;		
	};
	
	void AddWeaponTypeToWeaponList(int TypeID);
	void AddComponent(int WeaponID, int TypeID, const char texture[], bool IsPhysical, bool Bounces, GLfloat BlastRadius, GLfloat Elasticity);
	int FireWeapon(int TypeID, GLfloat nx, GLfloat ny, GLfloat new_angle, GLfloat new_accel);
	void Test_Init(void);
	void Test_Fire(GLfloat angle);
	void UpdatePhysicalObjects(void);
	
	extern vector <iteam::IT_Weapon> WeaponsList;
	extern GLfloat WeaponStrenght;
	extern GLfloat WeaponAngle;
}


#endif
