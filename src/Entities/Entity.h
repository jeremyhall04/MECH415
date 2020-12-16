#pragma once
#include "../GameObject.h"
#include "../Bullet/Bullet.h"
#include "../SceneHandler/SceneHandler.h"

#define RESPAWN_DELAY 5.0f
#define RESPAWN_DT 0.03f
#define BULLET_TIMER 1.0f
 
const int N_MAX_BULLETS = 20;

class Entity: public GameObject
{
public:
	Entity();
	Entity(SceneHandler* SH);
	Entity(float x, float y);
	void shoot();
	void bullet_collided(int index);
	void damage();
	void damage(Bullet b);
	void initialize(); //for resetting the levels

	bool is_alive;
	float max_speed, facing_dir[2], ScreenWidth, ScreenHeight;
	int i_bullet; //number of active bullets
	Bullet* bullets[N_MAX_BULLETS] = { NULL };
	int bullet_damage, bullet_speed;

protected:
	SceneHandler* SH;
	float default_x, default_y;
	int default_health;
};
