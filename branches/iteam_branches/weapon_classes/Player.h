#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "SpriteMap.h"
#include "physics.h"

/*! \file Player.h
\brief Player class

Player class.
*/

//#include "library_h/gp2d.h"
//#include "Weapon.h"

// avatar types
#define IT_PLAYER_SUSI 1
#define IT_PLAYER_MAGE 2

// CURRENT PLAYER TUEN TEST
#define IT_PLAYER_ONE 1
#define IT_PLAYER_TWO 2

// direction macros
#define IT_PLAYER_FACE_LEFT true
#define IT_PLAYER_FACE_RIGHT false

// AI defines
#define IT_PLAYER_INIT          1
#define IT_PLAYER_TARGETING     2
#define IT_PLAYER_MOVING        3
#define IT_PLAYER_READY         4

namespace iteam {

	//TODO: A Player could be made of different sprites: vehicle+player+hat+etc
	//TODO: Eliminate useless variables
	class Player : public gp2d::Sprite {
		public:
			//==================================
			//VARIABLES
			//==================================
			//general variables
			char Name[256];			/**< Player's name. */
			char Team[256];         /**< Player's team. */
			char Vehicle[256];      /**< Player's vehicle. */

			//special variables
			//shooting variables
			GLfloat m_FireAngle;		/**< Player's shooting angle. (iteam Angle, not SDL angle!) */
			GLfloat m_FirePower;		/**< Player's shooting power (initial velocity). */
			//jumping variables
			GLfloat JumpPower; /**< Player's jumping power (initial velocity). */
			//other variables
			int Health; /**< Player's Health. */
			bool Alive; /**< Is the player alive? */
			bool Dying; /**< Is the player dying? (for death animation) */
			bool CanMove;		/**< Can the player move?. */
			bool CanJump;		/**< Can the player jump? i.e: is the player on solid ground?. */
			int newTicks;
			bool FacingRight;
			GLfloat TiltAngle; /**< Player's orientation angle (for terrain tilting). */
			GLfloat MovementAngle; /**< Player's movement angle */
			bool HasFired;
			int CurrentWeapon;
			GLfloat m_TriggerTime;
			GLfloat PowerMultiplier;

			// AI Stuff
			int Status;
			GLfloat dest_x;
			GLfloat dest_y;

			//physics engine variables
			GLfloat vX;			/**< Player's X velocity. */
			GLfloat vY;			/**< Player's Y velocity. */
			GLfloat velocity;	/**< length of velocity vector */
			GLfloat accel_x;		/**< Player's X acceleration. */
			GLfloat accel_y;		/**< Player's Y acceleration. */
			GLfloat acceleration;	/**< length of vector accelrating in angle direction */
			//time
			int LastTicks;		/**< record of last frame ticks */
			int delta_time;	/**< Small time interval used for movement calculation. It is initialized with "delta_time=iTimer.GetTicks() - LastTicks;" in "UpdatePhysicalObjects". */
			//bouncing
			bool IsPhysical;	/**< does this player get effects of gravity or bouncing applied? */
			GLfloat Elasticity; /**< how much movement does this player keep when he bounces? */
			//object's own/internal acceleration (jetpack, missile, etc.)
			GLfloat obj_accel_x; /**< object's own X acceleration */
			GLfloat obj_accel_y; /**< object's own Y acceleration. */

			struct _Movement {
				bool walkingLeft;
				bool walkingRight;
				bool jumping;
			} Movement;

		protected:
			//Weapon* m_PlayerWeapon;
			bool m_TimeToTakeMyTurn;
			bool m_WallEncountered;
			bool m_HumanPlayer;

			//==================================
			//FUNCTIONS
			//==================================

		public:
			//general functions
			Player();
			Player( const char texture[], int numSpritesWide=1, int numSpritesHigh=1 );
			Player( gp2d::Texture* tex, int numSpritesWide=1, int numSpritesHigh=1 );

			void DrawMe();		/**< Draws the player's sprite. */
			void DrawName();	/**< Draws the player's name. */

			//special functions
			void FlipFireAngle ( int direction );
			void AddAcceleration ( GLfloat new_accel, GLfloat new_angle );

			//accessors
			const GLfloat FirePower() { return m_FirePower; }
			const GLfloat FireAngle() { return m_FireAngle; }

			//physics engine functions
			void SetBeginPosition ( GLfloat nx, GLfloat ny );
			void SetVelocity ( GLfloat new_vel, GLfloat new_angle );
			void SetAcceleration ( GLfloat new_accel, GLfloat new_angle );/**< Set obj_accel_x and obj_accel_y. */
			void CalculateVelocity ( void );
			void CalculateAcceleration ( void );
			void WalkLeft();
			void WalkRight();
			int MoveMe();/**< Execute player movement actions (keyboard input included here). Returns 1 if there was a collision, 0 otherwise.*/

			//void SetPlayerWeapon(Weapon* a_Weapon){ m_PlayerWeapon = a_Weapon; }
//			int PlayerWeaponID() { return m_PlayerWeapon->GetID(); }

			void Fire();
			// keep track of turns, (for use with AI)
			bool TimeToTakeMyTurn() { return m_TimeToTakeMyTurn; }
			void SetTimeToTakeMyTurn() { m_TimeToTakeMyTurn = true; }
			void SetNotTimeToTakeMyTurn() { m_TimeToTakeMyTurn = false; }
			bool IsHumanPlayer() { return m_HumanPlayer; }

			int DoBehaviour();
			int Update(){ return(iteamPhysics->UpdateObject(this)); };
			int Render(gp2d::Camera Cam);
	};//end of Player class

	void ProccessPlayer ( void );

	extern map <int,iteam::Player> PlayerList;
}
//namespace end
#endif
