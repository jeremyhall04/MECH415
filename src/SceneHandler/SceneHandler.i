#line 1 "SceneHandler.h"
#pragma once




class SceneHandler
{
public:
	SceneHandler();
	void round_timer_count();
	float get_round_timer();
	void play_background_loop(char file_name[]);
protected:
	float round_timer = 10.0f;
};
