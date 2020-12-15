#include "Entity.h"

Entity::Entity()
{
	is_alive = true;
	theta = 0;
	bullet_speed = 20.0f;
	bullet_damage = 20.0f;
	i_bullet = 0;
}

Entity::Entity(float x, float y)
{
	x_p = x;
	y_p = y;
	width = 60.0;
	height = 100.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 0.0;
		g[i] = 0.0;
		b[i] = 0.0;
	}
	max_speed = 0;
	health = 200;
	maxHealth = 200;
	is_alive = true;
	theta = 0;
}

void Entity::shoot()
{
	//MODIFY SHOOT() to scan for uninitialized bullet, then initialize that one
	if (i_bullet >= N_MAX_BULLETS)
	{
		std::cout << "\nOut of Bullets!";
		return;
	}
	else
	{
		if (bullets[i_bullet] == NULL)
		{
			//initialize new bullet
			bullets[i_bullet] = new Bullet(x_p + R * atan(facing_dir[1] / facing_dir[0]),
				y_p + R * atan(facing_dir[1] / facing_dir[0]), facing_dir, bullet_speed, bullet_damage);
			i_bullet++;
		}
		else
		{
			//re-initialize bullet with new parameters
			bullets[i_bullet]->is_alive = true;
			bullets[i_bullet]->x_p = x_p + R * atan(facing_dir[1] / facing_dir[0]);
			bullets[i_bullet]->y_p = y_p + R * atan(facing_dir[1] / facing_dir[0]);
			bullets[i_bullet]->direction[0] = facing_dir[0];
			bullets[i_bullet]->direction[1] = facing_dir[1];
			bullets[i_bullet]->speed = bullet_speed;
			bullets[i_bullet]->damage = bullet_damage;
			i_bullet++;
		}
	}
}

//void Entity::Update()
//{
//	std::cout << "\nEntity update";
//}

void Entity::bullet_collided(int index)
{
	if (bullets[index] == NULL)
	{
		std::cout << "\nERROR in bullet_collided; nullptr";
		return;
	}
	else
	{
		i_bullet--; //decrement first so that bullets[i_bullets] is the last allocated bullet
		bullets[index]->is_alive = false;
		Bullet* tmp = bullets[index];
		if (i_bullet != 0)
		{
			bullets[index] = bullets[i_bullet];
			bullets[i_bullet] = tmp;
		}
	}
}
