#include "globals.h"

namespace iteam {

	void Intro()
	{
		bool flag;
		gp2d::Timer  T;
		gp2d::Sprite Title;
		Title.Load("data/gui/intro.png");
		Title.width[0]=800;
		Title.height[0]=600;
		Title.Move(0,0);
		Title.alpha[0]=0;
		
		gp2d::SetBackgroundColor(0,0,0,1);
		while(1){
			gp2d::Cls();
			gp2d::CatchEvents();
			if(gp2d::KeyPressed(SDLK_ESCAPE)){ break; }
			if(gp2d::KeyPressed(SDLK_f)){ ToggleFullscreen(); }
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

	void MainMenu()
	{
		gp2d::Sprite Menu;
		Menu.Load("data/gui/menu.png");
		Menu.width[0]=800;
		Menu.height[0]=600;
		Menu.Move(0,0);
		Menu.alpha[0]=0;
		
		gp2d::SetBackgroundColor(0,0,0,1);
		while(1){
			gp2d::Cls();
			gp2d::CatchEvents();
			if(gp2d::KeyPressed(SDLK_SPACE)){ break; }
			if(gp2d::KeyPressed(SDLK_f)){ ToggleFullscreen(); }
			if(gp2d::EventResizeWindow()){ ResizeWindow(true,0,0,true); }
			
			if(Menu.alpha[0]<1.0f){ Menu.alpha[0]+=0.05f; }
			if(Menu.alpha[0]>1.0f){ Menu.alpha[0]=1.0f; }
			
			Cam.Begin();
				Cam.Move(0,0);
				Menu.Draw();
				Text(FNTGameGUI, 10,10, 0,1,1,1, 1,1,1, "Press SPACE key to start");
			Cam.End();
				
			gp2d::ShowFPS();
			gp2d::Sync();			
		}
	}

}
