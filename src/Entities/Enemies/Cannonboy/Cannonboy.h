#pragma once
#include "../Enemy.h"

class Cannonboy : public Enemy
{
public:
	Cannonboy(float x, float y, Map* map, SceneHandler* SH);
};
