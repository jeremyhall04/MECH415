#pragma once
#include "../Entity.h"
#include "../Enemies/Enemy.h"
#define PLAYER_BULLET_TIMER_DT 0.05f

class Player: public Entity
{
public: 
	Player();
	Player(float x, float y, Map* map, SceneHandler* SH);
	void update(float cursorX, float cursorY);
	void update(char* buffer_in);
	void check_player_inputs();
	void facing(float cursorX, float cursorY);
	void load_buffer_out(char* p_buffer_out);//this loads the outgoing buffer and sends the data

	bool has_shot = false;
private:
	float bullet_timer = BULLET_TIMER, bullet_dt = PLAYER_BULLET_TIMER_DT, death_timer = RESPAWN_DELAY, death_dt = RESPAWN_DT;
	bool tile_collision_test(float x, float y);
	void read_buffer_in(char* buffer_in); //this overload of update() takes in the character buffer recieved from network containing the x and y positions of the player 2
};
