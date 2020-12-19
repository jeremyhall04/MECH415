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
	virtual void draw();
	float x_p, y_p;
	double theta;
protected:
	int sprite_id, sprite_size;
	double width, height, r[3], g[3], b[3];
};