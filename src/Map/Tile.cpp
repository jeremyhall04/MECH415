#include "../Header.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, double width, double height)
{
	hitbox = new Hitbox(x, y, width, height);
	this->width = width;
	this->height = height;
	x_p = x;
	y_p = y;
}
