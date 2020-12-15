#pragma once

class Tile 
{
public:
	Tile();
	Tile(double x, double y);

	void draw();
	double get_w();
	double get_h();

	double x_p, y_p;

private:
	double width = 25, height = 25;
	double r[3] = { 0 }, g[3] = { 0 }, b[3] = { 0 };
};