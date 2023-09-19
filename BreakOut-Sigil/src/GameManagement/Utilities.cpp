#include "GameManagement/Utilities.h"
#include "GameManagement/Screen.h"

float Clampf(float min, float max, float value)
{
	if (value <= min)
		return min;
	else if (value >= max)
		return max;
	else
		return value;
}

Vector2 Vector2Add(Vector2 firstVector, Vector2 secondVector)
{
	return { firstVector.x + secondVector.x, firstVector.y + secondVector.y };
}

Vector2 Vector2Scale(Vector2 vector, float scaleMultiplier)
{
	return { vector.x * scaleMultiplier, vector.y * scaleMultiplier };
}

static const double PI = 4.0 * atan(1.0);

float deg2rad(double deg)
{
	return deg * PI / 180.0;
}
