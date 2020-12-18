#include "Smallboy.h"

Smallboy::Smallboy(float x, float y, SceneHandler* SH) : Enemy(SH)
{
	this->ScreenWidth = SH->get_WIDTH();
	this->ScreenHeight = SH->get_WIDTH();
	create_sprite("src/Entities/Enemies/Smallboy/smallboy.png", sprite_id);
	sprite_size = 2;
	x_p = x;
	y_p = y;
	width = 20.0;
	height = 20.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 1.0;
		g[i] = 0.0;
		b[i] = 0.0;
	}
	//____Health____//
	maxHealth = 70.0f;
	health = maxHealth;
	//____Movement____//
	is_moving = true;
	max_speed = 3;
	move_dir[0] = 0; //x direction
	move_dir[1] = 1; //y direction
	path[1] = 200.0f;
	path[3] = 600.0f;
	//____Shoot/Aim____//
	facing_dir[0] = -1.0f;
	facing_dir[1] = 0.0f;
	fire_rate = 0.065f;
	bullet_damage = 15;
	theta = 1.5 - 2.0 * atan(facing_dir[0]); //sprite angle in facing direction
};