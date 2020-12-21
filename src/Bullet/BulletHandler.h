#pragma once
#include "Bullet.h"
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


	void check_bullet_collision_environemnt(Bullet* b);

protected:
	Map* map;
	float ScreenWidth, ScreenHeight;
};