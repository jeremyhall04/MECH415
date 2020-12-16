#pragma once
#include "Bullet.h"
#include "../Entities/Entity.h"
#include "../Entities/Enemies/Enemy.h"
class Bullet;
class Entity;
class Enemy;

class BulletHandler
{
public:
	BulletHandler(float ScreenWidth, float ScreenHeight); //all entities with bullets?

	void update_player_bullets(Entity* shooter, Enemy* shootees, int N_enemies);
	void update_enemy_bullets(Entity* shooter, Entity* shootee);
	void bullet_collided(Entity* shooter, int index);

	int N_entities;
	float ScreenWidth, ScreenHeight;
};