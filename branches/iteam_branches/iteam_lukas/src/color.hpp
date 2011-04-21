#ifndef _COLOR_H_
#define _COLOR_H_

#include "SDL/SDL.h"

class iColor {
	
public:

	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	
	iColor(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);
	~iColor();
	SDL_Color getSDLColor();

private:
	
};

#endif
