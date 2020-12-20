#pragma once
#include "../Entity.h"
#include "../Enemies/Enemy.h"

#define PLAYER_BULLET_TIMER_DT 0.05f

//class Enemy;

class Player: public Entity
{
public: 
	Player();
	Player(float x, float y, SceneHandler* SH, int playerID);

	void facing(float direction[2]);
	void update(float cursorX, float cursorY);
	void update(char* buffer_in); //this overload of update() takes in the character buffer recieved from network containing the x and y positions of the player 2
	void load_buffer_out(char* p_buffer_out);//this loads the outgoing buffer and sends the data


	float get_hitbox_right();

	bool has_shot = false, map_collided_right = false, map_collided_left = false, map_collided_up = false, map_collided_down = false;
private:
	int playerID;
	float bullet_timer = BULLET_TIMER, bullet_dt = PLAYER_BULLET_TIMER_DT, death_timer = RESPAWN_DELAY, death_dt = RESPAWN_DT;
};
