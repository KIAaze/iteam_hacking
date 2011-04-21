/*! \file players.h
\brief Header for the main player functions.
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
			PlayerObj();		/**< Constructor. */
			~PlayerObj();		/**< Deconstructor. */
			void DrawMe();		/**< Draws the player's sprite. */
			void DrawName();	/**< Draws the player's name. */
			void MoveMe();		/**< Executes player movement actions (keyboard input included here). */

			GLfloat vY;			/**< Player's Y velocity. */
			GLfloat vX;			/**< Player's X velocity. */
			char* Name;			/**< Player's name. */
			bool CanMove;		/**< Can the player move?. */
			bool CanJump;		/**< Can the player jump?. */
			int Angle;			/**< Player's angle (for terrain tilting). */

			struct _Movement {
				bool walkingLeft;
				bool walkingRight;
				bool jumping;
			} Movement;
	};
	
	void AddPlayer(int, GLfloat, GLfloat, bool, GLfloat);
}

#endif
