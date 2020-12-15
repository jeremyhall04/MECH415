#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(float x, float y)
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
}

/*void Enemy::collision_check(std::vector<Bullet>* b)
{
	for (size_t i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].x_p >= 1200 || bullets[i].x_p <= 0 || bullets[i].y_p >= 900 || bullets[i].y_p <= 0)
		{
			bullets.erase(bullets.begin() + i);
		}
	}
	for (size_t i = 0; i < (*b).size(); i++)
	{
		if (((*b)[i].x_p + 15.0 >= x_p - (width / 2) - 30 && (*b)[i].x_p - 15.0 <= x_p + (width / 2) + 30
			&& ((*b)[i].y_p + 15.0 >= y_p - (height / 2) - 30 && (*b)[i].y_p - 15.0 <= y_p + (height / 2) + 30)))
		{
			damage((*b)[i]);
			(*b).erase((*b).begin() + i);
		}
	}
	if (health < 0)
	{
		is_alive = false;
		bullets.clear();
	}
}*/

void Enemy::move()
{
	if (move_dir[0] != 0)
	{
		if (std::abs(x_p - path[0]) <= 2.0f || std::abs(x_p - path[2]) <= 2.0f)
			move_dir[0] = -move_dir[0];
		x_p += (max_speed * move_dir[0]);
	}
	if (move_dir[1] != 0)
	{
		if (std::abs(y_p - path[1]) <= 2.0f || std::abs(y_p - path[3]) <= 2.0f)
			move_dir[1] = -move_dir[1];
		y_p += (max_speed * move_dir[1]);
	}
}

/*void Enemy::shoot()
{
	Bullet b(x_p, y_p, shot_dir, 15.0, bullet_damage);
	bullets.push_back(b);
}*/

void Enemy::facing(Player p)
{
	float diff_x, diff_y, len, aim_dir[2];
	diff_x = p.x_p - x_p;
	diff_y = p.y_p - y_p;
	len = std::sqrt(std::pow(diff_x, 2) + std::pow(diff_y, 2));
	facing_dir[0] = diff_x / len;
	facing_dir[1] = diff_y / len;

	double diff;
	if (facing_dir[0] < 0)
	{
		diff = 1.5 + atan(facing_dir[1] / facing_dir[0]);
		theta = 1.5 + diff;
	}
	else
	{
		theta = atan(facing_dir[1] / facing_dir[0]);
	}
}

bool Enemy::can_shoot()
{
	if (bullet_time == 1.0)
	{
		bullet_time -= fire_rate;
		return true;
	}
	else if (bullet_time <= fire_rate)
	{
		bullet_time = 1.0;
		return false;
	}
	else 
	{ 
		bullet_time -= fire_rate;
		return false; 
	}
}