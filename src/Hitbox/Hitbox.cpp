#include "Hitbox.h"
#include <cmath>

Hitbox::Hitbox()
{
	x_p = y_p = 0.0;
	width = height = 0.0;
}

Hitbox::Hitbox(float x, float y, double width, double height)
{
	this->x_p = x;
	this->y_p = y;
	this->width = width;
	this->height = height;
}

void Hitbox::update(float x, float y)
{
	this->x_p = x;
	this->y_p = y;
}

float Hitbox::get_left()
{
	return x_p - (float)(width / 2.0);
}

float Hitbox::get_right()
{
	return x_p + (float)(width / 2.0);
}

float Hitbox::get_bottom()
{
	return y_p - (float)(height / 2.0);
}

float Hitbox::get_top()
{
	return y_p + (float)(height / 2.0);
}

bool Hitbox::collision_test(float x, float y, float radius)
{
	bool will_collide = false;
	bool coll1 = false;
	bool coll2 = false;
	bool coll3 = false;
	bool coll4 = false;
	if (x + radius >= get_left() &&
		x - radius <= get_right() &&
		y + radius >= get_bottom() &&
		y - radius <= get_top())
	{
		will_collide = true;
	}
	return will_collide;
}

bool Hitbox::collision_test(Hitbox* hb)
{
	bool will_collide = false;
	if (hb->get_right() >= get_left() &&
		hb->get_left() <= get_right() &&
		hb->get_top() >= get_bottom() &&
		hb->get_bottom() <= get_top())
	{
		will_collide = true;
	}
	return will_collide;
}
