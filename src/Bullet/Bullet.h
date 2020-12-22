#pragma once
#include "../Hitbox/Hitbox.h"

class Bullet : public Hitbox
{
public:
	Bullet();
	Bullet(float x, float y, float dir[2], float bulletSpeed, float bulletDamage);
	void initialize(float x, float y, float dir[2], float bulletSpeed, float bulletDamage);
	void update(); //this function will draw and move bullet
	float get_damage();

	float direction[2], speed, R; //bullet hitbox radius
	bool is_alive = false;
private:
	void draw();
	void move();
	double r[3] = { 1, 1, 1 }, g[3] = { 0 }, b[3] = { 0 };
	float damage = 20.0f; //default damage
};