#pragma once
#include "Objects/Ball.h"
#include "Objects/Brick.h"

namespace game
{
	struct SlowDown
	{
		float duration{};
		float timer{};
		bool isActive{};
	};

	void MultiBall(bool& isMultiBallActive, Ball& ball, Ball& secondBall, Ball& thirdBall);
	void SpeedDown(SlowDown& slowDown, Ball& ball);
	void SpeedDown(SlowDown& slowDown, Ball& ball, Ball& secondBall, Ball& thirdBall);
	void HpUp(int& Hp);

	void PowerUpsUpdate(SlowDown& slowDown, Ball& ball);
	void PowerUpsUpdate(SlowDown& slowDown, Ball& ball, Ball& secondBall, Ball& thirdBall);

	void SetPowerUp(Brick bricks[], int bricksQty, int bricksLeft, bool isMultiBallActive);
};