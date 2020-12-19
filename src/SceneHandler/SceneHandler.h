#pragma once

class SceneHandler
{
public:
	SceneHandler();
	float get_WIDTH();
	float get_HEIGHT();

	void load_level(int level);
	
	int N_enemies;
	float x[2], y[2];
private:
	float WIDTH, HEIGHT;
};