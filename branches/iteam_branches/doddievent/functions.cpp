#include "globals.h"

namespace iteam {

	int GameResW;
	int GameResH;
	int CurPlayer;
	int CountdownValue;
	bool GameRunning;
	int SecondsCounter, Seconds;

	void quitProgram(void) {
		printf("quit callback called\n");	
		bQuitGame = true;
	}

	// This function is responsible for registering the global events
	// i.e. Events that occur throughout the game
	void RegisterGlobalKeys() {

		// Make sure that we can get out of the game
		KeyHandler->registerInputCallback(SDLK_ESCAPE, quitProgram, GP2D_KEYUP);

		//Change screen mode fullscreen/normal
		KeyHandler->registerInputCallback(SDLK_f, ToggleFullscreen, GP2D_KEYUP);		
	}

	void gameQuit() {
		// Make sure we ahvent deleted it already
		printf("closing down event handler\n");
		if (KeyHandler != NULL) {
			delete KeyHandler;
		}

		SDL_Quit();
	}

	// Init the stuff
	int Init()
	{
		GameResW = 800;
		GameResH = 600;
		
		gp2d::SetDebug(true);

		gp2d::Init();
		gp2d::SetVideoMode(800,600,32,false,true);

		gp2d::SetFPS(60);
		gp2d::RandomSeed();
		gp2d::InitAudio(48000,AUDIO_S16,2,4096);

		atexit(gameQuit);
	}

	int Load()
	{
		CountdownValue = 3;
		GameRunning = false;
		
		Cam.Create();

		iteam::Font.push_back(gp2d::Font()); iteam::Font[0].Load("data/gui/ingame/counter.ttf", 64);
		iteam::Font.push_back(gp2d::Font()); iteam::Font[1].Load("data/gui/ingame/eras_bold.TTF", 12);
		iteam::Font.push_back(gp2d::Font()); iteam::Font[2].Load("data/gui/ingame/eras_bold.TTF", 11);
		
		Audio.push_back(gp2d::Sound());
		Audio.push_back(gp2d::Sound());
		Audio[0].LoadWAV("data/sound/characters/jump.wav");
		Audio[1].LoadWAV("data/sound/interface/clock5.wav");
		
		Song.push_back(gp2d::Music());
		Song[0].Load("data/music/song1.ogg");
		Song[0].SetLoop(-1);
		Song[0].Play();
		
		AddPlayer(IT_PLAYER_SUSI,iRand(0,800),50,IT_PLAYER_FACE_LEFT,1);
		AddPlayer(IT_PLAYER_SUSI,iRand(0,800),50,IT_PLAYER_FACE_RIGHT,1);

		Level.push_back(gp2d::Sprite());
		Level.push_back(gp2d::Sprite());
		Level.push_back(gp2d::Sprite());
		Level[0].Load("data/levels/grassymt/terrain.png");
		Level[1].Load("data/levels/grassymt/layer1.png");
		Level[2].Load("data/levels/grassymt/layer2.png");
		Level[0].Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Level[0].height[0]/2);
		Level[1].width[0]=2048;
		Level[1].height[0]=1024;
		Level[2].ResizePropW(GameResW);

		InGameGUI.push_back(gp2d::Sprite());
		InGameGUI.push_back(gp2d::Sprite());
		InGameGUI[0].Load("data/gui/ingame/bottom2.png");
		InGameGUI[0].ResizePropW(GameResW);
		InGameGUI[0].Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-InGameGUI[0].height[0]/2);
		InGameGUI[0].alpha[0]=0.9f;

		InGameGUI[1].Load("data/gui/ingame/countdown_3.png");
		InGameGUI[1].Load("data/gui/ingame/countdown_2.png");
		InGameGUI[1].Load("data/gui/ingame/countdown_1.png");
		InGameGUI[1].Load("data/gui/ingame/countdown_duel.png");
		InGameGUI[1].iterateSheets = true;
		InGameGUI[1].setAnimationSpeed(1.0f);
		InGameGUI[1].animationTimer.Start();
		
		Test_Init();
	}
	
	void DrawBackground()
	{
		Cam.Begin();
			Level[2].Draw();
			Level[2].Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-InGameGUI[0].width[0]/2),(VIEWPORT_HEIGHT/2)-(Cam.GetY()/20));
		Cam.Begin();
			Level[1].Draw();
			Level[1].Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-InGameGUI[0].width[0]/2)+(Cam.GetX()/4),(VIEWPORT_HEIGHT/2)-(Cam.GetY()/10));
	}

	void DrawTerrain()
	{
		Cam.Begin();
		Level[0].Draw();
	}
	
	void DrawGUI()
	{
		Cam.Begin();
		InGameGUI[0].Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-InGameGUI[0].width[0]/2),Cam.GetY()+((VIEWPORT_HEIGHT/2)-InGameGUI[0].height[0]/2));
		InGameGUI[0].Draw();
	}
	
	void NextTurn()
	{
		Player[CurPlayer].CanMove=false;
		Player[CurPlayer].CanJump=false;
		CurPlayer++;
		Seconds=20;
		if(CurPlayer>1){ 
			Player[CurPlayer].CanMove=false;
			Player[CurPlayer].CanJump=false;
			CurPlayer=0;
		}
		Player[CurPlayer].CanMove=true;
		Player[CurPlayer].CanJump=true;
	}

}
