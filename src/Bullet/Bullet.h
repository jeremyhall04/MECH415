#pragma once
#include "../Hitbox/Hitbox.h"

class Bullet : public Hitbox
{
public:
	Bullet();
	Bullet(float x, float y, float dir[2], float bulletSpeed, float bulletDamage);
	~Bullet();
	void initialize(float x, float y, float dir[2], float bulletSpeed, float bulletDamage);
	void update();
	float get_damage();

	float direction[2], speed, R; // R = bullet hitbox radius
	bool is_alive = false;
private:
	void draw();
	void move();
	double r[3] = { 1, 1, 1 }, g[3] = { 0 }, b[3] = { 0 }; // Bullet color
	float damage = 20.0f; // Default damage
};