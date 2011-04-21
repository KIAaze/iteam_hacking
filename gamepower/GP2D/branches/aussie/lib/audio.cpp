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

AUDIO FUNCTIONS (version 0.0.1)
By DARKGuy

MODIFICATIONS BY:
No one at the moment.
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/

#include "audio.h"

namespace gp2d {

	// Init the audio system.
	int InitAudio(int rate, Uint16 format, int channels, int buffers) 
	{
		if(Mix_OpenAudio(rate, format, channels, buffers))	// Can we open the audio device with the specified settings?
		{
			PrintDebug("Unable to open audio!");				// Guess not, print an error but keep going. Games can run without sound as it isn't essential.
			return (0);
		} else {
			return (1);													// Yes, we can :D.
		}
	}

	// Load a song.
	Mix_Music *LoadMusic(const char filename[])
	{
		Mix_Music * music;					// Create a pointer to an SDL-mixer music element.
		music = Mix_LoadMUS(filename);	// Load a song.
		return music;							// Return what Mix_LoadMUS() returns.
	}

	// Play a song.
	void PlayMusic(Mix_Music * music, int repeat){
		if(repeat<=0){ repeat=-1; }	// If Repeat <= 0 then set it to -1 (always loop)...
		Mix_PlayMusic(music,repeat);	// Else, play the song with the (times) repeat amount specified.
	}

}
