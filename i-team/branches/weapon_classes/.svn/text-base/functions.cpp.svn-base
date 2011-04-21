/*! \file functions.cpp
\brief Source for the main in-game functions (for now).
*/

#include "globals.h"
#include "functions.h"
#include "Player.h"
#include "iteam_maths.h"
#include "Explosion.h"
#include <iostream>

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

	// Initialises the GUI based mouse controlling
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

	int Load_Textures()
	{
		//TODO: Put textures into a map. This makes it easier to choose the right texture. ;)
		//Removal will also be easier.
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

		return(0);
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

	void InitPhysics() {
		iteamPhysics = new PhysicsSystem();
	}

	void InitWeapons ( PhysicsSystem *physics ) {
// 		iteamWeapons = new WeaponsList();

		/*		iteamGrenade* l_Grenade = new iteamGrenade();
				l_Grenade->UsePhysicsSystem(physics);
				iteamWeapons->Add(l_Grenade);*/

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

}//end of namespace
