#pragma once
#include "Objects/Ball.h"
#include "Objects/Brick.h"

struct SlowDown
{
	float duration{};
	float timer{};
	bool isActive{};
};

void MultiBall(bool& isMultiBallActive, Ball ball);
void SpeedDown(SlowDown& slowDown, Ball& ball);
void HpUp(int& Hp);

void PowerUpsUpdate(SlowDown& slowDown, Ball& ball);

void SetPowerUp(Brick bricks[], int brickQty);