#pragma once
#include "GameManagement/Utilities.h"

struct Brick
{
	Rect rect{};
	Color color{};
	bool isActive{};
};

void BricksDraw(Brick bricks[], int bricksQty);

void BricksInit(Brick bricks[], int bricksQty);
void ResetBricks(Brick bricks[], int bricksQty, int windowUpperLimit);
