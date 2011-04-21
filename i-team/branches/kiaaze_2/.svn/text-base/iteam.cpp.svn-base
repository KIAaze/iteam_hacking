#include "globals.h"
#include "functions.h"
#include "players.h"
#include "iteam-ai.h"
#include "iteam_maths.h"
#include "weapons.h"
#include "physics.h"
#include "settings.h"
#include "explosions.h"
#include <iostream>

#include "basicwidget.h"

using namespace std;
using namespace gp2d;
using namespace iteam;

vector <iteam::PlayerObj> iteam::Player;
vector <int> Turn;

gp2d::Sprite iteam::Terrain;
gp2d::Sprite iteam::BGLayer1;
gp2d::Sprite iteam::BGLayer2;
gp2d::Sprite iteam::GUIBottom;
gp2d::Sprite iteam::Countdown;
gp2d::Sprite iteam::AnglePointer;
gp2d::Sprite iteam::WeaponSelector;

gp2d::Font   iteam::FNTCounter;
gp2d::Font   iteam::FNTNames;
gp2d::Font   iteam::FNTGameGUI;

GLfloat iteam::TERRAIN_XMIN;
GLfloat iteam::TERRAIN_XMAX;
GLfloat iteam::TERRAIN_YMIN;
GLfloat iteam::TERRAIN_YMAX;

GLfloat iteam::ext_Nx;
GLfloat iteam::ext_Ny;
GLfloat iteam::ext_Tx;
GLfloat iteam::ext_Ty;

//commented because of change from openAL back to SDL_mixer, so currently no sound :(
// gp2d::Music  iteam::Song;
// gp2d::Sound  iteam::Jump;

gp2d::Camera iteam::Cam;
gp2d::Timer iteam::iTimer;

GLfloat IT_Angle = 0;
GLfloat IT_WeaponStrenght = 10;

int iteam::CurrentWeapon = IT_WT_GRENADE;
//int iteam::CurrentWeapon = IT_WT_MISSILE;
//int iteam::CurrentWeapon = IT_WT_CLUSTERBOMB;
//int iteam::CurrentWeapon = IT_WT_DYNAMITE;
//int iteam::CurrentWeapon = IT_WT_PISTOL;
//int iteam::CurrentWeapon = IT_WT_ROCKET;

bool iteam::bStartshaking = false;
bool bCameraShake = false;
int shakeSize;
int shakeTicks;
int shakes;

bool music_on = true;

bool iteam::bQuitGame = false;

#ifdef USE_EVENTCALLBACK
	iteam::GameState iteam::gameState = ITEAM_PREINTRO;
#else
	iteam::GameState iteam::gameState = ITEAM_PRECOUNTDOWN;
#endif

#ifdef USE_EVENTCALLBACK
	// This is what handles all events. Eventually it will handle mouse events
	gp2d::inputHandler *KeyHandler = NULL;

	/****************************************************************/
	/************ MainMenu widget event callbacks *******************/
	/****************************************************************/


	/****************************************************************/
	/************ Main game event callbacks *************************/
	/****************************************************************/
	/***** IDEALLY THESE SHOULD BE PUBLIC FUNCTIONS TO CLASSES ******/
	/***** FOR EXAMPLE THE PLAYER CLASS TO KEEP THE CODE TIDY  ******/
	/****************************************************************/
	void MouseDown() {
		printf("Left mouse button pressed\n");
	}
	void MouseUp() {
		printf("Left mouse button released\n");
	}
	void IncAngle() {
		Player[CurPlayer].Angle += 10;
		if(Player[CurPlayer].Angle > 360)	Player[CurPlayer].Angle = Player[CurPlayer].Angle - 360;
	}
	void DecAngle() {
		Player[CurPlayer].Angle -= 10;
		if(Player[CurPlayer].Angle < 0)	Player[CurPlayer].Angle = Player[CurPlayer].Angle + 360;
	}
	void IncSpeed() {
		Player[CurPlayer].Power += 0.5;
	}
	void DecSpeed() {
		Player[CurPlayer].Power -= 0.5;
	}
	void IncGravity() {
		Gravity += 1;
	}
	void DecGravity() {
		Gravity -= 1;
	}
	void IncGrenadeTime() {
		grenade_time += 1;
	}
	void DecGrenadeTime() {
		grenade_time -= 1;
	}
	void IncJumpPower() {
		Player[CurPlayer].JumpPower += 1;
	}
	void DecJumpPower() {
		Player[CurPlayer].JumpPower -= 1;
	}
	void IncElasticity() {
		Player[CurPlayer].Elasticity += 0.1;
	}
	void DecEleasticity() {
		Player[CurPlayer].Elasticity -= 0.1;
	}

	void SelectWeapon1() {
		CurrentWeapon = IT_WT_GRENADE;
	}
	void SelectWeapon2() {			
		CurrentWeapon = IT_WT_MISSILE;
	}
	void SelectWeapon3() {
		CurrentWeapon = IT_WT_CLUSTERBOMB;
	}
	void SelectWeapon4() {
		CurrentWeapon = IT_WT_DYNAMITE;
	}
	void FireWeapon() {
		Weapons_Fire(Player[CurPlayer].Angle, Player[CurPlayer].Power, CurrentWeapon);
	}

	void ChangeCharacter() {
		Player[CurPlayer].CanMove=false;
		CurPlayer=(CurPlayer+1)%Player.size();
		Player[CurPlayer].CanMove=true;
	}
	void AddCharacter() {
		AddPlayer(IT_PLAYER_SUSI,Player[CurPlayer].x,50,IT_PLAYER_FACE_RIGHT,1);
		sprintf(Player[Player.size()-1].Name,"Susi %d",Player.size()-1);
		cout<<Player[Player.size()-1].Name<<" has joined the game!"<<endl;
	}

	void PlayerJump() {
		if(Player[CurPlayer].CanJump)	{
			Player[CurPlayer].vY = -Player[CurPlayer].JumpPower;
		}
	}
	void PlayerLeft() {
		// If we are not walking the opposite way
		if (Player[CurPlayer].Movement.walkingRight==false) {
			Player[CurPlayer].Movement.walkingLeft = true;
		}
	}
	void PlayerLeftStop() {
		Player[CurPlayer].Movement.walkingLeft = false;
	} 
	void PlayerRight() {
		if (Player[CurPlayer].Movement.walkingLeft==false) {
			Player[CurPlayer].Movement.walkingRight = true;
		}
	}
	void PlayerRightStop() {
		Player[CurPlayer].Movement.walkingRight = false;
	} 
#else
/****************************************************************/
/****************************************************************/
	//================================================
	// KEY PROCESSING FUNCTION
	//================================================
	int ProcessKeys(settings &options)	{

		int iButton;
		int iX;
		int iY;
		int iRelX;
		int iRelY;
		//gp2d::CatchEvents();

		//put up/down events in here
		//Note: CatchEvents is true when something has changed.
		//This means that if you put another CatchEvents before this one, it won't work.
		while(/*gameState==RUNNING_STATE &&*/ CatchEvents()){
			// ============================ SWITCH PLAYER =============================
			if(gp2d::KeyDown(options.KEY_SWITCH_PLAYER))	{
				Player[CurPlayer].CanMove=false;
				//Player[CurPlayer].CanJump=false;//obsolete
				CurPlayer=(CurPlayer+1)%Player.size();
				Player[CurPlayer].CanMove=true;
				//Player[CurPlayer].CanJump=true;//obsolete
			}
			// ============================ SWITCH WEAPON =============================
			if(gp2d::KeyDown(options.KEY_SWITCH_WEAPON))	{
				CurrentWeapon=(CurrentWeapon+1)%IT_NB_OF_WEAPONS;
			}

	/*		if(gp2d::KeyDown(options.KEY_CHOOSE_ANGLE))	{ 
				if(choose_angle1) choose_angle1=false;
				else choose_angle1=true;
				}*/
			if(gp2d::KeyDown(options.KEY_ADD_PLAYER))	{ 
				AddPlayer(IT_PLAYER_SUSI,Player[CurPlayer].x,50,IT_PLAYER_FACE_RIGHT,1);
				sprintf(Player[Player.size()-1].Name,"Susi %d",Player.size()-1);
				cout<<Player[Player.size()-1].Name<<" has joined the game!"<<endl;
			}

			//here we get the mouse x,y position and the pressed button :)
			//Note that MouseMoved returns the mouse button currently, which means that it's only "true" if a mouse button is pressed and the mouse moved
			if(MouseMoved(iButton,iX,iY,iRelX,iRelY))
			{
				printf("MouseMoved\n");
			}
			if(MouseButtonUp(iButton,iX,iY,iRelX,iRelY))
			{
				printf("MouseButtonUp\n");
			}
			//set angle with mouse :) (left-click)
			//or add player at custom position for debugging (middle-click)
			//or place current player at custom position for debugging (right-click)
			if(MouseButtonDown(iButton,iX,iY,iRelX,iRelY))
			{
				//printf("MouseButtonDown: %d\n",iButton);
				//cout<<iX<<","<<iY<<endl;
				//cout<<Player[CurPlayer].x<<","<<Player[CurPlayer].y<<endl;
				//cout<<VIEWPORT_WIDTH<<","<<VIEWPORT_HEIGHT<<endl;
				//cout<<Cam.GetX()<<","<<Cam.GetY()<<endl;
				//get x,y of the click in the same coord system as player
				double click_X=iX-((VIEWPORT_WIDTH/2)-Cam.GetX());
				double click_Y=iY-((VIEWPORT_HEIGHT/2)-Cam.GetY());
				if(iButton==1)
				{
					Player[CurPlayer].Angle=limit_angle(rad2deg(-atan2(click_Y-Player[CurPlayer].y,click_X-Player[CurPlayer].x)));
				}
				if(iButton==2)	{ 
					AddPlayer(IT_PLAYER_SUSI,click_X,click_Y,IT_PLAYER_FACE_RIGHT,1);
					sprintf(Player[Player.size()-1].Name,"Susi %d",Player.size()-1);
					cout<<Player[Player.size()-1].Name<<" has joined the game!"<<endl;
				}
				if(iButton==3)
				{
					Player[CurPlayer].x=click_X;
					Player[CurPlayer].y=click_Y;
					Player[CurPlayer].vX=0;
					Player[CurPlayer].vY=0;
				}
			}

			//This returns true when the window is minimized (but not while it is minimized!)
			CheckWindowState();
		}


		//=== Global keys ===
		//close when the close button is clicked (or alt+F4, etc.)
		if(gp2d::Close_Event()) return(1);
		//close when the quit key is pressed (default: escape)
		if(gp2d::KeyPressed(SDLK_ESCAPE)) return(1);

		if(gp2d::KeyPressed(SDLK_f)){ ToggleFullscreen(); }
		if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }
	// 	if(gp2d::KeyPressed(SDLK_m))	{ 
	// 		if(music_on) {iteam::Song.Stop();music_on=false;}
	// 		else {iteam::Song.Play();music_on=true;}
	// 		}

		//==================


		// ============================ CHANGE VARIABLES =============================
		if(gp2d::KeyPressed(options.KEY_INC_ANGLE))	{ 
			Player[CurPlayer].Angle += 10;
			if(Player[CurPlayer].Angle > 360)	Player[CurPlayer].Angle = Player[CurPlayer].Angle - 360;
		}
		if(gp2d::KeyPressed(options.KEY_DEC_ANGLE))	{ 
			Player[CurPlayer].Angle -= 10;
			if(Player[CurPlayer].Angle < 0)	Player[CurPlayer].Angle = Player[CurPlayer].Angle + 360;
		}
		if(gp2d::KeyPressed(options.KEY_INC_SPEED))	{ 
			Player[CurPlayer].Power += 0.5;
		}
		if(gp2d::KeyPressed(options.KEY_DEC_SPEED))	{ 
			Player[CurPlayer].Power -= 0.5;
		}
	/*	if(gp2d::KeyPressed(options.KEY_INC_FLIGHTTIME))	{ 
			flighttime += 1;
		}
		if(gp2d::KeyPressed(options.KEY_DEC_FLIGHTTIME))	{ 
			flighttime -= 1;
		}*/
		if(gp2d::KeyPressed(options.KEY_INC_GRAV))	{ 
			Gravity += 1;
		}
		if(gp2d::KeyPressed(options.KEY_DEC_GRAV))	{ 
			Gravity -= 1;
		}
		if(gp2d::KeyPressed(options.KEY_INC_GRE_TIME))	{ 
			grenade_time += 1;
		}
		if(gp2d::KeyPressed(options.KEY_DEC_GRE_TIME))	{ 
			grenade_time -= 1;
		}
		if(gp2d::KeyPressed(options.KEY_INC_JUMP_POWER))	{ 
			Player[CurPlayer].JumpPower += 1;
		}
		if(gp2d::KeyPressed(options.KEY_DEC_JUMP_POWER))	{ 
			Player[CurPlayer].JumpPower -= 1;
		}
		if(gp2d::KeyPressed(options.KEY_INC_ELASTICITY))	{ 
			Player[CurPlayer].Elasticity += 0.1;
		}
		if(gp2d::KeyPressed(options.KEY_DEC_ELASTICITY))	{ 
			Player[CurPlayer].Elasticity -= 0.1;
		}

		// ============================ AI TEST =============================
	/*
		if(gp2d::KeyPressed(options.KEY_CALCVEL))	{
			calc_velocity(Player[CurPlayer].Angle,
				Player[CurPlayer].Power,flighttime,
				Gravity,
				Player[CurPlayer].x,Player[CurPlayer].y,
				Player[(CurPlayer+1)%2].x,Player[(CurPlayer+1)%2].y);
		}
		if(gp2d::KeyPressed(options.KEY_CALCANGLE))	{
			GLfloat DummyAngle,DummyTime;
			if(choose_angle1)
			calc_angle(Player[CurPlayer].Power,
				DummyAngle,DummyTime,
				Player[CurPlayer].Angle,flighttime,
				Gravity,
				Player[CurPlayer].x,Player[CurPlayer].y,
				Player[(CurPlayer+1)%2].x,Player[(CurPlayer+1)%2].y);
			else
			calc_angle(Player[CurPlayer].Power,
				Player[CurPlayer].Angle,flighttime,
				DummyAngle,DummyTime,
				Gravity,
				Player[CurPlayer].x,Player[CurPlayer].y,
				Player[(CurPlayer+1)%2].x,Player[(CurPlayer+1)%2].y);
		}
		if(gp2d::KeyPressed(options.KEY_CALCVECTOR))	{
			calc_vector(flighttime,
				Player[CurPlayer].Angle,Player[CurPlayer].Power,
				Gravity,
				Player[CurPlayer].x,Player[CurPlayer].y,
				Player[(CurPlayer+1)%2].x,Player[(CurPlayer+1)%2].y);
		}
	*/
		// ============================ WEAPONS TEST =============================
		if(gp2d::KeyPressed(options.KEY_FIRE))	{
			// fire the test weapon !!!!!!			
		Weapons_Fire(Player[CurPlayer].Angle, Player[CurPlayer].Power, CurrentWeapon);
			//cout << "[PLAYER] x = " << Player[CurPlayer].x << " y = " << Player[CurPlayer].y << "\n";
			//int retval = FireWeapon( IT_WT_GRENADE, Player[CurPlayer].x, Player[CurPlayer].y, (GLfloat) 45.0, (GLfloat) 500.0);
		}


		//==================

		if(gp2d::KeyPressed(SDLK_ESCAPE) || gp2d::KeyPressed(SDL_QUIT)){ return 1; }
		if(gp2d::KeyPressed(SDLK_f)){ ToggleFullscreen(); }
		if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }
		if(gp2d::KeyPressed(SDLK_EQUALS))	{ 
			Player[CurPlayer].Angle += 10;
			if(Player[CurPlayer].Angle > 360)	Player[CurPlayer].Angle = Player[CurPlayer].Angle - 360;
					
		}
		if(gp2d::KeyPressed(SDLK_MINUS))	{ 
			Player[CurPlayer].Angle -= 10;
			if(Player[CurPlayer].Angle < 0)	Player[CurPlayer].Angle = 360;
					
		}
		if(gp2d::KeyPressed(SDLK_RIGHTBRACKET))	{ 
			Player[CurPlayer].Power += 0.5;
		}
			
		if(gp2d::KeyPressed(SDLK_LEFTBRACKET))	{ 
			Player[CurPlayer].Power -= 0.5;
		}
		if(gp2d::KeyPressed(SDLK_c))	{ 
			if(CurPlayer == (IT_PLAYER_ONE - 1))	{
				CurPlayer = IT_PLAYER_TWO - 1; 
				
			
			} else {
				CurPlayer = IT_PLAYER_ONE - 1;
				
			}
		}
		if(gp2d::KeyPressed(SDLK_UP))	{ 
			if(Player[CurPlayer].CanJump)	{
	/*			Player[CurPlayer].SetAcceleration(6, 315);
				Player[CurPlayer].CanJump = false;*/
				//Jump.Play();
				Player[CurPlayer].vY = -Player[CurPlayer].JumpPower;
			}
		}
		
		if(gp2d::KeyPressed(SDLK_LEFT))	{ 
			//Player[CurPlayer].AddAcceleration(2, 225);
	//		Player[CurPlayer].vX -=10;
		}
		
		if(gp2d::KeyPressed(SDLK_RIGHT))	{ 
			//Player[CurPlayer].AddAcceleration(2, 0);
	//		Player[CurPlayer].vX +=10;
		}
				
		// ============================ WEAPONS TEST =============================
		if(gp2d::KeyPressed(SDLK_1))	{ 
			CurrentWeapon = IT_WT_GRENADE;
		}
			
		if(gp2d::KeyPressed(SDLK_2))	{ 
			CurrentWeapon = IT_WT_MISSILE;
		}
		if(gp2d::KeyPressed(SDLK_3))	{ 
			CurrentWeapon = IT_WT_CLUSTERBOMB;
		}
		if(gp2d::KeyPressed(SDLK_4))	{ 
			CurrentWeapon = IT_WT_DYNAMITE;
		}
		
		if(gp2d::KeyPressed(SDLK_SPACE))	{
			// fire the test weapon !!!!!!
				
			Weapons_Fire(Player[CurPlayer].Angle, Player[CurPlayer].Power, CurrentWeapon);
			//cout << "[PLAYER] x = " << Player[CurPlayer].x << " y = " << Player[CurPlayer].y << "\n";
			//int retval = FireWeapon( IT_WT_GRENADE, Player[CurPlayer].x, Player[CurPlayer].y, (GLfloat) 45.0, (GLfloat) 500.0);
		}
			
		return 0;
	}
#endif

//================================================
// MAIN FUNCTION
//================================================
#ifdef _WIN32
int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int) { // If we're on Windows we'll need this line instead of main()
#else
int main() { // Else if we're on Linux, just use main :)
#endif

#ifndef USE_EVENTCALLBACK
	//load settings
	settings options;
	options.Load("options.cfg");

	iteam::Init();
#else
	// This now initialises the video (calls iteam::init())- This is required because of threading purposes
	printf("About to kick off keyhandler\n");
	KeyHandler = new gp2d::inputHandler(iteam::Init);
	RegisterGlobalKeys();
	printf("inputHanlder registered\n");
	SDL_Delay(1000);		// TODO: Need a better way to detect that the initialisation is complete before messing with video

	GuiManager *GuiMan = new gp2d::GuiManager(KeyHandler);

	int can;
	Button *btn;
#endif

	while(bQuitGame==false){

		gp2d::Cls();
#ifndef USE_EVENTCALLBACK
		bQuitGame = ProcessKeys(options);
#endif

		switch (gameState) {
			case ITEAM_PREINTRO:
				PreIntro();
				break;
			case ITEAM_INTRO:
				//Intro();
				gameState = ITEAM_PREMAINMENU;
				break;
			case ITEAM_PREMAINMENU:
#ifdef USE_EVENTCALLBACK
				// Create the mainmenu canvas
				can = GuiMan->CreateCanvas(0, 0, 800, 600);

				// Add a start button to the canvas and assign a function 
				// to be called when the left mouse button is released
				// THIS IS THE SAME FUNCTION THAT IS USED FOR THE SPACEBAR
				// which makes the callback system generic for button presses and widgets
				btn = new Button(240, 140, 320, 50, "Start Game");
				btn->SetReleasedButtonCallback(MainMenuSpaceCallback);
				GuiMan->AddToCanvas(can, btn);

				btn = new Button(240, 410, 320, 50, "Quit Game");
				btn->SetReleasedButtonCallback(quitProgram);
				GuiMan->AddToCanvas(can, btn);
#endif
				PreMainMenu();
				break;
			case ITEAM_MAINMENU:
				MainMenu();
				break;
			case ITEAM_PRECOUNTDOWN:
				printf("Pre countdown state\n");
#ifdef USE_EVENTCALLBACK
				//Remove the functionality of the space bar used in main_menu
				KeyHandler->unregisterInputCallback(SDLK_SPACE);

				printf("About to delete canvas\n");
				GuiMan->DeleteCanvas(can);
				printf("Canvas delted\n");
#endif
				iteam::Load();
	TERRAIN_XMIN=Terrain.x-Terrain.width[0]/2.0;
	TERRAIN_XMAX=Terrain.x+Terrain.width[0]/2.0;
	TERRAIN_YMIN=Terrain.y-Terrain.height[0]/2.0;
	TERRAIN_YMAX=Terrain.y+Terrain.height[0]/2.0;

				iTimer.Start();
				if(iTimer.IsStarted())	{
					cout << "Timer started\n";
				}

				for(int i=0;i<=Player.size()-1;i++){
					Player[i].CanMove=false;
					Player[i].CanJump=false;
				}
				gameState = ITEAM_COUNTDOWN;
				break;
			case ITEAM_COUNTDOWN:		
				DrawBackground();
				DrawTerrain();

				ProcessAllPhysicalObjects();
	
				Cam.Begin();

				Countdown.Move((Cam.GetX()-(VIEWPORT_WIDTH/2))+VIEWPORT_WIDTH/2,(Cam.GetY()-(VIEWPORT_HEIGHT/2))+VIEWPORT_HEIGHT/2);
				Countdown.DrawFrame();
				if (Countdown.setNextFrame() == false) {
					gameState = ITEAM_PRERUNNING;
					Player[0].CanMove=true;
					CurPlayer=0; 
				}
				DrawGUI();

				UpdateWeaponThumbs();
				if(Cam.GetX()>1022){ Cam.Move(1022,Cam.GetY()); }
				if(Cam.GetX()<-220){ Cam.Move(-220,Cam.GetY()); }
				if(Cam.GetY()>298){ Cam.Move(Cam.GetX(),298); }
				if(Cam.GetY()<200){ Cam.Move(Cam.GetX(),200); }

				Cam.End();
				break;
			case ITEAM_PRERUNNING:
#ifdef USE_EVENTCALLBACK
				// Lets configure the weapon
				KeyHandler->registerInputCallback(SDLK_1, SelectWeapon1, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_2, SelectWeapon2, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_3, SelectWeapon3, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_4, SelectWeapon4, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_SPACE, FireWeapon, GP2D_KEYDOWN);
			
				KeyHandler->registerInputCallback(SDLK_EQUALS, IncAngle, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_EQUALS, IncAngle, GP2D_KEYPRESSED);
				KeyHandler->registerInputCallback(SDLK_MINUS, DecAngle, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_MINUS, DecAngle, GP2D_KEYPRESSED);
				KeyHandler->registerInputCallback(SDLK_RIGHTBRACKET, IncSpeed, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_RIGHTBRACKET, IncSpeed, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_LEFTBRACKET, DecSpeed, GP2D_KEYPRESSED);
				KeyHandler->registerInputCallback(SDLK_RIGHTBRACKET, IncSpeed, GP2D_KEYPRESSED);
#if 0			//TODO: Find the keys that handle these functions
				KeyHandler->registerInputCallback(SDLK_EQUAL, IncGravity, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_EQUAL, Decgravity, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_EQUAL, IncGrenadeTime, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_EQUAL, DecGrenadeTime, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_EQUAL, IncJumpPower, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_EQUAL, DecJumpPower, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_EQUAL, IncElasticity, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_EQUAL, DecElasticity, GP2D_KEYDOWN);
#endif
				KeyHandler->registerInputCallback(SDLK_c, ChangeCharacter, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_a, AddCharacter, GP2D_KEYDOWN);

				//Character movement
				KeyHandler->registerInputCallback(SDLK_UP, PlayerJump, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_LEFT, PlayerLeft, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_LEFT, PlayerLeftStop, GP2D_KEYUP);
				KeyHandler->registerInputCallback(SDLK_RIGHT, PlayerRight, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_RIGHT, PlayerRightStop, GP2D_KEYUP);

				KeyHandler->registerInputCallback(SDL_BUTTON_LEFT, MouseDown, GP2D_MOUSEDOWN);
				KeyHandler->registerInputCallback(SDL_BUTTON_LEFT, MouseUp, GP2D_MOUSEUP);

#endif
				gameState = ITEAM_RUNNING;
				break;
			case ITEAM_RUNNING:
				DrawBackground();
				DrawTerrain();
				ProcessAllPhysicalObjects();
				ProccessExplosions();		
				DrawGUI();

		Cam.Begin();
// 		DrawLine(Player[CurPlayer].x,Player[CurPlayer].y,Player[CurPlayer].x+ext_Nx,Player[CurPlayer].y+ext_Ny,1,0,0);
// 		DrawLine(Player[CurPlayer].x,Player[CurPlayer].y,Player[CurPlayer].x+ext_Tx,Player[CurPlayer].y+ext_Ty,0,0,1);

		double factor=10;

		DrawLine(Player[CurPlayer].x,
		Player[CurPlayer].y,
		Player[CurPlayer].x+factor*Player[CurPlayer].obj_Nx,
		Player[CurPlayer].y+factor*Player[CurPlayer].obj_Ny,
		1,0,0);

		DrawLine(Player[CurPlayer].x,
		Player[CurPlayer].y,
		Player[CurPlayer].x+factor*Player[CurPlayer].obj_Tx,
		Player[CurPlayer].y+factor*Player[CurPlayer].obj_Ty,
		0,0,1);

		DrawLine(Player[CurPlayer].x,
		Player[CurPlayer].y,
		Player[CurPlayer].x+factor*Player[CurPlayer].vX,
		Player[CurPlayer].y+factor*Player[CurPlayer].vY,
		1,1,1);

		DrawLine(Player[CurPlayer].x,
		Player[CurPlayer].y,
		Player[CurPlayer].x+factor*Player[CurPlayer].accel_x,
		Player[CurPlayer].y+factor*Player[CurPlayer].accel_y,
		0,0,0);
	cout<<"[MAIN]accel="<<Player[CurPlayer].accel_x<<","<<Player[CurPlayer].accel_y<<endl;

		DrawLine(Player[CurPlayer].x,
		Player[CurPlayer].y,
		Player[CurPlayer].x+factor*Player[CurPlayer].ReactionX,
		Player[CurPlayer].y+factor*Player[CurPlayer].ReactionY,
		0,1,0);

				Cam.Begin();
// 				DrawLine(0,0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(-Terrain.width[0],0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(Terrain.width[0],0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(VIEWPORT_WIDTH/2,0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(-(VIEWPORT_WIDTH/2),0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(-400,0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(400,0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(-624,0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(1424,0,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(0,-56,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(0,344,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(0,88,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(0,600,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(-624,88,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);
// 				DrawLine(1424,600,Player[CurPlayer].x,Player[CurPlayer].y,1,1,1);

// 				DrawLine((VIEWPORT_WIDTH-Terrain.width[0])/2.0,0,(VIEWPORT_WIDTH-Terrain.width[0])/2.0,VIEWPORT_HEIGHT,0,0,1);
// 				DrawLine((VIEWPORT_WIDTH+Terrain.width[0])/2.0,0,(VIEWPORT_WIDTH+Terrain.width[0])/2.0,VIEWPORT_HEIGHT,0,0,1);

				DrawLine(TERRAIN_XMIN,0,TERRAIN_XMIN,VIEWPORT_HEIGHT,0,0,1);
				DrawLine(TERRAIN_XMAX,0,TERRAIN_XMAX,VIEWPORT_HEIGHT,0,0,1);
				DrawLine(TERRAIN_XMIN,TERRAIN_YMIN,TERRAIN_XMAX,TERRAIN_YMAX,1,0,0);

				cout<<"Terrain position: "<<Terrain.x<<","<<Terrain.y<<endl;
				cout<<"Terrain dimensions: "<<Terrain.width[0]<<","<<Terrain.height[0]<<endl;
				cout<<"viewport: "<<VIEWPORT_WIDTH<<","<<VIEWPORT_HEIGHT<<endl;
				//VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-Terrain.height[0]/2

				if (bStartshaking == true) {
					bStartshaking = false;
					bCameraShake = true;
					shakes = 0;
					shakeSize = 50;
					shakeTicks = iTimer.GetTicks();
					printf("Camera shake started\n @ %i\n", shakeTicks);
				}

				if (bCameraShake == true) {
					//printf("Shaking\n");
					if ( (iTimer.GetTicks() - shakeTicks) > 100) {
						if (++shakes > 20) {
							bCameraShake = false;
							printf("Stopped shaking\n");
						}
						else {
							shakeSize -= 2;
							int movementX = (rand()%shakeSize)-shakeSize/2;
							int movementY = (rand()%shakeSize)-shakeSize/2;
							shakeTicks = iTimer.GetTicks();
							Cam.Move(Player[CurPlayer].x+ movementX, Player[CurPlayer].y+ movementY);
							Cam.Move(CurveValueGLf(Player[CurPlayer].x,Cam.GetX(),5.0f),CurveValueGLf(Player[CurPlayer].y,Cam.GetY(),5.0f));
						}
					}
				}
				else {
					Cam.Move(CurveValueGLf(Player[CurPlayer].x,Cam.GetX(),50.0f),CurveValueGLf(Player[CurPlayer].y,Cam.GetY(),50.0f));
				}

// 				if(Cam.GetX()>1022){ Cam.Move(1022,Cam.GetY()); }
// 				if(Cam.GetX()<-220){ Cam.Move(-220,Cam.GetY()); }
// 				if(Cam.GetY()<200){ Cam.Move(Cam.GetX(),200); }
// 				if(Cam.GetY()>298){ Cam.Move(Cam.GetX(),298); }

				Cam.Begin();
DrawLine(Cam.GetX(),Cam.GetY(),Cam.GetX()-VIEWPORT_WIDTH/2.0,Cam.GetY()-VIEWPORT_HEIGHT/2.0,0,0,1);
DrawLine(Cam.GetX(),Cam.GetY(),Cam.GetX()+VIEWPORT_WIDTH/2.0,Cam.GetY()-VIEWPORT_HEIGHT/2.0,0,0,1);
DrawLine(Cam.GetX(),Cam.GetY(),Cam.GetX()-VIEWPORT_WIDTH/2.0,Cam.GetY()+VIEWPORT_HEIGHT/2.0,0,0,1);
DrawLine(Cam.GetX(),Cam.GetY(),Cam.GetX()+VIEWPORT_WIDTH/2.0,Cam.GetY()+VIEWPORT_HEIGHT/2.0,0,0,1);

				GLfloat CAM_XMIN=TERRAIN_XMIN+VIEWPORT_WIDTH/2.0;
				GLfloat CAM_XMAX=TERRAIN_XMAX-VIEWPORT_WIDTH/2.0;
//				GLfloat CAM_YMIN=TERRAIN_YMIN+VIEWPORT_HEIGHT/2.0;
				GLfloat CAM_YMIN=(BGLayer2.y-BGLayer2.height[0]/2.0)+VIEWPORT_HEIGHT/2.0;
				GLfloat CAM_YMAX=TERRAIN_YMAX-VIEWPORT_HEIGHT/2.0;

				Cam.Begin();
DrawLine(0,(BGLayer2.y-BGLayer2.height[0]/2.0),VIEWPORT_WIDTH,(BGLayer2.y-BGLayer2.height[0]/2.0),1,1,1);
DrawLine(0,TERRAIN_YMAX,VIEWPORT_WIDTH,TERRAIN_YMAX,1,1,1);
DrawLine(TERRAIN_XMIN,0,TERRAIN_XMIN,VIEWPORT_HEIGHT,1,1,1);
DrawLine(TERRAIN_XMAX,0,TERRAIN_XMAX,VIEWPORT_HEIGHT,1,1,1);

				if(Cam.GetX()<CAM_XMIN){ Cam.Move(CAM_XMIN,Cam.GetY()); }
				if(Cam.GetX()>CAM_XMAX){ Cam.Move(CAM_XMAX,Cam.GetY()); }
				if(Cam.GetY()<CAM_YMIN){ Cam.Move(Cam.GetX(),CAM_YMIN); }
				if(Cam.GetY()>CAM_YMAX){ Cam.Move(Cam.GetX(),CAM_YMAX); }

				Cam.End();
				break;
		}
	
		if (gameState >=ITEAM_PRECOUNTDOWN) {
			Text(FNTGameGUI, 10,64, 0,1,1,1, 1,1,1, "Player X: %f",Player[0].x);
			Text(FNTGameGUI, 10,64+1*16, 0,1,1,1, 1,1,1, "Player Y: %f",Player[0].y);
			Text(FNTGameGUI, 10,64+2*16, 0,1,1,1, 1,1,1, "Player vX: %f",Player[0].vX);
			Text(FNTGameGUI, 10,64+3*16, 0,1,1,1, 1,1,1, "Player vY: %f",Player[0].vY);

			Text(FNTGameGUI, 10,64+4*16, 0,1,1,1, 1,1,1, "Angle: %i%c",(unsigned int)Player[CurPlayer].Angle, 0xB0);	
			Text(FNTGameGUI, 10,64+5*16, 0,1,1,1, 1,1,1, "Strenght:  %f",Player[CurPlayer].Power);
			//Text(FNTGameGUI, 10,64+6*16, 0,1,1,1, 1,1,1, "flighttime:  %f",flighttime);
			Text(FNTGameGUI, 10,64+7*16, 0,1,1,1, 1,1,1, "Gravity:  %f",Gravity);
			Text(FNTGameGUI, 10,64+8*16, 0,1,1,1, 1,1,1, "grenade_time:  %d",grenade_time);
			//Text(FNTGameGUI, 10,64+9*16, 0,1,1,1, 1,1,1, "choose_angle1:  %d",choose_angle1);
			Text(FNTGameGUI, 10,64+10*16, 0,1,1,1, 1,1,1, "CurPlayer:  %d",CurPlayer);
			Text(FNTGameGUI, 10,64+11*16, 0,1,1,1, 1,1,1, "JumpPower: %f",Player[CurPlayer].JumpPower);	
			Text(FNTGameGUI, 10,64+12*16, 0,1,1,1, 1,1,1, "Elasticity: %f",Player[CurPlayer].Elasticity);	
		}

#ifdef USE_EVENTCALLBACK
		GuiMan->Update();
		GuiMan->Draw();
		Cam.End();
#endif
		gp2d::ShowFPS();
		gp2d::Sync();

	}
#ifndef USE_EVENTCALLBACK
	//save settings
	options.Save("options.cfg");
#endif
}
