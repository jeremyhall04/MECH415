#include "../Header.h"
#include "../../2D_graphics.h"

Tile::Tile() {}

/// Constructs a tile at given coordinates and size.
Tile::Tile(float x, float y, double width, double height)
{
	this->width = width;
	this->height = height;
	x_p = x;
	y_p = y;
}

Tile::~Tile() {}
