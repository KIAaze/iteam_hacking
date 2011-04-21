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

	int AudioCalls = 0;
	int AudioMaxChannels = MIX_CHANNELS;
	bool AudioAllocateNewChannels = 0;

	/*
	=================================================================================================================================
	GENERAL AUDIO FUNCTIONS
	=================================================================================================================================
	*/

	void InitAudio ( int rate, Uint16 format, int channels, int buffers ) {
		if ( Mix_OpenAudio ( rate, format, channels, buffers ) !=0 ) {
			PrintDebug ( "SOUND: Can't init the sound system. (Rate:%dHz - Format:%s - Channels:%d - Buffers: %i",rate,format,channels,buffers );
			exit ( 1 );
		}
// get and print the audio format in use
		int num;
		num = Mix_QuerySpec ( &rate, &format, &channels );
		if ( !num ) {
			PrintDebug ( "SOUND: ERROR - Mix_QuerySpec error: ",Mix_GetError() );
			exit ( 1 );
		}
		else {
			char *format_str="Unknown format!";
			switch ( format ) {
				case AUDIO_U8: format_str="U8 (Unsigned 8-bit samples)"; break;
				case AUDIO_S8: format_str="S8 (Signed 8-bit samples)"; break;
				case AUDIO_U16LSB: format_str="U16LSB (Unsigned 16-bit samples, in little-endian byte order)"; break;
				case AUDIO_S16LSB: format_str="S16LSB (Signed 16-bit samples, in little-endian byte order)"; break;
				case AUDIO_U16MSB: format_str="U16MSB (Unsigned 16-bit samples, in big-endian byte order)"; break;
				case AUDIO_S16MSB: format_str="S16MSB (Signed 16-bit samples, in big-endian byte order)"; break;
			}
			PrintDebug ( "SOUND: Sound system opened %i times",num );
			PrintDebug ( "SOUND: Rate=%dHz - Channels=%d - Format=%s", rate, channels, format_str );
			PrintDebug ( "SOUND: Average sound volume is %d (0 min, %i max).",Mix_Volume ( -1,-1 ),MIX_MAX_VOLUME );
			AudioCalls=num;
			AudioMaxChannels=channels;
		}
	}

	void StopAudio() {
		PrintDebug ( "SOUND: Closing sound system %i times",AudioCalls );
		for ( int i=0;i<=AudioCalls;i++ ) {
			Mix_CloseAudio();
			PrintDebug ( "SOUND: Closing Audio system %i times",AudioCalls );
		}
		AudioCalls=0;
	}
	int SetMasterVolume ( int vol ) {
		int newvol;
		if ( vol<0 ) { PrintDebug ( "SOUND: Cannot set master volume to %i because it's less than 0!",vol ); return -1; }
		if ( vol>MIX_MAX_VOLUME ) { PrintDebug ( "SOUND: Cannot set mastervolume to %i because it's greater than %i!",vol,MIX_MAX_VOLUME ); return -1; }
		newvol = Mix_Volume ( -1,vol );
		PrintDebug ( "SOUND: Master sound volume set to %i",newvol );
		return newvol;
	}

	int SetAudioChannels ( int chans ) {
		int newchans;
		newchans = Mix_AllocateChannels ( chans );
		PrintDebug ( "SOUND: %i Sound channels allocated successfully.",newchans );
		return newchans;
	}

	int GetAudioChannels() { return Mix_AllocateChannels ( -1 ); }

	/*
	=================================================================================================================================
	SOUND CLASS
	=================================================================================================================================
	*/

	Sound::Sound() { loop=0; };
	Sound::~Sound() {};

	void Sound::Free() {
		if ( Mix_Playing ( channel ) !=0 ) { Mix_HaltChannel ( channel ); }
		Mix_FreeChunk ( sample );
		sample=NULL;
	}

	bool Sound::LoadWAV ( const char filename_branch[] ) {
		char filename[256];
		sprintf ( filename,"%s/%s",DATA_DIR,filename_branch );

		if ( !FileExists ( filename ) ) { exit ( 1 ); }
		sample=Mix_LoadWAV_RW ( SDL_RWFromFile ( filename, "rb" ), 1 );
		if ( !sample ) { PrintDebug ( "SOUND: ERROR - Mix_LoadWAV_RW: ", Mix_GetError() ); }
		PrintDebug ( "SOUND: '%s' loaded.",filename );
		return true;
	}

	bool Sound::SetChannel ( int chan ) {
		if ( chan<0 ) { PrintDebug ( "SOUND: Cannot set sound channel %i because it's less than zero!",chan ); return false; }
		if ( chan>AudioMaxChannels ) { PrintDebug ( "SOUND: Cannot set sound channel %i because it's greater than the maximum number of sound channels allowed (%i)!",chan,AudioMaxChannels ); return false; }
		channel = chan;
		return true;
	}

	int Sound::GetVolume() {	return Mix_Volume ( channel,-1 ); }
	int Sound::SetVolume ( int vol ) {
		int newvol;
		if ( vol<0 ) { PrintDebug ( "SOUND: Cannot set sound volume to %i because it's less than 0!",vol ); return -1; }
		if ( vol>MIX_MAX_VOLUME ) { PrintDebug ( "SOUND: Cannot set sound volume to %i because it's greater than %i!",vol,MIX_MAX_VOLUME ); return -1; }
		newvol = Mix_Volume ( channel,vol );
		PrintDebug ( "SOUND: Sound volume set to %i",newvol );
		return newvol;
	}

	void Sound::SetLoop ( int l ) { loop=l; }

	bool Sound::Play() {
		if ( Mix_PlayChannel ( -1, sample, loop ) ==-1 ) {
			if ( AudioAllocateNewChannels == true ) {
				if ( SetAudioChannels ( GetAudioChannels() +1 ) ) {
					if ( Mix_PlayChannel ( -1, sample, loop ) ==-1 ) {
						PrintDebug ( "SOUND: <ERROR> Error playing sound (Code 1)-> Mix_PlayChannel: %s",Mix_GetError() );
						return false;
					}
				}
			}
			else {
				PrintDebug ( "SOUND: <ERROR> Error playing sound (Code 2) -> Mix_PlayChannel: %s",Mix_GetError() );
				return false;
			}
		}
		return true;
	}

	/*
	=================================================================================================================================
	MUSIC CLASS
	=================================================================================================================================
	*/

	Music::Music() { loop=0; };
	Music::~Music() {};

	void Music::Free() {
		Mix_FreeMusic ( music );
		music=NULL;
	}

	bool Music::Load ( const char *filename_branch ) {

		char f[256];
		sprintf ( f,"%s/%s",DATA_DIR,filename_branch );

		filename = f;
		if ( !FileExists ( filename ) ) { exit ( 1 ); }
		music=Mix_LoadMUS ( filename );
		if ( !music ) {
			PrintDebug ( "MUSIC: Cannot load '%s'. %s",filename,Mix_GetError() );
			return false;
		}

// TODO: Check if this works correctly?
		char *format;
		switch ( Mix_GetMusicType ( music ) ) {
			case MUS_NONE: format="None"; break;
// case MUS_CMD: format="Command-based"; break;
// case MUS_WAV: format="WAVE/RIFF"; break;
// case MUS_MOD: format="MOD"; break;
// case MUS_MID: format="MIDI"; break;
// case MUS_OGG: format="OGG"; break;
// case MUS_MP3: format="MP3"; break;
			default: format="Unknown"; break;
		}

		PrintDebug ( "MUSIC: '%s' loaded. Format: %s",filename,format );
		return true;
	}

	int Music::GetVolume() { return Mix_VolumeMusic ( -1 ); }
	int Music::SetVolume ( int vol ) {
		int newvol;
		if ( vol<0 ) { PrintDebug ( "MUSIC: Cannot set music volume to %i because it's less than 0!",vol ); return -1; }
		if ( vol>MIX_MAX_VOLUME ) { PrintDebug ( "MUSIC: Cannot set music volume to %i because it's greater than %i!",vol,MIX_MAX_VOLUME ); return -1; }
		newvol = Mix_VolumeMusic ( vol );
		PrintDebug ( "MUSIC: Music volume set to %i",newvol );
		return newvol;
	}

	void Music::SetLoop ( int l ) { loop=l; }

	bool Music::Play() {
		if ( Mix_PlayMusic ( music, loop ) ==-1 ) {
			PrintDebug ( "MUSIC: Error playing music '%s'. Error: %s",filename,Mix_GetError() );
			return false;
		}
		PrintDebug ( "MUSIC: Playing '%s'",filename );
		return true;
	}

	bool Music::Stop(){ return(Mix_HaltMusic ()); }
}
