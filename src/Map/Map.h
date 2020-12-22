#pragma once
#include <string>
#include "Tile.h"
#define N_MAX_TILES 1000
#define TILES_X 20
#define TILES_Y 50
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

	int n_tiles; // number of active tiles
	Tile* tiles[N_MAX_TILES] = { NULL };

	int win_height();
	int win_width();
	int tile_res_y();
	int tile_res_x();
protected:
	float screenWidth, screenHeight;
	void get_screen_size();
	int tile_cols, tile_rows;
};