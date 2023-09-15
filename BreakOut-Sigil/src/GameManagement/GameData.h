#pragma once
#include "Objects/Paddle.h"
#include "Objects/Ball.h"

struct GameData
{
	bool areRulesBeingShown = false;
	bool isPaused = false;
	Paddle paddle{};
	Ball ball{};

	bool isGameOver = false;
	bool justRestarted = false;

};