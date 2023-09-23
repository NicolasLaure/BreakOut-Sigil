#pragma once
#include "Objects/Ball.h"
#include "Objects/Brick.h"

void MultiBall(bool& isMultiBallActive, Ball ball);
void SlowDown(bool& isSlowDownActive, Ball& ball);
void HpUp(int& Hp);

void SetPowerUp(Brick bricks[], int brickQty);