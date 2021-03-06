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

#define DATA_DIR "."

using namespace std;
using namespace gp2d;
using namespace iteam;

vector <iteam::PlayerObj> iteam::Player;
vector <int> Turn;
vector <char> msg_history;

gp2d::Sprite iteam::Tank_base;
gp2d::Sprite iteam::Tank_canon;

vector <gp2d::Sprite> iteam::Level;
vector <gp2d::Sprite> iteam::InGameGUI;
vector <gp2d::Font>   iteam::Font;
vector <gp2d::Timer>  iteam::Timer;
vector <gp2d::Sound>  iteam::Audio;
vector <gp2d::Music>  iteam::Song;
gp2d::Sprite iteam::AnglePointer;
gp2d::Sprite iteam::WeaponSelector;

GLfloat iteam::TERRAIN_XMIN;
GLfloat iteam::TERRAIN_XMAX;
GLfloat iteam::TERRAIN_YMIN;
GLfloat iteam::TERRAIN_YMAX;

GLfloat iteam::CAM_XMIN;
GLfloat iteam::CAM_XMAX;
GLfloat iteam::CAM_YMIN;
GLfloat iteam::CAM_YMAX;

gp2d::Camera iteam::Cam;

int iteam::talk = 0;
char iteam::message[256];
char iteam::message_buffer[3][256];

GLfloat IT_Angle = 0;
GLfloat IT_WeaponStrenght = 10;

int iteam::CurrentWeapon = IT_WT_GRENADE;
//int iteam::CurrentWeapon = IT_WT_MISSILE;
//int iteam::CurrentWeapon = IT_WT_CLUSTERBOMB;
//int iteam::CurrentWeapon = IT_WT_DYNAMITE;
//int iteam::CurrentWeapon = IT_WT_PISTOL;
//int iteam::CurrentWeapon = IT_WT_ROCKET;

settings iteam::options;

bool iteam::bStartshaking = false;
bool bCameraShake = false;
int shakeSize;
int shakeTicks;
int shakes;

bool iteam::music_on = false;

bool	iteam::bQuitGame = false;
int	iteam::can;
Button *iteam::btn=NULL;


//if you want to avoid intro and menu
/*iteam::GameState iteam::gameState = ITEAM_COUNTDOWNPRE;
iteam::GameState iteam::nextState = ITEAM_COUNTDOWNPRE;*/
//normal initial gamestate
iteam::GameState iteam::gameState = ITEAM_INTROPRE;
iteam::GameState iteam::nextState = ITEAM_INTROPRE;

// This is what handles all events. Eventually it will handle mouse events
gp2d::inputHandler *KeyHandler = NULL;
gp2d::CursorType *GameCursor=NULL;

/************************************************************************************/
/************ Function to add pressed characters into the message *******************/
/************************************************************************************/

void ShowChar ( SDLKey key, Uint16 unicode ) {
	cout<<"+++++ShowChar called+++++"<<endl;
	cout<<key<<endl;
	cout<<unicode<<endl;
	cout<<"++++++++++"<<endl;

	if ( unicode && ( unicode <= 255 ) ) {
		Uint8 ch;
		char ch2;

		ch = ( Uint8 ) unicode;
		ch2 = ( Uint8 ) unicode;
		cout<<"++++++++++"<<endl;
		cout<<ch<<endl;
		cout<<ch2<<endl;
		//cout<<strcat(message,(char *)&ch)<<endl;
		sprintf ( message,"%s%c",message,ch );
		cout<<message<<endl;
		/*		FILE *debugfile=fopen("debug.log","a");
				fprintf(debugfile,"========================\n");
				fprintf(debugfile,"%s\n",message_buffer[0]);
				fprintf(debugfile,"%s\n",message_buffer[1]);
				fprintf(debugfile,"%s\n",message_buffer[2]);
				fprintf(debugfile,"%s\n",message);
				fclose(debugfile);*/
		cout<<"++++++++++"<<endl;
//		terminal->AddText((char *)&ch, 1);
	}
}

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
	printf ( "Left mouse button pressed\n" );
}
void MouseUp() {
	printf ( "Left mouse button released\n" );
}
void IncAngle() {
	Player[CurPlayer].Angle += 10;
	if ( Player[CurPlayer].Angle > 360 )	Player[CurPlayer].Angle = Player[CurPlayer].Angle - 360;
}
void DecAngle() {
	Player[CurPlayer].Angle -= 10;
	if ( Player[CurPlayer].Angle < 0 )	Player[CurPlayer].Angle = Player[CurPlayer].Angle + 360;
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
void DecElasticity() {
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
void SwitchWeapon() {
	CurrentWeapon = ( CurrentWeapon+1 ) %5;
}

void FireWeapon() {
	Weapons_Fire ( Player[CurPlayer].Angle, Player[CurPlayer].Power, CurrentWeapon );
}

void ChangeCharacter() {
	NextTurn();
}
void AddCharacter() {
	AddPlayer ( IT_PLAYER_SUSI,Player[CurPlayer].x,50,IT_PLAYER_FACE_RIGHT,1 );
	sprintf ( Player[Player.size()-1].Name,"Susi %d",Player.size()-1 );
	cout<<Player[Player.size()-1].Name<<" has joined the game!"<<endl;
}

void PlayerJump() {
	if ( Player[CurPlayer].CanJump )	{
		Audio[0].Play();
		Player[CurPlayer].vY = -Player[CurPlayer].JumpPower;
	}
}
void PlayerLeft() {
	// If we are not walking the opposite way
	if ( Player[CurPlayer].Movement.walkingRight==false ) {
		Player[CurPlayer].Movement.walkingLeft = true;
	}
}
void PlayerLeftStop() {
	Player[CurPlayer].Movement.walkingLeft = false;
}
void PlayerRight() {
	if ( Player[CurPlayer].Movement.walkingLeft==false ) {
		Player[CurPlayer].Movement.walkingRight = true;
	}
}
void PlayerRightStop() {
	Player[CurPlayer].Movement.walkingRight = false;
}

void ToggleMusic() {
	if(music_on) {iteam::Song[0].Stop();music_on=false;}
	else {iteam::Song[0].Play();music_on=true;}
}

// This function is responsible for registering the ingame events
// i.e. Events that occur throughout the game
void RegisterIngameKeys() {
	KeyHandler->registerInputCallback ( options.KEY_FIRE, FireWeapon, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_INC_ANGLE, IncAngle, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_INC_ANGLE, IncAngle, GP2D_KEYPRESSED );
	KeyHandler->registerInputCallback ( options.KEY_DEC_ANGLE, DecAngle, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_DEC_ANGLE, DecAngle, GP2D_KEYPRESSED );
	KeyHandler->registerInputCallback ( options.KEY_DEC_SPEED, DecSpeed, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_INC_SPEED, IncSpeed, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_DEC_SPEED, DecSpeed, GP2D_KEYPRESSED );
	KeyHandler->registerInputCallback ( options.KEY_INC_SPEED, IncSpeed, GP2D_KEYPRESSED );
	KeyHandler->registerInputCallback ( options.KEY_INC_GRAV, IncGravity, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_DEC_GRAV, DecGravity, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_INC_GRE_TIME, IncGrenadeTime, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_DEC_GRE_TIME, DecGrenadeTime, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_INC_JUMP_POWER, IncJumpPower, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_DEC_JUMP_POWER, DecJumpPower, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_INC_ELASTICITY, IncElasticity, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_DEC_ELASTICITY, DecElasticity, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_SWITCH_PLAYER, ChangeCharacter, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_ADD_PLAYER, AddCharacter, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_SWITCH_WEAPON, SwitchWeapon, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( options.KEY_MUSIC, ToggleMusic, GP2D_KEYDOWN );

	//TODO: Character movement, this needs adding to the configurable control system
	KeyHandler->registerInputCallback ( SDLK_UP, PlayerJump, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_LEFT, PlayerLeft, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_LEFT, PlayerLeftStop, GP2D_KEYUP );
	KeyHandler->registerInputCallback ( SDLK_RIGHT, PlayerRight, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_RIGHT, PlayerRightStop, GP2D_KEYUP );

	// TODO: Lets configure the weapon, this needs adding to the configurable control system
	KeyHandler->registerInputCallback ( SDLK_1, SelectWeapon1, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_2, SelectWeapon2, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_3, SelectWeapon3, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_4, SelectWeapon4, GP2D_KEYDOWN );
}

// This function is responsible for unregistering the ingame events
// i.e. Events that occur throughout the game
void UnRegisterIngameKeys() {
	KeyHandler->unregisterInputCallback ( options.KEY_FIRE );
	KeyHandler->unregisterInputCallback ( options.KEY_INC_ANGLE );
	KeyHandler->unregisterInputCallback ( options.KEY_INC_ANGLE );
	KeyHandler->unregisterInputCallback ( options.KEY_DEC_ANGLE );
	KeyHandler->unregisterInputCallback ( options.KEY_DEC_ANGLE );
	KeyHandler->unregisterInputCallback ( options.KEY_DEC_SPEED );
	KeyHandler->unregisterInputCallback ( options.KEY_INC_SPEED );
	KeyHandler->unregisterInputCallback ( options.KEY_DEC_SPEED );
	KeyHandler->unregisterInputCallback ( options.KEY_INC_SPEED );
	KeyHandler->unregisterInputCallback ( options.KEY_INC_GRAV );
	KeyHandler->unregisterInputCallback ( options.KEY_DEC_GRAV );
	KeyHandler->unregisterInputCallback ( options.KEY_INC_GRE_TIME );
	KeyHandler->unregisterInputCallback ( options.KEY_DEC_GRE_TIME );
	KeyHandler->unregisterInputCallback ( options.KEY_INC_JUMP_POWER );
	KeyHandler->unregisterInputCallback ( options.KEY_DEC_JUMP_POWER );
	KeyHandler->unregisterInputCallback ( options.KEY_INC_ELASTICITY );
	KeyHandler->unregisterInputCallback ( options.KEY_DEC_ELASTICITY );
	KeyHandler->unregisterInputCallback ( options.KEY_SWITCH_PLAYER );
	KeyHandler->unregisterInputCallback ( options.KEY_ADD_PLAYER );

	//TODO: Character movement, this needs adding to the configurable control system
	KeyHandler->unregisterInputCallback ( SDLK_UP );
	KeyHandler->unregisterInputCallback ( SDLK_LEFT );
	KeyHandler->unregisterInputCallback ( SDLK_RIGHT );

	// TODO: Lets configure the weapon, this needs adding to the configurable control system
	KeyHandler->unregisterInputCallback ( SDLK_1 );
	KeyHandler->unregisterInputCallback ( SDLK_2 );
	KeyHandler->unregisterInputCallback ( SDLK_3 );
	KeyHandler->unregisterInputCallback ( SDLK_4 );
}

void toggle_talk() {
	if ( talk && strlen ( message ) !=0 ) {
		//msg_history.push_back(char());
		cout<<"-------------->strlen="<<strlen ( message ) <<endl;
		cout<<"-------------->message="<<message<<endl;
		//msg_history.size();
		snprintf ( message_buffer[0],256,message_buffer[1] );
		snprintf ( message_buffer[1],256,message_buffer[2] );
		snprintf ( message_buffer[2],256,message );
		strcpy ( message,"" );
	}
	talk= ( talk+1 ) %2;
	if ( talk ) {
		UnRegisterGlobalKeys();
		UnRegisterIngameKeys();
	}
	else {
		RegisterGlobalKeys();
		RegisterIngameKeys();
	}
}

//================================================
// MAIN FUNCTION
//================================================
#ifdef _WIN32
int WINAPI WinMain ( HINSTANCE, HINSTANCE, LPSTR, int ) { // If we're on Windows we'll need this line instead of main()
#else
int main() { // Else if we're on Linux, just use main :)
#endif

//gp2d::SetDataDir("/usr/share/games/i-team/");
	gp2d::SetDataDir ( "." );

	bool flag1;
	GLfloat size1=1.0f;

	//load settings
	options.Load ( "options.cfg" );

	// This now initialises the video (calls iteam::init())- This is required because of threading purposes
	printf ( "About to kick off keyhandler\n" );
	iteam::Init();

	printf ( "About to really kick off keyhandler\n" );
	KeyHandler = new gp2d::inputHandler();
	RegisterGlobalKeys();
	printf ( "inputHanlder registered\n" );

	// Initialise the GIU driven mouse
	InitialiseMouse();

	// Passes a pointer to the event handler so that the gui
	// is able to register all its required event.
	// If you dont want to use the event handler then pass NULL
	// to this, and configure the GUI callbacks individually.
	GuiManager *GuiMan = new gp2d::GuiManager ( KeyHandler );

	int translated;	/* Whether or not UNICODE translation was enabled */
	translated = SDL_EnableUNICODE ( 1 );

	while ( bQuitGame==false ) {

		gp2d::Cls();

		// Process any event waiting in the queues and call the callback
		// routines setup to handle them
		//cout<<"before KeyHandler"<<endl;
		int whatevent=KeyHandler->processEvents();
		if ( talk && whatevent==-1 ) {
			cout<<"HOLY SHIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
			cout<<"=============="<<endl;
			SDLKey value;
			value=KeyHandler->current_keysym_sym;
			cout<<SDL_GetKeyName ( KeyHandler->current_keysym_sym ) <<endl;
			ShowChar ( KeyHandler->current_keysym_sym,KeyHandler->current_keysym_unicode );
			cout<<"=============="<<endl;

		}
		//cout<<"after KeyHandler"<<endl;

		switch ( gameState ) {
			case ITEAM_INTROPRE:
				cout<<"===ITEAM_INTROPRE==="<<endl;
				IntroPre();
				break;
			case ITEAM_INTRO:
				Intro();
				break;
			case ITEAM_INTROPOST:
				cout<<"===ITEAM_INTROPOST==="<<endl;
				IntroPost();
				break;
			case ITEAM_MAINMENUPRE:
				cout<<"===ITEAM_MAINMENUPRE==="<<endl;
				MainMenuPre();
				cout<<"===ITEAM_MAINMENUPRE END==="<<endl;
				break;
			case ITEAM_MAINMENU:
				MainMenu();
				break;
			case ITEAM_MAINMENUPOST:
				cout<<"===ITEAM_MAINMENUPOST==="<<endl;
				MainMenuPost();
				cout<<"===ITEAM_MAINMENUPOST END==="<<endl;
				break;
			case ITEAM_OPTIONSMENUPRE:
				cout<<"===ITEAM_OPTIONSMENUPRE==="<<endl;
				OptionsMenuPre();
				break;
			case ITEAM_OPTIONSMENU:
				OptionsMenu();
				break;
			case ITEAM_OPTIONSMENUPOST:
				cout<<"===ITEAM_OPTIONSMENUPOST==="<<endl;
				OptionsMenuPost();
				break;
			case ITEAM_COUNTDOWNPRE:
				cout<<"===ITEAM_COUNTDOWNPRE==="<<endl;
				GameCursor->SetCursor ( GP2D_CURSOR_NORMAL );
				printf ( "count pre\n" );
				iteam::Timer.push_back ( gp2d::Timer() );
				iteam::Timer[0].Start();
				if ( iteam::Timer[0].IsStarted() )	{
					cout << "Timer started\n";
				}
				iteam::LoadGameData();
				TERRAIN_XMIN=Level[0].x-Level[0].width[0]/2.0;
				TERRAIN_XMAX=Level[0].x+Level[0].width[0]/2.0;
				TERRAIN_YMIN=Level[0].y-Level[0].height[0]/2.0;
				TERRAIN_YMAX=Level[0].y+Level[0].height[0]/2.0;
				CAM_XMIN=TERRAIN_XMIN+VIEWPORT_WIDTH/2.0;
				CAM_XMAX=TERRAIN_XMAX-VIEWPORT_WIDTH/2.0;
//				GLfloat CAM_YMIN=TERRAIN_YMIN+VIEWPORT_HEIGHT/2.0;
				CAM_YMAX=TERRAIN_YMAX-VIEWPORT_HEIGHT/2.0;

				for ( int i=0;i<=Player.size()-1;i++ ) {
					Player[i].CanMove=false;
					Player[i].CanJump=false;
				}
				gameState = ITEAM_COUNTDOWN;
				iteam::InGameGUI[1].currentSheet=0;//make sure we start the countdown with 3
				cout<<"===ITEAM_COUNTDOWNPRE END==="<<endl;
				break;
			case ITEAM_COUNTDOWN:
				DrawBackground();
				DrawTerrain();

				ProcessAllPhysicalObjects();

				Cam.Begin();

				iteam::InGameGUI[1].Move ( ( Cam.GetX()- ( VIEWPORT_WIDTH/2 ) ) +VIEWPORT_WIDTH/2, ( Cam.GetY()- ( VIEWPORT_HEIGHT/2 ) ) +VIEWPORT_HEIGHT/2 );
				iteam::InGameGUI[1].DrawFrame();
				if ( iteam::InGameGUI[1].setNextFrame() == false ) {
					gameState = ITEAM_COUNTDOWNPOST;
				}
				DrawGUI();

				UpdateWeaponThumbs();
				CAM_YMIN= ( Level[2].y-Level[2].height[0]/2.0 ) +VIEWPORT_HEIGHT/2.0;
				if ( Cam.GetX() >CAM_XMAX ) { Cam.Move ( CAM_XMAX,Cam.GetY() ); }
				if ( Cam.GetX() <CAM_XMIN ) { Cam.Move ( CAM_XMIN,Cam.GetY() ); }
				if ( Cam.GetY() >CAM_YMAX ) { Cam.Move ( Cam.GetX(),CAM_YMAX ); }
				if ( Cam.GetY() <CAM_YMIN ) { Cam.Move ( Cam.GetX(),CAM_YMIN ); }

				Cam.End();
				break;
			case ITEAM_COUNTDOWNPOST:
				gameState = ITEAM_RUNNINGPRE;
				SecondsCounter = iteam::Timer[0].GetTicks();
				Seconds = 20;
				Player[0].CanMove=true;
				CurPlayer=0;
				flag1 = true;//for the start effect
				size1=1.0f;//for the start effect
				break;
			case ITEAM_RUNNINGPRE:
				cout<<"===ITEAM_RUNNINGPRE==="<<endl;
				RegisterIngameKeys();
				KeyHandler->registerInputCallback ( options.KEY_TOGGLE_TALK, toggle_talk, GP2D_KEYDOWN );
				gameState = ITEAM_RUNNING;
				cout<<"===ITEAM_RUNNINGPRE END==="<<endl;
				break;
			case ITEAM_RUNNING:

				if ( ( iteam::Timer[0].GetTicks() - SecondsCounter ) > 1000 ) {
					Audio[1].Play();
					Seconds--;
					SecondsCounter = iteam::Timer[0].GetTicks();
				}

				DrawBackground();
				DrawTerrain();
				ProcessAllPhysicalObjects();
				ProccessExplosions();

				if ( flag1==true ) {
					iteam::InGameGUI[1].Move ( ( Cam.GetX()- ( VIEWPORT_WIDTH/2 ) ) +VIEWPORT_WIDTH/2, ( Cam.GetY()- ( VIEWPORT_HEIGHT/2 ) ) +VIEWPORT_HEIGHT/2 );
					iteam::InGameGUI[1].selectSheet ( 3 );
					Cam.Begin();
					iteam::InGameGUI[1].DrawFrame();
					Cam.End();
					size1-=0.01f;
					iteam::InGameGUI[1].alpha[3] = size1;
					iteam::InGameGUI[1].Scale ( 1.0f+ ( fabs ( size1 ) /10 ) );
					if ( iteam::InGameGUI[1].alpha[3]<=0 ) { flag1=false; }
				}

				DrawGUI();

				if ( bStartshaking == true ) {
					bStartshaking = false;
					bCameraShake = true;
					shakes = 0;
					shakeSize = 50;
					shakeTicks = iteam::Timer[0].GetTicks();
					printf ( "Camera shake started\n @ %i\n", shakeTicks );
				}

				if ( bCameraShake == true ) {
					if ( ( iteam::Timer[0].GetTicks() - shakeTicks ) > 100 ) {
						if ( ++shakes > 20 ) {
							bCameraShake = false;
							printf ( "Stopped shaking\n" );
						}
						else {
							shakeSize -= 2;
							int movementX = ( rand() %shakeSize )-shakeSize/2;
							int movementY = ( rand() %shakeSize )-shakeSize/2;
							shakeTicks = iteam::Timer[0].GetTicks();
							Cam.Move ( Player[CurPlayer].x+ movementX, Player[CurPlayer].y+ movementY );
							Cam.Move ( CurveValueGLf ( Player[CurPlayer].x,Cam.GetX(),5.0f ),CurveValueGLf ( Player[CurPlayer].y,Cam.GetY(),5.0f ) );
						}
					}
				}
				else {
					Cam.Move ( CurveValueGLf ( Player[CurPlayer].x,Cam.GetX(),50.0f ),CurveValueGLf ( Player[CurPlayer].y,Cam.GetY(),50.0f ) );
				}

				CAM_YMIN= ( Level[2].y-Level[2].height[0]/2.0 ) +VIEWPORT_HEIGHT/2.0;
				if ( Cam.GetX() >CAM_XMAX ) { Cam.Move ( CAM_XMAX,Cam.GetY() ); }
				if ( Cam.GetX() <CAM_XMIN ) { Cam.Move ( CAM_XMIN,Cam.GetY() ); }
				if ( Cam.GetY() >CAM_YMAX ) { Cam.Move ( Cam.GetX(),CAM_YMAX ); }
				if ( Cam.GetY() <CAM_YMIN ) { Cam.Move ( Cam.GetX(),CAM_YMIN ); }

				if ( Seconds>=10 ) {
					Text ( iteam::Font[0], 800-124,12+68, 0,1,1,1, 0,0,0, "%i",Seconds );
					Text ( iteam::Font[0], 800-128,12+64, 0,1,1,1, 1,0,0, "%i",Seconds );
				}
				else {
					Text ( iteam::Font[0], 800-124,12+68, 0,1,1,1, 0,0,0, "0%i",Seconds );
					Text ( iteam::Font[0], 800-128,12+64, 0,1,1,1, 1,0,0, "0%i",Seconds );
				}

				if ( Seconds<=0 ) { NextTurn(); }


				Cam.End();
				break;
			case ITEAM_RUNNINGPOST:
				iteam::CleanGameData();
				break;
		}//end of switch ( gameState )

		if ( gameState >=ITEAM_COUNTDOWN ) {
			Text ( iteam::Font[1], 10,64, 0,1,1,1, 1,1,1, "Player X: %f",Player[0].x );
			Text ( iteam::Font[1], 10,64+1*16, 0,1,1,1, 1,1,1, "Player Y: %f",Player[0].y );
			Text ( iteam::Font[1], 10,64+2*16, 0,1,1,1, 1,1,1, "Player vX: %f",Player[0].vX );
			Text ( iteam::Font[1], 10,64+3*16, 0,1,1,1, 1,1,1, "Player vY: %f",Player[0].vY );

			Text ( iteam::Font[1], 10,64+4*16, 0,1,1,1, 1,1,1, "Angle: %i%c", ( unsigned int ) Player[CurPlayer].Angle, 0xB0 );
			Text ( iteam::Font[1], 10,64+5*16, 0,1,1,1, 1,1,1, "Strenght:  %f",Player[CurPlayer].Power );
			//Text(iteam::Font[1], 10,64+6*16, 0,1,1,1, 1,1,1, "flighttime:  %f",flighttime);
			Text ( iteam::Font[1], 10,64+7*16, 0,1,1,1, 1,1,1, "Gravity:  %f",Gravity );
			Text ( iteam::Font[1], 10,64+8*16, 0,1,1,1, 1,1,1, "grenade_time:  %d",grenade_time );
			//Text(iteam::Font[1], 10,64+9*16, 0,1,1,1, 1,1,1, "choose_angle1:  %d",choose_angle1);
			Text ( iteam::Font[1], 10,64+10*16, 0,1,1,1, 1,1,1, "CurPlayer:  %d",CurPlayer );
			Text ( iteam::Font[1], 10,64+11*16, 0,1,1,1, 1,1,1, "JumpPower: %f",Player[CurPlayer].JumpPower );
			Text ( iteam::Font[1], 10,64+12*16, 0,1,1,1, 1,1,1, "Elasticity: %f",Player[CurPlayer].Elasticity );
			Text ( iteam::Font[1], 10,64+17*16, 0,1,1,1, 1,1,1, "%s",message_buffer[0] );
			Text ( iteam::Font[1], 10,64+18*16, 0,1,1,1, 1,1,1, "%s",message_buffer[1] );
			Text ( iteam::Font[1], 10,64+19*16, 0,1,1,1, 1,1,1, "%s",message_buffer[2] );
			if ( talk ) Text ( iteam::Font[1], 10,64+20*16, 0,1,1,1, 1,1,1, "Talk:%s",message );
		}

		//Update the GUI Manager system and Draw each widget
		GuiMan->Update();
		GuiMan->Draw();

		//Draw the cursor with currently set texture onto the screen
		Cam.Begin();
		GameCursor->Draw ( Cam.GetX(),Cam.GetY() );
		Cam.End();

		gp2d::ShowFPS();
		gp2d::Sync();
	}
	cout<<"==================>quitting"<<endl;
	//save settings
	options.Save ( "options.cfg" );
}
