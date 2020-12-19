#pragma once
#include "../MovingEnemy.h"

class Smallboy : public MovingEnemy
{
public:
	Smallboy(float x, float y, SceneHandler* SH);

	void path_dt(double time);
};
