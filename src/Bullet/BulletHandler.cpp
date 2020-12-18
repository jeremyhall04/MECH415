#include "BulletHandler.h"

BulletHandler::BulletHandler(SceneHandler* SH)
{
	this->ScreenWidth = SH->get_WIDTH();
	this->ScreenHeight = SH->get_HEIGHT();
}

void BulletHandler::update_player_bullets(Player* player, Enemy* enemies, int N_enemies)
{
	for (int i = 0; i < player->i_bullet; i++)
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
			for (int i = 0; i < player->i_bullet; i++)
			{
				float distance;
				distance = sqrt(pow((enemies->x_p - player->bullets[i]->x_p), 2) + pow((enemies->y_p - player->bullets[i]->y_p), 2));
				if (distance <= player->bullets[i]->R + enemies->R)
				{
					enemies->damage(*player->bullets[i]);
					bullet_collided(player, i);
				}
			}
			enemies++;
			j++;
		}
	}
}

void BulletHandler::update_enemy_bullets(Enemy* enemy, Player* player)
{
	for (int i = 0; i < enemy->i_bullet; i++)
	{
		enemy->bullets[i]->update();
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