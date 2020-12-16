#include "Turret.h"

Turret::Turret(float x, float y, SceneHandler* SH) : Enemy(SH)
{
	this->ScreenWidth = SH->get_WIDTH();
	this->ScreenHeight = SH->get_HEIGHT();
	create_sprite("src/Entities/Enemies/Turret/Turret.png", sprite_id);
	x_p = x;
	y_p = y;
	width = 60.0;
	height = 100.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 0.0;
		g[i] = 0.0;
		b[i] = 0.0;
	}
	max_speed = 0;
	maxHealth = 150;
	health = maxHealth;
	fire_rate = 0.015;
	bullet_damage = 30;
	shoot_player = true;
}