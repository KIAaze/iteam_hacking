#include <gp2d/gp2d.h>

float gravityConstant;
int pixelToMetersRatio;

class physSolidObject
{
	public:

		physSolidObject()
		{
		}

		~physSolidObject(void)
		{
		}		

	private:

		float massInGrams;
		float xVelocity; // eastern velocity is positive and western velocity is negative
		float yVelocity; // northern velocity is positive
		float xAcceleration;
		float yAcceleration;
		float netVelocity; // only used to cacluate other dynamic attributes;
		float netKineticEnergy;
		float netPotentialEnergy; // will be subtracted from for both x and y velocities and added to during a fall
		
		
};


class physEngine
{
	public:
		
		physEngine(void)
		{
		}

		~physEngine(void)
		{
			// REMOVE ALL physSolidOjbect's!
		}

	private:

		float gravityConstant;
		int pixelToMetersRatio;

};


bool quit = false;
void Quit(void) { quit = true; }

int main(void)
{
	gp2d::GP2DInputHandler* handler;
	handler = new gp2d::GP2DInputHandler();
	gp2d::setDebug(True);
	gp2d::setVideoAPI(GP2D_SDL);
	gp2d::setVideoFlags();
	gp2d::init();
	gp2d::setVideoMode(640,400,32);
	gp2d::setWindowTitle("GP2D - Physics Test");
	handler->registerKeyDown(gp2d::GP2DKeyEvent::GP2D_KEY_ESCAPE, Quit);

	while(!quit)
	{
		physMain();		
	}

	return 0;
}
