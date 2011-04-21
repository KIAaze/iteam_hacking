/*! \file iteam.cpp
\brief Main game source file.

This is the heart of the whole game.
*/

#include "globals.h"

using namespace std;
using namespace gp2d;
using namespace iteam;

vector <iteam::PlayerObj> iteam::Player;
vector <int> Turn;

vector <gp2d::Sprite> iteam::Level;
vector <gp2d::Sprite> iteam::InGameGUI;
vector <gp2d::Font>   iteam::Font;
vector <gp2d::Timer>  iteam::Timer;
vector <gp2d::Sound>  iteam::Audio;
vector <gp2d::Music>  iteam::Song;

gp2d::Camera iteam::Cam;

GLfloat IT_Angle = 0;

/* Used for the camera shake*/
bool bCameraShake = false;
int	shakeTicks = 0;
int	shakes = 0;
int	shakeSize = 0;
int movementX;
int movementY;

bool iteam::bQuitGame = false;
gp2d::inputHandler *KeyHandler = NULL;

iteam::GameState iteam::gameState = ITEAM_PREINTRO;


/****************************************************************/
/************ Main game event callbacks *************************/
/****************************************************************/
/***** IDEALLY THESE SHOULD BE PUBLIC FUNCTIONS TO CLASSES ******/
/***** FOR EXAMPLE THE PLAYER CLASS TO KEEP THE CODE TIDY  ******/
/****************************************************************/
void RunningChangeAngle() {
	printf("changing angle\n");
	IT_Angle += 10;
	if(IT_Angle > 360)	IT_Angle = IT_Angle - 360;
}
void RunningChangeWeaponStrength() {
	WeaponStrenght += 1;
}
void RunningFireWeapon() {
	Test_Fire(IT_Angle);
}
void RunningChangeCharacter() {
	if(CurPlayer == (IT_PLAYER_ONE - 1))	{
		CurPlayer = IT_PLAYER_TWO - 1; 
		Player[IT_PLAYER_ONE - 1].CanMove=false;
		Player[IT_PLAYER_ONE - 1].CanJump=false;
		Player[IT_PLAYER_TWO - 1].CanMove=true;
		Player[IT_PLAYER_TWO - 1].CanJump=true;					
	} else {
		CurPlayer = IT_PLAYER_ONE - 1;
		Player[IT_PLAYER_ONE - 1].CanMove=true;
		Player[IT_PLAYER_ONE - 1].CanJump=true;
		Player[IT_PLAYER_TWO - 1].CanMove=false;
		Player[IT_PLAYER_TWO - 1].CanJump=false;
	}
}
void RunningActivateCameraShake() {
	bCameraShake = true;
	shakes = 0;
	shakeSize = 50;
	shakeTicks = iteam::Timer[0].GetTicks();
	printf("Camera shake started\n @ %i\n", shakeTicks);
}
void RunningPlayerJump() {
	Player[CurPlayer].Movement.jumping = true;
}
void RunningPlayerJumpStop() {
	Player[CurPlayer].Movement.jumping = false;
}
void RunningPlayerLeft() {
	// If we are not walking the opposite way
	if (Player[CurPlayer].Movement.walkingRight==false) {
		Player[CurPlayer].Movement.walkingLeft = true;
	}
}
void RunningPlayerLeftStop() {
	Player[CurPlayer].Movement.walkingLeft = false;
} 
void RunningPlayerRight() {
	if (Player[CurPlayer].Movement.walkingLeft==false) {
		Player[CurPlayer].Movement.walkingRight = true;
	}
}
void RunningPlayerRightStop() {
	Player[CurPlayer].Movement.walkingRight = false;
} 

/****************************************************************/
/****************************************************************/


#ifdef _WIN32
int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int) { // If we're on Windows we'll need this line instead of main()
#else
/*! \brief Main procedure (READ DETAILS!!)

Depending on the compiler used, the code will detect if we're using MinGW32 (Windows) or GNU GCC/GPP (Linux). If you read the iteam.cpp code in lines 45-54, there's a compiler conditional to determine if we're gonna use
main() (for Linux) or WinMain (for Windows). There should be a workaround for this and just use main(), but I haven't been able to find another one, so this works and it doesn't look too messy.
*/
int main() { // Else if we're on Linux, just use main :)
#endif

	// This now initialises the video (calls iteam::init())- This is required because of threading purposes
	printf("About to kick off keyhandler\n");
	KeyHandler = new gp2d::inputHandler(iteam::Init);
	RegisterGlobalKeys();
	printf("inputHanlder registered\n");

	SDL_Delay(1000);		// TODO: Need a better way to detect that the initialisation is complete before messing with video

	
	bool flag1;
	GLfloat size1=1.0f;

	while(bQuitGame==false){

		gp2d::Cls();
	
		switch (gameState) {
			case ITEAM_PREINTRO:
				PreIntro();
				break;
			case ITEAM_INTRO:
				Intro();
				break;
			case ITEAM_PREMAINMENU:
				PreMainMenu();
				break;
			case ITEAM_MAINMENU:
				MainMenu();
				break;
			case ITEAM_PRECOUNTDOWN:
				//Remove the functionality of the space bar used in main_menu
				KeyHandler->unregisterInputCallback(SDLK_SPACE);

				iteam::Load();
				iteam::Timer.push_back(gp2d::Timer());
				iteam::Timer[0].Start();

				for(int i=0;i<=Player.size()-1;i++){
					Player[0].CanMove=true;
					Player[0].CanJump=true;
				}
				gameState = ITEAM_COUNTDOWN;
				break;
			case ITEAM_COUNTDOWN:
				DrawBackground();
				DrawTerrain();
				for(int i=0;i<=Player.size()-1;i++){ 
					Player[i].CanMove=false;
					Player[i].MoveMe();
					Cam.Begin();
						Player[i].DrawMe();
					Cam.Begin();
						Player[i].DrawName();
				}
			
				Cam.Begin();
					iteam::InGameGUI[1].Move((Cam.GetX()-(VIEWPORT_WIDTH/2))+VIEWPORT_WIDTH/2,(Cam.GetY()-(VIEWPORT_HEIGHT/2))+VIEWPORT_HEIGHT/2);
					iteam::InGameGUI[1].DrawFrame();
						if (iteam::InGameGUI[1].setNextFrame() == false) {
							gameState = ITEAM_PRERUNNING;
							SecondsCounter = iteam::Timer[0].GetTicks();
							Seconds = 20;
							Player[0].CanMove=true;
							CurPlayer=0;
							flag1 = true;
						}
					DrawGUI();	

					if(Cam.GetX()>1022){ Cam.Move(1022,Cam.GetY()); }
					if(Cam.GetX()<-220){ Cam.Move(-220,Cam.GetY()); }
					if(Cam.GetY()>298){ Cam.Move(Cam.GetX(),298); }
					if(Cam.GetY()<200){ Cam.Move(Cam.GetX(),200); }
				
				Cam.End();
				break;
			case ITEAM_PRERUNNING:
				//Change screen mode fullscreen/normal
				KeyHandler->registerInputCallback(SDLK_a, RunningChangeAngle, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_a, RunningChangeAngle, GP2D_KEYPRESSED);

				KeyHandler->registerInputCallback(SDLK_MINUS, RunningChangeWeaponStrength, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_MINUS, RunningChangeWeaponStrength, GP2D_KEYPRESSED);

				KeyHandler->registerInputCallback(SDLK_b, RunningFireWeapon, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_b, RunningFireWeapon, GP2D_KEYPRESSED);

				KeyHandler->registerInputCallback(SDLK_c, RunningChangeCharacter, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_c, RunningChangeCharacter, GP2D_KEYPRESSED);

				KeyHandler->registerInputCallback(SDLK_s, RunningActivateCameraShake, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_s, RunningActivateCameraShake, GP2D_KEYPRESSED);

				KeyHandler->registerInputCallback(SDLK_UP, RunningPlayerJump, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_UP, RunningPlayerJump, GP2D_KEYPRESSED);
				KeyHandler->registerInputCallback(SDLK_UP, RunningPlayerJumpStop, GP2D_KEYUP);
				KeyHandler->registerInputCallback(SDLK_LEFT, RunningPlayerLeft, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_LEFT, RunningPlayerLeft, GP2D_KEYPRESSED);
				KeyHandler->registerInputCallback(SDLK_LEFT, RunningPlayerLeftStop, GP2D_KEYUP);
				KeyHandler->registerInputCallback(SDLK_RIGHT, RunningPlayerRight, GP2D_KEYDOWN);
				KeyHandler->registerInputCallback(SDLK_RIGHT, RunningPlayerRight, GP2D_KEYPRESSED);
				KeyHandler->registerInputCallback(SDLK_RIGHT, RunningPlayerRightStop, GP2D_KEYUP);

				gameState = ITEAM_RUNNING;
				break;
			case ITEAM_RUNNING:

				if ((iteam::Timer[0].GetTicks() - SecondsCounter) > 1000) {
					Audio[1].Play();
					Seconds--;
					SecondsCounter = iteam::Timer[0].GetTicks();
				}

				DrawBackground();
				DrawTerrain();

				for(int i=0;i<=Player.size()-1;i++){ 
					Player[i].MoveMe();
					Cam.Begin();
						Player[i].DrawMe();
					Cam.Begin();
						Player[i].DrawName();
				}
				UpdatePhysicalObjects();
				
				if(flag1==true){
					iteam::InGameGUI[1].Move((Cam.GetX()-(VIEWPORT_WIDTH/2))+VIEWPORT_WIDTH/2,(Cam.GetY()-(VIEWPORT_HEIGHT/2))+VIEWPORT_HEIGHT/2);
					iteam::InGameGUI[1].selectSheet(3);
					iteam::InGameGUI[1].DrawFrame();
					size1-=0.01f;
					iteam::InGameGUI[1].alpha[3] = size1;
					iteam::InGameGUI[1].Scale(1.0f+(fabs(size1)/10));
					if(iteam::InGameGUI[1].alpha[3]<=0){ flag1=false; }
				}
				
				DrawGUI();

				if (bCameraShake == true) {
					printf("Shaking\n");
					if ( (iteam::Timer[0].GetTicks() - shakeTicks) > 100) {
						if (++shakes > 20) {
							bCameraShake = false;
							printf("Stopped shaking\n");
						}
						else {
							shakeSize -= 2;
							int movementX = (rand()%shakeSize)-shakeSize/2;
							int movementY = (rand()%shakeSize)-shakeSize/2;
							shakeTicks = iteam::Timer[0].GetTicks();
							Cam.Move(Player[CurPlayer].x+ movementX, Player[CurPlayer].y+ movementY);
							Cam.Move(CurveValueGLf(Player[CurPlayer].x,Cam.GetX(),5.0f),CurveValueGLf(Player[CurPlayer].y,Cam.GetY(),5.0f));
						}
					}
				}
				else {
					Cam.Move(CurveValueGLf(Player[CurPlayer].x,Cam.GetX(),50.0f),CurveValueGLf(Player[CurPlayer].y,Cam.GetY(),50.0f));
				}

				if(Cam.GetX()>1022){ Cam.Move(1022,Cam.GetY()); }
				if(Cam.GetX()<-220){ Cam.Move(-220,Cam.GetY()); }
				if(Cam.GetY()<200){ Cam.Move(Cam.GetX(),200); }
				if(Cam.GetY()>298){ Cam.Move(Cam.GetX(),298); }

				
				Text(iteam::Font[1], 10,24, 0,1,1,1, 1,1,1, "Angle: %i%c",(unsigned int)IT_Angle, 0xB0);	
				Text(iteam::Font[1], 10,24+24, 0,1,1,1, 1,1,1, "Strength:  %f",WeaponStrenght);
				
				if(Seconds>=10){
					Text(iteam::Font[0], 800-124,12+68, 0,1,1,1, 0,0,0, "%i",Seconds);
					Text(iteam::Font[0], 800-128,12+64, 0,1,1,1, 1,0,0, "%i",Seconds);
				} else {
					Text(iteam::Font[0], 800-124,12+68, 0,1,1,1, 0,0,0, "0%i",Seconds);
					Text(iteam::Font[0], 800-128,12+64, 0,1,1,1, 1,0,0, "0%i",Seconds);
				}
				
				if(Seconds<=0){ NextTurn(); }
				
				Cam.End();
				break;
			}
			gp2d::ShowFPS();
			gp2d::Sync();
		}
}
