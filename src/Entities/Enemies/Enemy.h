#pragma once
#include "../Entity.h"
#include "../Player/Player.h"
class Player;

class Enemy: public Entity
{
public:
	Enemy();
	Enemy(float x, float y);
	void move();
	void facing(Player p); // face player then call shoot()
	bool can_shoot();
	void update(Player p1, Player p2);
	bool shoot_player = false, is_moving = false;
	float bullet_time = 1.5f, fire_rate, move_dir[2];
	float path[5];
};