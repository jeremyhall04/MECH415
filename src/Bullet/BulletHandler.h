#pragma once
#include "../Entities/Enemies/Enemy.h"
#include "../Map/Map.h"

class BulletHandler
{
public:
	BulletHandler(Map* map);
	void update_entity_bullets(Entity* shooter, Entity** targets, int N_targets);
	void map_collision_check(Entity* shooter);
	void bullet_collided(Entity* shooter, int index);

protected:
	Map* map;
	float ScreenWidth, ScreenHeight;
};