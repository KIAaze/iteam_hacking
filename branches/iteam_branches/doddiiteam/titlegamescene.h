#include "gamestate.h"

using namespace gp2d;

namespace iteam {
	
	class game;
		
	class titleGameScene : public gameScene
	{
		public:
			titleGameScene () {
				cameraVelocityX = 0.1;	// 1/10 of the texture size per second
				cameraVelocityY = cameraVelocityX / 5;				
			}
			
			~titleGameScene () {
			}
		
		
			// This function is used to assign all sprites, backgrounds etc
			// into the relevant map arrays used in a scene class
			void AssignResources(void) {

				//Backgrounds
				sceneHashBackGround["TitleScreen"] =	&TitleScreen;

				// Fonts used
				sceneHashFont["GUIFont"] = &FNTGameGUI;	
				sceneHashPlayers["donut"] = &doughnutSpin;
			}
			
			// This function physically loads all the resources required for the given state
			// into memory. This function could be used when the state enters the intialising
			// stage rather than all at the beginning to preserve memory usage.
			void LoadResources(void) {
				
				FNTGameGUI.Load("data/gui/ingame/eras_bold.TTF", 11);
		
//				Song = gp2d::LoadMusic("data/music/song1.ogg");
//				PlayMusic(Song,0);
				
				TitleScreen.Load("data/gui/title/intro.png");
				TitleScreen.SetWindowing(0, 0.4, 0.15, 0.15);				
				TitleScreen.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT/2);
				
//				doughnutSpin.Load("data/chars/donut.png", 4, 4);
				doughnutSpin.iterateSheets = true;
				doughnutSpin.setAnimationSpeed(12.0f);
				doughnutSpin.Load("data/chars/susi/1.png");
				doughnutSpin.Load("data/chars/susi/2.png");
				doughnutSpin.Load("data/chars/susi/3.png");
				doughnutSpin.Load("data/chars/susi/4.png");
				doughnutSpin.Load("data/chars/susi/5.png");
				doughnutSpin.Load("data/chars/susi/6.png");
				doughnutSpin.Load("data/chars/susi/7.png");
				doughnutSpin.Load("data/chars/susi/8.png");
				doughnutSpin.Load("data/chars/susi/9.png");
				doughnutSpin.Load("data/chars/susi/10.png");
				doughnutSpin.Load("data/chars/susi/11.png");
				doughnutSpin.Load("data/chars/susi/12.png");
				doughnutSpin.Name = "Test Anim";
				doughnutSpin.Move(VIEWPORT_WIDTH - doughnutSpin.width[0],VIEWPORT_HEIGHT - doughnutSpin.height[0]);

				AssignResources();
				
				sceneCamera.Create();
			}
									
			
			void intialise(void) {
		
				printf("titleGame load state called\n");
								
				// This rests the frame animation timer.
				sceneHashPlayers["donut"]->animationTimer.start();
			}
			
			void drawPressSpace(void) {								
				
				GetCamera()->Begin();
				Text( *sceneHashFont["GUIFont"], 100,100, 0,1,1,1, 1,1,1, "Press Space");
				Text( *sceneHashFont["GUIFont"], 120,120, 0,1,1,1, 1,1,1, "To Start");				
			}
			
			void drawScollingTitleScreen(Uint32 ticks) {
				
				gp2d::Sprite		*ptrBackGround;
				static bool finishScroll = false;
				static GLfloat x=0, y=0.5, w=0.15, h=0.15;
							
				GetCamera()->Begin();

				ptrBackGround = sceneHashBackGround["TitleScreen"];
				ptrBackGround->Move(512, 512);
		
				if (finishScroll == false) {
					
					// Get the distance the camera should move in pixels based on time changed
					x += gp2d::getMovementFactor(cameraVelocityX, ticks);
					if (x>0.3) {
						y += gp2d::getMovementFactor(cameraVelocityY, ticks);			
					}
					else {
						y -= gp2d::getMovementFactor(cameraVelocityY, ticks);
					}			
		
					if (x>=0.6)		// 60% across then jump to full screen
					{
						finishScroll = true;
						x = 0; y = 0; w = 1; h = 1;
					}
				}
				
				ptrBackGround->DrawFrame();
				ptrBackGround->SetWindowing(x, y, w, h);				
			}
			
			void drawDoughnut(void) {

				GetCamera()->Begin();
				
				sceneHashPlayers["donut"]->DrawFrame();
				sceneHashPlayers["donut"]->setNextFrame();
			}
			
		private:		
			PlayerObj doughnutSpin;
			gp2d::Sprite TitleScreen;		
			gp2d::Font   FNTGameGUI;
		
			GLfloat 		cameraVelocityX;
			GLfloat 		cameraVelocityY;
	};
}
