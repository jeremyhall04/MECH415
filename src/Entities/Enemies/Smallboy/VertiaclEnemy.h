#pragma once
#include "../Enemy.h"

class VerticalEnemy : public Enemy
{
public:
	VerticalEnemy(float x, float y, Map* map, SceneHandler* SH);
};
