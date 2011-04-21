#include "primitives.h"
#include "globals.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <cmath>
#include <iostream>
#include <stdlib.h>

using namespace std;

//------------------------------------------
//added by KIAaze
//Those primitives should soon be available in SDL gfx hopefully. ;)
//We really should use SDL gfx as much as possible. They have some crazy optimized code!
//Things could also be improved so that we can draw where alpha=0 and not where alpha!=0...
//Put primitives into GP2D?
//Is what I call "add" = blending? (can't "add" to alpha=0 pixels :/ )

int Draw_hlineColor ( SDL_Surface * dest, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color, bool add, bool visible_only ) {
//if(x2<x1)exit(101);
//	cout<<"---------------->[Draw_hlineColor] called"<<endl;
	int i;
	int width;
	Uint8  r,g,b,a;
	width = ( int ) fabs ( ( float ) x2 - ( float ) x1 );
//	cout<<"width="<<width<<endl;
	for ( i=0; i < width; i++ )   {
		GetPixelRGBA ( dest,x1+i,y,r,g,b,a );
		if ( !visible_only || a>0 ) {
			SetPixelColor ( dest,x1+i,y,color,add );
		}
	}
}

void Draw_hlineRGBA ( SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2, Uint32 color, bool add, bool visible_only )  {
	Draw_hlineColor ( dest, y, x1, x2, color, add, visible_only );
}

//stolen from SDL_gfxPrimitives.c v2.016
/* ----- Filled Circle */

/* Note: Based on algorithm from sge library with multiple-hline draw removal */

/* and other speedup changes. */

int Draw_filledCircleColor ( SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 r, Uint32 color, bool add, bool visible_only ) {
	Sint16 left, right, top, bottom;
	int result;
	Sint16 x1, y1, x2, y2;
	Sint16 cx = 0;
	Sint16 cy = r;
	Sint16 ocx = ( Sint16 ) 0xffff;
	Sint16 ocy = ( Sint16 ) 0xffff;
	Sint16 df = 1 - r;
	Sint16 d_e = 3;
	Sint16 d_se = -2 * r + 5;
	Sint16 xpcx, xmcx, xpcy, xmcy;
	Sint16 ypcy, ymcy, ypcx, ymcx;

	/*
	 * Sanity check radius
	 */
	if ( r < 0 ) {
		return ( -1 );
	}

	/*
	 * Special case for r=0 - draw a point
	 */
	if ( r == 0 ) {
		return ( pixelColor ( dst, x, y, color ) );
	}

	/*
	 * Get clipping boundary
	 */
	left = dst->clip_rect.x;
	right = dst->clip_rect.x + dst->clip_rect.w - 1;
	top = dst->clip_rect.y;
	bottom = dst->clip_rect.y + dst->clip_rect.h - 1;

	/*
	 * Test if bounding box of circle is visible
	 */
	x1 = x - r;
	x2 = x + r;
	y1 = y - r;
	y2 = y + r;
	if ( ( x1<left ) && ( x2<left ) ) {
		return ( 0 );
	}
	if ( ( x1>right ) && ( x2>right ) ) {
		return ( 0 );
	}
	if ( ( y1<top ) && ( y2<top ) ) {
		return ( 0 );
	}
	if ( ( y1>bottom ) && ( y2>bottom ) ) {
		return ( 0 );
	}

	/*
	 * Draw
	 */
	result = 0;
	do {
		xpcx = x + cx;
		xmcx = x - cx;
		xpcy = x + cy;
		xmcy = x - cy;
		if ( ocy != cy ) {
			if ( cy > 0 ) {
				ypcy = y + cy;
				ymcy = y - cy;
				result |= Draw_hlineColor ( dst, xmcx, xpcx, ypcy, color, add, visible_only );
				result |= Draw_hlineColor ( dst, xmcx, xpcx, ymcy, color, add, visible_only );
			}
			else {
				result |= Draw_hlineColor ( dst, xmcx, xpcx, y, color, add, visible_only );
			}
			ocy = cy;
		}
		if ( ocx != cx ) {
			if ( cx != cy ) {
				if ( cx > 0 ) {
					ypcx = y + cx;
					ymcx = y - cx;
					result |= Draw_hlineColor ( dst, xmcy, xpcy, ymcx, color, add, visible_only );
					result |= Draw_hlineColor ( dst, xmcy, xpcy, ypcx, color, add, visible_only );
				}
				else {
					result |= Draw_hlineColor ( dst, xmcy, xpcy, y, color, add, visible_only );
				}
			}
			ocx = cx;
		}
		/*
		 * Update
		 */
		if ( df < 0 ) {
			df += d_e;
			d_e += 2;
			d_se += 2;
		}
		else {
			df += d_se;
			d_e += 2;
			d_se += 4;
			cy--;
		}
		cx++;
	}
	while ( cx <= cy );

	return ( result );
}

int Draw_filledCircleRGBA ( SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool add, bool visible_only ) {
	return ( Draw_filledCircleColor ( dst,x,y,rad, ( ( Uint32 ) r << 24 ) | ( ( Uint32 ) g << 16 ) | ( ( Uint32 ) b << 8 ) | ( Uint32 ) a ,add,visible_only ) );
}

//------------------------------------------

//Functions by Mickeysofine
void hlineAlpha ( SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2 )  {
	int i;
	int width;
	Uint8  r,g,b,a;
	width = ( int ) fabs ( x2 -  x1 );
	for ( i=0; i < width; i++ )   {
		GetPixelRGBA ( dest,x1+i,y,r,g,b,a );
		if ( a>0 ) SetPixelColor ( dest,x1+i,y,0x00000000 );//sets the exact value of the pixel
	}
}

void hlineHalo ( SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2 )  {
	int i;
	int width;
	Uint8  r,g,b,a;
	width = ( int ) fabs ( x2 -  x1 );
	for ( i=0; i < width; i++ )   {
		GetPixelRGBA ( dest,x1+i,y,r,g,b,a );
		if ( a>0 ) pixelRGBA ( dest,x1+i,y,0,0,0,128 );//puts a pixel with the given rgba over the current pixel
	}
}

void DrawCircleFilled ( GLfloat x_off, GLfloat y_off, int Radius, SDL_Surface *dest, Uint32 color )    {

	int i,length;
	Uint32 x2, y2;

	for ( i=0; i < 2 * Radius; i++ )  {

		if ( ( y_off - Radius + i ) >= 0 && ( y_off - Radius + i ) < dest->h )   {
			//Note from KIAaze: Are you sure about this formula?
			//2*R*sqrt(cos(PI/2*(i-R)/R))?? O.o
			//Where the hell does it come from? Why not simply:
			//2*sqrt(R^2-(R-i)^2)=2*R*sqrt(1-((R-i)/R)^2) where R=Radius
			//(Pythagoras)
			length = ( int ) ( sqrt ( cos ( 0.5f * M_PI * ( i - Radius ) / Radius ) ) * Radius * 2 );


			x2 = ( Uint32 ) x_off - ( length / 2 );
			y2 = ( Uint32 ) ( y_off - Radius + i );

			if ( x2 < 0 )  {
				length += x2;
				x2 = 0;
			}

			if ( x2 + length > dest->w )   {

				length -= ( x2 + length ) - dest->w;
			}
			hlineAlpha ( dest, y2, x2 , x2 + length );
		}

	}


}

void DrawCircleHalo ( GLfloat x_off, GLfloat y_off, int Radius, SDL_Surface *dest, Uint32 color )    {

	int i, length;
	Uint32 x2, y2;

	for ( i=0; i < 2 * Radius; i++ )  {

		if ( ( y_off - Radius + i ) >= 0 && ( y_off - Radius + i ) < dest->h )   {
			length = ( int ) ( sqrt ( cos ( 0.5f * M_PI * ( i - Radius ) / Radius ) ) * Radius * 2 );


			x2 = ( Uint32 ) x_off - ( length / 2 );
			y2 = ( Uint32 ) ( y_off - Radius + i );

			if ( x2 < 0 )  {
				length += x2;
				x2 = 0;
			}

			if ( x2 + length > dest->w )   {

				length -= ( x2 + length ) - dest->w;
			}
			hlineHalo ( dest, y2, x2 , x2 + length );
		}

	}


}
