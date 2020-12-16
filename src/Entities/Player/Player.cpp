#include "Player.h"

Player::Player()
{
	create_sprite("src/Entities/Player/Player1.png", sprite_id);
	x_p = 250.0f;
	y_p = 250.0f;
	width = 25.0;
	height = 25.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 1.0;
		g[i] = 1.0;
		b[i] = 1.0;
	}
	health = 100;
	maxHealth = 100;
	max_speed = 6;
	playerID = 1;
	R = 25.0f;
}

Player::Player(float x, float y, float ScreenWidth, float ScreenHeight, int playerID)
{
	this->ScreenWidth = ScreenWidth;
	this->ScreenHeight = ScreenHeight;
	create_sprite("src/Entities/Player/Player1.png", sprite_id);
	this->playerID = playerID;
	x_p = x;
	y_p = y;
	width = 25.0;
	height = 25.0;
	for (int i = 0; i < 3; i++) {
		r[i] = 1.0;
		g[i] = 1.0;
		b[i] = 1.0;
	}
	health = 100;
	maxHealth = 100;
	max_speed = 8;
	R = 50.0f;

	bullet_speed = 50.0f;
	bullet_damage = 25.0f;
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
	if (has_shot)
	{
		has_shot = false;
	}
	if (KEY('D') && x_p + R < ScreenWidth) x_p += max_speed;
	if (KEY('A') && x_p - R > 0) x_p -= max_speed;
	if (KEY('W') && y_p + R < ScreenHeight) y_p += max_speed;
	if (KEY('S') && y_p - R > 0) y_p -= max_speed;
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0 && bullet_timer == 1.0f)
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

	if (bullet_timer != 1.0)
		bullet_timer -= bullet_dt;
	if (bullet_timer <= bullet_dt)
		bullet_timer = 1.0;
}

void Player::update(char* p_buffer_in) //For player 2
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
	
	pb2 = (bool*)p2;
	has_shot=*pb2;

	if (has_shot) {
		shoot();
	}

	draw();
}
