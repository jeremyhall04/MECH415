#pragma once
#include "Bullet.h"
#include "../Entities/Entity.h"
#include "../Entities/Enemies/Enemy.h"
#include "../SceneHandler/SceneHandler.h"
class Bullet;
class Entity;
class Enemy;

class BulletHandler
{
public:
	BulletHandler(SceneHandler* SH);
	void update_player_bullets(Player* player, Enemy* enemies, int N_enemies);
	void update_enemy_bullets(Enemy* enemy, Player* player);
	void bullet_collided(Entity* shooter, int index);

	void update_player_bullets_TEST(Player* player, Enemy** enemies, int N_enemies);

protected:
	SceneHandler* SH;
	float ScreenWidth, ScreenHeight;
};