#ifndef _ITEAM_GLOBALS_H
#define _ITEAM_GLOBALS_H
#include "library_h/gp2d.h"

#define IT_PLAYER_SUSI 1
#define IT_PLAYER_FACE_LEFT true
#define IT_PLAYER_FACE_RIGHT false

using namespace gp2d;
#include "players.h"

namespace iteam {
	
	extern vector <iteam::PlayerObj> Player;

	extern gp2d::Sprite Shade1;
	extern gp2d::Sprite Terrain;
	extern gp2d::Sprite GUIBottom;
	extern gp2d::Sprite BGLayer1;
	extern gp2d::Sprite BGLayer2;
	extern gp2d::Sprite Countdown;
	
	extern gp2d::Camera Cam;

	extern gp2d::Font   FNTCounter;
	extern gp2d::Font   FNTNames;
	extern gp2d::Font   FNTGameGUI;

	extern int GameResW;
	extern int GameResH;

	extern int CountdownValue;
	extern int CurPlayer;
	extern bool GameRunning;

}

#endif
