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