#include "primitives.h"
#include "globals.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>

using namespace std;

Uint32 scanlines[SCAN_HEIGHT][2];

void hlineAlpha(SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2)  {
	int i;
	int width;
	width = (int)fabs(x2 -  x1);	

	// cout << " Line = " << y - (SCAN_HEIGHT / 2) << " x1 = " << x1 << " x2 = " << x2 << " width = " << width << "\n";
	for(i=0; i < width; i++)   {
		//cout << " Line = " << y << "x = " << x1 + i << "\n";
		gp2d::SetPixelAlpha(dest, x1+ i,  y);
	}


}

void hlineHalo(SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2)  {
	int i;
	int width;
	Uint8  pr, pg, pb, pa2;
	if(x1 < x2)	{
		width = x2 -  x1;
	} else {
		width = x1 -  x2;
	}


	//cout << " Line = " << y - (SCAN_HEIGHT / 2) << " x1 = " << x1 << " x2 = " << x2 << " width = " << width << "\n";
	for(i=0; i < width; i++)   {
		//cout << " Line = " << y << "x = " << x1 + i << "\n";
		SDL_GetRGBA(GetPixel(dest,x1 + i, y),dest->format,&pr,&pg,&pb,&pa2);	// Get the pixel's alpha from the second image.
		if(pa2 > 0)	{
			// gp2d::SetPixelAlpha(dest, x1+ i,  y);
			pixelRGBA( dest, x1 + i, y, 0, 0, 0, 128);
		}
	}


}

void DrawCircleFilled(GLfloat x_off, GLfloat y_off, int Radius, SDL_Surface *dest, Uint32 color)    {
        
        int i,length;
        Uint32 x2, y2;

        for(i=0; i < 2 * Radius; i++)  {
		
            if((y_off - Radius + i) >= 0 && (y_off - Radius + i) < dest->h)   {
		length = (int)(sqrt(cos(0.5f * M_PI * (i - Radius) / Radius)) * Radius * 2);

                
                x2 = (Uint32) x_off - (length / 2);
                y2 = (Uint32) (y_off - Radius + i);

                if(x2 < 0)  {
                    length += x2;
                    x2 = 0;
                }

                if(x2 + length > dest->w)   {

                    length -= (x2 + length) - dest->w;
                }
                hlineAlpha( dest, y2, x2 , x2 + length);
            }
	    
        }


}

void DrawCircleHalo(GLfloat x_off, GLfloat y_off, int Radius, SDL_Surface *dest, Uint32 color)    {
        
        int i, length;
        Uint32 x2, y2;

        for(i=0; i < 2 * Radius; i++)  {
		
            if((y_off - Radius + i) >= 0 && (y_off - Radius + i) < dest->h)   {
		length = (int)(sqrt(cos(0.5f * M_PI * (i - Radius) / Radius)) * Radius * 2);

                
                x2 = (Uint32) x_off - (length / 2);
                y2 = (Uint32) (y_off - Radius + i);

                if(x2 < 0)  {
                    length += x2;
                    x2 = 0;
                }

                if(x2 + length > dest->w)   {

                    length -= (x2 + length) - dest->w;
                }
                hlineHalo( dest, y2, x2 , x2 + length);
            }
	    
        }


}
