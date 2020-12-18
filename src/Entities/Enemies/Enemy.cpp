#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(SceneHandler* SH) : Entity(SH) {}

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

void Enemy::facing(Player p)
{
	float diff_x, diff_y, len;
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

void Enemy::update(Player p1, Player p2)
{
	if (shoot_player) //ADD CONDITIONAL MULTIPLAYER
	{
		if (p2.is_alive)
		{
			//If the enemy can aim at player, calculate which player is closest
			float p1_d, p2_d;
			p1_d = sqrt(pow(p1.x_p - x_p, 2) + pow(p1.y_p - y_p, 2));
			p2_d = sqrt(pow(p2.x_p - x_p, 2) + pow(p2.y_p - y_p, 2));
			if (p1_d < p2_d)
			{
				facing(p1);
			}
			else if (p2_d < p1_d)
			{
				facing(p2);
			}
		}
		else
		{
			facing(p1);
		}
	}
	if (is_moving)
	{
		move();
	}
	draw();

	if (can_shoot())
	{
		shoot();
	}
}