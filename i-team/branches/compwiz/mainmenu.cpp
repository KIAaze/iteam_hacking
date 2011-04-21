#include "globals.h"

namespace iteam {

	bool flag=false;
	gp2d::Timer  T;

	gp2d::Sprite 	*Title;
	gp2d::Sprite 	*Option;
	gp2d::Sprite 	*Menu;
	gp2d::Font		*gblButtonFont=NULL;

	///////////////////////////////////////////////////////////////////////////////
	//////////////////////////	  INTRO SYSTEM	 ////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	// IntroPre is responsivble for setting up the images etc
	// for the intro state within the statemachine - this will
	// entered only once and immediately transitions to the next
	// state.
	// gameState = ITEAM_INTRO
	void IntroPre() {
		Title = new gp2d::Sprite();
		Title->Load("data/gui/intro.png");
		Title->width[0]=800;
		Title->height[0]=600;
		Title->Move(0,0);
		Title->alpha[0]=0;

		gp2d::SetBackgroundColor(0,0,0,1);

		gameState = ITEAM_INTRO;		// Go to the next state
	}

	// This function will be called repeatedly until an action is
	// taken to transisiton to another state
	// gameState:	the state to go to for cleanup code
	// nextState:	is where the state will go to after clean up code is run
	void Intro()
	{
		if(flag==false){
			if(Title->alpha[0]<1.0f){ Title->alpha[0]+=0.005f; }
			if(Title->alpha[0]>1.0f){ Title->alpha[0]=1.0f; T.Start(); flag=true; }
			Cam.Begin();
				Title->Draw();
			Cam.End();
		} else {
			if(T.GetTicks() > 5000){
				if(Title->alpha[0]>0.0f){ Title->alpha[0]-=0.005f; }
				if(Title->alpha[0]<=0.0f){
					Title->alpha[0]=0;
					gameState = ITEAM_INTROPOST;
					nextState = ITEAM_MAINMENUPRE;	// Go here after clean up
				}
			}

			Cam.Begin();			
				Title->Draw();
			Cam.End();
		}
	}

	// Restores all used memory within the INTRO state
	// then transitions to the state declared in nextState.
	void IntroPost() {
		delete Title;

		gameState = nextState;
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////	MAIN MENU SYSTEM	//////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	/*************	Callback rountines setup for MAINMENU state only **************/
	void MainMenuQuit(Widget *wid) {
		bQuitGame = true;
	}
	// All this does is transisiton to the actual running game
	void MainMenuStartGameKeyUpCallback() {
		gameState = ITEAM_MAINMENUPOST;
		nextState = ITEAM_COUNTDOWNPRE;
	}
	void MainMenuStartGameCallback(Widget *wid) {
		MainMenuStartGameKeyUpCallback();
	}

	void MainMenuOptionsCallback(Widget *wid) {
		gameState = ITEAM_MAINMENUPOST;
		nextState=ITEAM_OPTIONSMENUPRE;
	}

	// MainMenuPre is responsivble for setting up the images etc
	// for the intro state within the statemachine - this will
	// entered only once and immediately transitions to the next
	// state: ITEAM_MAINMENU
	void MainMenuPre() {
		Menu = new gp2d::Sprite();
		Menu->Load("data/gui/menubg.png");
		Menu->width[0]=800;
		Menu->height[0]=600;
		Menu->Move(0,0);
		Menu->alpha[0]=0;
		
		gp2d::SetBackgroundColor(0,0,0,1);

		gblButtonFont = new gp2d::Font();
		gblButtonFont->Load("data/gui/ingame/counter.ttf", 30);

		//Register the spacebar key to get into the actual game
		KeyHandler->registerInputCallback(SDLK_SPACE, MainMenuStartGameKeyUpCallback, GP2D_KEYUP);

		// Create the mainmenu CANVAS on which all the WIDGETS are placed
		can = GuiMan->CreateCanvas(400, 300, 800, 600);
		btn = new ImageButton(130, 380, 60, 60, "Single Player", gblButtonFont, "data/gui/buttons/button_ON_anim","data/explosions/explosion_BOMB_animation_", 13, 30);
		GuiMan->AddToCanvas(can, btn);
		btn = new ImageButton(230, 405, 60, 60, "Multi Player", gblButtonFont, "data/gui/buttons/button_ON_anim","data/explosions/explosion_BOMB_animation_", 13, 30);
		btn->SetReleasedButtonCallback(MainMenuStartGameCallback);
		GuiMan->AddToCanvas(can, btn);
		btn = new ImageButton(330, 420, 60, 60, "Options", gblButtonFont, "data/gui/buttons/button_ON_anim","data/explosions/explosion_BOMB_animation_", 13, 30);
		btn->SetReleasedButtonCallback(MainMenuOptionsCallback);
		GuiMan->AddToCanvas(can, btn);
		btn = new ImageButton(430, 420, 60, 60, "Mods", gblButtonFont, "data/gui/buttons/button_ON_anim","data/explosions/explosion_BOMB_animation_", 13, 30);
		GuiMan->AddToCanvas(can, btn);
		btn = new ImageButton(530, 405, 60, 60, "Credits", gblButtonFont, "data/gui/buttons/button_ON_anim","data/explosions/explosion_BOMB_animation_", 13, 30);
		GuiMan->AddToCanvas(can, btn);
		btn = new ImageButton(630, 380, 60, 60, "Quit Game", gblButtonFont, "data/gui/buttons/button_ON_anim","data/explosions/explosion_BOMB_animation_", 13, 30);
		btn->SetReleasedButtonCallback(MainMenuQuit);
		GuiMan->AddToCanvas(can, btn);

		gameState = ITEAM_MAINMENU;
	}

	// This function will be called repeatedly until an action is
	// taken to transisiton to another state
	// gameState:	the state to go to for cleanup code
	// nextState:	is where the state will go to after clean up code is run
	void MainMenu()
	{
		if(Menu->alpha[0]<1.0f){ Menu->alpha[0]+=0.05f; }
		if(Menu->alpha[0]>1.0f){ Menu->alpha[0]=1.0f; }
		
		Cam.Begin();
			Cam.Move(0,0);
			Menu->Draw();
		Cam.End();		
	}

	// Restores all used memory within the INTRO state
	// then transitions to the state declared in nextState.
	void MainMenuPost() {
		delete Menu;

		delete gblButtonFont;		// Delete the font used for the buttons
		gblButtonFont=NULL;

		//Remove the functionality of the space bar used in main_menu
		KeyHandler->unregisterInputCallback(SDLK_SPACE);
		GuiMan->DeleteCanvas(can);

		gameState = nextState;
	}

	///////////////////////////////////////////////////////////////////////////////
	//////////////////////	OPTIONS MENU SYSTEM	//////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	int buttonToSet=0;
	bool setting = false;
	SDLKey *keyAssignment;	
	string name;

	// This is called when an unregistered key is pressed
	// this allows us to set keys
	void OptionsCallbackForUnknownKey(SDL_Event *e) {
		if (setting==true) {
			setting=false;
			printf("%s changed from %c to %c\n", name.c_str(), *keyAssignment, e->key.keysym.sym);
			*keyAssignment = e->key.keysym.sym;
		}		
	}

	// When any button is clicked this function is called
	// which triggers a wait for a key press
	void OptionsCallbackButtonUp(Widget *widget) {
		if (setting==false) {
			setting=true;
			keyAssignment = ((SetKeyButton*)widget)->btnkey;
			name = widget->WidgetName;
		}
		else {
			printf("Already trying to set a key\n");
		}		
	}

	// OptionsPre is responsivble for setting up the images etc
	// for the intro state within the statemachine - this will
	// entered only once and immediately transitions to the next
	// state: ITEAM_OPTIONSMENU
	void OptionsMenuPre() {
		Option = new gp2d::Sprite();

		Option->Load("data/gui/menubg.png");
		Option->width[0]=800;
		Option->height[0]=600;
		Option->Move(0,0);
		Option->alpha[0]=1;
		
		gp2d::SetBackgroundColor(0,0,0,1);
		gblButtonFont = new gp2d::Font();
		gblButtonFont->Load("data/gui/ingame/eras_bold.TTF", 12);

		// Create the mainmenu canvas
		can = GuiMan->CreateCanvas(400, 300, 800, 600);

		int xpos = 150;
		int width = 150;
		int ypos = 50;
		int height = 20;
		int gap=5;
		int offset = gap+height;

		// TODO: Fullscreen, Pause, Quit
		btn = new SetKeyButton(xpos, ypos, width, height, "Switch Player", gblButtonFont, &options.KEY_SWITCH_PLAYER);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Switch Weapon", gblButtonFont, &options.KEY_SWITCH_WEAPON);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Fire", gblButtonFont, &options.KEY_FIRE);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Choose Angle", gblButtonFont, &options.KEY_CHOOSE_ANGLE);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Add Player", gblButtonFont, &options.KEY_ADD_PLAYER);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Dec Angle", gblButtonFont, &options.KEY_DEC_ANGLE);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Inc Angle", gblButtonFont, &options.KEY_INC_ANGLE);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Dec Speed", gblButtonFont, &options.KEY_DEC_SPEED);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Inc Speed", gblButtonFont, &options.KEY_INC_SPEED);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Dec Flighttime", gblButtonFont, &options.KEY_DEC_FLIGHTTIME);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Inc Flighttime", gblButtonFont, &options.KEY_INC_FLIGHTTIME);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Calc Velocity", gblButtonFont, &options.KEY_CALCVEL);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Calc Angle", gblButtonFont, &options.KEY_CALCANGLE);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Calc Vector", gblButtonFont, &options.KEY_CALCVECTOR);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Dec Gravity", gblButtonFont, &options.KEY_DEC_GRAV);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Inc Gravity", gblButtonFont, &options.KEY_INC_GRAV);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Dec Gre Time", gblButtonFont, &options.KEY_DEC_GRE_TIME);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Inc Gre Time", gblButtonFont, &options.KEY_INC_GRE_TIME);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Dec Jump Power", gblButtonFont, &options.KEY_DEC_JUMP_POWER);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Inc Jump Power", gblButtonFont, &options.KEY_INC_JUMP_POWER);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Dec Elasticity", gblButtonFont, &options.KEY_DEC_ELASTICITY);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);
		btn = new SetKeyButton(xpos, ypos+=offset, width, height, "Inc Elasticity", gblButtonFont, &options.KEY_INC_ELASTICITY);
		btn->SetReleasedButtonCallback(OptionsCallbackButtonUp);
		GuiMan->AddToCanvas(can, btn);

		KeyHandler->UnregisteredKeyUpCallback = OptionsCallbackForUnknownKey;

		gameState = ITEAM_OPTIONSMENU;
	}

	// This function will be called repeatedly until an action is
	// taken to transisiton to another state
	// gameState:	the state to go to for cleanup code
	// nextState:	is where the state will go to after clean up code is run
	void OptionsMenu()
	{
		Cam.Begin();
			Cam.Move(0,0);
			Option->Draw();
		Cam.End();		
	}

	// Restores all used memory within the OPTIONS state
	// then transitions to the state declared in nextState.
	void OptionsMenuPost() {
		printf("Post options\n");

		// Clean up all code here
		delete Option;
		delete gblButtonFont;
		gblButtonFont = NULL;
		GuiMan->DeleteCanvas(can);
		KeyHandler->UnregisteredKeyUpCallback = NULL;

		gameState = nextState;
	}

}
