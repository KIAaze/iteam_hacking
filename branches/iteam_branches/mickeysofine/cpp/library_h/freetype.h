/*

	This file is part of GamePower 2D.

    GamePower 2D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 2D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 2D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 2D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  - libsdl1.2-dev
                          - libsdl-image1.2-dev
                          - libsdl-mixer1.2-dev
                        * FreeType development libraries
                          - libfreetype6-dev

FREETYPE FUNCTIONS (version 0.0.1)
By Sven Olsen

MODIFICATIONS BY:

DARKGuy
  - Adapted the code go GP2D's library format plus minor modifications.
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

/*
	A quick and simple opengl font library that uses GNU freetype2, written
	and distributed as part of a tutorial for nehe.gamedev.net.
	Sven Olsen, 2003
*/

#ifndef _GP2D_FREE_H
#define _GP2D_FREE_H

#include <vector>
#include <string>
#include <stdexcept>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

namespace gp2d {

	// Inside Of This Namespace, Give Ourselves The Ability
	// To Write Just "vector" Instead Of "std::vector"
	using std::vector;
	using std::string;

	// This Holds All Of The Information Related To Any
	// FreeType Font That We Want To Create.  
		// MODIF: I just changed the structure name.
	struct Font {
		float h;					// Holds The Height Of The Font.
		GLuint * textures;	// Holds The Texture Id's 
		GLuint list_base;		// Holds The First Display List Id

		// The Init Function Will Create A Font With
		// The Height h From The File fname.
			// MODIF: I just changed the function name.
		void Load(const char * fname, unsigned int h);

		// Free All The Resources Associated With The Font.
			// MODIF: I just changed the function name.
      void Clean();
	};

	// The Flagship Function Of The Library - This Thing Will Print
	// Out Text At Window Coordinates X, Y, Using The Font ft_font.
	// The Current Modelview Matrix Will Also Be Applied To The Text. 
	float Text(const Font &ft_font, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, const char *fmt, ...);

}												// Close The Namespace

#endif
