#ifndef _WEAPONCOMPONENT_H
#define _WEAPONCOMPONENT_H

#include "library_h/gp2d.h"

namespace iteam {

	/*!
		class WeaponComponent

		Usage:

		each weapon has at least one component. a grenade for example has one
		grenade in its list but a cluster bomb has five grenades in it so you
		need one component for each part of your weapon.


	*/
	class WeaponComponent : public gp2d::Sprite	{
		public:

			WeaponComponent();		/**< Constructor. */
			WeaponComponent (
			    char* a_Name			/**< Weapon's name. */
			    , bool a_Active			/**< Is the weapon active? */
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
			);

			void DrawMe();		/**< Draws the weapon's sprite. */
			void DrawName();	/**< Draws the weapon's name. */

			//special functions
			int BlastObjects(); /**< Applies blast and damage to all physical objects within the blast radius. Effect is proportional to BlastRadius/distance and can be tweaked with BlastFactor and BlastDamage. */
			double orientate();	/**< Sets sprite angle to movement angle and returns movement angle. */

			//physics engine functions
			void SetBeginPosition ( GLfloat nx, GLfloat ny );
			void SetVelocity ( GLfloat new_vel, GLfloat new_angle );

			char* AccessName() { return Name; }
			void SetName ( char *a_Str ) { strcpy ( Name , a_Str ); }

			int Fire (
			    GLfloat nx
			    , GLfloat ny
			    , GLfloat vel_x
			    , GLfloat vel_y
			    , GLfloat a_TriggerTime
			);

			const int GetStartTicks() { return StartTicks; }
			const int GetTriggerTime() { return m_TriggerTime; }
			void SetTriggerTime ( const int a_MiliSeconds ) { m_TriggerTime = a_MiliSeconds; }
			void SetActive() { Active = true; }
			void SetInactive() { Active = false; }
			const bool IsActive() { return Active; }
			void DestroyTerrain();

			void SetWeaponID ( int a_WeaponID ) { m_WeaponID = a_WeaponID; }

			GLfloat GetBlastRadius() { return BlastRadius; }

		protected:
			//VARIABLES
			//==================================

			//general variables
			char Name[20];			/**< Weapon's name. */
			bool Active;			/**< Is the weapon active? */
			bool IsController;
			int TypeID;

			//special variables
			GLfloat BlastRadius; /**< how big of a boom does it make? */
			GLfloat BlastFactor; /**< how much blast does it apply to objects? */
			GLfloat BlastDamage; /**< how much damage does it make? */

			int m_TriggerTime;	/**< how many ticks do we wait to blowup? */
			int StartTicks;		/**< when did we start counting? */
			int LastTicks;
			bool Bounces;		/**< can this weapon bounce of things? */
			int m_WeaponID;
			bool Visible;


	};

} // end namespace

#endif
