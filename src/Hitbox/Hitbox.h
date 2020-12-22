#pragma once

class Hitbox
{
public:
	Hitbox();
	Hitbox(float x, float y, double width, double height);
	void update(float x, float y);
	float get_left();
	float get_right();
	float get_bottom();
	float get_top();
	bool collision_test(float x, float y, float radius);
	bool collision_test(Hitbox* hb);

	float x_p, y_p;
	double width, height; 
};