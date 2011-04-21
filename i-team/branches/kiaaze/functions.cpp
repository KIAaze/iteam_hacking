/*! \file functions.cpp
\brief Source for the main in-game functions (for now).
*/

#include "globals.h"
#include "functions.h"
#include "players.h"
#include "weapons.h"
#include "explosions.h"
#include <iostream>

#define MUSIC_ON false

namespace iteam {

	int GameResW;
	int GameResH;
	int CurPlayer;
	int CountdownValue;
	bool GameRunning;
	bool GamePaused=false;

	// Init the stuff
	int Init()
	{
		GameResW = 800;
		GameResH = 600;
		CountdownValue = 3;
		GameRunning = false;
		
		gp2d::SetDebug(true);
		gp2d::Init();
		gp2d::SetVideoMode(800,600,32,false,true);
		gp2d::SetFPS(60);
		gp2d::RandomSeed();
		gp2d::InitAudio(48000,AUDIO_S16,2,4096);
		atexit(SDL_Quit);
	}

	int Load()
	{
		Cam.Create();

		FNTCounter.Load("data/gui/ingame/counter.ttf", 64);
		FNTNames.Load("data/gui/ingame/eras_bold.TTF", 12);
		FNTGameGUI.Load("data/gui/ingame/eras_bold.TTF", 11);
		
//		Song.Load("data/music/song1.ogg");
//		Song.loop = -1;
//		if(MUSIC_ON) Song.Play();
		
//		Jump.Load("data/sound/jump.wav");

		init_rand();
		cout<<"random seed initialized"<<endl;

		//add players
		for(int i=0;i<2;i++)
		{
			AddPlayer(IT_PLAYER_SUSI,(int)rand_uniform(50,180),50,IT_PLAYER_FACE_RIGHT,1); 
			//Change player names to make it easier to differentiate them.
			sprintf(Player[i].Name,"Susi %d",i);
		}

		strcpy(Player[0].Team,"Good");
		strcpy(Player[1].Team,"Evil");

		Tank_base.Load("data/vehicles/tank_base.png", 1, 1);
		Tank_canon.Load("data/vehicles/tank_canon.png", 1, 1);

		Terrain.Load("data/levels/egypt/terrain.png");
		Terrain.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Terrain.height[0]/2);
		BGLayer2.Load("data/levels/egypt/layer2.png");
		BGLayer2.ResizePropW(GameResW);
		BGLayer1.Load("data/levels/egypt/layer1.png");
		BGLayer1.width[0]=2048;
		BGLayer1.height[0]=1024;

		GUIBottom.Load("data/gui/ingame/bottom.png");
		GUIBottom.ResizePropW(GameResW);
		GUIBottom.Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-GUIBottom.height[0]/2);

		Countdown.Load("data/gui/ingame/countdown_3.png");
		Countdown.Load("data/gui/ingame/countdown_2.png");
		Countdown.Load("data/gui/ingame/countdown_1.png");
		Countdown.Load("data/gui/ingame/countdown_duel.png");
		Countdown.iterateSheets = true;
		Countdown.setAnimationSpeed(1.0f);
		Countdown.animationTimer.Start();

		AnglePointer.Load("data/gui/ingame/angle_pointer.png");
		AnglePointer.Move(GUIBottom.x + 100, GUIBottom.y + 20);

		WeaponSelector.Load("data/weapons/weapon_selector.png");
		WeaponSelector.Scale(38./32.);
		WeaponSelector.Move(THUMBS_WIDTH, 600 - THUMBS_HEIGHT);
		
		//Test_Init();
		Init_Explosions();
		Weapons_Init();
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
		int fontwidths = 0;
		Cam.Begin();
		GUIBottom.Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-GUIBottom.width[0]/2),Cam.GetY()+((VIEWPORT_HEIGHT/2)-GUIBottom.height[0]/2));
		GUIBottom.Draw();
		if(GameResW==800){
			if(Player[CurPlayer].Angle > 9)	fontwidths += 6;	// adjust for centered text on angle meter
			if(Player[CurPlayer].Angle > 99)	fontwidths += 6;	
				
			Text(FNTGameGUI, 155-fontwidths,600-45, 0,1,1,1, 1,1,1, "%i%c",(unsigned int)Player[CurPlayer].Angle, 0xB0);
			Text(FNTGameGUI, 230,600-65, 0,1,1,1, 1,1,1, "%i",(int)Player[CurPlayer].Power);
		}
		UpdateWeaponThumbs();
		Cam.Begin();
		AnglePointer.Move(GUIBottom.x - (VIEWPORT_WIDTH/2) + 161, GUIBottom.y + 50);
		AnglePointer.angle = -Player[CurPlayer].Angle;//because GP2D uses non-trigonometrical direction for the angle while we use the trigonometrical direction
		AnglePointer.Draw();
		
		//WeaponSelector.Move(-(GUIBottom.x - (VIEWPORT_WIDTH/2) + 161)+(THUMBS_WIDTH), -(GUIBottom.y + 50)+(600 - THUMBS_HEIGHT));
		Cam.Begin();
		WeaponSelector.Move(Cam.GetX()-(VIEWPORT_WIDTH/2)+THUMBS_WIDTH+CurrentWeapon*34,Cam.GetY()-(VIEWPORT_HEIGHT/2)+(600 - THUMBS_HEIGHT));
		WeaponSelector.Draw();

		Text(FNTGameGUI, 10,16, 0,1,1,1, 1,1,1, "Cam X: %f",Cam.GetX());
		Text(FNTGameGUI, 10,16+16, 0,1,1,1, 1,1,1, "Cam Y: %f",Cam.GetY());
	}
}
