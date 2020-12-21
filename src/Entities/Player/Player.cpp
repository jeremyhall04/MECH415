#include "Player.h"

Player::Player() {}

Player::Player(float x, float y, Map* map, SceneHandler* SH, int playerID) : Entity(map, SH)
{
	this->map = map;
	this->ScreenWidth = map->get_screen_width();
	this->ScreenHeight = map->get_screen_height();
	this->SH = SH;
	create_sprite("src/Entities/Player/Player1.png", sprite_id);
	this->playerID = playerID;
	x_p = default_x = x; //starting coordinates
	y_p = default_y = y;
	//____Health____//
	maxHealth = 100.0f;
	health = default_health = maxHealth;
	R = 50.0f; // Player Hitbox Radius
	width = 25.0;
	height = 25.0;
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

void Player::facing(float direction[2])
{
	facing_dir[0] = direction[0];
	facing_dir[1] = direction[1];
	double diff;
	if (direction[0] < 0)
	{
		diff = 1.5 + atan(direction[1] / direction[0]);
		theta = 1.5 + diff;
	}
	else
	{
		theta = atan(direction[1] / direction[0]);
	}
}

void Player::update(float cursorX, float cursorY) //For player 1
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

	if (KEY('D') && x_p + R < ScreenWidth && !map_collided_right) x_p += max_speed;
	if (KEY('A') && x_p - R > 0 && !map_collided_left) x_p -= max_speed;
	if (KEY('W') && y_p + R < ScreenHeight && !map_collided_up) y_p += max_speed;
	if (KEY('S') && y_p - R > 0 && !map_collided_down) y_p -= max_speed;
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && bullet_timer == 1.0f && SH->get_round_timer() < 0)
	{
		shoot();
		has_shot = true;
		bullet_timer -= bullet_dt;
	}
	
	float diff_x, diff_y, len, aim_dir[2];
	diff_x = cursorX - x_p;
	diff_y = cursorY - y_p;
	len = sqrt(pow(diff_x, 2) + pow(diff_y, 2));
	aim_dir[0] = diff_x / len;
	aim_dir[1] = diff_y / len;
	facing(aim_dir);
	draw();

	for (int i = 0; i < i_bullet; i++)
	{
		bullets[i]->update();
	}

	if (bullet_timer != 1.0)
		bullet_timer -= bullet_dt;
	if (bullet_timer <= bullet_dt)
		bullet_timer = 1.0;
}

void Player::update(char* p_buffer_in) //For player 2
{
	if (!is_alive)
	{
		return;
	}
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

	if (has_shot) {
		shoot();
	}

	draw();
}

void Player::load_buffer_out(char* p_buffer_out)
{
	char* p;
	float* pf;
	double* pd;
	bool* pb;

	p = p_buffer_out;

	//Loading player x, y, theta and firing info in buffer_out
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
