#ifndef _ITEAM_ENGINE_H
#define _ITEAM_ENGINE_H
#include <GP2D/gp2d.h>
using namespace gp;
#include <iostream>
#include "statemachine.h"
#include "intro.h"
#include "menu.h"

namespace game {

	class iteamIntro;
	class iteamMenu;
	
	class iteam : public stateMachine {
		protected:
			static iteam* m_self;
		private:
			iteam();
			GPEngine*       m_engine;
			GPWindow*       m_window;
			GPInputHandler* m_input;

                        GPKeyboardHandler* m_KeyboardHandler;
                        GPInputProcessor* m_InputProcessor;

			iteamIntro* m_intro;
			iteamMenu*  m_menu;

			GPGuiCamera*  m_camGui;
			GPGameCamera* m_camGame;
			GPDirector*   m_camDirector;
			
			bool m_quit;
		public:
			static iteam* instance();
			~iteam();
			
			GPEngine* engine();
			GPWindow* window();
			GPInputHandler* input();
			GPDirector* director();
			GPGuiCamera* camGui();
			GPGameCamera* camGame();
			
			enum STATE {
				BEGIN = 0,END = -1,
				INTRO = 1,
				MENU,
				GAME,
				QUIT,
				FREE_INTRO = 100,
			};
		
			void init();
			void run();
			void quit();
	};

}
#endif
