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

bool Hitbox::collision_test(float x, float y)
{
	bool will_collide = false;
	if (x >= get_left() &&
		x <= get_right() &&
		y >= get_bottom() &&
		y <= get_top())
	{
		will_collide = true;
	}
	return will_collide;
}

bool Hitbox::collision_test(Hitbox* hb)
{
	bool collided = false;
	if (collision_test(hb->get_left(), hb->get_top()) ||
		collision_test(hb->get_left(), hb->get_bottom()) || 
		collision_test(hb->get_right(), hb->get_top()) || 
		collision_test(hb->get_right(), hb->get_bottom()))	// Checking if corners of hb is within this.hb
	{
		collided = true;
	}
	return collided;
}