/*! \file functions.cpp
\brief Source for the main in-game functions (for now).
*/

#include "globals.h"
#include "functions.h"
#include "players.h"
#include "weapons.h"
#include "iteam_maths.h"
#include "explosions.h"
#include "iteam-ai.h"
#include <iostream>

#include "iteamGrenade.h"

#define MUSIC_ON false

namespace iteam {

	int GameResW;
	int GameResH;
	int CurPlayer;
	int CountdownValue;
	bool GameRunning;
	int SecondsCounter, Seconds;
	vector <gp2d::Texture*> Player_Texture;
	vector <gp2d::Texture*> Weapon_Texture;
	vector <gp2d::Texture*> Explosion_Texture;

	//TODO: This should be changed
	void quitOrAdvanceProgram ( void ) {

		if ( gameState==ITEAM_INTRO ) {
			gameState = ITEAM_INTROPOST;
			nextState = ITEAM_MAINMENUPRE;	// Go here after clean up
		} else if ( gameState==ITEAM_OPTIONSMENU ) {
			gameState = ITEAM_OPTIONSMENUPOST;
			nextState = ITEAM_MAINMENUPRE;
		} else if ( gameState==ITEAM_MAINMENU ) {
			gameState = ITEAM_MAINMENUPOST;
			nextState = ITEAM_COUNTDOWNPRE;
		} else if ( gameState==ITEAM_COUNTDOWN ) {
			gameState = ITEAM_COUNTDOWNPOST;
			nextState = ITEAM_RUNNINGPRE;
		} else if ( gameState==ITEAM_RUNNING ) {
			gameState = ITEAM_RUNNINGPOST;
			nextState = ITEAM_MAINMENUPRE;
		} else if ( gameState==ITEAM_GAMEOVER ) {
			gameState = ITEAM_RUNNINGPOST;
			nextState = ITEAM_MAINMENUPRE;
		} else {
			printf ( "quit callback called\n" );
			bQuitGame = true;
		}
	}

	// Intialises the GUI based mouse controlling
	// The available mouse pointer types are still basic
	// but very easily added. See unputhandler class MouseType
	void InitialiseMouse() {
		gp2d::Texture	*tex1, *tex2;
		tex1 = new gp2d::Texture();
		tex1->Load ( "data/gui/cursors/normal.png" );
		tex2 = new gp2d::Texture();
		tex2->Load ( "data/gui/cursors/dynamite_ptr.png" );

		cout<<"initializing GameCursor"<<endl;
		GameCursor = new gp2d::CursorType();
		cout<<"Adding cursor normal"<<endl;
		GameCursor->AddCursor ( GP2D_CURSOR_NORMAL, tex1 );
		cout<<"Adding cursor cross"<<endl;
		GameCursor->AddCursor ( GP2D_CURSOR_CROSS, tex2 );

// 		if(!glIsTexture(GameCursor->CursorTextures[0].id))
// 		{
// 			PrintDebug("[InitialiseMouse] FATAL ERROR");exit(27);
// 		}

		GameCursor->SetCursor ( GP2D_CURSOR_NORMAL );
		GameCursor->Enable ( true );
		KeyHandler->registerMouseMoveCallback ( GameCursor->Update );
	}

	void TakeScreenshot() {
		SDL_OGL_SaveScreenshot ( "screenshot.bmp" );
	}

	// This function is responsible for registering the global events
	// i.e. Events that occur throughout the game
	void RegisterGlobalKeys() {

		// Make sure that we can get out of the game
		KeyHandler->registerInputCallback ( SDLK_ESCAPE, quitOrAdvanceProgram, GP2D_KEYUP );

		//Change screen mode fullscreen/normal
		KeyHandler->registerInputCallback ( SDLK_f, ToggleFullscreen, GP2D_KEYUP );
		KeyHandler->registerInputCallback ( SDLK_l, TakeScreenshot, GP2D_KEYUP );

	}

	// This function is responsible for unregistering the global events
	// i.e. Events that occur throughout the game
	void UnRegisterGlobalKeys() {

		// Make sure that we can get out of the game
		KeyHandler->unregisterInputCallback ( SDLK_ESCAPE );

		//Change screen mode fullscreen/normal
		KeyHandler->unregisterInputCallback ( SDLK_f );
	}

	// This function gets registered with atexit
	// It will garauntee a clean exit
	void gameQuit() {
		switch ( gameState ) {
			case ITEAM_INTROPRE:
				IntroPre();
				break;
			case ITEAM_INTRO:
				Intro();
				break;
			case ITEAM_INTROPOST:
				IntroPost();
				break;
			case ITEAM_MAINMENUPRE:
				MainMenuPre();
				break;
			case ITEAM_MAINMENU:
				MainMenu();
				break;
			case ITEAM_MAINMENUPOST:
				MainMenuPost();
				break;
			case ITEAM_OPTIONSMENUPRE:
				OptionsMenuPre();
				break;
			case ITEAM_OPTIONSMENU:
				OptionsMenu();
				break;
			case ITEAM_OPTIONSMENUPOST:
				OptionsMenuPost();
				break;
			case ITEAM_COUNTDOWNPRE:
				break;
			case ITEAM_COUNTDOWN:
				break;
			case ITEAM_RUNNINGPRE:
				break;
			case ITEAM_RUNNING:
				break;
		}

		// Make sure we haven't deleted it already
		if ( KeyHandler != NULL ) {
			delete KeyHandler;
		}

		SDL_Quit();
	}

	// Init the stuff
	int Init() {
		GameResW = 800;
		GameResH = 600;

		gp2d::SetDebug ( gnDebug );//set to false to remove all PrintDebug statements
		gp2d::Init();
		gp2d::SetVideoMode ( 800,600,32,false,true );
		gp2d::SetFPS ( 60 );
		gp2d::RandomSeed();
		gp2d::InitAudio ( 48000,AUDIO_S16,2,4096 );
		//atexit ( gameQuit );
		return ( 0 );
	}

	int LoadGameData() {
		CountdownValue = 3;
		GameRunning = false;

		Cam.Create();

		iteam::Font.push_back ( gp2d::Font() ); iteam::Font[0].Load ( "data/gui/ingame/counter.ttf", 64 );
		iteam::Font.push_back ( gp2d::Font() ); iteam::Font[1].Load ( "data/gui/ingame/eras_bold.TTF", 12 );
		iteam::Font.push_back ( gp2d::Font() ); iteam::Font[2].Load ( "data/gui/ingame/eras_bold.TTF", 11 );

		Audio.push_back ( gp2d::Sound() );
		Audio.push_back ( gp2d::Sound() );
		Audio[0].LoadWAV ( "data/sound/characters/jump.wav" );
		Audio[1].LoadWAV ( "data/sound/interface/clock5.wav" );

		Song.push_back ( gp2d::Music() );
		Song[0].Load ( "data/music/song1.ogg" );
		Song[0].SetLoop ( -1 );
		if ( music_on ) Song[0].Play();

		//Load textures
		Player_Texture.push_back ( new Texture ( "./data/chars/susi_film_2of2.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/susi_died_animation.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/susi_film_1of2.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/susi_gun_trowing_animation.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/susi_loses_energy_animation.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/susi_standby_eyes_blink_animation.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/susi_standby_eyes_looking_animation.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/susi_walking_animation.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/frog.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/lini_character.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/susi.png" ) );
		Player_Texture.push_back ( new Texture ( "./data/chars/ubin_character.png" ) );

		Weapon_Texture.push_back ( new Texture ( "./data/weapons/grenade.png" ) );
		Weapon_Texture.push_back ( new Texture ( "./data/weapons/missile.png" ) );
		Weapon_Texture.push_back ( new Texture ( "./data/weapons/cluster_bomb.png" ) );
		Weapon_Texture.push_back ( new Texture ( "./data/weapons/dynamite.png" ) );
		Weapon_Texture.push_back ( new Texture ( "./data/weapons/leaves.png" ) );
		Weapon_Texture.push_back ( new Texture ( "./data/weapons/iteam_leaves_animation.png" ) );
		Weapon_Texture.push_back ( new Texture ( "./data/weapons/bandaid.png" ) );

		Explosion_Texture.push_back ( new Texture ( "./data/explosions/explo1.png" ) );
		Explosion_Texture.push_back ( new Texture ( "./data/explosions/explo2.png" ) );

		init_rand();
		cout<<"random seed initialized"<<endl;

		//add players
		for ( int i=0;i<2;i++ ) {
			AddPlayer ( IT_PLAYER_SUSI, ( int ) rand_uniform ( 50,180 ),50,IT_PLAYER_FACE_RIGHT,1 );
			//Change player names to make it easier to differentiate them.
			sprintf ( Player[i].Name,"Susi %d",i );
		}

		strcpy ( Player[0].Team,"Good" );
		strcpy ( Player[1].Team,"Evil" );
		//Player[1].currentSheet=1;

		Level.push_back ( gp2d::Sprite() );
		Level.push_back ( gp2d::Sprite() );
		Level.push_back ( gp2d::Sprite() );
		Level[0].Load ( "data/levels/grassymt/terrain.png" );
		Level[1].Load ( "data/levels/grassymt/layer1.png" );
		Level[2].Load ( "data/levels/grassymt/layer2.png" );
		Level[0].Move ( VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Level[0].height[0]/2 );
		Level[1].width[0]=2048;
		Level[1].height[0]=1024;
		Level[2].ResizePropW ( GameResW );

		InGameGUI.push_back ( gp2d::Sprite() );
		InGameGUI.push_back ( gp2d::Sprite() );
		InGameGUI[0].Load ( "data/gui/ingame/bottom2.png" );
		InGameGUI[0].ResizePropW ( GameResW );
		InGameGUI[0].Move ( VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-InGameGUI[0].height[0]/2 );
		InGameGUI[0].alpha[0]=0.9f;

		InGameGUI[1].Load ( "data/gui/ingame/countdown_3.png" );
		InGameGUI[1].Load ( "data/gui/ingame/countdown_2.png" );
		InGameGUI[1].Load ( "data/gui/ingame/countdown_1.png" );
		InGameGUI[1].Load ( "data/gui/ingame/countdown_duel.png" );
		InGameGUI[1].iterateSheets = true;
		InGameGUI[1].setAnimationSpeed ( 1.0f );
		InGameGUI[1].animationTimer.Start();
		int check=InGameGUI[1].animationTimer.GetTicks();
		Tank_base.Load ( "data/vehicles/tank_base.png", 1, 1 );
		Tank_base.Scale ( 0.4 );
		Tank_canon.Load ( "data/vehicles/tank_canon.png", 1, 1 );
		Tank_canon.Scale ( 0.4 );

		AnglePointer.Load ( "data/gui/ingame/angle_pointer.png" );
		AnglePointer.Move ( iteam::InGameGUI[0].GetX() + 100, iteam::InGameGUI[0].GetY() + 20 );

		WeaponSelector.Load ( "data/weapons/weapon_selector.png" );
		WeaponSelector.Scale ( 38./32. );
		WeaponSelector.Move ( THUMBS_WIDTH, 600 - THUMBS_HEIGHT );

		//Test_Init();
//		InitPhysics();
//		cout<<"iteamPhysics->SizeCount()="<<iteamPhysics->SizeCount()<<endl;
		Init_Explosions();
//		InitWeapons ( iteamPhysics );
//		cout<<"iteamPhysics->SizeCount()="<<iteamPhysics->SizeCount()<<endl;
//		exit(68);
		Weapons_Init();
		return ( 0 );
	}

	//called if gameState=ITEAM_RUNNINGPOST
	//cleans up what has been loaded by Load()
	int CleanGameData() {
		cout<<"#############CleanGameData()"<<endl;
		//TODO: put all necessary deletes here

		//clean fonts
		for ( int i=0;i<Font.size();i++ ) Font[i].Clean();
		Font.clear();

		//delete textures
		for ( int i=0;i<Player_Texture.size();i++ ) delete Player_Texture[i];
		for ( int i=0;i<Weapon_Texture.size();i++ ) delete Weapon_Texture[i];
		for ( int i=0;i<Explosion_Texture.size();i++ ) delete Explosion_Texture[i];

		//clear Texture vectors
		Player_Texture.clear();
		Weapon_Texture.clear();
		Explosion_Texture.clear();

		//clear vectors that used them
		Player.clear();
		g_WeaponsList.clear();
		ExplosionsList.clear();

		//clean Sprite vectors
		for ( int i=0;i<Level.size();i++ ) Level[i].DeleteTextures();
		for ( int i=0;i<InGameGUI.size();i++ ) InGameGUI[i].DeleteTextures();

		//clean normal sprites
		Tank_base.DeleteTextures();
		Tank_canon.DeleteTextures();
		AnglePointer.DeleteTextures();
		WeaponSelector.DeleteTextures();

		//clear GameTimer vector
		GameTimer.clear();

		//other vectors
// 		Audio
// 		Song
// 		Turn
// 		msg_history
// 		lines

		gameState = nextState;
		return ( 0 );
	}

	void DrawBackground() {
		Cam.Begin();
		Level[2].Draw();
		Level[2].Move ( Cam.GetX()- ( ( VIEWPORT_WIDTH/2 )-InGameGUI[0].width[0]/2 ), ( VIEWPORT_HEIGHT/2 )- ( Cam.GetY() /20 ) );
		Cam.Begin();
		Level[1].Draw();
		Level[1].Move ( Cam.GetX()- ( ( VIEWPORT_WIDTH/2 )-InGameGUI[0].width[0]/2 ) + ( Cam.GetX() /4 ), ( VIEWPORT_HEIGHT/2 )- ( Cam.GetY() /10 ) );
	}

	void DrawTerrain() {
		Cam.Begin();
		Level[0].Draw();
	}


	void DrawGUI() {
		int fontwidths = 0;
		Cam.Begin();
		InGameGUI[0].Move ( Cam.GetX()- ( ( VIEWPORT_WIDTH/2 )-InGameGUI[0].width[0]/2 ),Cam.GetY() + ( ( VIEWPORT_HEIGHT/2 )-InGameGUI[0].height[0]/2 ) );
		InGameGUI[0].Draw();
		if ( GameResW==800 ) {
			if ( Player[CurPlayer].m_FireAngle > 9 )	fontwidths += 6;	// adjust for centered text on angle meter
			if ( Player[CurPlayer].m_FireAngle > 99 )	fontwidths += 6;

			Text ( iteam::Font[1], 155-fontwidths,600-45, 0,1,1,1, 1,1,1, "%i%c", ( unsigned int ) Player[CurPlayer].m_FireAngle, 0xB0 );
			Text ( iteam::Font[1], 230,600-65, 0,1,1,1, 1,1,1, "%i", ( int ) Player[CurPlayer].m_FirePower );
		}
		UpdateWeaponThumbs();
		Cam.Begin();
		AnglePointer.Move ( InGameGUI[0].GetX() - ( VIEWPORT_WIDTH/2 ) + 161, InGameGUI[0].GetY() + 50 );
		AnglePointer.angle = -Player[CurPlayer].m_FireAngle;//because GP2D uses non-trigonometrical direction for the angle while we use the trigonometrical direction
		AnglePointer.Draw();

		//WeaponSelector.Move(-(GUIBottom.x - (VIEWPORT_WIDTH/2) + 161)+(THUMBS_WIDTH), -(GUIBottom.y + 50)+(600 - THUMBS_HEIGHT));
		Cam.Begin();
		WeaponSelector.Move ( Cam.GetX()- ( VIEWPORT_WIDTH/2 ) +THUMBS_WIDTH+CurrentWeapon*34,Cam.GetY()- ( VIEWPORT_HEIGHT/2 ) + ( 600 - THUMBS_HEIGHT ) );
		WeaponSelector.Draw();

		Text ( iteam::Font[2], 10,16, 0,1,1,1, 1,1,1, "Cam X: %f",Cam.GetX() );
		Text ( iteam::Font[2], 10,16+16, 0,1,1,1, 1,1,1, "Cam Y: %f",Cam.GetY() );
	}

	void NextTurn() {
		Player[CurPlayer].CanMove=false;
		Player[CurPlayer].CanJump=false;
		Player[CurPlayer].Movement.walkingRight=false;
		Player[CurPlayer].Movement.walkingLeft=false;

		do {CurPlayer= ( CurPlayer+1 ) %Player.size();}
		while ( !Player[CurPlayer].Alive );//skips dead players

		Seconds=20;
		Player[CurPlayer].CanMove=true;
		Player[CurPlayer].CanJump=true;
		Player[CurPlayer].Movement.walkingRight=false;
		Player[CurPlayer].Movement.walkingLeft=false;
	}

//TODO: uncomment successfully
//==========================from mickey's branch.
	int LoadSinglePlayer() {
		CountdownValue = 3;
		GameRunning = false;

		Cam.Create();

		iteam::Font.push_back ( gp2d::Font() ); iteam::Font[0].Load ( "data/gui/ingame/counter.ttf", 64 );
		iteam::Font.push_back ( gp2d::Font() ); iteam::Font[1].Load ( "data/gui/ingame/eras_bold.TTF", 12 );
		iteam::Font.push_back ( gp2d::Font() ); iteam::Font[2].Load ( "data/gui/ingame/eras_bold.TTF", 11 );

		Audio.push_back ( gp2d::Sound() );
		Audio.push_back ( gp2d::Sound() );
		Audio[0].LoadWAV ( "data/sound/characters/jump.wav" );
		Audio[1].LoadWAV ( "data/sound/interface/clock5.wav" );

		Song.push_back ( gp2d::Music() );
		Song[0].Load ( "data/music/song1.ogg" );
		Song[0].SetLoop ( -1 );
		Song[0].Play();

		init_rand();
		cout<<"random seed initialized"<<endl;

		//add players
		AddPlayer ( IT_PLAYER_SUSI, ( int ) rand_uniform ( 50,180 ),50,IT_PLAYER_FACE_RIGHT,1 );
		//Change player names to make it easier to differentiate them.
		sprintf ( Player[0].Name,"Susi 1" );

		strcpy ( Player[0].Team,"Good" );
		strcpy ( Player[1].Team,"VEry GOOD" );//xD I love it. -KIAaze

		Tank_base.Load ( "data/vehicles/tank_base.png", 1, 1 );
		Tank_canon.Load ( "data/vehicles/tank_canon.png", 1, 1 );

		Level.push_back ( gp2d::Sprite() );
		Level.push_back ( gp2d::Sprite() );
		Level.push_back ( gp2d::Sprite() );
		Level[0].Load ( "data/levels/grassymt/terrain.png" );
		Level[1].Load ( "data/levels/grassymt/layer1.png" );
		Level[2].Load ( "data/levels/grassymt/layer2.png" );
		Level[0].Move ( VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Level[0].height[0]/2 );
		Level[1].width[0]=2048;
		Level[1].height[0]=1024;
		Level[2].ResizePropW ( GameResW );

		InGameGUI.push_back ( gp2d::Sprite() );
		InGameGUI.push_back ( gp2d::Sprite() );
		InGameGUI[0].Load ( "data/gui/ingame/bottom2.png" );
		InGameGUI[0].ResizePropW ( GameResW );
		InGameGUI[0].Move ( VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-InGameGUI[0].height[0]/2 );
		InGameGUI[0].alpha[0]=0.9f;


		InGameGUI[1].Load ( "data/gui/ingame/countdown_3.png" );
		InGameGUI[1].Load ( "data/gui/ingame/countdown_2.png" );
		InGameGUI[1].Load ( "data/gui/ingame/countdown_1.png" );
		InGameGUI[1].Load ( "data/gui/ingame/countdown_duel.png" );
		InGameGUI[1].iterateSheets = true;
		InGameGUI[1].setAnimationSpeed ( 1.0f );
		InGameGUI[1].animationTimer.Start();
		int check=InGameGUI[1].animationTimer.GetTicks();
		Tank_base.Load ( "data/vehicles/tank_base.png", 1, 1 );
		Tank_base.Scale ( 0.4 );
		Tank_canon.Load ( "data/vehicles/tank_canon.png", 1, 1 );
		Tank_canon.Scale ( 0.4 );

		AnglePointer.Load ( "data/gui/ingame/angle_pointer.png" );
		AnglePointer.Move ( iteam::InGameGUI[0].GetX() + 100, iteam::InGameGUI[0].GetY() + 20 );

		WeaponSelector.Load ( "data/weapons/weapon_selector.png" );
		WeaponSelector.Scale ( 38./32. );
		WeaponSelector.Move ( THUMBS_WIDTH, 600 - THUMBS_HEIGHT );

		InitPhysics();

		//Test_Init();
		Init_Explosions();
		InitWeapons ( iteamPhysics );

		AddAIPlayer ( IT_PLAYER_SUSI, ( int ) rand_uniform ( 50,180 ),50,IT_PLAYER_FACE_RIGHT,1 );
		//Change player names to make it easier to differentiate them.
		sprintf ( Player[1].Name,"AI Player 1" );

		for ( int i=0; i < Player.size(); i++ ) {
			// iteamPhysics->AddObject(Player[i]);
			PlayerObj* l_Player =  &Player[i];

			l_Player->JumpPower = 7.0 * iteamPhysics->OneMeterInPixels();
			l_Player->m_FirePower = 7.0 * iteamPhysics->OneMeterInPixels();
			//l_Player->SetPlayerWeapon ( iteamWeapons->AccessWeapon ( 0 ) );

			iteamPhysics->AddObject ( l_Player );
		}
		Player[0].SetTimeToTakeMyTurn();

	}

	void DestroyRunningGame() {
		CleanGameData();
		/*		for ( int i=0; i < Player.size(); i++ )
				{
					delete Player[i];
				}*/
	}

	void InitPhysics() {
		iteamPhysics = new PhysicsSystem();
	}

	void InitWeapons ( PhysicsSystem *physics ) {
		iteamWeapons = new WeaponsList();

		iteamGrenade* l_Grenade = new iteamGrenade();
		l_Grenade->UsePhysicsSystem ( physics );
		iteamWeapons->Add ( l_Grenade );

		/*		iteamMissile* l_Missile = new iteamMissile();
				l_Missile->UsePhysicsSystem(physics);
				iteamWeapons->Add(l_Missile);

				iteamClusterBomb* l_ClusterBomb = new iteamClusterBomb();
				l_ClusterBomb->UsePhysicsSystem(physics);
				iteamWeapons->Add(l_ClusterBomb);

				iteamDynamite* l_Dynamite = new iteamDynamite();
				l_Dynamite->UsePhysicsSystem(physics);
				iteamWeapons->Add(l_Dynamite);*/
	}

	void DoIteamBehaviours() {
		// Weapons
		iteamWeapons->DoWeaponBehaviours();

		// Players Last
		for ( int i = 0; i < Player.size(); i++ ) {
			Player[i].DoBehaviours();
		}
	}

}//end of namespace
