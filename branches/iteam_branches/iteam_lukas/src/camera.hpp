#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "sprite.hpp"

class iCamera {
	
public:

	int width;
	int height;

	iCamera();
	iCamera(int width, int height);
	~iCamera();
	void translate(int x, int y);
	void lookAt(int x, int y);
	void lookAt(iSprite* sprite);

};

#endif
