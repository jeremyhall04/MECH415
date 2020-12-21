#pragma once

class SceneHandler
{
public:
	SceneHandler();
	float get_WIDTH();
	float get_HEIGHT();

	void load_level(int level);
	void play_background_loop(char file_name[]);
	void play_shot_sound(char file_name[]);
	int N_enemies;
	float x[2], y[2];
private:
	float WIDTH, HEIGHT;
};