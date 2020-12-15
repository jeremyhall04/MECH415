#pragma once
#include "../GameObject.h"
#include "../Bullet/Bullet.h"

const int N_MAX_BULLETS = 20;

class Entity: public GameObject
{
public:
	Entity();
	Entity(float x, float y);
	void shoot();
	void bullet_collided(int index);
	void damage();
	void damage(Bullet b);


	bool is_alive;
	float max_speed, facing_dir[2], ScreenWidth, ScreenHeight;
	int i_bullet; //number of active bullets
	Bullet* bullets[N_MAX_BULLETS] = { NULL };
	int bullet_damage, bullet_speed;
};
