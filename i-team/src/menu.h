#ifndef _ITEAM_MENU_H
#define _ITEAM_MENU_H
#include <GP2D/gp2d.h>
using namespace gp;
#include "engine.h"
#include "statemachine.h"

namespace game {

	class engine;
	
	class iteamMenu : public stateMachine {
		private:
			GPSprite* bg;
			GPTimer* timer;
		public:
			enum STATE {
				BEGIN = 0,END = -1,
				FADE_IN = 1,
				FADE_OUT,
				MENU = 10,
				START,
				OPTIONS,
				QUIT,
			};
			
			iteamMenu();
			~iteamMenu();
			void run();
	};

}
#endif
