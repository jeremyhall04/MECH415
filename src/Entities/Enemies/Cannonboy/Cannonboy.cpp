#include "Cannonboy.h"

//Horizontal path enemy, shoots at player position
Cannonboy::Cannonboy(float x, float y)
{
	x_p = x;
	y_p = y;
	width = 50.0;
	height = 50.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 0.0;
		g[i] = 0.5;
		b[i] = 0.5;
	}
	max_speed = 1.5;
	maxHealth = 70;
	health = maxHealth;
	fire_rate = 0.010;
	bullet_damage = 40;
	is_moving = true;
	move_dir[0] = 1; //x direction
	move_dir[1] = 0; //y direction
	path[0] = 100.0f;
	path[2] = 1000.0f;

	shoot_player = true;
};
