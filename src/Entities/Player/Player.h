#pragma once
#include "../Entity.h"
#include "../Enemies/Enemy.h"
class Enemy;

class Player: public Entity
{
public: 
	Player();
	Player(float x, float y, float ScreenWidth, float ScreenHeight, int player_id);

	void facing(float direction[2]);
	void update(float cursorX, float cursorY);
	void update(char* buffer_in); //this overload of update() takes in the character buffer recieved from network
								//containing the x and y positions of the player 2

	float bullet_timer = 1.0f, bullet_dt = 0.05f;
private:
	int playerID;
};
