#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "library_h/gp2d.h"
#include "physics.h"
#include "globals.h"

namespace iteam {

	class Weapon : public gp2d::Sprite {
		public:

			Weapon();/**< Constructor. */
			Weapon( const char texture[], int numSpritesWide=1, int numSpritesHigh=1 );
			Weapon( gp2d::Texture* tex, int numSpritesWide=1, int numSpritesHigh=1 );

			void DrawMe(); /**< Draws the weapon's sprite. */
			void DrawName(); /**< Draws the weapon's name. */

			//special functions
			int BlastObjects(SpriteMap &a_map); /**< Applies blast and damage to all physical objects within the blast radius. Effect is proportional to BlastRadius/distance and can be tweaked with BlastFactor and BlastDamage. */
			double orientate(); /**< Sets sprite angle to movement angle and returns movement angle. */

			//physics engine functions
			void SetBeginPosition ( GLfloat nx, GLfloat ny );
			void SetVelocity ( GLfloat new_vel, GLfloat new_angle );

			char* AccessName() { return Name; }
			void SetName ( char *a_Str ) { strcpy ( Name , a_Str ); }


			const int GetStartTicks() { return StartTicks; }
			const int GetTriggerTime() { return m_TriggerTime; }
			void SetTriggerTime ( const int a_MiliSeconds ) { m_TriggerTime = a_MiliSeconds; }
			void SetActive() { Active = true; }
			void SetInactive() { Active = false; }
			const bool IsActive() { return Active; }

			void SetWeaponID ( int a_WeaponID ) { m_WeaponID = a_WeaponID; }

			GLfloat GetBlastRadius() { return BlastRadius; }

			virtual int Fire (GLfloat nx, GLfloat ny, GLfloat new_angle, GLfloat new_vel);
			virtual void DestroyTerrain();
			virtual int DoBehaviour();
			virtual int Update(){ return(iteamPhysics->UpdateObject(this)); };
			virtual int Render(gp2d::Camera Cam);

			virtual int DefineTextures()=0;//This is a pure virtual function, which causes the class to be abstract. It MUST be redefined in derived classes (or be declared pure virtual again).

		public:
			int Physics_ID;
			int m_target;//Used for smart weapons, but also for the medipack

		protected:
			//VARIABLES
			//==================================

			//general variables
			char Name[20]; /**< Weapon's name. */
			bool Active; /**< Is the weapon active? */
			bool IsController;
			int TypeID;

			//special variables
			GLfloat BlastRadius; /**< how big of a boom does it make? */
			GLfloat BlastFactor; /**< how much blast does it apply to objects? */
			GLfloat BlastDamage; /**< how much damage does it make? */

			int m_TriggerTime; /**< how many ticks do we wait to blowup? */
			int StartTicks; /**< when did we start counting? */
			int LastTicks;
			bool Bounces; /**< can this weapon bounce off things? */
			int m_WeaponID;
			bool Visible;
	};

} // end namespace

#endif
