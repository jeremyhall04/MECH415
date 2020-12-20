#pragma once
#include "Bullet.h"
#include "../Entities/Enemies/Enemy.h"
#include "../SceneHandler/SceneHandler.h"
#include "../Map/Map.h"

class BulletHandler
{
public:
	BulletHandler(SceneHandler* SH, Map* map);
	void update_enemy_bullets(Enemy* enemy, Player* player);
	void bullet_collided(Entity* shooter, int index);

	void update_player_bullets_TEST(Player* player, Enemy** enemies, int N_enemies);

	void map_collision_check(Entity* shooter);

protected:
	SceneHandler* SH;
	Map* map;
	float ScreenWidth, ScreenHeight;
};