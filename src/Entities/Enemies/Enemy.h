#pragma once
#include "../Entity.h"
#include "../Player/Player.h"
#define ENEMY_BULLET_SPEED 20.0f

class Player;

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(Map* map, SceneHandler* SH);
	void move();
	void facing(Player p); // face player then call shoot()
	bool can_shoot();
	void update(Player p1, Player p2, char *p_buffer_in, int enemy, bool multiplayer);
	void validate_path(float path_min, float path_max);
	void Load_health_status_buffer(char* p_buffer_out, int enemy);
protected:
	bool shoot_player = false, is_moving = false;
	float bullet_time = BULLET_TIMER, fire_rate, move_dir[2], path[5];
};