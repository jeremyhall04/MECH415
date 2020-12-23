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
	bool collision_test(Hitbox* hb);
	float x_p, y_p;
protected:
	bool collision_test(float x, float y); // for player collision with tiles (x and y are the "new" coordinates)
	double width, height; 
};