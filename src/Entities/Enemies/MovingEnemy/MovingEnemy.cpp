#include "MovingEnemy.h"

MovingEnemy::MovingEnemy(SceneHandler* SH) : Enemy(SH)
{

}

void MovingEnemy::move()
{
	//double t;
	//t = high_resolution_time();
	//path_dt(t);


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

void MovingEnemy::update(Player p1, Player p2)
{
	std::cout << "\nThis is Enemy::update()";

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

	move();
	draw();

	if (can_shoot())
	{
		shoot();
	}
}