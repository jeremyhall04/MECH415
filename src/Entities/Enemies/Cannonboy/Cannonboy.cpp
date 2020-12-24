#include "Cannonboy.h"
#include "../../../../2D_graphics.h"
#include <cmath>
//Horizontal path enemy, shoots at player position
Cannonboy::Cannonboy(float x, float y, Map* map, SceneHandler* SH) : Enemy(map, SH)
{
	create_sprite("src/Entities/Enemies/Enemy.png", sprite_id);
	sprite_size = 1;
	x_p = x;
	y_p = y;
	//____Health____//
	maxHealth = 110.0f;
	health = maxHealth;
	R = 60.0f;
	width = height = R;
	for (int i = 0; i < 3; i++) {
		r[i] = 1.0;
		g[i] = 0.0;
		b[i] = 0.0;
	}
	//____Movement____//
	is_moving = true;
	max_speed = 2.50f;
	move_dir[0] = 1; //x direction
	move_dir[1] = 0; //y direction
	path[0] = 200.0f;
	path[2] = 1200.0f;
	//____Shoot/Aim____//
	shoot_player = true;
	fire_rate = 0.010f;
	bullet_damage = 30.0f;
};
