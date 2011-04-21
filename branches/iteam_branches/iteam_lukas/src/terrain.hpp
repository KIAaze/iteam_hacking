#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "collisions.hpp"
#include "sprite.hpp"
#include "player.hpp"

class iTerrain {
	
public:

	iCollisions* collisions;
	iSprite* sprite;

	iTerrain();
	iTerrain(std::string filename);
	~iTerrain();
	void draw();
	void addExplosion(int x, int y, int radius); // (x, y) = center
	void placeOnTerrain(iPlayer* player); // only affects Y values
	/**
	 *  If, for example, a player wants to walk up a hill, you could
	 *  move it left or right and determine the Y location to place
	 *  the player on the hill.  As the title describes, this checks for
	 *  open areas above the current location that are usable.
	 */
	int getTerrainHeightAbove(iPlayer* player);
	/**
	 *  Like the above but it works in the opposite direction.
	 */
	int getTerrainHeightBelow(iPlayer* player);

private:

	void construct(std::string filename);

};

#endif

