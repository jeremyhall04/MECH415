#include "SceneHandler.h"
#include <iostream>
#include <fstream>
#include <string>

SceneHandler::SceneHandler()
{
	std::ifstream file;
	std::string str[6];
	size_t sz;
	int i = 0;

	file.open("DirectX_window/window_size.txt");
	if (!file.is_open())
	{
		std::cout << "\nError - get_screen_size(): could not open file";
		return;
	}
	while (i < 6)
	{
		getline(file, str[i]);
		i++;
	}

	file.close();

	WIDTH = std::stof(str[1], &sz); //initialize the Scene variables WIDTH & HEIGHT
	HEIGHT = std::stof(str[3], &sz);
}

float SceneHandler::get_WIDTH()
{
	return WIDTH;
}

float SceneHandler::get_HEIGHT()
{
	return HEIGHT;
}
