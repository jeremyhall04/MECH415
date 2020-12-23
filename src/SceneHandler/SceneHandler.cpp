#include "SceneHandler.h"
#include <iostream>
#include <fstream>
#include <string>

#include <Windows.h>
#include <mmsystem.h> // For audio functions
#pragma comment(lib, "winmm.lib") // links a windows library

/// <summary>
/// Constructor initializes round_timer
/// </summary>
SceneHandler::SceneHandler() { round_timer = COUNTDOWN_TIMER_START; }

/// <summary>
/// Deconstructor for SceneHandler class
/// </summary>
SceneHandler::~SceneHandler(){}

/// <summary>
/// Decreases round timer by dt
/// 
/// if round time is at 0s or less sets round_timer to timer_end value
/// <>
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

/// <summary>
/// Function returns time remaining in round_timer
/// </summary>
/// <returns> return round_timer </returns>
float SceneHandler::get_round_timer()
{
	return round_timer;
}

/// <summary>
/// This function plays the audio filed passed to it 
/// </summary>
/// <param name="file_name"> The wav file to be played is passed as the function argument </param>
void SceneHandler::play_audio_loop(char file_name[]) 
{

	PlaySoundA(file_name, NULL, SND_ASYNC | SND_LOOP);
}