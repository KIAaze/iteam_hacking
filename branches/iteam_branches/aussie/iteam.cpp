#include "globals.h"
#include "functions.h"
#include "players.h"

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

gp2d::Font   iteam::FNTCounter;
gp2d::Font   iteam::FNTNames;
gp2d::Font   iteam::FNTGameGUI;

gp2d::Camera iteam::Cam;

#ifdef _WIN32
int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int) { // If we're on Windows we'll need this line instead of main()
#else
int main() { // Else if we're on Linux, just use main :)
#endif
	iteam::Init();
	iteam::Load();

	int cnt=0;
	int cnt2=0;

	Player[0].CanMove=true;
	Player[0].CanJump=true;

	GLfloat px1,py1,px2,py2,angle1,finalangle;
	GLfloat vy1,vy2;
	
	while(1){

		gp2d::Cls();
		gp2d::CatchEvents();
		if(gp2d::KeyPressed(SDLK_ESCAPE)){ break; }
		if(gp2d::KeyPressed(SDLK_f)){ ToggleFullscreen(); }
		if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }

		if(GameRunning==false){
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
				// TODO: Make the countdown work. It only shows "3" now.
				Countdown.Move((Cam.GetX()-(VIEWPORT_WIDTH/2))+VIEWPORT_WIDTH/2,(Cam.GetY()-(VIEWPORT_HEIGHT/2))+VIEWPORT_HEIGHT/2);
				if(CountdownValue==3){ Countdown.Draw(); }
				if(CountdownValue==2){ Countdown.Draw(); }
				if(CountdownValue==1){ Countdown.Draw(); }
				if(CountdownValue<=0){ Countdown.Draw(); }

			DrawGUI();

			if(Cam.GetX()>1022){ Cam.Move(1022,Cam.GetY()); }
			if(Cam.GetX()<-220){ Cam.Move(-220,Cam.GetY()); }
			if(Cam.GetY()>298){ Cam.Move(Cam.GetX(),298); }
			if(Cam.GetY()<200){ Cam.Move(Cam.GetX(),200); }

			Cam.End();

			cnt++;
			cnt2++;
			// if(cnt>360){ CurPlayer++; if(CurPlayer>1){ CurPlayer=0; } cnt=0; }
			if(cnt2>60){ CountdownValue--; cnt2=0; }
			if(CountdownValue<=-1){ GameRunning=true; Player[0].CanMove=true; CurPlayer=0; }

		} else {
			DrawBackground();
			DrawTerrain();
			for(int i=0;i<=Player.size()-1;i++){ 
				Player[i].MoveMe();
				Cam.Begin();
					Player[i].DrawMe();
				Cam.Begin();
					Player[i].DrawName();
			}

			DrawGUI();

			Cam.Move(CurveValueGLf(Player[CurPlayer].x-320,Cam.GetX(),50.0f),CurveValueGLf(Player[CurPlayer].y,Cam.GetY(),50.0f));
			if(Cam.GetX()>1022){ Cam.Move(1022,Cam.GetY()); }
			if(Cam.GetX()<-220){ Cam.Move(-220,Cam.GetY()); }
			if(Cam.GetY()<200){ Cam.Move(Cam.GetX(),200); }
			if(Cam.GetY()>298){ Cam.Move(Cam.GetX(),298); }
			Cam.End();

			cnt++;
			// if(cnt>360){ CurPlayer++; if(CurPlayer>1){ CurPlayer=0; } cnt=0; }

		}

		Cam.Begin();
		
		px1 = (Player[0].x - Player[0].width[0]/2)+24;
		py1 = (Player[0].y + Player[0].height[0]/2)-2;
		px2 = (Player[0].x + Player[0].width[0]/2)-8;
		py2 = (Player[0].y + Player[0].height[0]/2)-2;
				
		gp2d::DisableTexturing();
			gp2d::SetPointSize(5.0f);
			gp2d::BeginPoints();
				SetColor3(1,1,1); 
				gp2d::DrawPixel(px1,py1);
			gp2d::EndPoints();
		gp2d::EnableTexturing();

		px2=(px1-(VIEWPORT_WIDTH/2))+Player[0].width[0]/2;
		py2=(py1-(VIEWPORT_HEIGHT/2))+Player[0].height[0]/2;

		gp2d::DisableTexturing();
			gp2d::SetPointSize(5.0f);
			gp2d::BeginPoints();
				SetColor3(1,1,1); 
				gp2d::DrawPixel(px2,py1);
			gp2d::EndPoints();
		gp2d::EnableTexturing();
		
		while(!CollisionOnPixel(&Terrain,0,(int)px2,(int)py1)){
			gp2d::DisableTexturing();
				gp2d::SetPointSize(5.0f);
				gp2d::BeginPoints();
					SetColor3(0,0,1); 
					gp2d::DrawPixel(px2+(VIEWPORT_WIDTH/2)-Player[0].width[0]/2,py1);
				gp2d::EndPoints();
			gp2d::EnableTexturing();
			py1+=2.0f;
		}

		// angle1 = atan2((lg.y-rg.y), (lg.x-rg.x));
		// finalangle = angle1 * CONST_RAD2DEG;
		
		// Player[0].angle = finalangle+180;
		
		Text(FNTGameGUI, 10,64, 0,1,1,1, 1,1,1, "Player X: %f",Player[0].x);
		Text(FNTGameGUI, 10,64+16, 0,1,1,1, 1,1,1, "Player Y: %f",Player[0].y);
		/*
		Text(FNTGameGUI, 10,64+32+16, 0,1,1,1, 1,1,1, "Left x, Left y: %f, %f",px1,py1);
		Text(FNTGameGUI, 10,64+32+32, 0,1,1,1, 1,1,1, "Right x, Right y: %f, %f",px2,py2);
		*/
		// Text(FNTGameGUI, 10,64+32+32+32, 0,1,1,1, 1,1,1, "Angle: %f",finalangle);

		gp2d::ShowFPS();
		gp2d::Sync();
	}

	SDL_Quit();
}
