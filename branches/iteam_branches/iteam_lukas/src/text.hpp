#ifndef _TEXT_H_
#define _TEXT_H_

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "color.hpp"
#include "font.hpp"

class iText {
	
public:

	iFont* font;
	std::string text;
	iColor* color;
	int x;
	int y;
	int width;
	int height;
	GLuint texture;
	SDL_Surface* surface;

	iText();
	iText(iFont* font);
	iText(std::string text);
	iText(std::string text, iColor* color);
	iText(iFont* font, std::string text);
	iText(iFont* font, std::string text, iColor* color);
	void draw();
	void setText(std::string text);
	void setFont(iFont* font);
	void setColor(iColor* color);
	void setStyle(int style);
	void move(int x, int y);
	

private:

	void updateSurface();
	void construct(iFont* font, std::string text, iColor* color);
	
};

#endif
