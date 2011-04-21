#include "globals.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "settings.h"

#define RECT_WIDTH 305
#define RECT_HEIGHT 50
#define FIRST_X -1
#define FIRST_Y 137
#define STEP_Y -54

#define TEXT_RECT_WIDTH 305
#define TEXT_RECT_HEIGHT 16
#define TEXT_FIRST_X 241
#define TEXT_FIRST_Y 279
#define TEXT_STEP_Y -16

#define NB_OF_KEYS 26

gp2d::Sprite Title;
gp2d::Sprite Menu;
gp2d::Sprite Settings;

namespace iteam {

	int LoadMenus(void)
	{
		//To avoid filling up the RAM when switching menus
		Title.Load("data/gui/intro.png");
		Menu.Load("data/gui/menu.png");
		Settings.Load("data/gui/black.png");

		return(0);
	}

	void Intro()
	{
		bool flag;
		gp2d::Timer  T;
		//gp2d::Sprite Title;
		//Title.Load("data/gui/intro.png");
		Title.width[0]=800;
		Title.height[0]=600;
		Title.Move(0,0);
		Title.alpha[0]=0;
		
		gp2d::SetBackgroundColor(0,0,0,1);
		while(1){
			gp2d::Cls();
			gp2d::CatchEvents();
			if(gp2d::Close_Event()) exit(0);
			if(gp2d::KeyPressed(options.KEY_QUIT)){ break; }
			if(gp2d::KeyPressed(options.KEY_FULLSCREEN)){ ToggleFullscreen(); }
			if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }
			
			if(flag==false){
				if(Title.alpha[0]<1.0f){ Title.alpha[0]+=0.005f; }
				if(Title.alpha[0]>1.0f){ Title.alpha[0]=1.0f; T.Start(); flag=true; }
				Cam.Begin();			
					Title.Draw();
			} else {
				if(T.GetTicks() > 5000){
					if(Title.alpha[0]>0.0f){ Title.alpha[0]-=0.005f; }
					if(Title.alpha[0]<=0.0f){ Title.alpha[0]=0; break; }
				}
				Cam.Begin();			
					Title.Draw();
				Cam.End();
			}
				
			gp2d::ShowFPS();
			gp2d::Sync();			
		}
		T.Stop();
	}

// 	void MainMenu()
// 	{
// 		gp2d::Sprite Menu;
// 		Menu.Load("data/gui/menu.png");
// 		Menu.width[0]=800;
// 		Menu.height[0]=600;
// 		Menu.Move(0,0);
// 		Menu.alpha[0]=0;
// 		
// 		gp2d::SetBackgroundColor(0,0,0,1);
// 		while(1){
// 			gp2d::Cls();
// 			gp2d::CatchEvents();
// 			if(gp2d::KeyPressed(SDLK_SPACE)){ break; }
// 			if(gp2d::KeyPressed(SDLK_f)){ ToggleFullscreen(); }
// 			if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }
// 			
// 			if(Menu.alpha[0]<1.0f){ Menu.alpha[0]+=0.05f; }
// 			if(Menu.alpha[0]>1.0f){ Menu.alpha[0]=1.0f; }
// 			
// 			Cam.Begin();
// 				Cam.Move(0,0);
// 				Menu.Draw();
// 				Text(FNTGameGUI, 10,10, 0,1,1,1, 1,1,1, "Press SPACE key to start");
// 			Cam.End();
// 				
// 			gp2d::ShowFPS();
// 			gp2d::Sync();			
// 		}
// 	}

	SDLKey getKey(char *name)
	{
		SDL_Event keyevent;    //The SDL event that we will poll to get events.
		bool done=false;
		SDLKey value;
		while (1)//loop until a key or mouse button is pressed
		{
			while(SDL_PollEvent(&keyevent))//Poll our SDL key event for any keystrokes.
			{
				if(keyevent.type==SDL_KEYDOWN)
				{
					value=keyevent.key.keysym.sym;
					sprintf(name,SDL_GetKeyName(keyevent.key.keysym.sym));
					done=true;
				}
	/*			if(keyevent.type==SDL_MOUSEBUTTONDOWN)
				{
					value=-keyevent.button.button;
					sprintf(name,"mouse %d",-value);
					done=true;
				}*/
			}
			if(done) break;
		}
		return(value);
	}
	
	int MainMenu(void)
	{
		int ret=0;
	
		//gp2d::Sprite Menu;
		//Menu.Load("data/gui/menu.png");
		Menu.width[0]=800;
		Menu.height[0]=600;
		Menu.Move(0,0);
		Menu.alpha[0]=0;
		
		gp2d::SetBackgroundColor(0,0,0,1);
		int i=0;
		double rect_X=FIRST_X;
		double rect_Y=FIRST_Y;
	
		while(1){
			gp2d::Cls();
			
			if(Menu.alpha[0]<1.0f){ Menu.alpha[0]+=0.05f; }
			if(Menu.alpha[0]>1.0f){ Menu.alpha[0]=1.0f; }
			
			Cam.Begin();
				Cam.Move(0,0);
				Menu.Draw();
				//Text(FNTGameGUI, 10,10, 0,1,1,1, 1,1,1, "Press SPACE key to start");
			Cam.End();
			
			rect_X=FIRST_X;
			rect_Y=FIRST_Y+i*STEP_Y;
			DrawRectangle(rect_X-RECT_WIDTH/2.0,rect_Y-RECT_HEIGHT/2.0,rect_X+RECT_WIDTH/2.0,rect_Y+RECT_HEIGHT/2.0,1,1,1);
	
			int iButton;
			int iX;
			int iY;
			int iRelX;
			int iRelY;
	
			while(gp2d::CatchEvents())
			{
				if(MouseMoved(iButton,iX,iY,iRelX,iRelY))
				{
					double click_X=Cam.GetX()-iX+(VIEWPORT_WIDTH/2);
					double click_Y=Cam.GetY()-iY+(VIEWPORT_HEIGHT/2);
					i=(int)((click_Y-FIRST_Y)/STEP_Y);
					if(i<0) i=0;
					if(i>5) i=5;
				}
				if(MouseButtonUp(iButton,iX,iY,iRelX,iRelY))
				{
					printf("MouseButtonUp\n");
				}
				if(MouseButtonDown(iButton,iX,iY,iRelX,iRelY))
				{
					printf("MouseButtonDown\n");
					//get x,y of the click in the same coord system as menu
					double click_X=Cam.GetX()-iX+(VIEWPORT_WIDTH/2);
					double click_Y=Cam.GetY()-iY+(VIEWPORT_HEIGHT/2);
					ret=i+1;
				}
			}
	
			//if(gp2d::KeyPressed(SDLK_SPACE)){ break; }
			if(gp2d::Close_Event()) exit(0);
			if(gp2d::KeyPressed(options.KEY_FULLSCREEN)){ ToggleFullscreen(); }
			if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }
	
			gp2d::ShowFPS();
			gp2d::Sync();
	
			if(ret!=0) break;
		}
		return(ret);
	}//end of MainMenu
	
	int SettingsMenu(void)
	{
		bool done=false;
	
		//gp2d::Sprite Settings;
		//Settings.Load("data/gui/black.png");
		Settings.width[0]=800;
		Settings.height[0]=600;
		Settings.Move(0,0);
		Settings.alpha[0]=0;
		
		int i=0;
		double rect_X=TEXT_FIRST_X;
		double rect_Y=TEXT_FIRST_Y;
	
		gp2d::SetBackgroundColor(0,0,0,1);
		while(!done){
			gp2d::Cls();
			//gp2d::CatchEvents();
			//if(gp2d::KeyPressed(SDLK_ESCAPE)){ break; }
			//if(gp2d::KeyPressed(SDLK_f)){ ToggleFullscreen(); }
			if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }
			
			if(Settings.alpha[0]<1.0f){ Settings.alpha[0]+=0.05f; }
			if(Settings.alpha[0]>1.0f){ Settings.alpha[0]=1.0f; }
			
			Cam.Begin();
				Cam.Move(0,0);
				Settings.Draw();
				//Text(FNTGameGUI, 10,10, 0,1,1,1, 1,1,1, "Press ESCAPE key to return to main menu");
	
			int j=1;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_QUIT");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_FULLSCREEN");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_MUSIC");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_SWITCH_PLAYER");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_SWITCH_WEAPON");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_FIRE");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_CHOOSE_ANGLE");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_ADD_PLAYER");j++;
		
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_DEC_ANGLE");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_INC_ANGLE");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_DEC_SPEED");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_INC_SPEED");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_DEC_FLIGHTTIME");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_INC_FLIGHTTIME");j++;
		
			//calc velocity+time from angle
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_CALCVEL");j++;
			//calc angle+time from velocity
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_CALCANGLE");j++;
			//calc velocity+angle from time
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_CALCVECTOR");j++;
		
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_DEC_GRAV");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_INC_GRAV");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_DEC_GRE_TIME");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_INC_GRE_TIME");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_DEC_JUMP_POWER");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_INC_JUMP_POWER");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_DEC_ELASTICITY");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_INC_ELASTICITY");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "KEY_PAUSE");j++;
			Text(FNTGameGUI, 10,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, "Return to main menu");j++;
	
			j=1;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1,SDL_GetKeyName( options.KEY_QUIT));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_FULLSCREEN));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_MUSIC));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_SWITCH_PLAYER));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_SWITCH_WEAPON));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_FIRE));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_CHOOSE_ANGLE));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_ADD_PLAYER));j++;
		
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_DEC_ANGLE));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_INC_ANGLE));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_DEC_SPEED));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_INC_SPEED));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_DEC_FLIGHTTIME));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_INC_FLIGHTTIME));j++;
		
			//calc velocity+time from angle
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_CALCVEL));j++;
			//calc angle+time from velocity
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_CALCANGLE));j++;
			//calc velocity+angle from time
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_CALCVECTOR));j++;
		
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_DEC_GRAV));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_INC_GRAV));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_DEC_GRE_TIME));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_INC_GRE_TIME));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_DEC_JUMP_POWER));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_INC_JUMP_POWER));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_DEC_ELASTICITY));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_INC_ELASTICITY));j++;
			Text(FNTGameGUI, 10+TEXT_RECT_WIDTH,10-j*TEXT_STEP_Y, 0,1,1,1, 1,1,1, SDL_GetKeyName(options.KEY_PAUSE));j++;
	
			Cam.End();
	
			rect_X=TEXT_FIRST_X;
			rect_Y=TEXT_FIRST_Y+i*TEXT_STEP_Y;
			DrawRectangle(rect_X-1.5*TEXT_RECT_WIDTH,rect_Y-TEXT_RECT_HEIGHT/2.0,rect_X+0.5*TEXT_RECT_WIDTH,rect_Y+TEXT_RECT_HEIGHT/2.0,1,1,1);
	
			int iButton;
			int iX;
			int iY;
			int iRelX;
			int iRelY;
	
			while(gp2d::CatchEvents())
			{
				if(MouseMoved(iButton,iX,iY,iRelX,iRelY))
				{
					double click_X=Cam.GetX()-iX+(VIEWPORT_WIDTH/2);
					double click_Y=Cam.GetY()-iY+(VIEWPORT_HEIGHT/2);
					i=(int)((click_Y-TEXT_FIRST_Y)/TEXT_STEP_Y);
					if(i<0) i=0;
					if(i>NB_OF_KEYS) i=NB_OF_KEYS;
				}
				if(MouseButtonUp(iButton,iX,iY,iRelX,iRelY))
				{
					printf("MouseButtonUp\n");
				}
				if(MouseButtonDown(iButton,iX,iY,iRelX,iRelY))
				{
					printf("MouseButtonDown\n");
					//get x,y of the click in the same coord system as menu
					double click_X=Cam.GetX()-iX+(VIEWPORT_WIDTH/2);
					double click_Y=Cam.GetY()-iY+(VIEWPORT_HEIGHT/2);
	
					if(i==NB_OF_KEYS) done=true;
					else
					{
						SDLKey value;
						char str[18];
						cout<<"press a key or button..."<<endl;
						value=getKey(str);
						options.set(i,value);
						cout<<value<<":"<<str<<endl;
					}
				}
			}
			gp2d::ShowFPS();
			gp2d::Sync();
		}
		return(0);
	}//end of SettingsMenu

}//end of namespace iteam
