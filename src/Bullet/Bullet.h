#pragma once

class Bullet 
{
public:
	Bullet();
	Bullet(float x, float y, float dir[2], float bulletSpeed, float bulletDamage);
	void update(); //this function will draw and move bullet
	void draw();
	void move();
	float get_damage();
	float get_w();

	float x_p, y_p, direction[2], speed, R; //bullet hitbox radius
	bool is_alive = false;
	
	double width = 15, height = 15;
	double r[3] = { 1, 1, 1 }, g[3] = { 0 }, b[3] = { 0 };
	float damage = 20;
};