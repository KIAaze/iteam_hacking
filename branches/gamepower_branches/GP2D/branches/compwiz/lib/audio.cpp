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
	int SetAudioChannels(int channels){
		if(Mix_AllocateChannels(channels)){ return(1); } else { return(0); }
	}

	Music::Music() { loop = 1; }
	int Music::Load(const char filename[]) { msong = Mix_LoadMUS(filename);	}
	void Music::SetVolume(int vol){ if(vol > SDL_MIX_MAXVOLUME) { vol = SDL_MIX_MAXVOLUME; } volume = vol; Mix_VolumeMusic(vol); }
	void Music::Play(){ Mix_PlayMusic(msong,loop); }
	void Music::Stop(){ Mix_HaltMusic (); }
	void Music::Rewind() { Mix_RewindMusic (); }
	void Music::Pause() { Mix_RewindMusic (); }
	void Music::Resume() { Mix_ResumeMusic (); }
	Music::~Music() { Mix_HaltMusic (); Mix_FreeMusic (msong); }

	Sound::Sound() { loop = 0; }
	int Sound::Load(const char filename[]) { msound = Mix_LoadWAV(filename);	}
	void Sound::SetVolume(int vol){ if(vol > 128) { vol = 128; } volume = vol; Mix_VolumeChunk(msound,vol); }
	void Sound::Play(){ Mix_PlayChannel(channel,msound,loop); }
	void Sound::Stop(){ Mix_HaltChannel(channel); }
	Sound::~Sound() { Mix_HaltChannel(channel); Mix_FreeChunk(msound); }
	
}
