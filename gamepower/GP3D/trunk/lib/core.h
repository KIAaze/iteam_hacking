/*

	This file is part of GamePower 3D.

    GamePower 3D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 3D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 3D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 3D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  (libsdl1.2-dev, libsdl-image1.2-dev)

CORE HEADER FILE (version 0.0.3)
BY DARKGUY

MODIFICATIONS BY:
No one at the moment.
===================================================================================
This is the header for the core functions.
===================================================================================
CHANGELOG:

0.0.3:
-> Full code rewrite. Too many changes to list, but everything was moved to
	a namespace, there are new functions and some variables were taken out.

0.0.1:
-> First code release, basic video/system handling and created a header file for
   basic primitive handling.
===================================================================================
*/

#ifndef _GP3D_CORE_H
#define _GP3D_CORE_H

namespace gp {
	extern SDL_Event Event;
	extern Uint8 *Keystate;
	class Camera;

	void SetDebug(bool);
	void PrintDebug(char *text);
	void PrintDebug(char *text, char *text2);

	int Init();
	void Cls();
	void Sync();
	void ShowFPS();
	int SetVideoMode(int,int,int,bool,bool);
	void ResizeWindow(bool, int, int, Camera);

	void SetBackgroundColor(float,float,float,float);
	void ToggleFullscreen();
	void EnableCulling();
	void DisableCulling();
	void SwapCullingMode(int);
	void EnableLighting();
	void DisableLighting();
	void EnableTexturing();
	void DisableTexturing();
	void EnableDepth();
	void DisableDepth();
	void RotateTextureMatrix(float);
	GLuint LoadTexture(const char[]);

	void CatchEvents();
	int KeyPressed(int);

}

#endif
