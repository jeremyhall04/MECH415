#pragma once
#include "Hitbox/Hitbox.h"

class GameObject : public Hitbox
{
public:
	GameObject();
	virtual void draw();
	double theta;
protected:
	int sprite_id, sprite_size;
	double r[3], g[3], b[3];
};