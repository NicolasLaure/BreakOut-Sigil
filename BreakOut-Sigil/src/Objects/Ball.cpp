#include "Objects/Ball.h"
#include <math.h>

void BallInit(Ball& ball)
{
	ball.startPosition = { static_cast<float>(GetScreenWidth()) / 2, 100.0f };
	ball.position = ball.startPosition;

	ball.dir = { 0,1 };
	//RandomServe(ball, true);
}

void BallUpdate(Ball& ball)
{
	ball.position = Vector2Add(ball.position, Vector2Scale(ball.dir, ball.speed * slGetDeltaTime()));
}

void BallDraw(Ball& ball)
{
	slSetForeColor(ball.color.r, ball.color.g, ball.color.b, 1.0f);
	slCircleFill(ball.position.x, ball.position.y, ball.size, 50);
}

void RandomServe(Ball& ball, bool isFirstServe)
{
	/*float value = 0;
	float randX;
	if (isFirstServe)
	{
		value = GetRandomValue(-9, 9) * 0.1f;
		if (value <= 0.3f && value >= 0) value = 0.4f;
		if (value >= -0.3f && value < 0) value = -0.4f;
		randX = value;
	}
	else
		randX = ball.dir.x;
	if (GetRandomValue(0, 1) == 0)
	{
		if (value < 0)
			value = value * -1 - 1;
		else
			value -= 1.0f;
	}
	else
	{
		if (value < 0)
			value += 1.0f;
		else
			value = 1.0f - value;
	}

	float randY = value;
	ball.dir = Vector2Normalize({ randX, randY });*/
}

void BallSwitchDirY(Ball& ball)
{
	if (ball.position.y <= 0)
	{
		ball.position.y = 0;
		ball.dir.y *= -1;
	}
	else if (ball.position.y + ball.size >= GetScreenHeight())
	{
		ball.position.y = GetScreenHeight() - ball.size;
		ball.dir.y *= -1;
	}
}

void BallSwitchDirX(Ball& ball)
{
	ball.dir.x *= -1;
	if (ball.speed + 20 <= ball.maxSpeed)
		ball.speed += 20;
}

void ResetBall(Ball& ball)
{
	ball.position = ball.startPosition;
}

void DirOscillation(Ball& ball)
{

	float x = ball.dir.x;

	float rotationSpeed = 1 * slGetDeltaTime();

	if (x + rotationSpeed >= 1)
		ball.dirIncreasing = false;
	else if (x - rotationSpeed <= -1)
		ball.dirIncreasing = true;

	if (ball.dirIncreasing)
		x += rotationSpeed;
	else
		x -= rotationSpeed;

	x = Clampf(-1.0f, 1.0f, x);

	ball.dir = { x, static_cast<float>(1 - sqrt(pow(x, 2)))};
}

void DirDraw(Ball& ball)
{
	slLine(ball.position.x, ball.position.y, ball.position.x + ball.dir.x * 100, ball.position.y + ball.dir.y * 100);
}
