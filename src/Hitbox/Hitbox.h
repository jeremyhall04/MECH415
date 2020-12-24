#pragma once

class Hitbox
{
public:
	Hitbox();
	Hitbox(float x, float y, double width, double height);
	float get_left();
	float get_right();
	float get_bottom();
	float get_top();
	double get_width();
	double get_height();
	bool collision_test(Hitbox* hb);
	float x_p, y_p;
protected:
	bool collision_test(float x, float y);
	double width, height; 
};