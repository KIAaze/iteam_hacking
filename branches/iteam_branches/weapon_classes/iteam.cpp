#include "globals.h"
#include "functions.h"
#include "Player.h"
#include "iteam_maths.h"
#include "physics.h"

#include "Weapon.h"

#include "iteamClusterbomb.h"
#include "iteamDynamite.h"
#include "iteamGrenade.h"
#include "iteam_maths.h"
#include "iteamMedipack.h"
#include "iteamMissile.h"
#include "iteamMultirazor.h"
#include "iteamRazor.h"

#include "settings.h"
#include "Explosion.h"
#include <iostream>
#include <getopt.h>
#include <typeinfo>

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

unsigned int iteam::CurrentWeapon = IT_WT_GRENADE;
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

bool iteam::bQuitGame = false;
int iteam::can;

GLfloat iteam::Gravity = IT_GRAVITY_DEFAULT;

//normal initial gamestate
iteam::GameState iteam::gameState = iteam::initial_gamestate;
iteam::GameState iteam::nextState = iteam::initial_gamestate;

// This is what handles all events. Eventually it will handle mouse events
gp2d::inputHandler *KeyHandler = NULL;
gp2d::CursorType *GameCursor=NULL;

//========================================

vector <Texture*> vec_Texture;
vector <Weapon*> vec_Weapon;
SpriteMap iteam::supermap;

void AddPlayer ( int mx,int my ) {
	printf ( "Left mouse button pressed at (%d,%d)\n",mx,my );
	vec3 M=screen2universe(&Cam,vec3(mx,my,0));

	int N=Add( supermap, new Player(vec_Texture[1] ) );
	supermap[N]->SetX ( M.GetX() );
	supermap[N]->SetY ( M.GetY() );
}

void AddWeapon ( int mx,int my ) {
	printf ( "Right mouse button pressed at (%d,%d)\n",mx,my );
	vec3 M=screen2universe(&Cam,vec3(mx,my,0));

	int N;
	Weapon* W;
	if(CurrentWeapon==0) W=new iteamGrenade();
	if(CurrentWeapon==1) W=new iteamMissile();
	if(CurrentWeapon==2) W=new iteamClusterbomb();
	if(CurrentWeapon==3) W=new iteamDynamite();
	if(CurrentWeapon==4) W=new iteamRazor();
	if(CurrentWeapon==5) W=new iteamMultirazor();
	if(CurrentWeapon==6) W=new iteamMedipack();
	W->Fire ( M.GetX(),M.GetY(), 45, 100 );
	N=Add( supermap, W );
}

void Destroy( int mx,int my )
{
	printf ( "Middle mouse button pressed at (%d,%d)\n",mx,my );
	vec3 M=screen2universe(&Cam,vec3(mx,my,0));
	//destroy terrain
	GenericDestroyTerrain(&(Level[0]),M.GetX(),M.GetY(),60,5);

	int N=Add( supermap, new Explosion(Explosion_Texture[0], 4, 4 ) );
	supermap[N]->SetX ( M.GetX() );
	supermap[N]->SetY ( M.GetY() );
}

void ChangeWeaponUp( int mx,int my )
{
	CurrentWeapon=(CurrentWeapon+1)%7;
	printf ( "Mousewheel up at (%d,%d)->CurrentWeapon=%d\n",mx,my,CurrentWeapon);
}

void ChangeWeaponDown( int mx,int my )
{
	if(CurrentWeapon==0) CurrentWeapon=6;
	else CurrentWeapon--;
	printf ( "Mousewheel down at (%d,%d)->CurrentWeapon=%d\n",mx,my,CurrentWeapon);
}

void QuitGame() {
	printf ( "escape pressed\n" );
	bQuitGame=true;
}

void RegisterIngameKeys() {
	KeyHandler->registerInputCallback ( SDLK_ESCAPE, QuitGame, GP2D_KEYDOWN );
	KeyHandler->registerInputCallback ( SDL_BUTTON_LEFT, AddPlayer, GP2D_MOUSEDOWN );
	KeyHandler->registerInputCallback ( SDL_BUTTON_RIGHT, AddWeapon, GP2D_MOUSEDOWN );
	KeyHandler->registerInputCallback ( SDL_BUTTON_MIDDLE, Destroy, GP2D_MOUSEDOWN );
	KeyHandler->registerInputCallback ( SDL_BUTTON_WHEELUP, ChangeWeaponUp, GP2D_MOUSEDOWN );
	KeyHandler->registerInputCallback ( SDL_BUTTON_WHEELDOWN, ChangeWeaponDown, GP2D_MOUSEDOWN );
}
//======================
//======================
// int main ( int argc, char *argv[] ) {
// 	gp2d::SetDataDir ( "." );
// 	iteam::Init();
// 	KeyHandler = new gp2d::inputHandler();
// 	RegisterIngameKeys();
// 	delete KeyHandler;
// 	return(0);
// }

int main ( int argc, char *argv[] ) {

	gp2d::SetDataDir ( "." );
	iteam::Init();
	KeyHandler = new gp2d::inputHandler();
	RegisterIngameKeys();

	Cam.Move(0,0);

	iteam::Load_Textures();

	vec_Texture.push_back ( new Texture ( "data/levels/grassymt/pit.png" ) );
	vec_Texture.push_back ( new Texture ( "data/chars/susi.png" ) );
	vec_Texture.push_back ( new Texture ( "data/weapons/grenade.png" ) );

	Sprite terrain ( vec_Texture[0] );
	terrain.Move(0,0);
	Level.push_back ( terrain );

	iteam::Font.push_back ( gp2d::Font() ); iteam::Font[0].Load ( "data/gui/ingame/counter.ttf", 64 );
	iteam::Font.push_back ( gp2d::Font() ); iteam::Font[1].Load ( "data/gui/ingame/eras_bold.TTF", 12 );
	iteam::Font.push_back ( gp2d::Font() ); iteam::Font[2].Load ( "data/gui/ingame/eras_bold.TTF", 11 );

	iteam::GameTimer.push_back ( gp2d::Timer() );
	iteam::GameTimer[0].Start();
	InitPhysics();

// 	Add( supermap, new Player(vec_Texture[1] ) );
// 	Add( supermap, new iteamGrenade() );
// 	Add( supermap, new Explosion(Explosion_Texture[0], 4, 4 ) );

	while ( !bQuitGame ) {
		Cls();
		Cam.Begin();
		Level[0].Draw();
		Cam.End();

		iteamPhysics->Step();
		ProcessAll(supermap);

		Sync();
		KeyHandler->processEvents();
	};
	ClearSpriteMap(supermap);
	for ( unsigned int i=0;i<vec_Texture.size();i++ ) {
		delete vec_Texture[i];
	}
	return ( 0 );
}
