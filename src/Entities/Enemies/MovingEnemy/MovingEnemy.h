#pragma once
#include "../Enemy.h"

class MovingEnemy : public Enemy
{
public:
	MovingEnemy(SceneHandler* SH);
	void move();
	void update(Player p1, Player p2);
	virtual void path_dt(double time) = 0; //pure virtual function

	float move_dir[2], path[5];
};