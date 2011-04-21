/*! \file functions.cpp
\brief Source for the main in-game functions (for now).
*/

#include "globals.h"
#include "functions.h"
#include "players.h"
#include "physics.h"
#include "WeaponsList.h"
#include "iteam_maths.h"
#include "explosions.h"
#include "iteam-ai.h"

// Add you include here for weapons
#include "iteamGrenade.h"
#include "iteamMissile.h"
#include "iteamClusterBomb.h"
#include "iteamDynamite.h"

// non local libararies
#include <iostream>

#define MUSIC_ON false

namespace iteam {

	int GameResW;
	int GameResH;
	int CurPlayer;
	int CountdownValue;
	bool GameRunning;
	int SecondsCounter, Seconds;


	//TODO: This should be changed
	void quitOrAdvanceProgram(void) {

		switch(gameState)   {
            case ITEAM_INTRO:
                gameState = ITEAM_INTROPOST;
                nextState = ITEAM_MAINMENUPRE;	// Go here after clean up
                break;
            case ITEAM_OPTIONSMENU:
                gameState = ITEAM_OPTIONSMENUPOST;
                nextState = ITEAM_MAINMENUPRE;
                break;
            default:
                printf("quit callback called\n");
                bQuitGame = true;

		}
	}

	// Intialises the GUI based mouse controlling
	// The available mouse pointer types are still basic
	// but very easily added. See unputhandler class MouseType
	void InitialiseMouse() {
		gp2d::Texture	*tex1, *tex2;
		tex1 = new gp2d::Texture();
		tex1->Load("data/gui/cursors/normal.png");
		tex2 = new gp2d::Texture();
		tex2->Load("data/gui/cursors/dynamite_ptr.png");

		GameCursor = new gp2d::CursorType();
		GameCursor->AddCursor(GP2D_CURSOR_NORMAL, tex1);
		GameCursor->AddCursor(GP2D_CURSOR_CROSS, tex2);

		GameCursor->SetCursor(GP2D_CURSOR_NORMAL);
		GameCursor->Enable(true);
		KeyHandler->registerMouseMoveCallback(GameCursor->Update);
	}

	// This function is responsible for registering the global events
	// i.e. Events that occur throughout the game
	void RegisterGlobalKeys() {

		// Make sure that we can get out of the game
		KeyHandler->registerInputCallback(SDLK_ESCAPE, quitOrAdvanceProgram, GP2D_KEYUP);

		//Change screen mode fullscreen/normal
		KeyHandler->registerInputCallback(SDLK_f, ToggleFullscreen, GP2D_KEYUP);
	}

	// This function is responsible for unregistering the global events
	// i.e. Events that occur throughout the game
	void UnRegisterGlobalKeys() {

		// Make sure that we can get out of the game
		KeyHandler->unregisterInputCallback(SDLK_ESCAPE);

		//Change screen mode fullscreen/normal
		KeyHandler->unregisterInputCallback(SDLK_f);
	}

	// This function gets registered with atexit
	// It will garauntee the sucesful
	void gameQuit() {
		// Make sure we ahvent deleted it already



		if (KeyHandler != NULL) {
			delete KeyHandler;
		}

		for(int i = 0; i < InGameGUI.size(); i++)   {
		    delete InGameGUI[i];
		}

        for(int i = 0; i < Player.size(); i++)  {
            delete Player[i];
        }
        for(int i = 0; i < Level.size(); i++)  {
            delete Level[i];
        }

        //for(int i = 0; i < Font.size(); i++)  {
        //    delete &Font[i];
        //}
        //delete &Song[0];

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

		init_rand();
		cout<<"random seed initialized"<<endl;

		//add players
		for(int i=0;i<2;i++)
		{
			AddPlayer(IT_PLAYER_SUSI,(int)rand_uniform(50,180),50,IT_PLAYER_FACE_RIGHT,1);
			//Change player names to make it easier to differentiate them.
			sprintf(Player[i]->Name,"Susi %d",i);
		}

		strcpy(Player[0]->Team,"Good");
		strcpy(Player[1]->Team,"Evil");

		Tank_base.Load("data/vehicles/tank_base.png", 1, 1);
		Tank_canon.Load("data/vehicles/tank_canon.png", 1, 1);


		gp2d::Sprite* l_LevelSprite= new gp2d::Sprite();

		l_LevelSprite->Load("data/levels/grassymt/terrain.png");
		l_LevelSprite->Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-l_LevelSprite->height[0]/2);

		Level.push_back(l_LevelSprite);

		l_LevelSprite = new gp2d::Sprite();
		l_LevelSprite->Load("data/levels/grassymt/layer1.png");
		l_LevelSprite->width[0]=2048;
		l_LevelSprite->height[0]=1024;

		Level.push_back(l_LevelSprite);

		l_LevelSprite= new gp2d::Sprite();

		l_LevelSprite->Load("data/levels/grassymt/layer2.png");


		l_LevelSprite->ResizePropW(GameResW);
		Level.push_back(l_LevelSprite);


		gp2d::Sprite* l_InGameGUISprite = new gp2d::Sprite();

		l_InGameGUISprite->Load("data/gui/ingame/bottom2.png");
		l_InGameGUISprite->ResizePropW(GameResW);
		l_InGameGUISprite->Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-l_InGameGUISprite->height[0]/2);
		l_InGameGUISprite->alpha[0]=0.9f;
        InGameGUI.push_back(l_InGameGUISprite);

        l_InGameGUISprite = new gp2d::Sprite();
		l_InGameGUISprite->Load("data/gui/ingame/countdown_3.png");
		l_InGameGUISprite->Load("data/gui/ingame/countdown_2.png");
		l_InGameGUISprite->Load("data/gui/ingame/countdown_1.png");
		l_InGameGUISprite->Load("data/gui/ingame/countdown_duel.png");
		l_InGameGUISprite->iterateSheets = true;
		l_InGameGUISprite->setAnimationSpeed(1.0f);
		l_InGameGUISprite->animationTimer.Start();
		InGameGUI.push_back(l_InGameGUISprite);

		AnglePointer.Load("data/gui/ingame/angle_pointer.png");
		AnglePointer.Move(iteam::InGameGUI[0]->GetX() + 100, iteam::InGameGUI[0]->GetY() + 20);

		WeaponSelector.Load("data/weapons/weapon_selector.png");
		WeaponSelector.Scale(38./32.);
		WeaponSelector.Move(THUMBS_WIDTH, 600 - THUMBS_HEIGHT);
        InitPhysics();


		//Test_Init();
		Init_Explosions();
		InitWeapons(iteamPhysics);

        for(int i=0; i < Player.size(); i++)    {
            // iteamPhysics->AddObject(Player[i]);
            PlayerObj* l_Player =  Player[i];

            l_Player->JumpPower = 7.0 * iteamPhysics->OneMeterInPixels();
            l_Player->m_FirePower = 7.0 * iteamPhysics->OneMeterInPixels();
            l_Player->SetPlayerWeapon(iteamWeapons->AccessWeapon(0));
            iteamPhysics->AddObject(l_Player);
		}



	}

	int LoadSinglePlayer()
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

		init_rand();
		cout<<"random seed initialized"<<endl;

		//add players
		AddPlayer(IT_PLAYER_SUSI,(int)rand_uniform(50,180),50,IT_PLAYER_FACE_RIGHT,1);
		//Change player names to make it easier to differentiate them.
		sprintf(Player[0]->Name,"Susi 1");




		strcpy(Player[0]->Team,"Good");
		strcpy(Player[1]->Team,"VEry GOOD");

		Tank_base.Load("data/vehicles/tank_base.png", 1, 1);
		Tank_canon.Load("data/vehicles/tank_canon.png", 1, 1);

        gp2d::Sprite* l_LevelSprite= new gp2d::Sprite();

		l_LevelSprite->Load("data/levels/grassymt/terrain.png");
		l_LevelSprite->Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-l_LevelSprite->height[0]/2);

		Level.push_back(l_LevelSprite);

		l_LevelSprite = new gp2d::Sprite();
		l_LevelSprite->Load("data/levels/grassymt/layer1.png");
		l_LevelSprite->width[0]=2048;
		l_LevelSprite->height[0]=1024;

		Level.push_back(l_LevelSprite);

		l_LevelSprite = new gp2d::Sprite();

		l_LevelSprite->Load("data/levels/grassymt/layer2.png");


		l_LevelSprite->ResizePropW(GameResW);
		Level.push_back(l_LevelSprite);





		gp2d::Sprite* l_InGameGUISprite = new gp2d::Sprite();

		l_InGameGUISprite->Load("data/gui/ingame/bottom2.png");
		l_InGameGUISprite->ResizePropW(GameResW);
		l_InGameGUISprite->Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-l_InGameGUISprite->height[0]/2);
		l_InGameGUISprite->alpha[0]=0.9f;
        InGameGUI.push_back(l_InGameGUISprite);

        l_InGameGUISprite = new gp2d::Sprite();
		l_InGameGUISprite->Load("data/gui/ingame/countdown_3.png");
		l_InGameGUISprite->Load("data/gui/ingame/countdown_2.png");
		l_InGameGUISprite->Load("data/gui/ingame/countdown_1.png");
		l_InGameGUISprite->Load("data/gui/ingame/countdown_duel.png");
		l_InGameGUISprite->iterateSheets = true;
		l_InGameGUISprite->setAnimationSpeed(1.0f);
		l_InGameGUISprite->animationTimer.Start();
		InGameGUI.push_back(l_InGameGUISprite);

		AnglePointer.Load("data/gui/ingame/angle_pointer.png");
		AnglePointer.Move(iteam::InGameGUI[0]->GetX() + 100, iteam::InGameGUI[0]->GetY() + 20);

		WeaponSelector.Load("data/weapons/weapon_selector.png");
		WeaponSelector.Scale(38./32.);
		WeaponSelector.Move(THUMBS_WIDTH, 600 - THUMBS_HEIGHT);
        InitPhysics();


		//Test_Init();
		Init_Explosions();
		InitWeapons(iteamPhysics);

		AddAIPlayer(IT_PLAYER_SUSI,(int)rand_uniform(50,180),50,IT_PLAYER_FACE_RIGHT,1);
		//Change player names to make it easier to differentiate them.
		sprintf(Player[1]->Name,"AI Player 1");

        for(int i=0; i < Player.size(); i++)    {
            // iteamPhysics->AddObject(Player[i]);
            PlayerObj* l_Player =  Player[i];

            l_Player->JumpPower = 7.0 * iteamPhysics->OneMeterInPixels();
            l_Player->m_FirePower = 7.0 * iteamPhysics->OneMeterInPixels();
            l_Player->SetPlayerWeapon(iteamWeapons->AccessWeapon(0));

            iteamPhysics->AddObject(l_Player);
		}
        PlayerObj* l_Player =  Player[0];
        l_Player->SetTimeToTakeMyTurn();

	}

	void DestroyRunningGame() {
        for(int i=0; i < Player.size(); i++)    {
            delete Player[i];
        }


        delete iteamWeapons;


	}


	void DrawBackground()
	{
		Cam.Begin();
			Level[2]->Draw();
			Level[2]->Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-InGameGUI[0]->width[0]/2),(VIEWPORT_HEIGHT/2)-(Cam.GetY()/20));
		Cam.Begin();
			Level[1]->Draw();
			Level[1]->Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-InGameGUI[0]->width[0]/2)+(Cam.GetX()/4),(VIEWPORT_HEIGHT/2)-(Cam.GetY()/10));
	}

	void DrawTerrain()
	{
		Cam.Begin();
		Level[0]->Draw();
	}


	void DrawGUI()
	{
	    PlayerObj* l_Player = Player[CurPlayer];
		int fontwidths = 0;
		Cam.Begin();
		InGameGUI[0]->Move(Cam.GetX()-((VIEWPORT_WIDTH/2)-InGameGUI[0]->width[0]/2),Cam.GetY()+((VIEWPORT_HEIGHT/2)-InGameGUI[0]->height[0]/2));
		InGameGUI[0]->Draw();
		if(GameResW==800){
			if(Player[CurPlayer]->m_FireAngle > 9)	fontwidths += 6;	// adjust for centered text on m_FireAngle meter
			if(Player[CurPlayer]->m_FireAngle > 99)	fontwidths += 6;

			Text(iteam::Font[1], 155-fontwidths,600-45, 0,1,1,1, 1,1,1, "%i%c",(unsigned int)l_Player->m_FireAngle, 0xB0);
			Text(iteam::Font[1], 230,600-65, 0,1,1,1, 1,1,1, "%i",(int)l_Player->m_FirePower);
		}
		iteamWeapons->UpdateWeaponThumbs();
		Cam.Begin();
		AnglePointer.Move(InGameGUI[0]->GetX() - (VIEWPORT_WIDTH/2) + 161, InGameGUI[0]->GetY() + 50);
		AnglePointer.angle = -Player[CurPlayer]->m_FireAngle;//because GP2D uses non-trigonometrical direction for the m_FireAngle while we use the trigonometrical direction
		AnglePointer.Draw();

		//WeaponSelector.Move(-(GUIBottom.x - (VIEWPORT_WIDTH/2) + 161)+(THUMBS_WIDTH), -(GUIBottom.y + 50)+(600 - THUMBS_HEIGHT));
		Cam.Begin();
		WeaponSelector.Move(Cam.GetX()-(VIEWPORT_WIDTH/2)+THUMBS_WIDTH+CurrentWeapon*34,Cam.GetY()-(VIEWPORT_HEIGHT/2)+(600 - THUMBS_HEIGHT));
		WeaponSelector.Draw();

		Text(iteam::Font[2], 10,16, 0,1,1,1, 1,1,1, "Cam X: %f",Cam.GetX());
		Text(iteam::Font[2], 10,16+16, 0,1,1,1, 1,1,1, "Cam Y: %f",Cam.GetY());
        Weapon* l_Weapon = iteamWeapons->AccessWeapon(l_Player->PlayerWeaponID());
        Text(iteam::Font[1], 10,600-165, 0,1,1,1, 1,1,1, "Weapon VX: %f",l_Weapon->AccessComponent(0)->GetVX());
        Text(iteam::Font[1], 10,600-155, 0,1,1,1, 1,1,1, "Weapon VY: %f",l_Weapon->AccessComponent(0)->GetVY());
        Text(iteam::Font[1], 10,600-135, 0,1,1,1, 1,1,1, "Weapon X: %f",l_Weapon->AccessComponent(0)->GetX());
        Text(iteam::Font[1], 10,600-145, 0,1,1,1, 1,1,1, "Weapon Y: %f",l_Weapon->AccessComponent(0)->GetY());
	}

	void NextTurn()
	{
	    PlayerObj* l_Player = Player[CurPlayer];
		l_Player->CanMove=false;
		l_Player->CanJump=false;
		l_Player->setAnimationSpeed(0.0f);
		l_Player->Movement.walkingRight = false;
		l_Player->Movement.walkingLeft = false;
        l_Player->SetNotTimeToTakeMyTurn();
		CurPlayer++;
		Seconds=20;
		if(CurPlayer>1){
		    CurPlayer=0;
		}
		l_Player = Player[CurPlayer];
		l_Player->CanMove=true;
		l_Player->CanJump=true;
		l_Player->SetTimeToTakeMyTurn();
	}

	void InitPhysics()
    {
        iteamPhysics = new PhysicsSystem();
    }

    void InitWeapons(PhysicsSystem *physics)
    {    // ============================ GRENADES ===========================================

        iteamWeapons = new WeaponsList();
        iteamGrenade* l_Grenade = new iteamGrenade();

        l_Grenade->UsePhysicsSystem(physics);
        iteamWeapons->Add(l_Grenade);

        iteamMissile* l_Missile = new iteamMissile();
        l_Missile->UsePhysicsSystem(physics);
        iteamWeapons->Add(l_Missile);

        iteamClusterBomb* l_ClusterBomb = new iteamClusterBomb();
        l_ClusterBomb->UsePhysicsSystem(physics);
        iteamWeapons->Add(l_ClusterBomb);

        iteamDynamite* l_Dynamite = new iteamDynamite();
        l_Dynamite->UsePhysicsSystem(physics);
        iteamWeapons->Add(l_Dynamite);

	/*AddWeaponTypeToWeaponsList(THUMBS_WIDTH + IT_WT_GRENADE*34, 600 - THUMBS_HEIGHT, IT_WT_GRENADE, "data/weapons/grenade.png" );

	// ============================ MISSILES ============================================
	AddWeaponTypeToWeaponsList(THUMBS_WIDTH + IT_WT_MISSILE*34, 600 - THUMBS_HEIGHT, IT_WT_MISSILE, "data/weapons/missile.png" );
	AddComponent(0, IT_WT_MISSILE, "data/weapons/missile.png", true, true, (GLfloat) IT_WT_MISSILE_BLAST_RADIUS,IT_WT_MISSILE_BLAST_FACTOR,IT_WT_MISSILE_BLAST_DAMAGE, (GLfloat) 0, 0);

	// ============================ CLUSTER BOMBS =======================================
	AddWeaponTypeToWeaponsList(THUMBS_WIDTH + IT_WT_CLUSTERBOMB*34, 600 - THUMBS_HEIGHT, IT_WT_CLUSTERBOMB, "data/weapons/cluster_bomb.png" );
	AddComponent(0, IT_WT_CLUSTERBOMB, "data/weapons/grenade.png", true, true, (GLfloat) IT_WT_CLUSTERBOMB_BLAST_RADIUS,IT_WT_CLUSTERBOMB_BLAST_FACTOR,IT_WT_CLUSTERBOMB_BLAST_DAMAGE, (GLfloat) 0.80, grenade_time, true);//main grenade active at first
	for(int i=1;i<9;i++)//add baby grenades
	{
		AddComponent(i, IT_WT_CLUSTERBOMB, "data/weapons/grenade.png", true, true, (GLfloat) IT_WT_CLUSTERBOMB_BLAST_RADIUS,IT_WT_CLUSTERBOMB_BLAST_FACTOR,IT_WT_CLUSTERBOMB_BLAST_DAMAGE, (GLfloat) 0.80, grenade_time, false, 0.5);//inactive at first
	}

	// ============================ DYNAMITE ===========================================
	AddWeaponTypeToWeaponsList(THUMBS_WIDTH + IT_WT_DYNAMITE*34, 600 - THUMBS_HEIGHT, IT_WT_DYNAMITE, "data/weapons/dynamite.png" );
	AddComponent(0, IT_WT_DYNAMITE, "data/weapons/dynamite.png", true, true, (GLfloat) IT_WT_DYNAMITE_BLAST_RADIUS,IT_WT_DYNAMITE_BLAST_FACTOR,IT_WT_DYNAMITE_BLAST_DAMAGE, (GLfloat) 0, dynamite_time);

	// ============================ PISTOL ===========================================
	AddWeaponTypeToWeaponsList(THUMBS_WIDTH + IT_WT_PISTOL*34, 600 - THUMBS_HEIGHT, IT_WT_PISTOL, "data/weapons/pistol.png" );
	*/
    }

    void DoIteamBehaviours()
    {
        // Weapons
        iteamWeapons->DoWeaponBehaviours();

        // Players Last
        for(int i = 0; i < Player.size(); i++)  {
            Player[i]->DoBehaviours();
        }


    }


}

