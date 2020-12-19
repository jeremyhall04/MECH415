#include "GameObject.h"

GameObject::GameObject()
{
	sprite_size = 1;
}

void GameObject::draw()
{
	double x1[3];
	double y1[3];
	//Top triangle
	x1[0] = x_p - width / 2.0;
	y1[0] = y_p - height / 2.0;
	x1[1] = x_p + width / 2.0;
	y1[1] = y_p + height / 2.0;
	x1[2] = x_p - width / 2.0;
	y1[2] = y_p + height / 2.0;
	triangle(x1, y1, r, g, b);
	//Bottom triangle
	x1[0] = x_p - width / 2.0;
	y1[0] = y_p - height / 2.0;
	x1[1] = x_p + width / 2.0;
	y1[1] = y_p + height / 2.0;
	x1[2] = x_p + width / 2.0;
	y1[2] = y_p - height / 2.0;
	triangle(x1, y1, r, g, b);
}