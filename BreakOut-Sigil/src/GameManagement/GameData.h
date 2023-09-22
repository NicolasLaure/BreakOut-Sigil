#pragma once
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "Objects/Brick.h"

struct GameData
{
	bool areRulesBeingShown = false;
	bool isPaused = false;
	Paddle player{};
	Ball ball{};

	bool isGameOver = false;
	bool justRestarted = false;
	bool objectsCanMove = false;

	bool isEscapePressed = false;

	int score = 0;
	int lives = 3;
	bool hasWon = false;

	int windowUpperLimit = 80;

	static const int bricksQty = 50;
	Brick bricks[bricksQty];
};