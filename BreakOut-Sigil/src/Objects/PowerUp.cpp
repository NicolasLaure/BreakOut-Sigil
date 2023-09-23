#include "Objects/PowerUp.h"
#include "Objects/PowerUpTypes.h"
#include <iostream>

void MultiBall(bool& isMultiBallActive, Ball ball)
{
	isMultiBallActive = true;
}

void SlowDown(bool& isSlowDownActive, Ball& ball)
{
	isSlowDownActive = true;
	ball.speed *= 0.65f;
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

	int randomPowerUp = rand() % static_cast<int>(PowerUpType::None);
	bricks[randomIndex].powerUp = static_cast<PowerUpType>(randomPowerUp);
}