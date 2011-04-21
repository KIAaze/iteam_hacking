#ifndef _FONT_H_
#define _FONT_H_

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class iFont {

public:

	std::string fontName;
	int size;
	TTF_Font* ttf;

	iFont();
	iFont(std::string filename, int size);
	iFont(std::string fontname, std::string filename, int size);
	~iFont();
	void loadFont(std::string filename, std::string fontname, int size);
	void setStyle(int style);

};

#endif
