#ifndef _ITEAM_INPUT_H
#define _ITEAM_INPUT_H
#include <GP2D/gp2d.h>
using namespace gp;
#include "engine.h"

namespace game {

	class iteam;
	class introAction : public GPKeyAction {
		public:
			void keyDown(GPKeyEvent& event);
			void keyUp(GPKeyEvent& event);
	};

}
#endif
