#pragma once
#include "GameManagement/Utilities.h"
#include "Objects/PowerUpTypes.h"

namespace game
{
	struct Brick
	{
		Rect rect{};
		Color color{};
		bool isActive{};

		PowerUpType powerUp{ PowerUpType::None };
	};

	void BricksDraw(Brick bricks[], int bricksQty);

	void BricksInit(Brick bricks[], int bricksQty);
	void ResetBricks(Brick bricks[], int bricksQty, int windowUpperLimit);
};