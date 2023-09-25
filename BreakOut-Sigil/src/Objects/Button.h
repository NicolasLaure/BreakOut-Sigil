#pragma once
#include "GameManagement/Utilities.h"
#include "GameManagement/Scenes.h"
#include "GameManagement/Color.h"

namespace game
{
	struct Button
	{
		Rect buttonRect;
		Scenes sceneTo;
		const char* text;
		int fontSize = 70;
		Color textColor = colorsData.WHITE;
		Color currentTextColor = colorsData.WHITE;

		float textHeightSpacerMultiplier = 2.25f;
		float textPositionX = 15;
	};
};