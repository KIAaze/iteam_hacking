#ifndef _ITEAM_PLAYERS_H
#define _ITEAM_PLAYERS_H

namespace iteam {

	class PlayerObj : public gp2d::Sprite {
		public:
			PlayerObj();
			~PlayerObj();
			void DrawMe();
			void DrawName();
			void MoveMe();

			GLfloat vY;
			GLfloat vX;
			char* Name;
			bool CanMove;
			bool CanJump;
			int Angle;
	};
	void AddPlayer(int, GLfloat, GLfloat, bool, GLfloat);
}

#endif
