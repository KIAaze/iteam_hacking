#include "gamestate.h"
#include "missiles.h"
#include "players.h"
#include <vector>

using namespace gp2d;

namespace iteam {
	
	class game;
		
////////////////////////////////////////////////////
////////////////////////////////////////////////////
	
	class prerunGameScene : public gameScene
	{
		public:
			prerunGameScene () {
			}
			
			~prerunGameScene () {
			}
		
		
			// This function is used to assign all sprites, backgrounds etc
			// into the relevant map arrays used in a scene class
			void AssignResources(void) {

				//Backgrounds
				sceneHashBackGround["Terrain"] = 			&Terrain;
				sceneHashBackGround["Background1"] =	&BGLayer1;
				sceneHashBackGround["Background2"] =	&BGLayer2;
				sceneHashBackGround["GUIBottom"] = 		&GUIBottom;
				sceneHashBackGround["Countdown"] = 		&Countdown;
				
				// Fonts used
				sceneHashFont["Counter"] =			 			&FNTCounter;
				sceneHashFont["Names"] =			 				&FNTNames;
				sceneHashFont["GUI"] =				 				&FNTGameGUI;
			
				// Players used
				//sceneHashPlayers["Player1"] =				 		&Player[0];	
				//sceneHashPlayers["Player2"] =				 		&Player[1];										
			}
			
			// This function physically loads all the resources required for the given state
			// into memory. This function could be used when the state enters the intialising
			// stage rather than all at the beginning to preserve memory usage.
			void LoadResources(void) {

				FNTCounter.Load("data/gui/ingame/counter.ttf", 64);
				FNTNames.Load("data/gui/ingame/eras_bold.TTF", 12);
				FNTGameGUI.Load("data/gui/ingame/eras_bold.TTF", 11);
		
				//Song = gp2d::LoadMusic("data/music/song1.ogg");
				//PlayMusic(Song,0);

				//AddPlayer(IT_PLAYER_SUSI,50,50,IT_PLAYER_FACE_RIGHT,1);
				//AddPlayer(IT_PLAYER_SUSI,180,50,IT_PLAYER_FACE_LEFT,1);
								
				Terrain.Load("data/levels/egypt/terrain.png");
				Terrain.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Terrain.height[0]/2);
				BGLayer2.Load("data/levels/egypt/layer2.png");
				BGLayer2.ResizePropW(800);		// TODO: game::GameResW nned to make it globally accessable
				BGLayer1.Load("data/levels/egypt/layer1.png");
				BGLayer1.width[0]=2048;
				BGLayer1.height[0]=1024;
		
				GUIBottom.Load("data/gui/ingame/bottom2.png");
				GUIBottom.ResizePropW(800);		// TODO: game::GameResW nned to make it globally accessable
				GUIBottom.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-GUIBottom.height[0]/2);

				Countdown.iterateSheets = true;
				Countdown.setAnimationSpeed(1.0f);
				Countdown.Load("data/gui/ingame/countdown_3.png");
				Countdown.Load("data/gui/ingame/countdown_2.png");
				Countdown.Load("data/gui/ingame/countdown_1.png");
				Countdown.Load("data/gui/ingame/countdown_duel.png");
				
				AssignResources();
				
				sceneCamera.Create();
			}
/*			
			void AddPlayer(int PlayerID, GLfloat x, GLfloat y, bool Mirror2, GLfloat Scaling)
			{
				Player.push_back(PlayerObj());
				
				if(PlayerID == IT_PLAYER_SUSI) {
					Player[Player.size()-1].Name="Susi";
					Player[Player.size()-1].Load("data/chars/susi.png"); 
				}
				Player[Player.size()-1].Move(x,y);
				Player[Player.size()-1].Mirror=Mirror2;
				Player[Player.size()-1].Scale(Scaling);
				Player[Player.size()-1].Angle=iRand(0,360);
				Player[Player.size()-1].col_x[0]=(64/2)-10;
				Player[Player.size()-1].col_y[0]=8;
				Player[Player.size()-1].col_width[0]=20;
				Player[Player.size()-1].col_height[0]=60-8;
			}
	*/								
			void initialise(void) {
	
				sceneHashBackGround["Countdown"]->animationTimer.start();				
			}
	
			void drawMap(void) {				
				gp2d::Sprite		*ptrBackGround;
				gp2d::Sprite		*ptrGUIBottom;		
				gp2d::Camera	*ptrCam = GetCamera();
				
				//Get pointers to resources used here
				ptrGUIBottom = sceneHashBackGround["GUIBottom"];
		
				//Draw background				
				ptrCam->Begin();
				ptrBackGround = sceneHashBackGround["Background2"];
				ptrBackGround->Draw();
				ptrBackGround->Move(	ptrCam->GetX()-((VIEWPORT_WIDTH/2)-ptrGUIBottom->width[0]/2),	\
														(VIEWPORT_HEIGHT/2)-(ptrCam->GetY()/20));
		
				ptrCam->Begin();
				ptrBackGround = sceneHashBackGround["Background1"];
				ptrBackGround->Draw();
				ptrBackGround->Move(	ptrCam->GetX()-((VIEWPORT_WIDTH/2)-ptrGUIBottom->width[0]/2)+(ptrCam->GetX()/4),	\
														(VIEWPORT_HEIGHT/2)-(ptrCam->GetY()/10));
				
				//Draw terrain
				ptrCam->Begin();
				ptrBackGround = sceneHashBackGround["Terrain"];
				ptrBackGround->Draw();						
			}
			
			bool updateCountdown(void) {
				gp2d::Sprite *ptrBackGround;
				gp2d::Camera *ptrCam = GetCamera();
				bool bOK = true;				
				
				ptrBackGround	= sceneHashBackGround["Countdown"];
					
				ptrCam->Begin();
				ptrBackGround->Move(	(ptrCam->GetX()-(VIEWPORT_WIDTH/2))+VIEWPORT_WIDTH/2,	\
														(ptrCam->GetY()-(VIEWPORT_HEIGHT/2))+VIEWPORT_HEIGHT/2);
				
				// Have we iterated through all the sheets once
				if (ptrBackGround->setNextFrame() == false) {
					bOK = false;
				}
				
				ptrBackGround->DrawFrame();				
				
				return bOK;
			}
			
			void updateGUI(void) {
				gp2d::Sprite 	*ptrBackGround;
				gp2d::Camera	*ptrCam = GetCamera();
					
				ptrBackGround = sceneHashBackGround["GUIBottom"];
				
				ptrCam->Begin();
				ptrBackGround->Move(	ptrCam->GetX()-((VIEWPORT_WIDTH/2)-ptrBackGround->width[0]/2),	\
														ptrCam->GetY()+((VIEWPORT_HEIGHT/2)-ptrBackGround->height[0]/2));
				ptrBackGround->Draw();			
			}
			
			void displayCameraCoords(void) {
				gp2d::Camera *ptrCam = GetCamera();
				
				Text( *sceneHashFont["GUI"], 10,16, 0,1,1,1, 1,1,1, "Cam X: %f",ptrCam->GetX());
				Text( *sceneHashFont["GUI"], 10,16+16, 0,1,1,1, 1,1,1, "Cam Y: %f",ptrCam->GetY());								
			}

			void updateCamera(void) {
				gp2d::Camera *ptrCam = GetCamera();
				
				if(ptrCam->GetX()>1022){ ptrCam->Move(1022,ptrCam->GetY()); }
				if(ptrCam->GetX()<-220){ ptrCam->Move(-220,ptrCam->GetY()); }
				if(ptrCam->GetY()>298){ ptrCam->Move(ptrCam->GetX(),298); }
				if(ptrCam->GetY()<200){ ptrCam->Move(ptrCam->GetX(),200); }
		
				ptrCam->End();				
			}
			
		private:
			
//			vector<PlayerObj> Player;
		
			gp2d::Sprite Terrain;
			gp2d::Sprite BGLayer1;
			gp2d::Sprite BGLayer2;
			gp2d::Sprite GUIBottom;
			gp2d::Sprite Countdown;
			
			gp2d::Font   FNTCounter;
			gp2d::Font   FNTNames;
			gp2d::Font   FNTGameGUI;
	};
	
///////////////////////////////////////////////////
///////////////////////////////////////////////////

	class runningGameScene : public gameScene
	{
		public:
			runningGameScene () {
			}
			
			~runningGameScene () {
			}
		
		
			// This function is used to assign all sprites, backgrounds etc
			// into the relevant map arrays used in a scene class
			void AssignResources(void) {

				//Backgrounds
				sceneHashBackGround["Terrain"] = 			&Terrain;
				sceneHashBackGround["Background1"] =	&BGLayer1;
				sceneHashBackGround["Background2"] =	&BGLayer2;
				sceneHashBackGround["GUIBottom"] = 		&GUIBottom;
				sceneHashBackGround["Countdown"] = 		&Countdown;
				
				// Fonts used
				sceneHashFont["Counter"] =			 			&FNTCounter;
				sceneHashFont["Names"] =			 				&FNTNames;
				sceneHashFont["GUI"] =				 				&FNTGameGUI;
			
				// Players used
				sceneHashPlayers["Player1"] =				 		&Player[0];	
				sceneHashPlayers["Player2"] =				 		&Player[1];										
			}
			
			// This function physically loads all the resources required for the given state
			// into memory. This function could be used when the state enters the intialising
			// stage rather than all at the beginning to preserve memory usage.
			void LoadResources(void) {

				FNTCounter.Load("data/gui/ingame/counter.ttf", 64);
				FNTNames.Load("data/gui/ingame/eras_bold.TTF", 12);
				FNTGameGUI.Load("data/gui/ingame/eras_bold.TTF", 11);
		
				Song = gp2d::LoadMusic("data/music/song1.ogg");
				//PlayMusic(Song,0);
							
				Terrain.Load("data/levels/egypt/terrain.png");
				Terrain.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Terrain.height[0]/2);
				BGLayer2.Load("data/levels/egypt/layer2.png");
				BGLayer2.ResizePropW(800);		// TODO: game::GameResW nned to make it globally accessable
				BGLayer1.Load("data/levels/egypt/layer1.png");
				BGLayer1.width[0]=2048;
				BGLayer1.height[0]=1024;
		
				GUIBottom.Load("data/gui/ingame/bottom2.png");
				GUIBottom.ResizePropW(800);		// TODO: game::GameResW nned to make it globally accessable
				GUIBottom.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-GUIBottom.height[0]/2);

				Countdown.iterateSheets = true;
				Countdown.setAnimationSpeed(1.0f);
				Countdown.Load("data/gui/ingame/countdown_3.png");
				Countdown.Load("data/gui/ingame/countdown_2.png");
				Countdown.Load("data/gui/ingame/countdown_1.png");
				Countdown.Load("data/gui/ingame/countdown_duel.png");

				AddPlayer(IT_PLAYER_SUSI,(VIEWPORT_WIDTH/2)-(Terrain.width[0]/2),50,IT_PLAYER_FACE_RIGHT,1);
				AddPlayer(IT_PLAYER_SUSI,180,50,IT_PLAYER_FACE_LEFT,1);

				AssignResources();
				
				sceneCamera.Create();
			}
			
			void AddPlayer(int PlayerID, GLfloat x, GLfloat y, bool Mirror2, GLfloat Scaling)
			{
				Player.push_back(PlayerObj());
				
				if(PlayerID == IT_PLAYER_SUSI) {
					Player[Player.size()-1].Name="Susi";					
					Player[Player.size()-1].iterateSheets = true;
					Player[Player.size()-1].setAnimationSpeed(0.0f);
					Player[Player.size()-1].Load("data/chars/susi/1.png");
					Player[Player.size()-1].Load("data/chars/susi/2.png");
					Player[Player.size()-1].Load("data/chars/susi/3.png");
					Player[Player.size()-1].Load("data/chars/susi/4.png");
					Player[Player.size()-1].Load("data/chars/susi/5.png");
					Player[Player.size()-1].Load("data/chars/susi/6.png");
					Player[Player.size()-1].Load("data/chars/susi/7.png");
					Player[Player.size()-1].Load("data/chars/susi/8.png");
					Player[Player.size()-1].Load("data/chars/susi/9.png");
					Player[Player.size()-1].Load("data/chars/susi/10.png");
					Player[Player.size()-1].Load("data/chars/susi/11.png");
					Player[Player.size()-1].Load("data/chars/susi/12.png");
					
					//Player[Player.size()-1].Load("data/chars/susi.png"); 
				}
				
				Player[Player.size()-1].Move(x,y);
				Player[Player.size()-1].Mirror=Mirror2;
				Player[Player.size()-1].Scale(Scaling);
				Player[Player.size()-1].Angle=iRand(0,360);
				Player[Player.size()-1].col_x[0]=(64/2)-10;
				Player[Player.size()-1].col_y[0]=8;
				Player[Player.size()-1].col_width[0]=20;
				Player[Player.size()-1].col_height[0]=60-8;
			}
									
			void initialise(void) {
				sceneHashPlayers["Player1"]->CanMove = true;
				
				// This rests the frame animation timer.
				sceneHashPlayers["Player1"]->animationTimer.start();
				
			}
			
			void FireMissile(void) {
				
				GLfloat startX;
				
				if (weaponCollection.numOfMissiles == 0) {								
					iteam::PlayerObj *ptrPlayer = sceneHashPlayers["Player1"];
					
					if (ptrPlayer->Mirror == true)
						startX = ptrPlayer->x;
					else
						startX = ptrPlayer->x;
					weaponCollection.CreateMissile(startX, ptrPlayer->y);
				}
			}
			
			void drawMap(void) {
				gp2d::Sprite		*ptrBackGround;
				gp2d::Sprite		*ptrGUIBottom;		
				gp2d::Camera	*ptrCam = GetCamera();
				
				//Get pointers to resources used here
				ptrGUIBottom = sceneHashBackGround["GUIBottom"];
		
				//Draw background				
				ptrCam->Begin();
				ptrBackGround = sceneHashBackGround["Background2"];
				ptrBackGround->Draw();
				ptrBackGround->Move(	ptrCam->GetX()-((VIEWPORT_WIDTH/2)-ptrGUIBottom->width[0]/2),	\
														(VIEWPORT_HEIGHT/2)-(ptrCam->GetY()/20));
		
				ptrCam->Begin();
				ptrBackGround = sceneHashBackGround["Background1"];
				ptrBackGround->Draw();
				ptrBackGround->Move(	ptrCam->GetX()-((VIEWPORT_WIDTH/2)-ptrGUIBottom->width[0]/2)+(ptrCam->GetX()/4),	\
														(VIEWPORT_HEIGHT/2)-(ptrCam->GetY()/10));
				
				//Draw terrain
				ptrCam->Begin();
				ptrBackGround = sceneHashBackGround["Terrain"];
				ptrBackGround->Draw();						
			}				
		
			void updatePlayers(void) {
				gp2d::Camera			*ptrCam = GetCamera();
				gp2d::Sprite				*ptrTerrain;
				iteam::PlayerObj		*ptrPlayer;
								
				//Get pointers to resources used here
				ptrCam->Begin();		
				ptrTerrain = sceneHashBackGround["Terrain"];						
				ptrPlayer = sceneHashPlayers["Player1"];
				ptrPlayer->MoveMe(ptrTerrain);
				
				ptrCam->Begin();
				ptrPlayer->DrawMe();				
			}
			
			void updateMissiles(void) {
				gp2d::Sprite				*ptrTerrain;				
				gp2d::Camera			*ptrCam = GetCamera();
				
				ptrCam->Begin();						
				ptrTerrain = sceneHashBackGround["Terrain"];				
				weaponCollection.UpdateObjects(ptrTerrain);
				
				ptrCam->Begin();		
				weaponCollection.DrawObjects();				
			}
			
			void drawPlayerName(void) {
				gp2d::Font *ptrFont = GetFont("Names");
				gp2d::Camera			*ptrCam = GetCamera();
				iteam::PlayerObj		*ptrPlayer = sceneHashPlayers["Player1"];
		
				ptrCam->Begin();				
				Text(	*ptrFont,																					\
							(ptrPlayer->x+(VIEWPORT_WIDTH/2)-ptrCam->GetX())-18,	\
							(ptrPlayer->y+(VIEWPORT_HEIGHT/2)-ptrCam->GetY())-48,	\
							0,1,1,1, 0.1,0.1,0.1,																	\
							ptrPlayer->Name);
				Text(	*ptrFont,																					\
							(ptrPlayer->x+(VIEWPORT_WIDTH/2)-ptrCam->GetX())-20,	\
							(ptrPlayer->y+(VIEWPORT_HEIGHT/2)-ptrCam->GetY())-50,	\
							0,1,1,1, 1, 1, 1,																		\
							ptrPlayer->Name);						
			}

			void drawPlayerPosition(void) {
				gp2d::Camera			*ptrCam = GetCamera();
				iteam::PlayerObj		*ptrPlayer = sceneHashPlayers["Player1"];
		
				ptrCam->Begin();				
				Text( *sceneHashFont["GUI"], 10,48, 0,1,1,1, 1,1,1, "Player X: %f",ptrPlayer->x);
				Text( *sceneHashFont["GUI"], 10,48+16, 0,1,1,1, 1,1,1, "Player Y: %f",ptrPlayer->y);
			}
			void drawMissilePosition(void) {
				gp2d::Camera			*ptrCam = GetCamera();

				if (weaponCollection.numOfMissiles != 0) {
					ptrCam->Begin();
					Text( *sceneHashFont["GUI"], 10,80, 0,1,1,1, 1,1,1, "Missile X: %f",weaponCollection.missiles[0]->x);
					Text( *sceneHashFont["GUI"], 10,80+16, 0,1,1,1, 1,1,1, "Missile Y: %f",weaponCollection.missiles[0]->y);
				}
			}
			
			void updateGUI(void) {
				gp2d::Sprite 	*ptrBackGround = sceneHashBackGround["GUIBottom"];
				gp2d::Camera	*ptrCam = GetCamera();
								
				ptrCam->Begin();
				ptrBackGround->Move(	ptrCam->GetX()-((VIEWPORT_WIDTH/2)-ptrBackGround->width[0]/2),	\
														ptrCam->GetY()+((VIEWPORT_HEIGHT/2)-ptrBackGround->height[0]/2));
				ptrBackGround->Draw();				
			}
			
			void displayCameraCoords(void) {
				gp2d::Camera	*ptrCam = GetCamera();
				
				// Update the on screen camera values
				Text( *sceneHashFont["GUI"], 10,16, 0,1,1,1, 1,1,1, "Cam X: %f",ptrCam->GetX());
				Text( *sceneHashFont["GUI"], 10,16+16, 0,1,1,1, 1,1,1, "Cam Y: %f",ptrCam->GetY());							
			}
				
			void updateCamera(void) {
				gp2d::Camera		*ptrCam = GetCamera();
				iteam::PlayerObj	*ptrPlayer;

/*				
				if (ptrThisParent->currentPlayer == 0) {
					ptrPlayer = sceneHashPlayers["Player1"];
				}
				else {
					ptrPlayer = sceneHashPlayers["Player2"];
				}		
*/
				// TODO: For now just use player1				
				ptrPlayer = sceneHashPlayers["Player1"];
				
				ptrCam->Move(	CurveValueGLf(	ptrPlayer->x,												\
																		ptrCam->GetX(),											\
																		50.0f),															\
											CurveValueGLf(	ptrPlayer->y,												\
																		ptrCam->GetY(),											\
																		50.0f)															\
								);
/*		
				if(ptrCam->GetX()>1022){ ptrCam->Move(1022,ptrCam->GetY()); }
				if(ptrCam->GetX()<-220){ ptrCam->Move(-220,ptrCam->GetY()); }
				if(ptrCam->GetY()<200){ ptrCam->Move(ptrCam->GetX(),200); }
				if(ptrCam->GetY()>298){ ptrCam->Move(ptrCam->GetX(),298); }
*/				
				ptrCam->End();				
			}
			
		private:
			
			vector<PlayerObj> Player;
		
			gp2d::Sprite Terrain;
			gp2d::Sprite BGLayer1;
			gp2d::Sprite BGLayer2;
			gp2d::Sprite GUIBottom;
			gp2d::Sprite Countdown;
			
			gp2d::Font   FNTCounter;
			gp2d::Font   FNTNames;
			gp2d::Font   FNTGameGUI;
		
			gameMissiles	weaponCollection;
	};
}
