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
	slCircleFill(ball.position.x, ball.position.y, ball.radius, 50);
}

void BallSwitchDirY(Ball& ball)
{
	ball.dir.y *= -1;
}

void BallSwitchDirX(Ball& ball)
{
	ball.dir.x *= -1;
}

void ResetBallSpeed(Ball& ball)
{
	ball.speed = ball.prevSpeed;
	ball.isSlowedDown = false;
}

void ResetBall(Ball& ball)
{
	ball.position = ball.startPosition;
	ball.speed = ball.baseSpeed;
	ball.isActive = true;
}

void DirOscillation(Ball& ball)
{
	float angle = acosf(ball.dir.x);

	float maxAngle = 175.0f;
	float minAngle = 5.0f;

	float rotationSpeed = 1 * slGetDeltaTime();

	if (angle + rotationSpeed >= deg2rad(maxAngle))
		ball.dirIncreasing = false;
	else if (angle - rotationSpeed <= deg2rad(minAngle))
		ball.dirIncreasing = true;

	if (ball.dirIncreasing)
		angle += rotationSpeed;
	else
		angle -= rotationSpeed;

	angle = Clampf(deg2rad(minAngle), deg2rad(maxAngle), angle);

	ball.dir = { cosf(angle), sinf(angle) };
}

void DirDraw(Ball& ball)
{
	slSetForeColor(colors.RED.r, colors.RED.g, colors.RED.b, 1);
	slLine(ball.position.x, ball.position.y, ball.position.x + ball.dir.x * 100, ball.position.y + ball.dir.y * 100);
}

void BallSpeedUp(Ball& ball)
{
	if (ball.speed + ball.speedIncrement < ball.maxSpeed)
		ball.speed += ball.speedIncrement;
	else
		ball.speed = ball.maxSpeed;
}