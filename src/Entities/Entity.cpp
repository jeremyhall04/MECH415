#include "Entity.h"

Entity::Entity() {}

Entity::Entity(SceneHandler* SH)
{
	this->SH = SH;
	is_alive = true;
	theta = 0;
	bullet_speed = 20.0f;
	bullet_damage = 20.0f;
	i_bullet = 0;
	R = 50.0f;
}

void Entity::initialize()
{
	is_alive = true;
	health = default_health;
	x_p = default_x;
	y_p = default_y;
	for (int i = 0; i < i_bullet; i++) //i_bullet is the number of active bullets
	{
		bullets[i]->is_alive = false;
	}
	i_bullet = 0;
}

void Entity::draw()
{
	draw_sprite(sprite_id, x_p, y_p, theta, sprite_size);
	draw_healthbar();
}

void Entity::draw_healthbar()
{
	double x1[3];
	double y1[3];
	double length = 2.0 * (double)R;
	//Healthbar
		//Top triangle
	x1[0] = x_p - (length / 2.0);
	y1[0] = y_p + (double)R;
	x1[1] = x1[0] + (length * (double)(health / maxHealth));
	y1[1] = y1[0] + 5.0;
	x1[2] = x1[0];
	y1[2] = y1[1];
	triangle(x1, y1, r, g, b);
		//Bottom triangle
	x1[0] = x_p - (length / 2.0);
	y1[0] = y_p + (double)R;
	x1[1] = x1[0] + (length * (double)(health / maxHealth));
	y1[1] = y1[0] + 5.0;
	x1[2] = x1[1];
	y1[2] = y1[0];
	triangle(x1, y1, r, g, b);

	//Health display
	std::string str = std::to_string((int)health);
	char txt[11];
	strcpy_s(txt, str.c_str());
	text(txt, x_p - (width), y_p + (height / 2.0) + 40.0, 0.5);
}

void Entity::shoot()
{
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
			bullets[i_bullet] = new Bullet(x_p + R * (float)cos(theta),
				y_p + R * (float)sin(theta), facing_dir, bullet_speed, bullet_damage);
			i_bullet++;
		}
		else
		{
			//re-initialize bullet with new parameters
			bullets[i_bullet]->is_alive = true;
			bullets[i_bullet]->x_p = x_p + R * (float)cos(theta);
			bullets[i_bullet]->y_p = y_p + R * (float)sin(theta);
			bullets[i_bullet]->direction[0] = facing_dir[0];
			bullets[i_bullet]->direction[1] = facing_dir[1];
			bullets[i_bullet]->speed = bullet_speed;
			bullets[i_bullet]->damage = bullet_damage;
			i_bullet++;
		}
	}
}

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

void Entity::damage()
{
	health -= 20;
	if (health <= 0)
	{
		is_alive = false;
	}
}

void Entity::damage(Bullet b)
{
	health -= (int)b.get_damage();
	if (health <= 0)
	{
		is_alive = false;
	}
}