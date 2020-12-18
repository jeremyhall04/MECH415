#pragma once
#include "../Entity.h"
#include "../Player/Player.h"

class Player;

class Enemy: public Entity
{
public:
	Enemy();
	Enemy(SceneHandler* SH);
	void move();
	void facing(Player p); // face player then call shoot()
	bool can_shoot();
	void update(Player p1, Player p2);
	void validate_path(float path_min, float path_max);
protected:
	bool shoot_player = false, is_moving = false;
	float bullet_time = BULLET_TIMER, fire_rate, move_dir[2], path[5];
};