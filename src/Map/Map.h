#pragma once
#include "Tile.h"

class Map 
{

public:

	Map(double W, double H);
	
	void drawMap();
	void drawMap2();
	void setMap();

private: 
	Tile t[1000];
	int n_tiles;
	std::string map_t[20];
	float screenW, screenH;
};