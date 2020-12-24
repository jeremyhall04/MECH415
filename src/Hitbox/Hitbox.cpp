#include "Hitbox.h"
#include <cmath>

// Default constructor for Hitbox
Hitbox::Hitbox()
{
	x_p = y_p = 0.0;
	width = height = 0.0;
}

/// <summary>
/// Hitbox constructor.
/// 
/// Uses parameters to assign the coordinates of the object as well as the width and height.
/// </summary>
Hitbox::Hitbox(float x, float y, double width, double height)
{
	this->x_p = x;
	this->y_p = y;
	this->width = width;
	this->height = height;
}

/// Returns the coordinate of the left side of the Hitbox
float Hitbox::get_left()
{
	return x_p - (float)(width / 2.0);
}

/// Returns the coordinate of the right side of the Hitbox
float Hitbox::get_right()
{
	return x_p + (float)(width / 2.0);
}

/// Returns the coordinate of the bottom side of the Hitbox
float Hitbox::get_bottom()
{
	return y_p - (float)(height / 2.0);
}

/// Returns the coordinate of the top side of the Hitbox
float Hitbox::get_top()
{
	return y_p + (float)(height / 2.0);
}

double Hitbox::get_width()
{
	return width;
}

double Hitbox::get_height()
{
	return height;
}

/// <summary>
/// Takes a point (x,y) and verifies if it is within the Hitbox boundaries.
/// </summary>
/// <param name="x">x coordinate of point</param>
/// <param name="y">y coordinate of point</param>
/// <returns>Whether the point is interfering with the hitbox</returns>
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

/// <summary>
/// Takes a Hitbox reference and tests if any of its four corners are interfering with the Object's Hitbox
/// </summary>
/// <param name="hb">Hitbox reference to test</param>
/// <returns>Whether the Hitbox reference is interfering</returns>
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