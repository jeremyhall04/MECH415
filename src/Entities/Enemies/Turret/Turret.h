#pragma once
#include "../Enemy.h"

class Turret: public Enemy
{
public:
	Turret(float x, float y, float ScreenWidth, float ScreenHeight);
};