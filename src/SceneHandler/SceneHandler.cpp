#include "SceneHandler.h"
#include <iostream>
#include <fstream>
#include <string>

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") // links a windows library

SceneHandler::SceneHandler() { round_timer = COUNTDOWN_TIMER_START; }

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

float SceneHandler::get_round_timer()
{
	return round_timer;
}

void SceneHandler::play_background_loop(char file_name[]) 
{

	PlaySoundA(file_name, NULL, SND_ASYNC | SND_LOOP);
}