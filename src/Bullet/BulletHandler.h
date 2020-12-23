#pragma once
#include "../Entities/Enemies/Enemy.h"
#include "../Map/Map.h"

class BulletHandler
{
public:
	BulletHandler(Map* map);
	void update_entity_bullets(Entity* shooter, Entity** targets, int N_targets);
	bool map_collision_check(Hitbox* bullet_hb);
	void bullet_collided(Entity* shooter, int index);

protected:
	Map* map;
	float ScreenWidth, ScreenHeight;
};