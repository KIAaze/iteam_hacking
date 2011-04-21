/*! \file settings.cpp
\brief settings class

Used to store game settings like language and key configuration.
Contains methods for loading and saving the settings.
On GNU/Linux, settings will be saved to ~/.i-team/settings.txt
On Windows, settings will be saved to ./userdata/settings.txt
*/

/***************************************************************************
 *            settings.cpp
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

#include <fstream>
#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "settings.h"
#include "globals.h"

#define FNLEN	256

namespace iteam {

bool debugOn=true;

//constructor
settings::settings()
{
	strcpy(language,"en");

	KEY_QUIT = SDLK_ESCAPE;
	KEY_FULLSCREEN = SDLK_f;
	KEY_MUSIC = SDLK_m;
	KEY_SWITCH_PLAYER = SDLK_TAB;
	KEY_SWITCH_WEAPON = SDLK_b;
	KEY_FIRE = SDLK_SPACE;
	KEY_CHOOSE_ANGLE = SDLK_v;
	KEY_ADD_PLAYER = SDLK_n;

	KEY_DEC_ANGLE = SDLK_a;
	KEY_INC_ANGLE = SDLK_z;
	KEY_DEC_SPEED = SDLK_q;
	KEY_INC_SPEED = SDLK_s;
	KEY_DEC_FLIGHTTIME = SDLK_w;
	KEY_INC_FLIGHTTIME = SDLK_x;

	//calc velocity+time from angle;
	KEY_CALCVEL = SDLK_e;
	//calc angle+time from velocity;
	KEY_CALCANGLE = SDLK_d;
	//calc velocity+angle from time;
	KEY_CALCVECTOR = SDLK_c;

	KEY_DEC_GRAV = SDLK_r;
	KEY_INC_GRAV = SDLK_t;
	KEY_DEC_GRE_TIME = SDLK_y;
	KEY_INC_GRE_TIME = SDLK_u;
	KEY_DEC_JUMP_POWER = SDLK_i;
	KEY_INC_JUMP_POWER = SDLK_o;
	KEY_DEC_ELASTICITY = SDLK_h;
	KEY_INC_ELASTICITY = SDLK_j;
	KEY_PAUSE = SDLK_PAUSE;

	KEY_TOGGLE_TALK = SDLK_RETURN;

	m_GameType = ITEAMSETTING_MULTIPLAYER;
}

//destructor
settings::~settings()
{}

//save class
int settings::Save(char* filename)
{
	cout<<"SAVING SETTINGS AS BINARY"<<endl;
	ofstream ofs(filename, ios::binary);
	ofs.write((char *)this, sizeof(settings));
	return(0);
}

//load class
int settings::Load(char* filename)
{
	cout<<"LOADING SETTINGS FROM BINARY"<<endl;
	ifstream ifs(filename, ios::binary);

	// if fstream cannot open file
	if ( !ifs )
	{
		cerr << "WARNING: Settings file could not be opened." << endl;
		return(1);
	} // end if

	ifs.read((char *)this, sizeof(settings));
	return(0);
}

int settings::set(int i,SDLKey value)
{
	if(i==0) KEY_QUIT = value;
	if(i==1) KEY_FULLSCREEN = value;
	if(i==2) KEY_MUSIC = value;
	if(i==3) KEY_SWITCH_PLAYER = value;
	if(i==4) KEY_SWITCH_WEAPON = value;
	if(i==5) KEY_FIRE = value;
	if(i==6) KEY_CHOOSE_ANGLE = value;
	if(i==7) KEY_ADD_PLAYER = value;
	if(i==8) KEY_DEC_ANGLE = value;
	if(i==9) KEY_INC_ANGLE = value;
	if(i==10) KEY_DEC_SPEED = value;
	if(i==11) KEY_INC_SPEED = value;
	if(i==12) KEY_DEC_FLIGHTTIME = value;
	if(i==13) KEY_INC_FLIGHTTIME = value;
	if(i==14) KEY_CALCVEL = value;
	if(i==15) KEY_CALCANGLE = value;
	if(i==16) KEY_CALCVECTOR = value;
	if(i==17) KEY_DEC_GRAV = value;
	if(i==18) KEY_INC_GRAV = value;
	if(i==19) KEY_DEC_GRE_TIME = value;
	if(i==20) KEY_INC_GRE_TIME = value;
	if(i==21) KEY_DEC_JUMP_POWER = value;
	if(i==22) KEY_INC_JUMP_POWER = value;
	if(i==23) KEY_DEC_ELASTICITY = value;
	if(i==24) KEY_INC_ELASTICITY = value;
	if(i==25) KEY_PAUSE = value;
	if(i==26) KEY_TOGGLE_TALK = value;

	return(0);
}

//sets var to value if name=settings
//returns 1 if var has been set and else 0
// int settings::set(int &var,char* name,char* setting,int value)
// {
//       if (strncmp( setting, name, FNLEN ) == 0 )
//         {
//           DEBUGCODE { printf("LoadSettings: Setting %s to %d\n",name, value);}
//           var=value;
// 	  return(1);
//         }
// 	return(0);
// }

/* Load the settings from a file... make sure to update SaveSettings if you change
 *  what can be saved/loaded
 */
// void settings::LoadSettings(void)
// {
//
//   char fn[FNLEN];
//   char setting[FNLEN];
//   char value[FNLEN];
//
//   FILE *settingsFile;
//
//   /* set the settings directory/file */
//
// #ifdef _WIN32
//   snprintf( fn, FNLEN-1, "userdata/settings.txt" );
// #else
//   snprintf( fn, FNLEN-1, (const char*)"%s/.i-team/settings.txt", getenv("HOME") );
// #endif
//
//   DEBUGCODE
//   {
//     printf("LoadSettings: settings file is '%s'\n", fn );
//   }
//
//   LOG("LoadSettings: opening settings file\n");
//
//   settingsFile = fopen( fn, "r" );
//
//   if (settingsFile == NULL)
//     {
//       printf("LoadSettings: Settings file does not exist! settings not loaded\n");
//       return;
//     }
//
//   /* we load all the settings here */
//
//   while (!feof(settingsFile))
//     {
//       fscanf( settingsFile, "%[^=]=%[^\n]\n", setting, value );
//
//       DEBUGCODE { printf( "%s = %s\n", setting, value );
//                 }
//
//       if (strncmp( setting, "lang", FNLEN ) == 0 )
//         {
//           DEBUGCODE { printf("LoadSettings: Setting language to %s\n", value);
//                     }
//           strncpy( language, value, FNLEN-1 );
//           language[FNLEN-1]=0;
//         }
//
// 	set(KEY_QUIT,"KEY_QUIT",setting,atoi(value));
// 	set(KEY_FULLSCREEN,"KEY_FULLSCREEN",setting,atoi(value));
// 	set(KEY_MUSIC,"KEY_MUSIC",setting,atoi(value));
// 	set(KEY_SWITCH_PLAYER,"KEY_SWITCH_PLAYER",setting,atoi(value));
// 	set(KEY_SWITCH_WEAPON,"KEY_SWITCH_WEAPON",setting,atoi(value));
// 	set(KEY_FIRE,"KEY_FIRE",setting,atoi(value));
// 	set(KEY_CHOOSE_ANGLE,"KEY_CHOOSE_ANGLE",setting,atoi(value));
// 	set(KEY_ADD_PLAYER,"KEY_ADD_PLAYER",setting,atoi(value));
//
// 	set(KEY_DEC_ANGLE,"KEY_DEC_ANGLE",setting,atoi(value));
// 	set(KEY_INC_ANGLE,"KEY_INC_ANGLE",setting,atoi(value));
// 	set(KEY_DEC_SPEED,"KEY_DEC_SPEED",setting,atoi(value));
// 	set(KEY_INC_SPEED,"KEY_INC_SPEED",setting,atoi(value));
// 	set(KEY_DEC_FLIGHTTIME,"KEY_DEC_FLIGHTTIME",setting,atoi(value));
// 	set(KEY_INC_FLIGHTTIME,"KEY_INC_FLIGHTTIME",setting,atoi(value));
//
// 	//calc velocity+time from angle
// 	set(KEY_CALCVEL,"KEY_CALCVEL",setting,atoi(value));
// 	//calc angle+time from velocity
// 	set(KEY_CALCANGLE,"KEY_CALCANGLE",setting,atoi(value));
// 	//calc velocity+angle from time
// 	set(KEY_CALCVECTOR,"KEY_CALCVECTOR",setting,atoi(value));
//
// 	set(KEY_DEC_GRAV,"KEY_DEC_GRAV",setting,atoi(value));
// 	set(KEY_INC_GRAV,"KEY_INC_GRAV",setting,atoi(value));
// 	set(KEY_DEC_GRE_TIME,"KEY_DEC_GRE_TIME",setting,atoi(value));
// 	set(KEY_INC_GRE_TIME,"KEY_INC_GRE_TIME",setting,atoi(value));
// 	set(KEY_DEC_JUMP_POWER,"KEY_DEC_JUMP_POWER",setting,atoi(value));
// 	set(KEY_INC_JUMP_POWER,"KEY_INC_JUMP_POWER",setting,atoi(value));
// 	set(KEY_DEC_ELASTICITY,"KEY_DEC_ELASTICITY",setting,atoi(value));
// 	set(KEY_INC_ELASTICITY,"KEY_INC_ELASTICITY",setting,atoi(value));
//
//     }
//
//   fclose( settingsFile );
//
// }

/* Save the settings from a file... make sure to update LoadSettings if you change
 *  what can be saved/loaded
 */
// void settings::SaveSettings(void)
// {
//   char fn[FNLEN];
//   FILE *settingsFile;
//
//   /* set the settings directory/file */
//
// #ifdef _WIN32
//   _mkdir( "userdata" );  // just in case try to create save location
//   snprintf( fn, FNLEN-1, "userdata/settings.txt" );
// #else
//   snprintf( fn, FNLEN-1, (const char*)"%s/.i-team", getenv("HOME") );
//   mkdir( fn, 0755 ); // just in case try to create save location
//   snprintf( fn, FNLEN-1, (const char*)"%s/.i-team/settings.txt", getenv("HOME") );
// #endif
//
//   DEBUGCODE
//   {
//     printf("SaveSettings: settings file is '%s'\n", fn );
//   }
//
//   LOG("SaveSettings: opening settings file\n");
//
//   settingsFile = fopen( fn, "w" );
//
//   if (settingsFile == NULL)
//     {
//       printf("SaveSettings: Settings file cannot be created!\n");
//       return;
//     }
//
// 	/* Save all the settings here! */
// 	fprintf( settingsFile, "lang=%s\n", language );
//
// 	fprintf( settingsFile, "KEY_QUIT=%d\n",KEY_QUIT);
// 	fprintf( settingsFile, "KEY_FULLSCREEN=%d\n",KEY_FULLSCREEN);
// 	fprintf( settingsFile, "KEY_MUSIC=%d\n",KEY_MUSIC);
// 	fprintf( settingsFile, "KEY_SWITCH_PLAYER=%d\n",KEY_SWITCH_PLAYER);
// 	fprintf( settingsFile, "KEY_SWITCH_WEAPON=%d\n",KEY_SWITCH_WEAPON);
// 	fprintf( settingsFile, "KEY_FIRE=%d\n",KEY_FIRE);
// 	fprintf( settingsFile, "KEY_CHOOSE_ANGLE=%d\n",KEY_CHOOSE_ANGLE);
// 	fprintf( settingsFile, "KEY_ADD_PLAYER=%d\n",KEY_ADD_PLAYER);
//
// 	fprintf( settingsFile, "KEY_DEC_ANGLE=%d\n",KEY_DEC_ANGLE);
// 	fprintf( settingsFile, "KEY_INC_ANGLE=%d\n",KEY_INC_ANGLE);
// 	fprintf( settingsFile, "KEY_DEC_SPEED=%d\n",KEY_DEC_SPEED);
// 	fprintf( settingsFile, "KEY_INC_SPEED=%d\n",KEY_INC_SPEED);
// 	fprintf( settingsFile, "KEY_DEC_FLIGHTTIME=%d\n",KEY_DEC_FLIGHTTIME);
// 	fprintf( settingsFile, "KEY_INC_FLIGHTTIME=%d\n",KEY_INC_FLIGHTTIME);
//
// 	//calc velocity+time from angle
// 	fprintf( settingsFile, "KEY_CALCVEL=%d\n",KEY_CALCVEL);
// 	//calc angle+time from velocity
// 	fprintf( settingsFile, "KEY_CALCANGLE=%d\n",KEY_CALCANGLE);
// 	//calc velocity+angle from time
// 	fprintf( settingsFile, "KEY_CALCVECTOR=%d\n",KEY_CALCVECTOR);
//
// 	fprintf( settingsFile, "KEY_DEC_GRAV=%d\n",KEY_DEC_GRAV);
// 	fprintf( settingsFile, "KEY_INC_GRAV=%d\n",KEY_INC_GRAV);
// 	fprintf( settingsFile, "KEY_DEC_GRE_TIME=%d\n",KEY_DEC_GRE_TIME);
// 	fprintf( settingsFile, "KEY_INC_GRE_TIME=%d\n",KEY_INC_GRE_TIME);
// 	fprintf( settingsFile, "KEY_DEC_JUMP_POWER=%d\n",KEY_DEC_JUMP_POWER);
// 	fprintf( settingsFile, "KEY_INC_JUMP_POWER=%d\n",KEY_INC_JUMP_POWER);
// 	fprintf( settingsFile, "KEY_DEC_ELASTICITY=%d\n",KEY_DEC_ELASTICITY);
// 	fprintf( settingsFile, "KEY_INC_ELASTICITY=%d\n",KEY_INC_ELASTICITY);
//
//   fclose( settingsFile );
//   LOG("SaveSettings: settings file successfully written\n");
// }

}
