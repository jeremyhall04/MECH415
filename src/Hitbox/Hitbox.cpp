#include "Hitbox.h"

Hitbox::Hitbox(float x, float y, double width, double height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void Hitbox::update(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Hitbox::get_left()
{
	return x - ((float)width / 2.0);
}

float Hitbox::get_right()
{
	return x + ((float)width / 2.0);
}

float Hitbox::get_bottom()
{
	return y - ((float)height / 2.0);
}

float Hitbox::get_top()
{
	return y + ((float)height / 2.0);
}