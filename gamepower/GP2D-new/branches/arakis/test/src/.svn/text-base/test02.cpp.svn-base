#include <string>
#include <iostream>
#include <SDL/SDL.h>
using namespace std;

bool quit = false;
int x=0;
int y=0;
int playerx=0;
int playery=0;

void drawpixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel)
  {
    case 1: // 8-bpp
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
    case 2: // 15-bpp or 16-bpp
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
    case 3: // 24-bpp mode, usually not used
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
          bufp[0] = color;
          bufp[1] = color >> 8;
          bufp[2] = color >> 16;
        } else {
          bufp[2] = color;
          bufp[1] = color >> 8;
          bufp[0] = color >> 16;
        }
      }
      break;
    case 4: // 32-bpp
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
  }
} 

void drawplayer(SDL_Surface *screen)
{
	for(int xx=0;xx<20;xx++){
		for(int yy=0;yy<20;yy++){
			drawpixel(screen,playerx+xx,playery+yy,255,255,255);
		}
	}
}

int main (int argc, char*argv[])
{
	SDL_Surface *screen;

	if(SDL_Init(SDL_INIT_VIDEO) < 0 ){ return 1; }
	if(!(screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE))){	SDL_Quit();	return 1; }

    while(!quit) {
    	SDL_FillRect(screen,NULL,0x000000);
    
		SDL_PumpEvents();
		Uint8 *keystate = SDL_GetKeyState(NULL);
		if(keystate[SDLK_ESCAPE]){	quit = true; }

		x=0;
		y=0;
		if(keystate[SDLK_UP]){ y=-1; }
		if(keystate[SDLK_DOWN]){ y=1; }
		if(keystate[SDLK_LEFT]){ x=-1; }
		if(keystate[SDLK_RIGHT]){ x=1; }

		if(keystate[SDLK_w]){ y=-1; }
		if(keystate[SDLK_s]){ y=1; }
		if(keystate[SDLK_a]){ x=-1; }
		if(keystate[SDLK_d]){ x=1; }
		
		playerx = playerx + x;
		playery = playery + y;
		
		drawplayer(screen);
		
		SDL_Flip(screen);
		SDL_Delay(1);
    }
     
   return(1);
}
