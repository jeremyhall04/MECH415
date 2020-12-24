#pragma once
#define COUNTDOWN_TIMER_START 3.01f
#define COUNTDOWN_TIMER_DT 0.01f
#define COUNTDOWN_TIMER_END -1.0f
#include "../Map/Map.h"
#include "Button.h"

class SceneHandler
{
public:
	SceneHandler(Map* map);
	~SceneHandler();
	void round_timer_count();
	float get_round_timer();
	int get_round_timer_secs();
	void display_countdown();
	void play_audio_loop(char file_name[]);

	int main_menu();

protected:
	Map* map;
	float round_timer, c_x, c_y;
};