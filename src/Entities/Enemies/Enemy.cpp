#include "Enemy.h"
#include <cmath>

Enemy::Enemy()
{

}

Enemy::Enemy(Map* map, SceneHandler* SH) : Entity(map, SH) 
{
	bullet_speed = ENEMY_BULLET_SPEED;
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

void Enemy::update(Player p1, Player p2, char* p_buffer_in, int enemy, bool multiplayer)
{
	if (multiplayer) {
	char* p4;
	float *pf4;
	int i;
	p4 = p_buffer_in;

	p4 += (4 + enemy) * sizeof(float) + sizeof(double) + sizeof(bool);//move to enemy section of buffer
	
	pf4 = (float*)p4;
		
		if (*pf4 < health){
		health = *pf4;
		}

	}

	if (is_alive)
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

		if (SH->get_round_timer() < 0)
		{
			if (is_moving)
			{
				move();
			}
			if (can_shoot())
			{
				shoot();
			}
		}

		draw();
	}

}

void Enemy::validate_path(float path_min, float path_max)
{
	if (path_min < path[0])
	{

	}
}

void Enemy::Load_health_status_buffer(char * p_buffer_out, int enemy) {
	char* p3;
	float* pf3;
	int i;
	
	p3 = p_buffer_out;
	p3 += (4 + enemy) * sizeof(float) + sizeof(double) + sizeof(bool);
	
	pf3 = (float*)p3;
	*pf3 = health;
		
}