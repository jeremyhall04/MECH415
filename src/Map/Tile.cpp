#include "../Header.h"

Tile::Tile()
{
}

Tile::Tile(double x, double y) 
{
	x_p = x;
	y_p = y;
}

void Tile::draw() 
{
	double x1[3];
	double y1[3];
	//Top triangle
	x1[0] = x_p;
	y1[0] = y_p;
	x1[1] = x_p;
	y1[1] = y_p + height;
	x1[2] = x_p + width;
	y1[2] = y_p + height;
	triangle(x1, y1, r, g, b);
	//Bottom triangle
	x1[1] = x_p + width;
	y1[1] = y_p;
	triangle(x1, y1, r, g, b);
}

double Tile::get_w()
{
	return width;
}

double Tile::get_h()
{
	return height;
}
