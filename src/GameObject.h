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
	GameObject(float x, float y, double w, double h, double r, double g, double b);
	void draw();
	void draw_healthbar();
	void damage();
	void damage(Bullet b);

	int sprite_id, sprite_size;
	double theta;
	float x_p, y_p, health, maxHealth, R; //R is the circular hitbox radius for the object
protected:
	double width, height;
	double r[3], g[3], b[3];
};