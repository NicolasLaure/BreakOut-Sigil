#pragma once
#include "Objects/Paddle.h"

struct Ball
{
public:
	Vector2 position{};
	Vector2 startPosition{};
	Vector2 dir = {-1,0};
	float size = 25;
	float baseSpeed = 500;
	float speed = 500;
	float prevSpeed = 500;
	float speedIncrement = 30;
	float maxSpeed = 1000;
	Paddle lastPaddleHitted;

	Color color = BLACK;
};

void BallInit(Ball& ball);
void BallUpdate(Ball& ball);

void RandomServe(Ball& ball, bool isFirstServe);

void BallDraw(Ball ball);

void BallSwitchDirY(Ball& ball);
void BallSwitchDirX(Ball& ball, Paddle player);
