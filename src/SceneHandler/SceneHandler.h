#pragma once
#define COUNTDOWN_TIMER_START 10.0f
#define COUNTDOWN_TIMER_DT 0.05f
#define COUNTDOWN_TIMER_END -1.0f

class SceneHandler
{
public:
	SceneHandler();
	~SceneHandler();
	void round_timer_count();
	float get_round_timer();
	void play_audio_loop(char file_name[]);
protected:
	float round_timer;
};