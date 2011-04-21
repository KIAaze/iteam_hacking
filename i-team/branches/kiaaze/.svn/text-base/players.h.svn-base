/*! \file players.h
\brief PlayerObj class

Player class.
*/

#ifndef _ITEAM_PLAYERS_H
#define _ITEAM_PLAYERS_H

namespace iteam {
	
	// avatar types
	#define IT_PLAYER_SUSI 1
	#define IT_PLAYER_MAGE 2

	// CURRENT PLAYER TUEN TEST
	#define IT_PLAYER_ONE 1
	#define IT_PLAYER_TWO 2

	// direction macros
	#define IT_PLAYER_FACE_LEFT true
	#define IT_PLAYER_FACE_RIGHT false

	class PlayerObj : public gp2d::Sprite {
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
			GLfloat Angle;		/**< Player's shooting angle. (iteam Angle, not SDL angle!) */
			GLfloat Power;		/**< Player's shooting power (initial velocity). */
			//jumping variables
			GLfloat JumpPower;	/**< Player's jumping power (initial velocity). */
			//other variables
			int Health;			/**< Player's Health. */
			bool CanMove;		/**< Can the player move?. */
			bool CanJump;		/**< Can the player jump? i.e: is the player on solid ground?. */
			int newTicks;
			bool FacingRight;
			GLfloat TiltAngle; /**< Player's orientation angle (for terrain tilting). */
			GLfloat MovementAngle; /**< Player's movement angle */

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

			//==================================
			//FUNCTIONS
			//==================================

			//general functions
			PlayerObj();		/**< Constructor. */
			~PlayerObj();		/**< Deconstructor. */
			void DrawMe();		/**< Draws the player's sprite. */
			void DrawName();	/**< Draws the player's name. */

			//special functions
			void FlipFireAngle(int direction);
			void AddAcceleration(GLfloat new_accel, GLfloat new_angle);

			//physics engine functions
			void SetBeginPosition(GLfloat nx, GLfloat ny);
			void SetVelocity(GLfloat new_vel, GLfloat new_angle);
			void SetAcceleration(GLfloat new_accel, GLfloat new_angle);/**< Set obj_accel_x and obj_accel_y. */
			void CaclulateVelocity(void);
			void CaclulateAcceleration(void);
			int MoveMe();/**< Execute player movement actions (keyboard input included here). Returns 1 if there was a collision, 0 otherwise.*/
	};
	void AddPlayer(int, GLfloat, GLfloat, bool, GLfloat);
}

#endif
