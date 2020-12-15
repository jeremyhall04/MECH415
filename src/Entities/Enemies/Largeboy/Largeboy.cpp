#include "Largeboy.h"
//horizontal path enemy, shoots vertically as it moves along path
Largeboy::Largeboy(float x, float y)
{
	x_p = x;
	y_p = y;
	width = 40.0;
	height = 40.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 0.5;
		g[i] = 0.0;
		b[i] = 0.5;
	}
	max_speed = 2;
	maxHealth = 90;
	health = maxHealth;
	fire_rate = 0.030;
	bullet_damage = 25;
	move_dir[0] = 1; //x direction
	move_dir[1] = 0; //y direction
	facing_dir[0] = 0.0f;
	facing_dir[1] = 1.0f;
	path[0] = 100.0f;
	path[2] = 800.0f;
	theta = 1.5 - 2.0 * atan(facing_dir[0]);
	is_moving = true;
};

