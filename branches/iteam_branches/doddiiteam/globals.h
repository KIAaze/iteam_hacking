#ifndef _ITEAM_GLOBALS_H
#define _ITEAM_GLOBALS_H

#include <gp2d.h>

#define IT_PLAYER_SUSI 1
#define IT_PLAYER_FACE_LEFT true
#define IT_PLAYER_FACE_RIGHT false

#define GRAVITY				400.0f
	
#define 	TITLE_SCREEN				0
#define 	PRE_RUN 						1
#define 	RUNNING						2

extern gp2d::gameTimer	myGameTimer;

//MACROS
#define ITEAM_DEFINE_HASH_TYPE(type, variable)	typedef std::map<std::string, type> variable;
//

#endif
