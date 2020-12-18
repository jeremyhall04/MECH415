#pragma once
#include "Bullet/Bullet.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <Windows.h>
#include <vector>
#include <string>
#include "../2D_graphics.h"
#include "../timer.h"

class GameObject 
{
public:
	GameObject();
	void draw();
	void draw_healthbar();

	float x_p, y_p, R, health; //R is the circular hitbox radius for the object
	double theta;
protected:
	int sprite_id, sprite_size;
	float maxHealth;
	double width, height, r[3], g[3], b[3];
};