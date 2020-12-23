#include "../Header.h"
#include "../../2D_graphics.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, double width, double height)
{
	this->width = width;
	this->height = height;
	x_p = x;
	y_p = y;
	r[0] = r[1] = r[2] = 0.65;
	g[0] = g[1] = g[2] = 0.27;
	b[0] = b[1] = b[2] = 0.07;
}
