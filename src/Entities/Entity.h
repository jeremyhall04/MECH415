#pragma once
#include "../GameObject.h"
#include "../Bullet/Bullet.h"
#include "../Map/Map.h"
#include "../SceneHandler/SceneHandler.h"
#define RESPAWN_DELAY 5.0f
#define RESPAWN_DT 0.03f
#define BULLET_TIMER 1.0f

const int N_MAX_BULLETS = 20;

class Entity: public GameObject
{
public:
	Entity();
	Entity(Map* map, SceneHandler* SH);
	void shoot();
	void damage(Bullet b);
	void initialize(); //for resetting the levels

	void draw() override; //override indicates that draw() is the Entity function (not GameObject)
	void draw_healthbar();

	bool is_alive;
	float facing_dir[2], health, R; //R is the circular hitbox radius for the object
	int i_bullet; //index @ number of active bullets
	Bullet* bullets[N_MAX_BULLETS] = { NULL };
protected:
	SceneHandler* SH;
	Map* map;
	float default_health, maxHealth, default_x, default_y, max_speed, bullet_damage, bullet_speed, ScreenWidth, ScreenHeight;
};
