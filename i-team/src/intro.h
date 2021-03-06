#ifndef _ITEAM_INTRO_H
#define _ITEAM_INTRO_H
#include <GP2D/gp2d.h>
using namespace gp;
#include "engine.h"

namespace game {

	class engine;
	
	class iteamIntro : public stateMachine {
		private:
			GPSprite* splash;
			GPTimer* timer;
		public:
			enum STATE {
				BEGIN = 0,END = -1,
				FADE_IN = 1,
				WAIT,
				FADE_OUT,
			};
			
			iteamIntro();
			~iteamIntro();
			void run();
	};

}
#endif
