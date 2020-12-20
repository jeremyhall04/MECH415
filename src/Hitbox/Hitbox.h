#pragma once

class Hitbox
{
public:
	Hitbox(float x, float y, double width, double height);
	void update(float x, float y);
	float get_left();
	float get_right();
	float get_bottom();
	float get_top();
private:
	float x, y;
	double width, height;
};