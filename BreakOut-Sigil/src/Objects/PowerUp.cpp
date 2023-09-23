#include "Objects/PowerUp.h"
#include "Objects/PowerUpTypes.h"
#include <iostream>




void MultiBall(bool& isMultiBallActive, Ball ball)
{
	isMultiBallActive = true;
}

void SpeedDown(SlowDown& slowDown, Ball& ball)
{
	slowDown.isActive = true;
	ball.isSlowedDown = true;
	ball.prevSpeed = ball.speed;
	ball.speed *= 0.35f;
}

void HpUp(int& healthPoints)
{
	healthPoints++;
}

void SetPowerUp(Brick bricks[], int bricksQty)
{
	int randomIndex = 0;
	do
	{
		randomIndex = rand() % bricksQty;
	} while (bricks[randomIndex].powerUp != PowerUpType::None || !bricks[randomIndex].isActive);
	
	int activePowerUps = 0;

	for (int i = 0; i < bricksQty; i++)
	{
		if (bricks[i].powerUp != PowerUpType::None && bricks[i].isActive)
			activePowerUps++;
	}

	if (activePowerUps < 3)
	{
		int randomPowerUp = rand() % static_cast<int>(PowerUpType::None);
		bricks[randomIndex].powerUp = static_cast<PowerUpType>(randomPowerUp);
	}
}

void PowerUpsUpdate(SlowDown& slowDown, Ball& ball)
{
	if (slowDown.isActive)
	{
		slowDown.timer += slGetDeltaTime();
		if (slowDown.timer >= slowDown.duration)
		{
			slowDown.isActive = false;
			slowDown.timer = 0;
			ResetBallSpeed(ball);
		}
	}
}