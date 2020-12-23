#pragma once
#include "../Entity.h"
#include "../Player/Player.h"
#define ENEMY_BULLET_SPEED 30.0f

class Player;

class Enemy: public Entity
{
public:
	Enemy();
	Enemy(Map* map, SceneHandler* SH);
	~Enemy();
	void move();
	void facing(Player* p);
	bool can_shoot();
	void update(Player* p1, Player* p2);
protected:
	bool shoot_player = false, is_moving = false;
	float bullet_timer = BULLET_TIMER, fire_rate, move_dir[2], path[5];
	// Enemy Behaviours
	// shoot_player: allows the Enemy to aim at a player object.
	// is_moving: allows the Enemy to move along a predetermined path
	// move_dir: the direction in which an Enemy is allowed to move
	// path: the line on which the Enemy can move
};