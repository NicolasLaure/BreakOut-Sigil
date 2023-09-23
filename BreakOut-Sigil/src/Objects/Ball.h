#pragma once
#include "GameManagement/Utilities.h"
#include "GameManagement/Color.h"

struct Ball
{
public:
	Vector2 position{};
	Vector2 startPosition{};
	Vector2 dir = {-1,0};
	float radius = 10;
	float baseSpeed = 300;
	float speed = 300;
	float prevSpeed = 300;
	float speedIncrement = 100;
	float maxSpeed = 750;

	bool dirIncreasing = false;

	Color color = colors.BLACK;
};

void BallInit(Ball& ball);
void BallUpdate(Ball& ball);

void BallDraw(Ball& ball);

void BallSwitchDirY(Ball& ball);
void BallSwitchDirX(Ball& ball);

void ResetBall(Ball& ball);

void DirOscillation(Ball& ball);
void DirDraw(Ball& ball);

void BallSpeedUp(Ball& ball);
