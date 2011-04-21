#ifndef _firstgame_h
#define _firstgame_h

#include "titlegamescene.h"
#include "titlegamestate.h"
#include "runningGameScenes.h"
#include "runningGameStates.h"
#include "game.h"
#include "gamescene.h"
#include "gamestate.h"

namespace iteam
{	
	class firstGame : public game
	{
		public:
			firstGame() {
				
				GameResW = 800;
				GameResH = 600;
				
				currentPlayer = 0;
				currentState = TITLE_SCREEN;
			}
			
			~firstGame() {
			}
			
			bool init () {
				
				gp2d::SetDebug(true);
				gp2d::Init();
				gp2d::SetVideoMode(GameResW,GameResH,32,false,true);
				Globals.FPS_max=200;
				Globals.FPS_min=60;
				gp2d::SetFPS(60);
				gp2d::RandomSeed();
				gp2d::InitAudio(48000,AUDIO_S16,2,4096);				
				
				myTitleState.ptrParent = this;
				myPreRunState.ptrParent = this;
				myRunningState.ptrParent = this;
			}
			
			bool LoadScenes(void)
			{
				myTitleScene.LoadResources();
				myTitleState.addScene(&myTitleScene);
				
				myRunningScene.LoadResources();
				myRunningState.addScene(&myRunningScene);
				
				myPreRunScene.LoadResources();				
				myPreRunState.addScene(&myPreRunScene);
			}
						
			bool AddStates(void)			
			{				
				AddGameState(&myTitleState);
				AddGameState(&myPreRunState);
				AddGameState(&myRunningState);							
			}
			
			bool game_keysHandler(void) {
				
				if(gp2d::KeyPressed(SDLK_ESCAPE)) {
					
					// At this point the state should be changed to the quiting state
					return false; 
				}
				
				if(gp2d::KeyPressed(SDLK_f)) {
					gp2d::ToggleFullscreen(); 
				}
				
				// Always remember to call the base classes function too
				game::game_keysHandler();
				
				return true;
			}

			bool game_handlePlayers(void) {
				
				// Always remember to call the base classes function too
				game::game_handlePlayers();

				myGameTimer.start();							// Start the delta timer						
				
				return true;
			}
					
		private:		
				
			// To replicate the current game we will need 2 states creating
			// 1. The countdown screen.
			// 2. The actual running game.
			titleState					myTitleState;
			prerunState		 		myPreRunState;
			runningState			myRunningState;			
		
			// For this game we only rquire one scene shared between all states
			titleGameScene					myTitleScene;		
			prerunGameScene				myPreRunScene;		
			runningGameScene 				myRunningScene;
		
			int GameResW;
			int GameResH;
	};	
}

#endif
