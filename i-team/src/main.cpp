#include <GP2D/gp2d.h>
#include "engine.h"

using namespace std;
using namespace gp;
using namespace game;

int main (int argc, char*argv[])
{
	iteam* engine = iteam::instance();
	engine->init();
	engine->run();
	return EXIT_SUCCESS;
}
