#pragma once
#include "../GameObject.h"
#include "../Hitbox/Hitbox.h"

class Tile : public GameObject
{
public:
	Tile();
	Tile(float x, float y, double width, double height);
	double get_width();
	double get_height();

	Hitbox* hitbox;
protected:
	bool is_halftile = false;
};