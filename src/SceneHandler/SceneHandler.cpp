#include "SceneHandler.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../../2D_graphics.h"
#include <Windows.h>
#include <mmsystem.h> // For audio functions
#pragma comment(lib, "winmm.lib") // links a windows library

/// <summary>
/// Constructor initializes round_timer
/// </summary>
SceneHandler::SceneHandler(Map* map) 
{ 
	this->map = map;
	round_timer = COUNTDOWN_TIMER_START; 
}

/// Deconstructor
SceneHandler::~SceneHandler() {}

/// <summary>
/// Decreases round timer by dt
/// 
/// Sets countdown timer to static number and stops decreasing
/// <summary>
void SceneHandler::round_timer_count()
{
	if (round_timer > 0.0)
	{
		round_timer -= COUNTDOWN_TIMER_DT;
	}
	if (round_timer <= 0.0)
	{
		round_timer = COUNTDOWN_TIMER_END;
	}
}

/// Returns round_timer
float SceneHandler::get_round_timer()
{
	return round_timer;
}

/// Returns the round timer as integer
int SceneHandler::get_round_timer_secs()
{
	return (int)round_timer;
}

/// Displays the countdown timer
void SceneHandler::display_countdown()
{
	if (get_round_timer() > 0.0f)
	{
		text("Round Begins In:", (double)map->get_screen_width() * 0.20, (double)map->get_screen_height() * 0.55, 1.5);
		text(get_round_timer_secs() + 1.0, (double)map->get_screen_width() * 0.60, (double)map->get_screen_height() * 0.55, 1.5);
	}
}

/// <summary>
/// This function plays the audio filed passed to it 
/// </summary>
/// <param name="file_name"> The wav file to be played is passed as the function argument </param>
void SceneHandler::play_audio_loop(char file_name[]) 
{
	PlaySoundA(file_name, NULL, SND_ASYNC | SND_LOOP);
}

/// <summary>
/// Command line menu.
/// 
/// Checks and sets input if valid.
/// 
/// Determines game mode:
/// 
/// 1 = SinglePlayer
/// 2 = Multiplayer
/// 3 = Test Mode (no enemies)
/// 4 = Exit program
/// 
/// </summary>
/// <returns> selected game mode </returns>
int SceneHandler::main_menu()
{
	std::cout << "\nMain Menu";
	int selection = 0;
	while (selection == 0)
	{
		std::cout << "\nType in an option: \n(1) Play Singleplayer\t(2) Play Multiplayer\t(3) Test Mode (SinglePlayer, No Enemies)\t(4) Exit\n";
		std::cin >> selection;
		if (selection != 1 && selection != 2 && selection != 3 && selection != 4)
		{
			std::cout << "\nError, invalid input";
			selection = 0;
		}
	}
	return selection;
}