#pragma once
#include <string>
#include "Tile.h"
#include "../SceneHandler/SceneHandler.h"

#define N_MAX_TILES 1000
#define PI 3.1415
	
class Player;

class Map 
{

public:
	Map();

	float get_screen_width();
	float get_screen_height();

	void drawMap();
	void generate_map();
	void collision_check(Player* player);

	int n_tiles; // number of active tiles
	Tile* tiles[N_MAX_TILES] = { NULL };

protected:
	float screenWidth, screenHeight;
private: 
	void get_screen_size();
};