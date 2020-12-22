#include <iostream>
#include <cmath>
#include <string>
#include "Entity.h"
#include "../../2D_graphics.h"

Entity::Entity() {}

Entity::Entity(Map* map, SceneHandler* SH)
{
	this->map = map;
	is_alive = true;
	theta = 0;
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
	double length = 2.0 * width, healthbar_height = 5.0;
	//Healthbar
		//Top triangle
	x1[0] = x_p - (length / 2.0);
	y1[0] = y_p + height;
	x1[1] = x1[0] + (length * (double)(health / maxHealth));
	y1[1] = y1[0] + healthbar_height;
	x1[2] = x1[0];
	y1[2] = y1[1];
	triangle(x1, y1, r, g, b);
		//Bottom triangle
	x1[0] = x_p - (length / 2.0);
	y1[0] = y_p + height;
	x1[1] = x1[0] + (length * (double)(health / maxHealth));
	y1[1] = y1[0] + healthbar_height;
	x1[2] = x1[1];
	y1[2] = y1[0];
	triangle(x1, y1, r, g, b);

	//Health display
	std::string str = std::to_string((int)health);
	char txt[11];
	strcpy_s(txt, str.c_str());
	text(txt, x_p - width, y_p + (1.75 * height), 0.5);
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
			bullets[i_bullet]->initialize(x_p, y_p, facing_dir, bullet_speed, bullet_damage);
			i_bullet++;
		}
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