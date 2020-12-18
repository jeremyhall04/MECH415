#include "../Header.h"

Bullet::Bullet()
{
	is_alive = true;
}

Bullet::Bullet(float x, float y, float dir[2], float bulletSpeed, float bulletDamage) 
{
	x_p = x;
	y_p = y;
	direction[0] = dir[0];
	direction[1] = dir[1];
	speed = bulletSpeed;
	damage = bulletDamage;
	is_alive = true;
	R = 10.0f;
}

void Bullet::update()
{
	move();
	draw();
}

void Bullet::draw() 
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
}

void Bullet::move() 
{
	if (direction[0] != 0)
	{
		x_p += speed * direction[0];
	}
	if (direction[1] != 0)
	{
		y_p += speed * direction[1];
	}
}

float Bullet::get_damage()
{
	return damage;
}
