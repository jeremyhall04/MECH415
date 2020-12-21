#pragma once

#define COUNTDOWN_TIMER_START 10.0f
#define COUNTDOWN_TIMER_DT 0.05f
#define COUNTDOWN_TIMER_END -1.0f

class SceneHandler
{
public:
	SceneHandler();
	float get_WIDTH();
	float get_HEIGHT();

	void load_level(int level);

	void round_timer_count();
	float get_round_timer();

	void play_background_loop(char file_name[]);
	void play_shot_sound(char file_name[]);

	int N_enemies;
	float x[2], y[2];
protected:
	float round_timer = COUNTDOWN_TIMER_START;
private:
	float WIDTH, HEIGHT;
};