/*! \file Weapon.h
\brief Weapon class
*/



#ifndef _ITEAM_WEAPONS_H
#define _ITEAM_WEAPONS_H

#include "library_h/gp2d.h"
#include "physics.h"
#include "WeaponComponent.h"

// ===================================================
// HELP!
// to use this class type in the console:
//	 python create_weapon_script <Weapon name>
//
//	this will create a basic derived class for you, ready to be programmed!
//
//===================================================
namespace iteam {

    #define IT_GRAVITY_DEFAULT 100

    #define PI 3.14159265

    // ================ PHYSICAL PROPERTIES ================

    #define IT_MAX_WEAPON_VELOCITY 1.0
    #define IT_BOUNCY_WEAPON 1
    #define IT_NONEBOUNCY_WEAPON 0
    #define IT_WEAPON_GRAVITY 1
    #define IT_NO_WEAPON_GRAVITY 0
    #define IT_NB_OF_WEAPONS 5

    // ================ Weapon TYPES =====================

    #define IT_WT_GRENADE 				0
    #define IT_WT_MISSILE				1
    #define IT_WT_CLUSTERBOMB			2
    #define IT_WT_DYNAMITE				3
    #define IT_WT_PISTOL				4
    #define IT_WT_ROCKET				5

    // ================ Weapon COMPONENTS ================

    #define IT_WC_GRENADE			0
    #define IT_WC_BULLET			1

    // ================ Weapon PROPERTIES ================

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


	// =========== Weapon IDs ===============
	// NOTE: These are suggested names but can be changed
	// 		to suite any type of Weapon
	enum {
      IT_WT_THROWABLE
    , IT_WT_TARGETABLE
    , IT_WT_LAYABLE
	};

    class PlayerObj;

    /*!
        class Weapon
        Usage:


        each Weapon must be a derived class from this base class and implement
        its own virtual functions for the ones below.

        once made you can instance it in InitWeapons() and pass it to the WeaponsList
        for handling.

    */
	class Weapon {
		public:
			Weapon();
            virtual ~Weapon();

			int SizeCount() { return NumberOfComponents; }


			void Add(
			  int TypeID
			, const char texture[]
			, bool IsPhysical = true
			, bool Bounces = true
			, GLfloat BlastRadius = 0
			, GLfloat BlastFactor = 0
			, GLfloat BlastDamage = 0
			, GLfloat a_Elasticity = 0.0
			, int a_TriggerTime = 3
			, bool Active = true
			, GLfloat scale = 1
			);


			int Fire(
			  PlayerObj *a_Player
			, GLfloat nx
			, GLfloat ny
			, GLfloat new_angle
			, GLfloat new_vel
			, GLfloat a_TriggerTime
			);

            void Move(GLfloat x, GLfloat y) { component[0]->Move(x , y); }

            void IncrementTriggerTime(const GLfloat a_Increment);
            void DecrementTriggerTime(const GLfloat a_Increment);

            void Draw() { component[0]->Draw(); }

			virtual void DoBehaviours(
			  int collision=0
			);

			const int GetID() { return WeaponID; }
            void SetID(const int a_WeaponID) { WeaponID = a_WeaponID; }
			const int GetTriggerTime();
			void UsePhysicsSystem(PhysicsSystem* a_PS) { m_PhysicsSystem = a_PS; }
			void SetName(char *a_Name);
            char * GetName();
            bool IsActive() { return m_Active; }
            WeaponComponent* AccessComponent(int i) { return component[i]; }

            bool ComponentTriggered(WeaponComponent* a_Component);

            void SetTarget(GLfloat a_X, GLfloat a_Y) { m_TargetX = a_X; m_TargetY = a_Y; }

            char* AccessThumbnailPath() { return m_PathToThumbnail; }

            bool IsThrowable() { return m_Throwable; }

		protected:

			// variables
			vector <WeaponComponent *> component;
			GLfloat m_TargetX; // for drawing the thumb on the gui
			GLfloat m_TargetY;
			char *m_Name;
			char *m_PathToThumbnail;
			int NumberOfComponents;
			int WeaponID;
			PhysicsSystem* m_PhysicsSystem;
			bool m_Active;
			PlayerObj* m_Player;
			bool m_Throwable;
        };






}

#endif
