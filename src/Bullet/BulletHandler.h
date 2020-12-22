#pragma once
#include "../Entities/Enemies/Enemy.h"
#include "../Map/Map.h"

class BulletHandler
{
public:
	BulletHandler(Map* map);
	void update_player_bullets(Player* player, Enemy** enemies, int N_enemies);
	void update_enemy_bullets(Enemy* enemy, Player* player);
	void map_collision_check(Entity* shooter);
	void bullet_collided(Entity* shooter, int index);

protected:
	Map* map;
	float ScreenWidth, ScreenHeight;
};