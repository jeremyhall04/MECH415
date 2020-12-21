#include "SceneHandler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
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

void SceneHandler::load_level(int level)
{
	std::ifstream fin;
	fin.open("src/SceneHandler/Level1.txt");
	if (!fin.is_open())
	{
		std::cout << "\nError in load_level; file open error";
		return;
	}
	fin >> N_enemies;
	std::cout << "\nN_enemies = " << N_enemies;
	for (int i = 0; i < 2; i++)
	{
		fin >> x[i];
		fin >> y[i];
	}

	fin.close();

	for (int i = 0; i < 2; i++)
	{
		std::cout << "\n" << x[i] << ", " << y[i];
	}

}

void SceneHandler::play_background_loop(char file_name[]) {

	PlaySoundA(file_name, NULL, SND_ASYNC | SND_LOOP);
}

void SceneHandler::play_shot_sound(char file_name[]) {

	PlaySoundA(file_name, NULL, SND_ASYNC);
	//This will be for player/enemy shots
}