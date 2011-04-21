#ifndef _PHYSICAL_H_
#define _PHYSICAL_H_

class iPhysical {

public:

	float x;
	float y;
	float xVelocity;
	float yVelocity;
	float xAcceleration;
	float yAcceleration;
	float gravityConstant;
	float terminalVelocity;

	iPhysical();
	iPhysical(int x, int y);
	~iPhysical();
	void stepPhysics(int changeInTicks);
	void translate(int x, int y);
	void move(int x, int y);
	void freeze(); // set velocity and acceleration to zero
	
private:

	void construct(int x, int y);

};

#endif

