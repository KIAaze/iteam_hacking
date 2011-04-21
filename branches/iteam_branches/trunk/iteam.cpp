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
#include <getopt.h>

#define DATA_DIR "."

using namespace std;
using namespace gp2d;
using namespace iteam;

//------------------
//These variables can be set by command-line ;)
int iteam::gnDebug=0;
bool iteam::draw_tanks=false;
bool iteam::music_on = true;
iteam::GameState iteam::initial_gamestate=ITEAM_INTROPRE;
//------------------

vector <iteam::PlayerObj> iteam::Player;
iteam::WeaponsList* iteam::iteamWeapons;
vector <int> Turn;
vector <char> msg_history;

gp2d::Sprite iteam::Tank_base;
gp2d::Sprite iteam::Tank_canon;

vector <gp2d::Sprite> iteam::Level;
vector <gp2d::Sprite> iteam::InGameGUI;
vector <gp2d::Font>   iteam::Font;
vector <gp2d::Timer>  iteam::GameTimer;
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

bool	iteam::bQuitGame = false;
int	iteam::can;
Button *iteam::btn=NULL;


//if you want to avoid intro and menu
//iteam::GameState iteam::gameState = ITEAM_COUNTDOWNPRE;
//iteam::GameState iteam::nextState = ITEAM_COUNTDOWNPRE;
//normal initial gamestate
iteam::GameState iteam::gameState = iteam::initial_gamestate;
iteam::GameState iteam::nextState = iteam::initial_gamestate;

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
	Player[CurPlayer].m_FireAngle += 10;
	if ( Player[CurPlayer].m_FireAngle > 360 )	Player[CurPlayer].m_FireAngle = Player[CurPlayer].m_FireAngle - 360;
}
void DecAngle() {
	Player[CurPlayer].m_FireAngle -= 10;
	if ( Player[CurPlayer].m_FireAngle < 0 )	Player[CurPlayer].m_FireAngle = Player[CurPlayer].m_FireAngle + 360;
}
void IncSpeed() {
	Player[CurPlayer].m_FirePower += 10;
}
void DecSpeed() {
	Player[CurPlayer].m_FirePower -= 10;
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
	CurrentWeapon = 0;
}
void SelectWeapon2() {
	CurrentWeapon = 1;
}
void SelectWeapon3() {
	CurrentWeapon = 2;
}
void SelectWeapon4() {
	CurrentWeapon = 3;
}
void SelectWeapon5() {
	CurrentWeapon = 4;
}
void SelectWeapon6() {
	CurrentWeapon = 5;
}
void SelectWeapon7() {
	CurrentWeapon = 6;
}
void SwitchWeapon() {
	//empty weaponlist test necessary to avoid division by 0
	if ( g_WeaponsList.size() ==0 ) CurrentWeapon=0;
	else CurrentWeapon = ( CurrentWeapon+1 ) % g_WeaponsList.size();
}

void FireWeapon() {
	//cout<<"iteamWeapons->SizeCount()="<<iteamWeapons->SizeCount()<<endl;
	//iteamWeapons->AccessWeapon(0);//->Fire(&(Player[CurPlayer]),0,0,0,0,10);
	//exit(67);
	Weapons_Fire ( CurPlayer, CurrentWeapon );
	//turn ends after shot if the weapon is of type artillery or bandaid
	//easy for now since dynamite is the only non-artillery weapon
	if ( CurrentWeapon!=IT_WT_DYNAMITE ) Seconds=0;
}

void ChangeCharacter() {
	NextTurn();
}
void AddCharacter() {
	AddPlayer ( IT_PLAYER_SUSI,Player[CurPlayer].GetX(),50,IT_PLAYER_FACE_RIGHT,1 );
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
	if ( music_on ) {iteam::Song[0].Stop();music_on=false;}
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
	//temporarily using Fn keys, because numeric keys don't work on azerty keyboards... ;)
	KeyHandler->registerInputCallback ( SDLK_F1, SelectWeapon1, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_F2, SelectWeapon2, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_F3, SelectWeapon3, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_F4, SelectWeapon4, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_F5, SelectWeapon5, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_F6, SelectWeapon6, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDLK_F7, SelectWeapon7, GP2D_KEYDOWN );
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
	KeyHandler->unregisterInputCallback ( SDLK_F1 );
	KeyHandler->unregisterInputCallback ( SDLK_F2 );
	KeyHandler->unregisterInputCallback ( SDLK_F3 );
	KeyHandler->unregisterInputCallback ( SDLK_F4 );
	KeyHandler->unregisterInputCallback ( SDLK_F5 );
	KeyHandler->unregisterInputCallback ( SDLK_F6 );
	KeyHandler->unregisterInputCallback ( SDLK_F7 );
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
	} else {
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
int main ( int argc, char *argv[] ) { // Else if we're on Linux, just use main :)
#endif

//command line parsing using getopt.h
//comment it out if it doesn't work in Windows or other

	while ( 1 ) {
		int option_index = 0;
		int optchr;

		static struct option long_options[7] = {
			{"nomusic",0,0,0}, {"debug",1,0,'d'}, {"gamestate",1,0,'g'}, {"tanks",0,0,'t'}, {"version",0,0,'v'}, {"help",0,0,'h'}, {0,0,0,0}
		};

		optchr=getopt_long ( argc, argv ,"hvV", long_options, &option_index );
		if ( optchr==-1 )
			break;
		switch ( optchr ) {
			case 0:
				music_on=false;
				printf ( "music disabled. You can toggle it back on using the m key ingame.\n" );
				break;
			case 'd':
				gnDebug=atoi ( optarg );
				if ( gnDebug ) printf ( "[Debug Mode Set] debug level=%d\n",gnDebug );
				else printf ( "[Debug Mode Off]\n" );
				break;
			case 'g':
				initial_gamestate= ( iteam::GameState ) atoi ( optarg );
				printf ( "initial_gamestate=%d\n",initial_gamestate );
				break;
			case 't':
				draw_tanks=true;
				printf ( "Tanks enabled. War is on!\n" );
				break;
			case 'v':
				printf ( "Version: iteam alpha\n" );
				return 0;
				break;
			case 'h':
				printf ( "Usage:\n" );
				printf ( " %s -v, --version: Check binary version\n",argv[0] );
				printf ( " %s -h, --help : Display this help\n",argv[0] );
				printf ( " %s --d, --debug DEBUGLEVEL : Enable debugging output\n",argv[0] );
				printf ( " %s --t, --tanks : Draw tanks\n",argv[0] );
				printf ( " %s --g, --gamestate GAMESTATE : select initial gamestate (0=intro_pre / 9=countdown_pre)\n",argv[0] );
				printf ( " %s --nomusic : disable music. It can be toggled back on ingame using the m key.\n",argv[0] );
				return 0;
				break;
			default:
				//quit the app in case of wrong command-line args
				return 0;
				break;
		}//end switch
	}//end while

	gameState = initial_gamestate;
	nextState = initial_gamestate;

	//set data directory
	//ideally, this should be passed through the build system using --prefix=...
	//gp2d::SetDataDir("/usr/share/games/i-team/");
	gp2d::SetDataDir ( "." );

	bool flag1;
	GLfloat size1=1.0f;

	bool GameOver=false;
	int winner=0;

	//load settings
	options.Load ( "options.cfg" );

	// This now initialises the video (calls iteam::init())- This is required because of threading purposes
	printf ( "About to initialize...\n" );
	iteam::Init();

//=====================
//Testing space
	/*Texture* leave=new Texture ("./data/weapons/iteam_leaves_animation.png");
	Sprite toto(leave,6,1);
	exit(7);*/
//=====================

	printf ( "About to kick off keyhandler\n" );
	KeyHandler = new gp2d::inputHandler();
	RegisterGlobalKeys();
	printf ( "inputHanlder registered\n" );

	// Initialise the GUI driven mouse
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
			cout<<"talk && whatevent==-1 => We type something."<<endl;
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
				iteam::GameTimer.push_back ( gp2d::Timer() );
				iteam::GameTimer[0].Start();
				if ( iteam::GameTimer[0].IsStarted() ) {
					cout << "GameTimer started\n";
				}
				iteam::LoadGameData();
				TERRAIN_XMIN=Level[0].GetX()-Level[0].width[0]/2.0;
				TERRAIN_XMAX=Level[0].GetX() +Level[0].width[0]/2.0;
				TERRAIN_YMIN=Level[0].GetY()-Level[0].height[0]/2.0;
				TERRAIN_YMAX=Level[0].GetY() +Level[0].height[0]/2.0;
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
				//make sure there's no shaking at start
				bStartshaking = false;
				bCameraShake = false;
				cout<<"===ITEAM_COUNTDOWNPRE END==="<<endl;
				break;
			case ITEAM_COUNTDOWN:
				DrawBackground();//render
				DrawTerrain();//render
				ProcessAllPhysicalObjects();//update

				Cam.Begin();

				iteam::InGameGUI[1].Move ( ( Cam.GetX()- ( VIEWPORT_WIDTH/2 ) ) +VIEWPORT_WIDTH/2, ( Cam.GetY()- ( VIEWPORT_HEIGHT/2 ) ) +VIEWPORT_HEIGHT/2 );
				iteam::InGameGUI[1].DrawFrame();
				if ( iteam::InGameGUI[1].setNextFrame() == false ) {
					gameState = ITEAM_COUNTDOWNPOST;
				}
				DrawGUI();//render

				UpdateWeaponThumbs();//render
				CAM_YMIN= ( Level[2].GetY()-Level[2].height[0]/2.0 ) +VIEWPORT_HEIGHT/2.0;
				if ( Cam.GetX() >CAM_XMAX ) { Cam.Move ( CAM_XMAX,Cam.GetY() ); }
				if ( Cam.GetX() <CAM_XMIN ) { Cam.Move ( CAM_XMIN,Cam.GetY() ); }
				if ( Cam.GetY() >CAM_YMAX ) { Cam.Move ( Cam.GetX(),CAM_YMAX ); }
				if ( Cam.GetY() <CAM_YMIN ) { Cam.Move ( Cam.GetX(),CAM_YMIN ); }

				Cam.End();
				break;
			case ITEAM_COUNTDOWNPOST:
				gameState = ITEAM_RUNNINGPRE;
				SecondsCounter = iteam::GameTimer[0].GetTicks();
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
			case ITEAM_RUNNING: {
				int survivors=0;
				for ( int i=0;i<Player.size();i++ ) {
					if ( Player[i].Alive ) {survivors++;winner=i;}
				}
				if ( survivors<=1 ) {
					GameOver=true;
					gameState = ITEAM_GAMEOVER;
				}

				if ( ( iteam::GameTimer[0].GetTicks() - SecondsCounter ) > 1000 ) {
					Audio[1].Play();
					Seconds--;
					SecondsCounter = iteam::GameTimer[0].GetTicks();
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
					shakeTicks = iteam::GameTimer[0].GetTicks();
					printf ( "Camera shake started @ %i\n", shakeTicks );
				}

				if ( bCameraShake == true ) {
					if ( ( iteam::GameTimer[0].GetTicks() - shakeTicks ) > 100 ) {
						if ( ++shakes > 20 ) {
							bCameraShake = false;
							printf ( "Stopped shaking\n" );
						} else {
							shakeSize -= 2;
							int movementX = ( rand() %shakeSize )-shakeSize/2;
							int movementY = ( rand() %shakeSize )-shakeSize/2;
							shakeTicks = iteam::GameTimer[0].GetTicks();
							Cam.Move ( Player[CurPlayer].GetX() + movementX, Player[CurPlayer].GetY() + movementY );
							Cam.Move ( CurveValueGLf ( Player[CurPlayer].GetX(),Cam.GetX(),5.0f ),CurveValueGLf ( Player[CurPlayer].GetY(),Cam.GetY(),5.0f ) );
						}
					}
				} else {
					Cam.Move ( CurveValueGLf ( Player[CurPlayer].GetX(),Cam.GetX(),50.0f ),CurveValueGLf ( Player[CurPlayer].GetY(),Cam.GetY(),50.0f ) );
				}

				CAM_YMIN= ( Level[2].GetY()-Level[2].height[0]/2.0 ) +VIEWPORT_HEIGHT/2.0;
				if ( Cam.GetX() >CAM_XMAX ) { Cam.Move ( CAM_XMAX,Cam.GetY() ); }
				if ( Cam.GetX() <CAM_XMIN ) { Cam.Move ( CAM_XMIN,Cam.GetY() ); }
				if ( Cam.GetY() >CAM_YMAX ) { Cam.Move ( Cam.GetX(),CAM_YMAX ); }
				if ( Cam.GetY() <CAM_YMIN ) { Cam.Move ( Cam.GetX(),CAM_YMIN ); }

				if ( Seconds>=10 ) {
					Text ( iteam::Font[0], 800-124,12+68, 0,1,1,1, 0,0,0, "%i",Seconds );
					Text ( iteam::Font[0], 800-128,12+64, 0,1,1,1, 1,0,0, "%i",Seconds );
				} else {
					Text ( iteam::Font[0], 800-124,12+68, 0,1,1,1, 0,0,0, "0%i",Seconds );
					Text ( iteam::Font[0], 800-128,12+64, 0,1,1,1, 1,0,0, "0%i",Seconds );
				}

				if ( Seconds<=0 ) { NextTurn(); }

				Cam.End();
			}
			break;
			case ITEAM_RUNNINGPOST:
				iteam::CleanGameData();
				break;
			case ITEAM_GAMEOVER:
				DrawBackground();//render
				DrawTerrain();//render
				ProcessAllPhysicalObjects();
				ProccessExplosions();

				Cam.Begin();
				DrawGUI();//render
				UpdateWeaponThumbs();//render
				CAM_YMIN= ( Level[2].GetY()-Level[2].height[0]/2.0 ) +VIEWPORT_HEIGHT/2.0;
				if ( Cam.GetX() >CAM_XMAX ) { Cam.Move ( CAM_XMAX,Cam.GetY() ); }
				if ( Cam.GetX() <CAM_XMIN ) { Cam.Move ( CAM_XMIN,Cam.GetY() ); }
				if ( Cam.GetY() >CAM_YMAX ) { Cam.Move ( Cam.GetX(),CAM_YMAX ); }
				if ( Cam.GetY() <CAM_YMIN ) { Cam.Move ( Cam.GetX(),CAM_YMIN ); }
				Cam.End();
				Text ( iteam::Font[0], 100,200, 0,1,1,1, 1,0,0, "Game over" );
				Text ( iteam::Font[0], 100,300, 0,1,1,1, 1,0,0, "Player %d won", winner );
				break;
		}//end of switch ( gameState )

		if ( gameState >=ITEAM_COUNTDOWN ) {
			Text ( iteam::Font[1], 10,64, 0,1,1,1, 1,1,1, "Player X: %f",Player[CurPlayer].GetX() );
			Text ( iteam::Font[1], 10,64+1*16, 0,1,1,1, 1,1,1, "Player Y: %f",Player[CurPlayer].GetY() );
			Text ( iteam::Font[1], 10,64+2*16, 0,1,1,1, 1,1,1, "Player vX: %f",Player[CurPlayer].GetVX() );
			Text ( iteam::Font[1], 10,64+3*16, 0,1,1,1, 1,1,1, "Player vY: %f",Player[CurPlayer].GetVY() );

			Text ( iteam::Font[1], 10,64+4*16, 0,1,1,1, 1,1,1, "Angle: %i%c", ( unsigned int ) Player[CurPlayer].m_FireAngle, 0xB0 );
			Text ( iteam::Font[1], 10,64+5*16, 0,1,1,1, 1,1,1, "Strenght:  %f",Player[CurPlayer].m_FirePower );
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
