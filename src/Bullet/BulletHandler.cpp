#include "BulletHandler.h"
#include <cmath>
#include <iostream>

BulletHandler::BulletHandler(Map* map)
{
	this->map = map;
	ScreenWidth = this->map->get_screen_width();
	ScreenHeight = this->map->get_screen_height();
}

void BulletHandler::update_entity_bullets(Entity* shooter, Entity** targets, int N_targets)
{
	for (int i = 0; i < shooter->i_bullet; i++)
	{
		Bullet* curBullet = shooter->bullets[i];
		Hitbox* bullet_hb = (Hitbox*)shooter->bullets[i];
		curBullet->update();

		for (int j = 0; j < N_targets; j++) 	//Checking collision against enemies
		{
			Entity* curTarget = targets[j];
			if (!curTarget->is_alive)
				continue;
			if (curTarget->collision_test(bullet_hb))
			{
				curTarget->damage(*curBullet);
				bullet_collided(shooter, i);
				break;
			}
		}
		if (curBullet->is_alive && map_collision_check(bullet_hb))
		{
			bullet_collided(shooter, i);
		}
	}
}

bool BulletHandler::map_collision_check(Hitbox* bullet_hb)
{
	bool is_collided = false;
	for (int j = 0; j < map->n_tiles; j++)  //Checking collisions against tiles
	{
		Tile* curTile = map->tiles[j];
		if (curTile != NULL)
		{
			if (curTile->collision_test(bullet_hb))
			{
				is_collided = true;
				break;
			}
		}
	}
	if (!is_collided)		//Checking collisions against boundaries
	{
		if (bullet_hb->get_right() >= ScreenWidth || bullet_hb->get_left() <= 0.0
			|| bullet_hb->get_top() >= ScreenHeight || bullet_hb->get_bottom() <= 0.0)
		{
			is_collided = true;
		}
	}
	return is_collided;
}

void BulletHandler::bullet_collided(Entity* shooter, int index)
{
	if (shooter->bullets[index] == NULL)
	{
		std::cout << "\nERROR in bullet_collided; nullptr";
		return;
	}
	else
	{
		shooter->i_bullet--; //decrement first so that bullets[i_bullets] is the last allocated bullet
		shooter->bullets[index]->is_alive = false;
		Bullet* tmp = shooter->bullets[index]; //this can probably go in the if statement
		if (shooter->i_bullet != 0)
		{
			shooter->bullets[index] = shooter->bullets[shooter->i_bullet];
			shooter->bullets[shooter->i_bullet] = tmp;
		}
	}
}