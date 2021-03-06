#include "Turret.h"
#include "../../../../2D_graphics.h"

Turret::Turret(float x, float y, Map* map, SceneHandler* SH) : Enemy(map, SH)
{
	create_sprite("src/Entities/Enemies/Turret/Turret.png", sprite_id);
	x_p = x;
	y_p = y;
	//____Health____//
	maxHealth = 150.0f;
	health = maxHealth;
	R = 70.0f;
	width = height = R;
	for (int i = 0; i < 3; i++) {
		r[i] = 0.0;
		g[i] = 0.0;
		b[i] = 0.0;
	}
	//____Movement____//
	max_speed = 0;
	//____Shoot/Aim____//
	shoot_player = true;
	fire_rate = 0.015f;
	bullet_damage = 30.0f;
}