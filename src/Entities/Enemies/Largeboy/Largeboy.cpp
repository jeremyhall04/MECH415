#include "Largeboy.h"
#include "../../../../2D_graphics.h"
#include <cmath>

//horizontal path enemy, shoots vertically as it moves along path
Largeboy::Largeboy(float x, float y, Map* map, SceneHandler* SH) : Enemy(map, SH)
{
	create_sprite("src/Entities/Enemies/Enemy.png", sprite_id);
	sprite_size = 1;
	x_p = x;
	y_p = y;
	//____Health____//
	maxHealth = 90.0f;
	health = maxHealth;
	R = 70.0f;
	width = height = R;
	for (int i = 0; i < 3; i++) {
		r[i] = 1.0;
		g[i] = 0.0;
		b[i] = 0.0;
	}
	//____Movement____//
	is_moving = true;
	max_speed = 2;
	move_dir[0] = 1; //x direction
	move_dir[1] = 0; //y direction
	path[0] = 100.0f;
	path[2] = 1400.0f;
	//____Shoot/Aim____//
	facing_dir[0] =  0.0f;
	facing_dir[1] = -1.0f;
	fire_rate = 0.030f;
	bullet_damage = 25;
	theta = -PI / 2; //sprite angle in facing direction
};

