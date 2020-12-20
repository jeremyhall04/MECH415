#include "BulletHandler.h"

BulletHandler::BulletHandler(SceneHandler* SH, Map* map)
{
	this->SH = SH;
	this->ScreenWidth = this->SH->get_WIDTH();
	this->ScreenHeight = this->SH->get_HEIGHT();
	this->map = map;
}

void BulletHandler::update_player_bullets_TEST(Player* player, Enemy** enemies, int N_enemies)
{
	for (int i = 0; i < player->i_bullet; i++)
	{
		bool is_collided = false;
		for (int j = 0; j < N_enemies; j++) 		//Checking collision against enemies
		{
			float distance;
			distance = sqrt(pow((enemies[j]->x_p - player->bullets[i]->x_p), 2) + pow((enemies[j]->y_p - player->bullets[i]->y_p), 2));
			if (distance <= player->bullets[i]->R + enemies[j]->R)
			{
				enemies[j]->damage(*player->bullets[i]);
				bullet_collided(player, i);
				break;
			}
		}
	}

	/*for (int i = 0; i < player->i_bullet; i++)
	{
		player->bullets[i]->update();
		if (player->bullets[i]->x_p >= ScreenWidth || player->bullets[i]->x_p <= 0.0
			|| player->bullets[i]->y_p >= ScreenHeight || player->bullets[i]->y_p <= 0.0)
		{
			bullet_collided(player, i);
		}
	}
	if (player->i_bullet > 0)
	{
		int j = 0;
		while (j < N_enemies)
		{
			if ((*enemies)->is_alive)
			{
				for (int i = 0; i < player->i_bullet; i++)
				{
					float distance;
					distance = sqrt(pow(((*enemies)->x_p - player->bullets[i]->x_p), 2) + pow(((*enemies)->y_p - player->bullets[i]->y_p), 2));
					if (distance <= player->bullets[i]->R + (*enemies)->R)
					{
						(*enemies)->damage(*player->bullets[i]);
						bullet_collided(player, i);
					}
				}
			}
			enemies++;
			j++;
		}
	}*/
}

//void BulletHandler::map_collision_check(Player* player)
//{
//	for (int i = 0; i < player->i_bullet; i++)
//	{
//		bool is_collided = false;
//		Hitbox* bullet_hb = player->bullets[i]->hitbox;
//		for (int j = 0; j < map->n_tiles; j++) 		//Checking collision against tiles
//		{
//			Hitbox * tile_hb = map->tiles[j]->hitbox;
//			if (bullet_hb->get_right() >= tile_hb->get_left() && bullet_hb->get_left() <= tile_hb->get_right()
//				&& bullet_hb->get_top() >= tile_hb->get_bottom() && bullet_hb->get_bottom() <= tile_hb->get_top())
//			{
//				bullet_collided(player, i);
//				is_collided = true;
//				break;
//			}
//		}
//		if (is_collided == false)		//Checking collisions against boundaries
//		{
//			if (bullet_hb->get_right() >= ScreenWidth || bullet_hb->get_left() <= 0.0
//				|| bullet_hb->get_top() >= ScreenHeight || bullet_hb->get_bottom() <= 0.0)
//			{
//				bullet_collided(player, i);
//			}
//		}
//	}
//}

void BulletHandler::map_collision_check(Entity* shooter)
{
	for (int i = 0; i < shooter->i_bullet; i++)
	{
		bool is_collided = false;
		Hitbox* bullet_hb = shooter->bullets[i]->hitbox;
		for (int j = 0; j < map->n_tiles; j++) 		//Checking collision against tiles
		{
			Hitbox* tile_hb = map->tiles[j]->hitbox;
			if (bullet_hb->get_right() >= tile_hb->get_left() && bullet_hb->get_left() <= tile_hb->get_right()
				&& bullet_hb->get_top() >= tile_hb->get_bottom() && bullet_hb->get_bottom() <= tile_hb->get_top())
			{
				bullet_collided(shooter, i);
				is_collided = true;
				break;
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

void BulletHandler::update_enemy_bullets(Enemy* enemy, Player* player)
{
	for (int i = 0; i < enemy->i_bullet; i++)
	{
		//enemy->bullets[i]->update();
		if (enemy->bullets[i]->x_p >= ScreenWidth || enemy->bullets[i]->x_p <= 0.0
			|| enemy->bullets[i]->y_p >= ScreenHeight || enemy->bullets[i]->y_p <= 0.0)
		{
			bullet_collided(enemy, i);
		}
	}
	if (enemy->i_bullet > 0 && player->is_alive)
	{
		for (int i = 0; i < enemy->i_bullet; i++)
		{
			float distance;
			distance = sqrt(pow((player->x_p - enemy->bullets[i]->x_p), 2) + pow((player->y_p - enemy->bullets[i]->y_p), 2));
			if (distance <= enemy->bullets[i]->R + player->R)
			{
				player->damage(*enemy->bullets[i]);
				bullet_collided(enemy, i);
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