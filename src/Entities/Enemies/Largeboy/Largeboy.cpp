#include "Largeboy.h"
//horizontal path enemy, shoots vertically as it moves along path
Largeboy::Largeboy(float x, float y, SceneHandler* SH) : Enemy(SH)
{
	this->ScreenWidth = SH->get_WIDTH();
	this->ScreenHeight = SH->get_HEIGHT();
	x_p = x;
	y_p = y;
	width = 40.0;
	height = 40.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 0.5;
		g[i] = 0.0;
		b[i] = 0.5;
	}
	//____Health____//
	maxHealth = 90.0f;
	health = maxHealth;
	//____Movement____//
	is_moving = true;
	max_speed = 2;
	move_dir[0] = 1; //x direction
	move_dir[1] = 0; //y direction
	path[0] = 100.0f;
	path[2] = 800.0f;
	//____Shoot/Aim____//
	facing_dir[0] = 0.0f;
	facing_dir[1] = 1.0f;
	fire_rate = 0.030f;
	bullet_damage = 25;
	theta = 1.5 - 2.0 * atan(facing_dir[0]); //sprite angle in facing direction
};

