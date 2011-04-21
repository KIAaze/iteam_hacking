#include "input.h"
using namespace std;
using namespace gp2d;

namespace game {

void introAction::keyDown(GP2DKeyEvent& event) {
	if (event.getKey() == GP2DKeyEvent::GP2D_KEY_ESCAPE) {
		iteam* engine = iteam::instance();
		engine->quit();
	}
}

void introAction::keyUp(GP2DKeyEvent& event) {}

}
