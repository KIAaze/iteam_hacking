#ifndef _SPRITEMAP_H_
#define _SPRITEMAP_H_

#include "globals.h"
using namespace iteam;

int GetUnusedMapNumber(map <int, Sprite*> &a_map);

int Add(SpriteMap &a_map, Sprite* obj);
int Remove(SpriteMap &a_map, SpriteMap::iterator i);

int ProcessAll(SpriteMap &a_map);

int ClearSpriteMap(SpriteMap &a_map);

bool CheckKey(SpriteMap &a_map, int key);

#endif
