#include "GameObject.h"

GameObject::GameObject()
{
	sprite_size = 1;
	R = 50.0f;
}

void GameObject::draw()
{
	double x1[3];
	double y1[3];
	//Top triangle
	x1[0] = x_p - width / 2;
	y1[0] = y_p - height / 2;
	x1[1] = x_p + width / 2;
	y1[1] = y_p + height / 2;
	x1[2] = x_p - width / 2;
	y1[2] = y_p + height / 2;
	triangle(x1, y1, r, g, b);
	//Bottom triangle
	x1[0] = x_p - width / 2;
	y1[0] = y_p - height / 2;
	x1[1] = x_p + width / 2;
	y1[1] = y_p + height / 2;
	x1[2] = x_p + width / 2;
	y1[2] = y_p - height / 2;
	triangle(x1, y1, r, g, b);
	draw_sprite(sprite_id, x_p, y_p, theta, sprite_size);
	draw_healthbar();
}

void GameObject::draw_healthbar()
{
	double x1[3];
	double y1[3];
	double length = 2 * width;
	//Top triangle
	x1[0] = x_p - width;
	y1[0] = y_p + height / 2 + 10;
	x1[1] = x1[0] + length * (health / maxHealth);
	y1[1] = y1[0] + 5;
	x1[2] = x1[0];
	y1[2] = y1[1];
	triangle(x1, y1, r, g, b);
	//Bottom triangle
	x1[0] = x_p - width;
	y1[0] = y_p + height / 2 + 10;
	x1[1] = x1[0] + length * (health / maxHealth);
	y1[1] = y1[0] + 5;
	x1[2] = x1[1];
	y1[2] = y1[0];
	triangle(x1, y1, r, g, b);
	std::string str = std::to_string((int)health);
	char txt[11];
	strcpy_s(txt, str.c_str());
	text(txt, x_p - (width), y_p + height / 2 + 40, 0.5);
}