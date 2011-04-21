#ifndef _GAMESCENE_H
#define _GAMESCENE_H

#include "globals.h"
#include "players.h"
#include <string>
#include <map>

namespace iteam {
	
	#define MAX_GAMESTATES	10
	
	#define GP2D_BACKGROUND 	0
	#define GP2D_FONT				1
	#define GP2D_PLAYERS			2
	
	ITEAM_DEFINE_HASH_TYPE(gp2d::Sprite*, gp2dHashBackGround);
	ITEAM_DEFINE_HASH_TYPE(gp2d::Font*, gp2dHashFont);
	ITEAM_DEFINE_HASH_TYPE(iteam::PlayerObj*, gp2dHashPlayers);
	
	// With every game state there is a game scene associated with it.
	// The idea of a game scene is to have information about all textures,
	// bitmaps etc required for the current state. Seperating it into a seperate
	// class gives the option to use the same textures etc in different states.	
	class gameScene
	{
		public:
			gameScene();
			~gameScene();
		
			virtual void LoadResources(void) {
			}
		
			// This function returns a pointer to the resource required based on
			// the string and type of resource
/*		
			virtual void GetResource(int type, char *string, void *retPtr) {
								
				switch (type)
				{
					case GP2D_BACKGROUND:
						retPtr = sceneHashBackGround[string];
						break;
					case GP2D_FONT:
						retPtr = sceneHashFont[string];
						break;
					case GP2D_PLAYERS:
						retPtr = sceneHashPlayers[string];
						break;
				}
			}
*/
		gp2d::Sprite *GetBackground(char *string) {
			return sceneHashBackGround[string];
		}
		gp2d::Font *GetFont(char *string) {
			return sceneHashFont[string];			
		}
		PlayerObj *GetPlayer(char *string) {
			return sceneHashPlayers[string];
		}		
		gp2d::Camera *GetCamera(void) {
			return &sceneCamera;
		}
			
		protected:
			gp2d::Camera						sceneCamera;			
			gp2dHashBackGround			sceneHashBackGround;
			gp2dHashFont 					sceneHashFont;
			gp2dHashPlayers 				sceneHashPlayers;
	};
}

#endif /* _GAMESCENE_H */
