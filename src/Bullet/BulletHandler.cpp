#include "BulletHandler.h"

BulletHandler::BulletHandler(float ScreenWidth, float ScreenHeight)
{
	this->ScreenWidth = ScreenWidth;
	this->ScreenHeight = ScreenHeight;
}

void BulletHandler::update_bullets(Entity* shooter, Entity shootees[], int N_enemies)
{
	for (int i = 0; i < shooter->i_bullet; i++)
	{
		shooter->bullets[i]->update();
		if (shooter->bullets[i]->x_p >= ScreenWidth || shooter->bullets[i]->x_p <= 0.0
			|| shooter->bullets[i]->y_p >= ScreenHeight || shooter->bullets[i]->y_p <= 0.0)
		{
			bullet_collided(shooter, i);
		}
	}
	if (shooter->bullets > 0)
	{
		for (int j = 0; j < N_enemies; j++)
		{
			for (int i = 0; i < shooter->i_bullet; i++)
			{
				float distance;
				distance = sqrt(pow((shootees[j].x_p - shooter->bullets[i]->x_p), 2) + pow((shootees[j].y_p - shooter->bullets[i]->y_p), 2));
				if (distance <= shooter->bullets[i]->R + shootees[j].R)
				{
					shootees[j].damage(*shooter->bullets[i]);
					bullet_collided(shooter, i);
				}
			}
		}
	}
}

void BulletHandler::update_bullets(Entity* shooter, Entity* shootee)
{
	for (int i = 0; i < shooter->i_bullet; i++)
	{
		shooter->bullets[i]->update();
		if (shooter->bullets[i]->x_p >= ScreenWidth || shooter->bullets[i]->x_p <= 0.0
			|| shooter->bullets[i]->y_p >= ScreenHeight || shooter->bullets[i]->y_p <= 0.0)
		{
			bullet_collided(shooter, i);
		}
	}
	if (shooter->bullets > 0)
	{
		for (int i = 0; i < shooter->i_bullet; i++)
		{
			float distance;
			distance = sqrt(pow((shootee->x_p - shooter->bullets[i]->x_p), 2) + pow((shootee->y_p - shooter->bullets[i]->y_p), 2));
			if (distance <= shooter->bullets[i]->R + shootee->R)
			{
				shootee->damage(*shooter->bullets[i]);
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
