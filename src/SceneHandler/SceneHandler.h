#pragma once
#define COUNTDOWN_TIMER_START 10.0f
#define COUNTDOWN_TIMER_DT 0.05f
#define COUNTDOWN_TIMER_END -1.0f

class SceneHandler
{
public:
	SceneHandler();
	void round_timer_count();
	float get_round_timer();
	void play_background_loop(char file_name[]);
protected:
	float round_timer = COUNTDOWN_TIMER_START;
};