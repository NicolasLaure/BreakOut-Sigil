#pragma once
#include "Objects/Paddle.h"
#include "Objects/Ball.h"

struct GameData
{
	bool areRulesBeingShown = false;
	bool isPaused = false;
	Paddle player{};
	Ball ball{};

	bool isGameOver = false;
	bool justRestarted = false;
	bool areRulesShown = false;
	bool objectsCanMove = false;

	bool isEscapePressed = false;

	int score = 0;
	bool hasWon = false;
};