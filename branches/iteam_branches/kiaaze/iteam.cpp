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

#include "GUI.h"
#include "GUI_widgets.h"
#include "GUI_output.h"

#define DATA_DIR "."

using namespace std;
using namespace gp2d;
using namespace iteam;

vector <iteam::PlayerObj> iteam::Player;
vector <int> Turn;
vector <char> msg_history;

gp2d::Sprite iteam::Tank_base;
gp2d::Sprite iteam::Tank_canon;

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

//commented because of change from openAL back to SDL_mixer, so currently no sound :(
// gp2d::Music  iteam::Song;
// gp2d::Sound  iteam::Jump;

gp2d::Camera iteam::Cam;
gp2d::Timer iteam::iTimer;

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

bool iteam::bStartshaking = false;
bool bCameraShake = false;
int shakeSize;
int shakeTicks;
int shakes;

bool music_on = true;

GLfloat flighttime = 10;
bool choose_angle1=true;


settings iteam::options;

enum GAME_STATES
{
  COUNTDOWN_STATE=0,
  RUNNING_STATE
} ;
typedef enum GAME_STATES GameState;
GameState gameState = COUNTDOWN_STATE;

////////////////////////////////////////////////////////////////////////////////
/* Variables that we'll need to clean up */
GUI *gui;
GUI_TermWin *terminal;
enum image_names {
	IMAGE_SCROLL_UP,
	IMAGE_SCROLL_DN,
	NUM_IMAGES
};
char *image_files[NUM_IMAGES] = {
	"scroll_up.bmp", "scroll_dn.bmp"
};
SDL_Surface *images[NUM_IMAGES];


void ShowChar(SDLKey key, Uint16 unicode)
{
	cout<<"+++++ShowChar called+++++"<<endl;
	cout<<key<<endl;
	cout<<unicode<<endl;
	cout<<"++++++++++"<<endl;

	if ( unicode && (unicode <= 255) ) {
		Uint8 ch;
		char ch2;

		ch = (Uint8)unicode;
		ch2 = (Uint8)unicode;
	cout<<"++++++++++"<<endl;
		cout<<ch<<endl;
		cout<<ch2<<endl;
		//cout<<strcat(message,(char *)&ch)<<endl;
		sprintf(message,"%s%c",message,ch);
		cout<<message<<endl;
		FILE *debugfile=fopen("debug.log","a");
		fprintf(debugfile,"========================\n");
		fprintf(debugfile,"%s\n",message_buffer[0]);
		fprintf(debugfile,"%s\n",message_buffer[1]);
		fprintf(debugfile,"%s\n",message_buffer[2]);
		fprintf(debugfile,"%s\n",message);
		fclose(debugfile);
	cout<<"++++++++++"<<endl;
//		terminal->AddText((char *)&ch, 1);
	}
}

void cleanup(void)
{
	int i;

	/* Delete the GUI */
	delete gui;

	/* Clean up any images we have */
	for ( i=0; i<NUM_IMAGES; ++i ) {
		if ( images[i] ) {
			SDL_FreeSurface(images[i]);
		}
	}
}

void Output(SDL_Surface *screen, const char *title, const char *text)
{
	GUI_Output *output;

	output = GUI_CreateOutput(screen, 60, 5, NULL);
	if ( output ) {
		unsigned int i, pos;
		char formatted_text[1024];
#if 1
		/* Center the text in our window */
		pos = 0;
		formatted_text[pos++] = '\n';
		formatted_text[pos++] = '\n';
		for ( i=0; i<((60-strlen(text))/2); ++i ) {
			formatted_text[pos++] = ' ';
		}
		formatted_text[pos] = '\0';
		strcat(formatted_text, text);
#else
		strcpy(formatted_text, text);
#endif

		/* Run the output window with our text */
		GUI_AddOutput(output, formatted_text);
		GUI_ShowOutput(output, 1);
		GUI_DeleteOutput(output);
	}
}
////////////////////////////////////////////////////////////////////////////////

//================================================
// PAUSE/UNPAUSE FUNCTIONS
//================================================
void PauseGame()
{
  iTimer.Pause();
  Player[CurPlayer].CanMove=false;
  Player[CurPlayer].CanJump=false;
  Player[CurPlayer].setAnimationSpeed(0.0f);
  Countdown.setAnimationSpeed(0.0f);
  for (int i=0; i < ExplosionsList.size()-1; i++) ExplosionsList[ i ].setAnimationSpeed(0.0f);
  GamePaused=true;
}
void UnPauseGame()
{
  iTimer.Unpause();
  Player[CurPlayer].CanMove=true;
  Player[CurPlayer].CanJump=true;
  //Player[CurPlayer].setAnimationSpeed(0.0f);
  Countdown.setAnimationSpeed(1.0f);
  for (int i=0; i < ExplosionsList.size()-1; i++) ExplosionsList[ i ].setAnimationSpeed(16.0f);
  GamePaused=false;
}

//================================================
// KEY PROCESSING FUNCTION
//================================================
int ProcessKeys()
{

  int iButton;
  int iX;
  int iY;
  int iRelX;
  int iRelY;
  //gp2d::CatchEvents();

  //put up/down events in here
  //Note: CatchEvents is true when something has changed.
  //This means that if you put another CatchEvents before this one, it won't work.
  while (CatchEvents())
    {
	SDL_Event keyevent=getEvent();    //The SDL event that we will poll to get events.
	SDLKey value;
	//SDL_keysym key;
	if(keyevent.type==SDL_KEYDOWN && talk && !gp2d::KeyDown(options.KEY_TALK))
	{
		cout<<"=============="<<endl;
		value=keyevent.key.keysym.sym;
		cout<<SDL_GetKeyName(keyevent.key.keysym.sym)<<endl;
		ShowChar(keyevent.key.keysym.sym, keyevent.key.keysym.unicode);
		cout<<"=============="<<endl;
	}

      if (gp2d::KeyDown(options.KEY_TALK))
        {
	  if(talk && strlen(message)!=0 )
		{
			//msg_history.push_back(char());
			cout<<"-------------->strlen="<<strlen(message)<<endl;
			cout<<"-------------->message="<<message<<endl;
			//msg_history.size();
			snprintf(message_buffer[0],256,message_buffer[1]);
			snprintf(message_buffer[1],256,message_buffer[2]);
			snprintf(message_buffer[2],256,message);
			strcpy(message,"");
		}
          talk=(talk+1)%2;
        }
      cout<<"talk="<<talk<<endl;
      if (!talk)
      {
      // ============================ SWITCH PLAYER =============================
      if (GameRunning && !GamePaused && gp2d::KeyDown(options.KEY_SWITCH_PLAYER))
        {
          Player[CurPlayer].CanMove=false;
          //Player[CurPlayer].CanJump=false;//obsolete
          CurPlayer=(CurPlayer+1)%Player.size();
          Player[CurPlayer].CanMove=true;
          //Player[CurPlayer].CanJump=true;//obsolete
        }
      // ============================ SWITCH WEAPON =============================
      if (GameRunning && !GamePaused && gp2d::KeyDown(options.KEY_SWITCH_WEAPON))
        {
          CurrentWeapon=(CurrentWeapon+1)%IT_NB_OF_WEAPONS;
        }

      /*		if(gp2d::KeyDown(options.KEY_CHOOSE_ANGLE))	{
      			if(choose_angle1) choose_angle1=false;
      			else choose_angle1=true;
      			}*/
      if (GameRunning && !GamePaused && gp2d::KeyDown(options.KEY_ADD_PLAYER))
        {
          AddPlayer(IT_PLAYER_SUSI,Player[CurPlayer].x,50,IT_PLAYER_FACE_RIGHT,1);
          sprintf(Player[Player.size()-1].Name,"Susi %d",Player.size()-1);
          cout<<Player[Player.size()-1].Name<<" has joined the game!"<<endl;
        }
      if (gp2d::KeyDown(options.KEY_PAUSE))
        {
          if (iTimer.IsPaused())
            {
              UnPauseGame();
            }
          else
            {
              PauseGame();
            }
        }

      //here we get the mouse x,y position and the pressed button :)
      //Note that MouseMoved returns the mouse button currently, which means that it's only "true" if a mouse button is pressed and the mouse moved
      if (MouseMoved(iButton,iX,iY,iRelX,iRelY))
        {
          //printf("MouseMoved\n");
        }
      if (MouseButtonUp(iButton,iX,iY,iRelX,iRelY))
        {
          printf("MouseButtonUp\n");
        }
      //set angle with mouse :) (left-click)
      //or add player at custom position for debugging (middle-click)
      //or place current player at custom position for debugging (right-click)
      if (GameRunning && !GamePaused && MouseButtonDown(iButton,iX,iY,iRelX,iRelY))
        {
          printf("MouseButtonDown: %d\n",iButton);
          cout<<iX<<","<<iY<<endl;
          cout<<Player[CurPlayer].x<<","<<Player[CurPlayer].y<<endl;
          cout<<VIEWPORT_WIDTH<<","<<VIEWPORT_HEIGHT<<endl;
          cout<<Cam.GetX()<<","<<Cam.GetY()<<endl;
          //get x,y of the click in the same coord system as player
          double click_X=iX-((VIEWPORT_WIDTH/2)-Cam.GetX());
          double click_Y=iY-((VIEWPORT_HEIGHT/2)-Cam.GetY());
          if (iButton==1)
            {
              Player[CurPlayer].Angle=limit_angle(rad2deg(-atan2(click_Y-Player[CurPlayer].y,click_X-Player[CurPlayer].x)));
            }
          if (iButton==2)
            {
              AddPlayer(IT_PLAYER_SUSI,click_X,click_Y,IT_PLAYER_FACE_RIGHT,1);
              sprintf(Player[Player.size()-1].Name,"Susi %d",Player.size()-1);
              cout<<Player[Player.size()-1].Name<<" has joined the game!"<<endl;
            }
          if (iButton==3)
            {
              Player[CurPlayer].x=click_X;
              Player[CurPlayer].y=click_Y;
              Player[CurPlayer].vX=0;
              Player[CurPlayer].vY=0;
            }
        }

	}//end of if talk
	else
	{
		cout<<"CANNOT PLAY WHILE TALKING"<<endl;
		//PUT TEXT ENTRY CODE HERE
	}
      //This returns true when the window is minimized (but not while it is minimized!)
      CheckWindowState();
    }


  //=== Global keys ===
  //close when the close button is clicked (or alt+F4, etc.)
  if (gp2d::Close_Event()) exit(0);
  //close when the quit key is pressed (default: escape)
  if (gp2d::KeyPressed(options.KEY_QUIT)) return(1);

  if (gp2d::KeyPressed(options.KEY_FULLSCREEN) && !talk)
    {
      ToggleFullscreen();
    }
  if (gp2d::EventResizeWindow())
    {
      ResizeWindow(true,0,0,true);
    }
// 	if(gp2d::KeyPressed(options.KEY_MUSIC))	{
// 		if(music_on) {iteam::Song.Stop();music_on=false;}
// 		else {iteam::Song.Play();music_on=true;}
// 		}

  //==================

  if (GameRunning && !GamePaused && !talk)
    {
      // ============================ CHANGE VARIABLES =============================
      if (gp2d::KeyPressed(options.KEY_INC_ANGLE))
        {
          Player[CurPlayer].Angle += 10;
          if (Player[CurPlayer].Angle > 360)	Player[CurPlayer].Angle = Player[CurPlayer].Angle - 360;
        }
      if (gp2d::KeyPressed(options.KEY_DEC_ANGLE))
        {
          Player[CurPlayer].Angle -= 10;
          if (Player[CurPlayer].Angle < 0)	Player[CurPlayer].Angle = Player[CurPlayer].Angle + 360;
        }
      if (gp2d::KeyPressed(options.KEY_INC_SPEED))
        {
          Player[CurPlayer].Power += 0.5;
        }
      if (gp2d::KeyPressed(options.KEY_DEC_SPEED))
        {
          Player[CurPlayer].Power -= 0.5;
        }
      if (gp2d::KeyPressed(options.KEY_INC_FLIGHTTIME))
        {
          flighttime += 1;
        }
      if (gp2d::KeyPressed(options.KEY_DEC_FLIGHTTIME))
        {
          flighttime -= 1;
        }
      if (gp2d::KeyPressed(options.KEY_INC_GRAV))
        {
          Gravity += 1;
        }
      if (gp2d::KeyPressed(options.KEY_DEC_GRAV))
        {
          Gravity -= 1;
        }
      if (gp2d::KeyPressed(options.KEY_INC_GRE_TIME))
        {
          grenade_time += 1;
        }
      if (gp2d::KeyPressed(options.KEY_DEC_GRE_TIME))
        {
          grenade_time -= 1;
        }
      if (gp2d::KeyPressed(options.KEY_INC_JUMP_POWER))
        {
          Player[CurPlayer].JumpPower += 1;
        }
      if (gp2d::KeyPressed(options.KEY_DEC_JUMP_POWER))
        {
          Player[CurPlayer].JumpPower -= 1;
        }
      if (gp2d::KeyPressed(options.KEY_INC_ELASTICITY))
        {
          Player[CurPlayer].Elasticity += 0.1;
        }
      if (gp2d::KeyPressed(options.KEY_DEC_ELASTICITY))
        {
          Player[CurPlayer].Elasticity -= 0.1;
        }

      // ============================ AI TEST =============================

      if (gp2d::KeyPressed(options.KEY_CALCVEL))
        {
          calc_velocity(Player[CurPlayer].Angle,
                        Player[CurPlayer].Power,flighttime,
                        Gravity,
                        Player[CurPlayer].x,Player[CurPlayer].y,
                        Player[(CurPlayer+1)%2].x,Player[(CurPlayer+1)%2].y);
        }
      if (gp2d::KeyPressed(options.KEY_CALCANGLE))
        {
          GLfloat DummyAngle,DummyTime;
          if (choose_angle1)
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
      if (gp2d::KeyPressed(options.KEY_CALCVECTOR))
        {
          calc_vector(flighttime,
                      Player[CurPlayer].Angle,Player[CurPlayer].Power,
                      Gravity,
                      Player[CurPlayer].x,Player[CurPlayer].y,
                      Player[(CurPlayer+1)%2].x,Player[(CurPlayer+1)%2].y);
        }

      // ============================ WEAPONS TEST =============================
      if (gp2d::KeyPressed(options.KEY_FIRE))
        {
          // fire the test weapon !!!!!!
          Weapons_Fire(Player[CurPlayer].Angle, Player[CurPlayer].Power, CurrentWeapon);
          //cout << "[PLAYER] x = " << Player[CurPlayer].x << " y = " << Player[CurPlayer].y << "\n";
          //int retval = FireWeapon( IT_WT_GRENADE, Player[CurPlayer].x, Player[CurPlayer].y, (GLfloat) 45.0, (GLfloat) 500.0);
        }


      //==================

      if (gp2d::KeyPressed(SDLK_UP))
        {
          if (Player[CurPlayer].CanJump)
            {
              /*			Player[CurPlayer].SetAcceleration(6, 315);
              			Player[CurPlayer].CanJump = false;*/
              //Jump.Play();
              Player[CurPlayer].vY = -Player[CurPlayer].JumpPower;
            }
        }

      if (gp2d::KeyPressed(SDLK_LEFT))
        {
          //Player[CurPlayer].AddAcceleration(2, 225);
//		Player[CurPlayer].vX -=10;
        }

      if (gp2d::KeyPressed(SDLK_RIGHT))
        {
          //Player[CurPlayer].AddAcceleration(2, 0);
//		Player[CurPlayer].vX +=10;
        }

      // ============================ WEAPONS TEST =============================
      if (gp2d::KeyPressed(SDLK_1))
        {
          CurrentWeapon = IT_WT_GRENADE;
        }

      if (gp2d::KeyPressed(SDLK_2))
        {
          CurrentWeapon = IT_WT_MISSILE;
        }
      if (gp2d::KeyPressed(SDLK_3))
        {
          CurrentWeapon = IT_WT_CLUSTERBOMB;
        }
      if (gp2d::KeyPressed(SDLK_4))
        {
          CurrentWeapon = IT_WT_DYNAMITE;
        }
    }//end of if(GameRunning)
  /*        }//end of if(talk)
        else
          {
            cout<<"CANNOT PLAY WHILE TALKING"<<endl;
          }*/
  return 0;
}

int MultiPlayer(void)
{
	int translated;	/* Whether or not UNICODE translation was enabled */
	translated = SDL_EnableUNICODE(1);

  UnPauseGame();
  cout<<"=============================NEW GAME================================"<<endl;
  //GameResW = 800;
  //GameResH = 600;
  //CountdownValue = 3;
  //GameRunning = false;
  //gp2d::Cls();

  int End = 0;

// 	for(int i=0;i<=Player.size()-1;i++)
// 	{
// 		Player[i].CanMove=false;
// 		Player[i].CanJump=false;
// 		Player[i].x=(int)rand_uniform(50,180);
// 		Player[i].y=50;
// 		Player[i].vX=0;
// 		Player[i].vY=0;
// 		Player[i].LastTicks=0;//VERY IMPORTANT!!!
// 	}

  cout<<"player initial position: "<<Player[0].x<<","<<Player[0].y<<endl;
  cout<<"player initial speed: "<<Player[0].vX<<","<<Player[0].vY<<endl;
  cout<<"player initial position: "<<Player[1].x<<","<<Player[1].y<<endl;
  cout<<"player initial speed: "<<Player[1].vX<<","<<Player[1].vY<<endl;

  while (!End)
    {
      End = ProcessKeys();
      gp2d::Cls();


      if (GameRunning==false)
        {
          DrawBackground();
          DrawTerrain();
          /*			cout<<"Player[0].x="<<Player[0].x<<endl;
          			cout<<"Player[0].y="<<Player[0].y<<endl;
          			cout<<"Player[0].vX="<<Player[0].vX<<endl;
          			cout<<"Player[0].vY="<<Player[0].vY<<endl;
          			cout<<"Player[0].accel_x="<<Player[0].accel_x<<endl;
          			cout<<"Player[0].accel_y="<<Player[0].accel_y<<endl;*/
          ProcessAllPhysicalObjects();

          Cam.Begin();

          Countdown.Move((Cam.GetX()-(VIEWPORT_WIDTH/2))+VIEWPORT_WIDTH/2,(Cam.GetY()-(VIEWPORT_HEIGHT/2))+VIEWPORT_HEIGHT/2);
          Countdown.DrawFrame();
          if (Countdown.setNextFrame() == false)
            {
              GameRunning=true;
              Player[0].CanMove=true;
              CurPlayer=0;
            }

          DrawGUI();
          UpdateWeaponThumbs();
          if (Cam.GetX()>1022)
            {
              Cam.Move(1022,Cam.GetY());
            }
          if (Cam.GetX()<-220)
            {
              Cam.Move(-220,Cam.GetY());
            }
          if (Cam.GetY()>298)
            {
              Cam.Move(Cam.GetX(),298);
            }
          if (Cam.GetY()<200)
            {
              Cam.Move(Cam.GetX(),200);
            }

          Cam.End();

        }
      else
        {
          DrawBackground();
          DrawTerrain();
          ProcessAllPhysicalObjects();
          ProccessExplosions();
          DrawGUI();

          if (bStartshaking == true)
            {
              bStartshaking = false;
              bCameraShake = true;
              shakes = 0;
              shakeSize = 50;
              shakeTicks = iTimer.GetTicks();
              printf("Camera shake started\n @ %i\n", shakeTicks);
            }

          if (bCameraShake == true)
            {
              printf("Shaking\n");
              if ( (iTimer.GetTicks() - shakeTicks) > 100)
                {
                  if (++shakes > 20)
                    {
                      bCameraShake = false;
                      printf("Stopped shaking\n");
                    }
                  else
                    {
                      shakeSize -= 2;
                      int movementX = (rand()%shakeSize)-shakeSize/2;
                      int movementY = (rand()%shakeSize)-shakeSize/2;
                      shakeTicks = iTimer.GetTicks();
                      Cam.Move(Player[CurPlayer].x+ movementX, Player[CurPlayer].y+ movementY);
                      Cam.Move(CurveValueGLf(Player[CurPlayer].x,Cam.GetX(),5.0f),CurveValueGLf(Player[CurPlayer].y,Cam.GetY(),5.0f));
                    }
                }
            }
          else
            {
              Cam.Move(CurveValueGLf(Player[CurPlayer].x,Cam.GetX(),50.0f),CurveValueGLf(Player[CurPlayer].y,Cam.GetY(),50.0f));
            }

          if (Cam.GetX()>1022)
            {
              Cam.Move(1022,Cam.GetY());
            }
          if (Cam.GetX()<-220)
            {
              Cam.Move(-220,Cam.GetY());
            }
          if (Cam.GetY()<200)
            {
              Cam.Move(Cam.GetX(),200);
            }
          if (Cam.GetY()>298)
            {
              Cam.Move(Cam.GetX(),298);
            }
          Cam.End();

        }

      //info display
      Text(FNTGameGUI, 10,64, 0,1,1,1, 1,1,1, "Player X: %f",Player[CurPlayer].x);
      Text(FNTGameGUI, 10,64+1*16, 0,1,1,1, 1,1,1, "Player Y: %f",Player[CurPlayer].y);
      Text(FNTGameGUI, 10,64+2*16, 0,1,1,1, 1,1,1, "Player vX: %f",Player[CurPlayer].vX);
      Text(FNTGameGUI, 10,64+3*16, 0,1,1,1, 1,1,1, "Player vY: %f",Player[CurPlayer].vY);

      Text(FNTGameGUI, 10,64+4*16, 0,1,1,1, 1,1,1, "Angle: %i%c",(unsigned int)Player[CurPlayer].Angle, 0xB0);
      Text(FNTGameGUI, 10,64+5*16, 0,1,1,1, 1,1,1, "Strenght:  %f",Player[CurPlayer].Power);
      Text(FNTGameGUI, 10,64+6*16, 0,1,1,1, 1,1,1, "flighttime:  %f",flighttime);
      Text(FNTGameGUI, 10,64+7*16, 0,1,1,1, 1,1,1, "Gravity:  %f",Gravity);
      Text(FNTGameGUI, 10,64+8*16, 0,1,1,1, 1,1,1, "grenade_time:  %d",grenade_time);
      Text(FNTGameGUI, 10,64+9*16, 0,1,1,1, 1,1,1, "choose_angle1:  %d",choose_angle1);
      Text(FNTGameGUI, 10,64+10*16, 0,1,1,1, 1,1,1, "CurPlayer:  %d",CurPlayer);
      Text(FNTGameGUI, 10,64+11*16, 0,1,1,1, 1,1,1, "JumpPower: %f",Player[CurPlayer].JumpPower);
      Text(FNTGameGUI, 10,64+12*16, 0,1,1,1, 1,1,1, "Elasticity: %f",Player[CurPlayer].Elasticity);
      Text(FNTGameGUI, 10,64+13*16, 0,1,1,1, 1,1,1, "");

//       char message_buffer[3][256];
//         snprintf(message_buffer[0],256,"hello world!");
//         snprintf(message_buffer[1],256,"How are you?");
//         snprintf(message_buffer[2],256,"very well. Thank you.");

      Text(FNTGameGUI, 10,64+17*16, 0,1,1,1, 1,1,1, "%s",message_buffer[0]);
      Text(FNTGameGUI, 10,64+18*16, 0,1,1,1, 1,1,1, "%s",message_buffer[1]);
      Text(FNTGameGUI, 10,64+19*16, 0,1,1,1, 1,1,1, "%s",message_buffer[2]);

	//strcpy(message,"");//like this it works correctly...
	if(talk) Text(FNTGameGUI, 10,64+20*16, 0,1,1,1, 1,1,1, "Talk:%s",message);

      gp2d::ShowFPS();
      gp2d::Sync();
    }

  PauseGame();
}

//================================================
// MAIN FUNCTION
//================================================
#ifdef _WIN32
int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int)   // If we're on Windows we'll need this line instead of main()
{
#else
int main()   // Else if we're on Linux, just use main :)
{
#endif
//gp2d::SetDataDir("/usr/share/games/i-team/");
gp2d::SetDataDir(".");
// sprintf(message,"%s/chars/susi.png",DATA_DIR);
// cout<<DATA_DIR<<endl;
// cout<<message<<endl;
// exit(0);

  //load settings
  options.Load("toto.cfg");

cout<<"Init"<<endl;
  iteam::Init();

//   LoadMenus();
//   iteam::Intro();
// 
//   iteam::Load();
//   iTimer.Start();
//   if (iTimer.IsStarted())
//     {
//       cout << "Timer started"<<endl;
//     }

/////////////////////////////////////////////////////////////////////////////
// // 	SDL_Surface *screen;
// cout<<"variable declaration"<<endl;
// 	int x, y, i;
// 	int error;
// 	GUI_Widget *widget;
// 	SDL_Rect null_rect = { 0, 0, 0, 0 };
// // 	GUI_Menu *menu;
// // 
// // 	/* Initialize SDL */
// // 	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
// // 		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
// // 		exit(1);
// // 	}
// // 	atexit(SDL_Quit);
// // 
// // 	/* Get a video mode for display */
// // 	screen = SDL_SetVideoMode(640, 480, 0, SDL_SWSURFACE);
// // 	if ( screen == NULL ) {
// // 		fprintf(stderr, "Couldn't set video mode: %s\n",SDL_GetError());
// // 		exit(1);
// // 	}
// // 	SDL_WM_SetCaption("GUI Hello!", "hello");
// 
// cout<<"get_Screen"<<endl;
// 	SDL_Surface *screen=gp2d::get_Screen();
// 
// cout<<"Create a GUI container"<<endl;
// 	/* Create a GUI container */
// 	gui = new GUI(screen);
// 
// cout<<"Load our images"<<endl;
// 	/* Load our images */
// 	for ( i=0; i<NUM_IMAGES; ++i ) {
// 		images[i] = NULL;
// 	}
// 	error = 0;
// 	for ( i=0; i<NUM_IMAGES; ++i ) {
// 		images[i] = SDL_LoadBMP(image_files[i]);
// 		if ( images[i] == NULL ) {
// 			fprintf(stderr, "Couldn't load '%s': %s\n",
// 					image_files[i], SDL_GetError());
// 			++error;
// 		}
// 	}
// 	if ( error ) {
// 		cleanup();
// 		exit(1);
// 	}
// 
// cout<<"We also want a small text window with scroll buttons"<<endl;
// 	/* We also want a small text window with scroll buttons */
// 	x = images[IMAGE_SCROLL_UP]->w;
// 	terminal = new GUI_TermWin(x, 18, screen->w-x, 32, NULL, ShowChar, 32);
// 	terminal->AddText("Talk: ");
// 	gui->AddWidget(terminal);
// 	y = images[IMAGE_SCROLL_UP]->h;
// 	widget = new GUI_ScrollButtons(0,18, images[IMAGE_SCROLL_UP], null_rect,
// 					0, y+18, images[IMAGE_SCROLL_DN],
// 					SCROLLBAR_VERTICAL, terminal);
// 	gui->AddWidget(widget);
// 
// cout<<"Run the GUI, and then clean up when it's done."<<endl;
// 	/* Run the GUI, and then clean up when it's done. */
// 	gui->Run(NULL);
// 	//Output(screen,"-= Thanks =-","Thanks for trying the C++ GUI interface");
// 	cout<<"Thanks for trying the C++ GUI interface"<<endl;
// 	cleanup();
// 	exit(0);
// 
// cout<<"To make the compiler happy"<<endl;
// 	/* To make the compiler happy */
// 	return(0);

/////////////////////////////////////////////////////////////////////////////

//   //load settings
//   options.Load("toto.cfg");
// 
//   iteam::Init();
// 
   LoadMenus();
   iteam::Intro();
// 
   iteam::Load();
   iTimer.Start();
  if (iTimer.IsStarted())
    {
      cout << "Timer started"<<endl;
    }

  int choice=0;
  while (choice!=6)
    {
      choice=iteam::MainMenu();
      if (choice==1) cout<<"single player"<<endl;
      if (choice==2) MultiPlayer();
      if (choice==3) SettingsMenu();
      if (choice==4) cout<<"mods"<<endl;
      if (choice==5) cout<<"credits"<<endl;
      if (choice==6) cout<<"exit"<<endl;
    }

  //save settings
  options.Save("toto.cfg");

}
