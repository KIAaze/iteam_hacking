/*! \file primitives.h
\brief Contains functions for terrain destruction.
*/

#ifndef _PRIMITIVES_H
#define _PRIMITIVES_H

#include "globals.h"


#define SURFACE_WIDTH 2
// allow for a circle radius of 200 pixels in scanline buffer
#define SCAN_HEIGHT 400

void hlineAlpha(SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2);
void hlineHalo(SDL_Surface *dest, Uint32 y, Uint32 x1, Uint32 x2);
void DrawCircleFilled(GLfloat x_off, GLfloat y_off, int Radius, SDL_Surface *dest, Uint32 color);
void DrawCircleHalo(GLfloat x_off, GLfloat y_off, int Radius, SDL_Surface *dest, Uint32 color);

#endif
