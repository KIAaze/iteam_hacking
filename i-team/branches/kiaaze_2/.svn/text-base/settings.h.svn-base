/*! \file settings.h
\brief settings class

Used to store game settings like language and key configuration.
Contains methods for loading and saving the settings.
On GNU/Linux, settings will be saved to ~/.i-team/settings.txt
On Windows, settings will be saved to ./userdata/settings.txt
*/

/***************************************************************************
 *            settings.h
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string.h>
#include <SDL/SDL.h>

class settings
  {
  public:
	char language[256];

	SDLKey KEY_QUIT;
	SDLKey KEY_FULLSCREEN;
	SDLKey KEY_MUSIC;
	SDLKey KEY_SWITCH_PLAYER;
	SDLKey KEY_SWITCH_WEAPON;
	SDLKey KEY_FIRE;
	SDLKey KEY_CHOOSE_ANGLE;
	SDLKey KEY_ADD_PLAYER;

	SDLKey KEY_DEC_ANGLE;
	SDLKey KEY_INC_ANGLE;
	SDLKey KEY_DEC_SPEED;
	SDLKey KEY_INC_SPEED;
	SDLKey KEY_DEC_FLIGHTTIME;
	SDLKey KEY_INC_FLIGHTTIME;

	//calc velocity+time from angle
	SDLKey KEY_CALCVEL;
	//calc angle+time from velocity
	SDLKey KEY_CALCANGLE;
	//calc velocity+angle from time
	SDLKey KEY_CALCVECTOR;

	SDLKey KEY_DEC_GRAV;
	SDLKey KEY_INC_GRAV;
	SDLKey KEY_DEC_GRE_TIME;
	SDLKey KEY_INC_GRE_TIME;
	SDLKey KEY_DEC_JUMP_POWER;
	SDLKey KEY_INC_JUMP_POWER;
	SDLKey KEY_DEC_ELASTICITY;
	SDLKey KEY_INC_ELASTICITY;
	SDLKey KEY_PAUSE;

  public:
    char* set_language(char* lang)
    {
      strcpy(language,lang);
      return(language);
    };
    char* get_language(void)
    {
      return(language);
    };
    settings();
    ~settings();
    //void SaveSettings(void); /**< save settings as textfile */
    //void LoadSettings(void); /**< load settings from textfile */
    int Save(char* filename); /**< save class as binary */
    int Load(char* filename); /**< load class from binary */
    //int set(int &var,char* name,char* setting,int value);
    int set(int i,SDLKey value);
  };

#endif
