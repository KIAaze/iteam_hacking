#ifndef _ITEAM_PLAYERS_H
#define _ITEAM_PLAYERS_H

#include "globals.h"

namespace iteam {

	class PlayerObj : public gp2d::Sprite {
		public:
			PlayerObj();
			~PlayerObj();
			void DrawMe();
			void DrawName();
			void MoveMe(gp2d::Sprite *blocker);
		
			GLfloat vY;
			GLfloat vX;
			bool CanMove;
			bool CanJump;
			int Angle;
			char* Name;
	};
}

#endif
