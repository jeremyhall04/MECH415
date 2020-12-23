#pragma once
#include "../GameObject.h"

class Tile : public GameObject
{
public:
	Tile();
	Tile(float x, float y, double width, double height);
	~Tile();
};