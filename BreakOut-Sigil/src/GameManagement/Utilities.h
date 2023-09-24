#pragma once
#include "sl.h"
#include "GameManagement/Color.h"
#include <cmath>

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

static Colors colors;

float Clampf(float min, float max, float value);
float deg2rad(double deg);

Vector2 Vector2Scale(Vector2 vector, float scaleMultiplier);
Vector2 Vector2Add(Vector2 firstVector, Vector2 secondVector);

int GetScreenWidth();
int GetScreenHeight();