/*! \file primitives.h
\brief Contains functions for terrain destruction.
*/

#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H

#include "globals.h"


#define SURFACE_WIDTH 2
// allow for a circle radius of 200 pixels in scanline buffer
#define SCAN_HEIGHT 400

void hlineAlpha ( SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2 );
void hlineHalo ( SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2 );
//Draw empty circle (x_off,y_off,Radius). color is not used yet.
void DrawCircleFilled ( GLfloat x_off, GLfloat y_off, int Radius, SDL_Surface *dest, Uint32 color );
//Draw halo circle (x_off,y_off,Radius). color is not used yet.
void DrawCircleHalo ( GLfloat x_off, GLfloat y_off, int Radius, SDL_Surface *dest, Uint32 color );

//-----------------------------------
//added by KIAaze
int Draw_hlineColor ( SDL_Surface * dest, Sint16 x1, Sint16 x2, Sint16 y, Uint32 color, bool add, bool visible_only );
void Draw_hlineRGBA ( SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2, Uint32 color, bool add, bool visible_only );
int Draw_filledCircleColor ( SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 r, Uint32 color, bool add, bool visible_only );
int Draw_filledCircleRGBA ( SDL_Surface * dst, Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool add, bool visible_only );
//-----------------------------------
#endif
