#ifndef _MISSILES_H
#define _MISSILES_H

#include "globals.h"
#include <vector>

using namespace std;

namespace iteam {
	
	class gameMissiles
	{
		public:
			gameMissiles();
			~gameMissiles();
					
			// This function is used to assign all sprites, backgrounds etc
			// into the relevant map arrays used in a scene class
			void CreateMissile(GLfloat xpos, GLfloat ypos);
			bool DeleteMissile(int index);
			
			void UpdateObjects(gp2d::Sprite *blocker);			
			void DrawObjects(void);

			static int numOfMissiles;
			vector<gp2d::Sprite *>	missiles;					
		
		private:
			GLfloat velocityX;
			GLfloat velocityY;
	};		
		
}
#endif /* _MISSILES_H */
