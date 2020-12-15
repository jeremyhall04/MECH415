#pragma once
#include "Bullet.h"
class Bullet;

class BulletHandler
{
public:
	BulletHandler(); //all entities with bullets?
	void collision_check(); //this will check all entities against all live bullets							//will probably need to take in manually player 2 bullets since
							//those arent known
	void update_bullets(Bullet* bullets); //this function takes in a bullet array and updates all of them
	int N_entities;
};