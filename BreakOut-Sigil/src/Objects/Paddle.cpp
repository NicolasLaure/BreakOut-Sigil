#include "Objects/Paddle.h"

void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne)
{
	paddle.rect.position.x = position.x;
	paddle.rect.position.y = position.y;
	paddle.isPlayer1 = isPlayerOne;
}

void PadMove(Paddle& paddle, Vector2 dir)
{
	if (paddle.rect.position.x >= 0 && paddle.rect.position.x + paddle.rect.width <= GetScreenWidth())
		paddle.rect.position = Vector2Add(paddle.rect.position, Vector2Scale(dir, paddle.speed * GetFrameTime()));
	else if (paddle.rect.position.x < 0)
		paddle.rect.position.x = 0;
	else if (paddle.rect.position.x + paddle.rect.width > GetScreenWidth())
		paddle.rect.position.x = GetScreenWidth() - paddle.rect.width;
}

void PaddleDraw(Paddle paddle)
{
	DrawRectangle(paddle.rect.position.x, paddle.rect.position.y, paddle.rect.width, paddle.rect.height, paddle.color);
}