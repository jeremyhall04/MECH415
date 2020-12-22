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

		curBullet->update();

		for (int j = 0; j < N_targets; j++) 	//Checking collision against enemies
		{
			Entity* curTarget = targets[j];
			if (!curTarget->is_alive)
				continue;

			if (curTarget->collision_test(curBullet->x_p, curBullet->y_p, curBullet->R) == true)
			{
				curTarget->damage(*curBullet);
				bullet_collided(shooter, i);
				break;
			}
		}
	}
	map_collision_check(shooter);	//Check bullet collision against map 
}

void BulletHandler::map_collision_check(Entity* shooter)
{
	for (int i = 0; i < shooter->i_bullet; i++)
	{
		bool is_collided = false;
		Hitbox* bullet_hb = (Hitbox*)shooter->bullets[i];
		/*for (int j = 0; j < map->n_tiles; j++) 		//Checking collision against tiles
		{
			Hitbox* tile_hb = (Hitbox*)map->tiles[j];
			float hb_left = tile_hb->get_left();
			float hb_right = tile_hb->get_right();
			float hb_top = tile_hb->get_top();
			float hb_bottom = tile_hb->get_bottom();

			float b_left = bullet_hb->get_left();
			float b_right = bullet_hb->get_right();
			float b_top = bullet_hb->get_top();
			float b_bottom = bullet_hb->get_bottom();

			if (b_right >= hb_left && b_left <= hb_right
				&& b_top >= hb_bottom && b_bottom <= hb_top)
			{
				bullet_collided(shooter, i);
				is_collided = true;
				break;
			}
		}*/
		for (int j = 0; j < map->n_tiles; j++)
		{
			if (map->tiles[j] != NULL)
			{
				Hitbox* tile_hb = (Hitbox*)map->tiles[j];
				if (tile_hb->collision_test(bullet_hb))
				{
					is_collided = true;
					bullet_collided(shooter, i);
					break;
				}
			}
		}
		if (is_collided == false)		//Checking collisions against boundaries
		{
			if (bullet_hb->get_right() >= ScreenWidth || bullet_hb->get_left() <= 0.0
				|| bullet_hb->get_top() >= ScreenHeight || bullet_hb->get_bottom() <= 0.0)
			{
				bullet_collided(shooter, i);
			}
		}
	}
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