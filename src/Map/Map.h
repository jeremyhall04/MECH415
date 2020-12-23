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
	~Map();
	void generate_map();
	void drawTiles();
	float get_screen_width();
	float get_screen_height();

	int n_tiles; // number of active tiles
	Tile* tiles[N_MAX_TILES] = { NULL };
protected:
	int map_sprite_id;
	void get_screen_size();
	float screenWidth, screenHeight;
};