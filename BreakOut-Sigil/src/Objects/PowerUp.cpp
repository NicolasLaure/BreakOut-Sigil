#include "Objects/PowerUp.h"
#include "Objects/PowerUpTypes.h"
#include <iostream>


void MultiBall(bool& isMultiBallActive, Ball& ball, Ball& secondBall, Ball& thirdBall)
{
	isMultiBallActive = true;
	secondBall.isActive = true;
	thirdBall.isActive = true;

	secondBall.speed = ball.speed;
	thirdBall.speed = ball.speed;
	secondBall.position = ball.position;
	thirdBall.position = ball.position;
	secondBall.dir.x = ball.dir.y;
	secondBall.dir.y = ball.dir.x * -1;
	thirdBall.dir.x = ball.dir.y;
	thirdBall.dir.y = ball.dir.x;
}

void SpeedDown(SlowDown& slowDown, Ball& ball)
{
	if (!slowDown.isActive)
	{
		ball.prevSpeed = ball.speed;
		ball.isSlowedDown = true;
		ball.prevSpeed = ball.speed;
		ball.speed *= 0.35f;
	}
	slowDown.isActive = true;
}

void SpeedDown(SlowDown& slowDown, Ball& ball, Ball& secondBall, Ball& thirdBall)
{
	if (!slowDown.isActive)
	{
		ball.prevSpeed = ball.speed;
		secondBall.prevSpeed = secondBall.speed;
		thirdBall.prevSpeed = thirdBall.speed;
		ball.isSlowedDown = true;
		ball.speed *= 0.35f;

		secondBall.isSlowedDown = true;
		secondBall.speed *= 0.35f;
		thirdBall.isSlowedDown = true;
		thirdBall.speed *= 0.35f;
	}
	slowDown.isActive = true;


}
void HpUp(int& healthPoints)
{
	healthPoints++;
}

void SetPowerUp(Brick bricks[], int bricksQty, int bricksLeft, bool isMultiBallActive)
{
	int spawnedMultiBalls = 0;
	if (bricksLeft > 8)
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
			if (bricks[i].powerUp == PowerUpType::MultiBall && bricks[i].isActive)
				spawnedMultiBalls++;
		}

		if (activePowerUps < 3)
		{
			int randomPowerUp = rand() % static_cast<int>(PowerUpType::None);
			if ((spawnedMultiBalls >= 1 && randomPowerUp == static_cast<int>(PowerUpType::MultiBall)) || isMultiBallActive)
			{
				do
				{
					randomPowerUp = rand() % static_cast<int>(PowerUpType::None);
				} while (randomPowerUp == static_cast<int>(PowerUpType::MultiBall));
			}

			bricks[randomIndex].powerUp = static_cast<PowerUpType>(randomPowerUp);
		}
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

void PowerUpsUpdate(SlowDown& slowDown, Ball& ball, Ball& secondBall, Ball& thirdBall)
{
	if (slowDown.isActive)
	{
		slowDown.timer += slGetDeltaTime();
		if (slowDown.timer >= slowDown.duration)
		{
			slowDown.isActive = false;
			slowDown.timer = 0;
			ResetBallSpeed(ball);
			ResetBallSpeed(secondBall);
			ResetBallSpeed(thirdBall);
		}
	}
}