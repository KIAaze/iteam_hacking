#include "globals.h"

namespace iteam {

	bool flag=false;
	gp2d::Timer  T;
	gp2d::Sprite Title;

	gp2d::Sprite Menu;

	void PreIntro() {
		Title.Load("data/gui/intro.png");
		Title.width[0]=800;
		Title.height[0]=600;
		Title.Move(0,0);
		Title.alpha[0]=0;
		
		gp2d::SetBackgroundColor(0,0,0,1);
		gameState = ITEAM_INTRO;		// Go to the next state
	}

	void Intro()
	{
		if(flag==false){
			if(Title.alpha[0]<1.0f){ Title.alpha[0]+=0.005f; }
			if(Title.alpha[0]>1.0f){ Title.alpha[0]=1.0f; T.Start(); flag=true; }
			Cam.Begin();
				Title.Draw();
			Cam.End();
		} else {
			if(T.GetTicks() > 5000){
				if(Title.alpha[0]>0.0f){ Title.alpha[0]-=0.005f; }
				if(Title.alpha[0]<=0.0f){ Title.alpha[0]=0; gameState = ITEAM_PREMAINMENU; }
			}
			Cam.Begin();			
				Title.Draw();
			Cam.End();
		}
//		gp2d::ShowFPS();
//		gp2d::Sync();			
	}

	// All this does is transisiton to the actual running game
	void MainMenuSpaceCallback() {
		gameState = ITEAM_PRECOUNTDOWN;
	}

	void PreMainMenu() {
		Menu.Load("data/gui/menu.png");
		Menu.width[0]=800;
		Menu.height[0]=600;
		Menu.Move(0,0);
		Menu.alpha[0]=0;
		
		gp2d::SetBackgroundColor(0,0,0,1);

		//Register the spacebar key to get into the actual game
		KeyHandler->registerInputCallback(SDLK_SPACE, MainMenuSpaceCallback, GP2D_KEYUP);		

		gameState = ITEAM_MAINMENU;
	}

	void MainMenu()
	{
		if(Menu.alpha[0]<1.0f){ Menu.alpha[0]+=0.05f; }
		if(Menu.alpha[0]>1.0f){ Menu.alpha[0]=1.0f; }
		
		Cam.Begin();
			Cam.Move(0,0);
			Menu.Draw();
		Cam.End();			
	}
}
