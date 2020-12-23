#include "Enemy.h"
#include <cmath>

Enemy::Enemy() {}

Enemy::Enemy(Map* map, SceneHandler* SH) : Entity(map, SH) 
{
	bullet_speed = ENEMY_BULLET_SPEED;
}

// Calculates the movement of the Enemy using the path and movement direction information.
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

// Calculates and sets the facing direction to a vector between the Enemy and the player object,
// and sets the sprite angle in the same direction.
void Enemy::facing(Player* p)
{
	float diff_x, diff_y, len;
	diff_x = p->x_p - x_p;
	diff_y = p->y_p - y_p;
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

// Determines if an Enemy can shoot (the firing rate) based off the bullet_timer.
// Returns true if the Enemy can shoot.
bool Enemy::can_shoot()
{
	if (bullet_timer == 1.0)
	{
		bullet_timer -= fire_rate;
		return true;
	}
	else if (bullet_timer <= fire_rate)
	{
		bullet_timer = 1.0;
		return false;
	}
	else 
	{ 
		bullet_timer -= fire_rate;
		return false; 
	}
}

/// <summary>
/// Updates Enemy state.
/// 
/// Draws Enemy sprite.
/// 
/// Based off of Enemy behaviour: 
/// Determines which player is closest (if in multiplayer) and aims at that player and moves Enemy
/// </summary>
/// <param name="p1"></param>
/// <param name="p2"></param>
void Enemy::update(Player* p1, Player* p2)
{
	if (is_alive)
	{
		if (shoot_player) //ADD CONDITIONAL MULTIPLAYER
		{
			if (p2->is_alive)
			{
				//If the enemy can aim at player, calculate which player is closest
				float p1_d, p2_d;
				p1_d = sqrt(pow(p1->x_p - x_p, 2) + pow(p1->y_p - y_p, 2));
				p2_d = sqrt(pow(p2->x_p - x_p, 2) + pow(p2->y_p - y_p, 2));
				if (p1_d < p2_d)
				{
					facing(p1);
				}
				else
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