#include "globals.h"
#include "functions.h"
#include "players.h"

namespace iteam {

	int GameResW = 800;
	int GameResH = 600;
	int CurPlayer;
	int CountdownValue = 3;
	bool GameRunning = false;

	int Init()
	{
		gp2d::SetDebug(true);
		gp2d::Init();
		gp2d::SetVideoMode(800,600,32,false,true);
		Globals.FPS_max=200;
		Globals.FPS_min=60;
		gp2d::SetFPS(60);
		gp2d::RandomSeed();
		gp2d::InitAudio(48000,AUDIO_S16,2,4096);
	}

	int Load()
	{
		Cam.Create();

		FNTCounter.Load("data/gui/ingame/counter.ttf", 64);
		FNTNames.Load("data/gui/ingame/eras_bold.TTF", 12);
		FNTGameGUI.Load("data/gui/ingame/eras_bold.TTF", 11);

		gp2d::Song = LoadMusic("data/music/song1.ogg");
		PlayMusic(Song,0);

		AddPlayer(IT_PLAYER_SUSI,50,50,IT_PLAYER_FACE_RIGHT,1);
		AddPlayer(IT_PLAYER_SUSI,180,50,IT_PLAYER_FACE_LEFT,1);

		Terrain.Load("data/levels/egypt/terrain.png");
		Terrain.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Terrain.height[0]/2);
		BGLayer2.Load("data/levels/egypt/layer2.png");
		BGLayer2.ResizePropW(GameResW);
		BGLayer1.Load("data/levels/egypt/layer1.png");
		BGLayer1.width[0]=2048;
		BGLayer1.height[0]=1024;

		GUIBottom.Load("data/gui/ingame/bottom2.png");
		GUIBottom.ResizePropW(GameResW);
		GUIBottom.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-GUIBottom.height[0]/2);

		Countdown.Load("data/gui/ingame/countdown_3.png");
		Countdown.Load("data/gui/ingame/countdown_2.png");
		Countdown.Load("data/gui/ingame/countdown_1.png");
		Countdown.Load("data/gui/ingame/countdown_duel.png");		
	}

	void DrawBackground()
	{
		Cam.Begin();
			BGLayer2.Draw();
			BGLayer2.Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-GUIBottom.width[0]/2),(VIEWPORT_HEIGHT/2)-(Cam.GetY()/20));
		Cam.Begin();
			BGLayer1.Draw();
			BGLayer1.Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-GUIBottom.width[0]/2)+(Cam.GetX()/4),(VIEWPORT_HEIGHT/2)-(Cam.GetY()/10));
	}

	void DrawTerrain()
	{
		Cam.Begin();
		Terrain.Draw();
	}

	void DrawGUI()
	{
		Cam.Begin();
		GUIBottom.Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-GUIBottom.width[0]/2),Cam.GetY()+((VIEWPORT_HEIGHT/2)-GUIBottom.height[0]/2));
		GUIBottom.Draw();
		/*
		if(GameResW==800){
			Text(FNTGameGUI, 90,600-20, 0,1,1,1, 1,1,1, "%iº",Player[CurPlayer].Angle);
		}
		*/
		Text(FNTGameGUI, 10,16, 0,1,1,1, 1,1,1, "Cam X: %f",Cam.GetX());
		Text(FNTGameGUI, 10,16+16, 0,1,1,1, 1,1,1, "Cam Y: %f",Cam.GetY());
	}

}
