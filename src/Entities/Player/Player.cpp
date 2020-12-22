#include <Windows.h>
#include <cmath>
#include "Player.h"
#include "../../../2D_graphics.h"

Player::Player() {}

Player::Player(float x, float y, Map* map, SceneHandler* SH) : Entity(map, SH)
{
	create_sprite("src/Entities/Player/Player1.png", sprite_id);
	x_p = default_x = x; //starting coordinates
	y_p = default_y = y;
	//____Health____//
	maxHealth = 100.0f;
	health = default_health = maxHealth;
	R = 40.0f; // Player Hitbox Radius
	width = height = (double)R;
	for (int i = 0; i < 3; i++) {
		r[i] = 1.0;
		g[i] = 1.0;
		b[i] = 1.0;
	}
	//____Movement____//
	max_speed = 6.0f;
	bullet_damage = 25.0f;
	bullet_speed = 50.0f;
}

void Player::update(float cursorX, float cursorY) // Updates player1 state
{
	if (!is_alive)
	{
		death_timer -= death_dt;
		if (death_timer <= 0.0f)
		{
			death_timer = 5.0f; //reset timer
			initialize();
		}
		return;
	}

	if (has_shot)
	{
		has_shot = false;
	}

	check_player_inputs();	// Test new position (after keyboard input) for collisions with map tiles

	facing(cursorX, cursorY);

	draw();

	if (bullet_timer != 1.0)
		bullet_timer -= bullet_dt;
	if (bullet_timer <= bullet_dt)
		bullet_timer = 1.0;
}

void Player::update(char* buffer_in) // Used for updating player2 (after read_buffer_in)
{
	read_buffer_in(buffer_in);
	if (!is_alive)
	{
		death_timer -= death_dt;
		if (death_timer <= 0.0f)
		{
			death_timer = 5.0f; //reset timer
			initialize();
		}
		return;
	}

	if (has_shot)
	{
		shoot();
	}

	draw();
}

void Player::check_player_inputs() // Gets keyboard inputs and tests if collision will occur
{
	float new_x_p = x_p;
	float new_y_p = y_p;

	if (KEY('A'))
		new_x_p -= max_speed;
	if (!tile_collision_test(new_x_p, new_y_p)) // can we move left?
		x_p = new_x_p;
	else
		new_x_p = x_p;

	if (KEY('D'))
		new_x_p += max_speed;
	if (!tile_collision_test(new_x_p, new_y_p))	// can we move right?
		x_p = new_x_p;
	else
		new_x_p = x_p;

	if (KEY('W'))
		new_y_p += max_speed;
	if (!tile_collision_test(new_x_p, new_y_p))	// can we move up?
		y_p = new_y_p;
	else
		new_y_p = y_p;

	if (KEY('S'))
		new_y_p -= max_speed;
	if (!tile_collision_test(new_x_p, new_y_p))	// can we move down?
		y_p = new_y_p;
	else
		new_y_p = y_p;

	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && bullet_timer == 1.0f && SH->get_round_timer() < 0)
	{
		shoot();
		has_shot = true;
		bullet_timer -= bullet_dt;
	}
}

void Player::facing(float cursorX, float cursorY)	// Calculates the sprite angle (theta) //Calculates the unit vector between the cursor and the player 
{
	float diff_x, diff_y, len;
	diff_x = cursorX - x_p;
	diff_y = cursorY - y_p;
	len = sqrt(pow(diff_x, 2) + pow(diff_y, 2));
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

void Player::read_buffer_in(char* p_buffer_in) //Reads buffer_in and updates player2 state
{
	char* p2;
	float* pf2;
	double* pd2;
	bool* pb2;

	p2 = p_buffer_in;

	pf2 = (float*)p2;
	x_p = *pf2;
	p2 += sizeof(float);

	pf2 = (float*)p2;
	y_p = *pf2;
	p2 += sizeof(float);

	pd2 = (double*)p2;
	theta = *pd2;
	p2 += sizeof(double);

	pf2 = (float*)p2;
	facing_dir[0] = *pf2;
	p2 += sizeof(float);

	pf2 = (float*)p2;
	facing_dir[1] = *pf2;
	p2 += sizeof(float);

	pb2 = (bool*)p2;
	has_shot = *pb2;
}

void Player::load_buffer_out(char* p_buffer_out) //Loads player state into buffer_out to send to network
{
	char* p;
	float* pf;
	double* pd;
	bool* pb;

	p = p_buffer_out;

	pf = (float*)p;
	*pf = x_p;
	p += sizeof(float);

	pf = (float*)p;
	*pf = y_p;
	p += sizeof(float);

	pd = (double*)p;
	*pd = theta;
	p += sizeof(double);

	pf = (float*)p;

	*pf = facing_dir[0];
	p += sizeof(float);

	pf = (float*)p;
	*pf = facing_dir[1];
	p += sizeof(float);

	pb = (bool*)p;
	*pb = has_shot;
}

bool Player::tile_collision_test(float x, float y) // test the proposed position for collision with all the map's current list of tiles
{
	bool collision = false;
	if (y + R > get_screen_height() || y - R < 0 ||
		x + R > get_screen_width() || x - R < 0)			//checking collision with window size
	{
		//printf("Map bounds collision\n");
		collision = true;
	}

	if (!collision)
	{
		for (int i = 0; i < map->n_tiles; i++)		//checking collision with tiles
		{
			collision = map->tiles[i]->collision_test(x, y, R);
			if (collision)
			{
				//printf("Map tile collision\n");
				break;
			}
		}
	}
	return collision;
}
