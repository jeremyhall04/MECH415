#include "GameObject.h"

GameObject::GameObject()
{
	sprite_size = 1;
	theta = 0;
	for (int i = 0; i < 3; i++)
	{
		r[i] = 1.0;
		g[i] = 1.0;
		b[i] = 1.0;
	}
}

void GameObject::draw()
{
	double d_x, d_y;
	d_x = (double)x_p;
	d_y = (double)y_p;
	double x1[3];
	double y1[3];
	//Top triangle
	x1[0] = d_x - width / 2.0;
	y1[0] = d_y - height / 2.0;
	x1[1] = d_x + width / 2.0;
	y1[1] = d_y + height / 2.0;
	x1[2] = d_x - width / 2.0;
	y1[2] = d_y + height / 2.0;
	triangle(x1, y1, r, g, b);
	//Bottom triangle
	x1[0] = d_x - width / 2.0;
	y1[0] = d_y - height / 2.0;
	x1[1] = d_x + width / 2.0;
	y1[1] = d_y + height / 2.0;
	x1[2] = d_x + width / 2.0;
	y1[2] = d_y - height / 2.0;
	triangle(x1, y1, r, g, b);
}