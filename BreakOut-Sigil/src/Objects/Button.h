#pragma once
#include "GameManagement/Utilities.h"
#include "GameManagement/Scenes.h"
#include "GameManagement/Color.h"
struct Button
{
	Rect buttonRect;
	Scenes sceneTo;
	const char* text;
	int fontSize = 70;
	Color textColor = colors::WHITE;
	Color currentTextColor = colors::WHITE;


	float textHeightSpacerMultiplier = 1.6f;
	float textPositionX = 15;
};