#pragma once
#include "Tile.h"
#include "../SceneHandler/SceneHandler.h"

#define N_MAX_TILES 500
//the worst case for the max number of voxels is when each voxel is one apart
//and therefore there are 1/2 * the max number of tiles (50 * 20 = 1000, 1000 / 2 = 500)	

class Player;

class Map 
{

public:
	Map(SceneHandler* SH);

	void drawMap();
	void generate_map();
	void collision_check(Player* player);

	int n_tiles; // number of active tiles
	Tile* tiles[N_MAX_TILES] = { NULL };

protected:
	SceneHandler* SH;
private: 
	std::string map_t[20];
};