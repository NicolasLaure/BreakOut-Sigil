#pragma once
#include "sl.h"
#include "GameManagement/Color.h"
struct Vector2
{
	float x{};
	float y{};
};

struct Rect
{
	Vector2 position{};
	float height{};
	float width{};
};

Color WHITE = { 252,252,252 };

float Clampf(float min, float max, float value);

Vector2 Vector2Scale(Vector2 vector, float scaleMultiplier);
Vector2 Vector2Add(Vector2 firstVector, Vector2 secondVector);

int GetScreenWidth();
int GetScreenHeight();