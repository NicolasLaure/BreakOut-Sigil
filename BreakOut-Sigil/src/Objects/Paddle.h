#pragma once
#include "GameManagement/Utilities.h"

struct Paddle
{
public:
	bool isPlayer1{};
	Rect rect = { {}, 25, 200 };
	float baseSpeed = 1000;
	float speed = 1000;
	Color color = LIGHTGRAY;
	bool isModified = false;
};

void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne);
void PadMove(Paddle& paddle, Vector2 dir);
void PaddleDraw(Paddle player);