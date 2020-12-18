#include "Cannonboy.h"

//Horizontal path enemy, shoots at player position
Cannonboy::Cannonboy(float x, float y, SceneHandler* SH) : Enemy(SH)
{
	this->ScreenWidth = SH->get_WIDTH();
	this->ScreenHeight = SH->get_WIDTH();
	x_p = x;
	y_p = y;
	width = 50.0;
	height = 50.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 0.0;
		g[i] = 0.5;
		b[i] = 0.5;
	}
	//____Health____//
	maxHealth = 70.0f;
	health = maxHealth;
	//____Movement____//
	is_moving = true;
	max_speed = 1.5;
	move_dir[0] = 1; //x direction
	move_dir[1] = 0; //y direction
	path[0] = 100.0f;
	path[2] = 1000.0f;
	//____Shoot/Aim____//
	shoot_player = true;
	fire_rate = 0.010f;
	bullet_damage = 40;
};
