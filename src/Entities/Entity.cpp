#include <iostream>
#include <cmath>
#include <string>
#include "Entity.h"
#include "../../2D_graphics.h"

Entity::Entity() {}

/// <summary>
/// Base constructor for all Entity-deriving classes (Player, Enemies, etc.).
/// 
/// Linked constructor that takes the derived class's parameteres for Map and SceneHandler 
/// and assigns them to the Entity member variables
/// </summary>
/// <param name="map">Map object reference (member variable)</param>
/// <param name="SH">SceneHandler object reference (member variable)</param>
Entity::Entity(Map* map, SceneHandler* SH)
{
	this->map = map;
	this->SH = SH;
	is_alive = true;
	theta = 0;
	bullet_damage = 20.0f;
	i_bullet = 0;
	R = 50.0f;
}

Entity::~Entity()
{
	for (int i = 0; i < N_MAX_BULLETS; i++)
	{
		if (bullets[i] != NULL)
		{
			delete bullets[i];
			bullets[i] = NULL;
		}
	}
}

/// Reset all properties to default (for respawning purposes).
void Entity::initialize()
{
	is_alive = true;
	health = default_health;
	x_p = default_x;
	y_p = default_y;
	for (int i = 0; i < i_bullet; i++)
	{
		bullets[i]->is_alive = false;
	}
	i_bullet = 0;
}

/// Overload of the GameObject.draw() method.
void Entity::draw()
{
	draw_sprite(sprite_id, x_p, y_p, theta, sprite_size);
	draw_healthbar();
}

/// Visual display of player health.
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

/// Use map object's get_screen_width and get_screen_height functions
float Entity::get_screen_width()
{
	return map->get_screen_width();
}

float Entity::get_screen_height()
{
	return map->get_screen_height();
}

/// <summary>
/// Create a new instance of bullet at index i_bullet if there is not one already initialized at index,
/// but reuse (re-initialize) if memory is already allocated.
/// </summary>
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

/// <summary>
/// Damage entity by an amount determined by the bullet b.
/// </summary>
/// <param name="b"></param>
void Entity::damage(Bullet b)
{
	health -= (int)b.get_damage();
	if (health <= 0)
	{
		is_alive = false;
	}
}