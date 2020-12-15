#pragma once
#include "Bullet.h"
#include "../Entities/Entity.h"
class Bullet;
class Entity;

class BulletHandler
{
public:
	BulletHandler(float ScreenWidth, float ScreenHeight); //all entities with bullets?

	void update_bullets(Entity* shooter, Entity shootees[], int N_enemies); //this function takes in a bullet array and updates all of them
	void update_bullets(Entity* shooter, Entity* shootee);
	void bullet_collided(Entity* shooter, int index);

	void test();

	int N_entities;
	float ScreenWidth, ScreenHeight;
};