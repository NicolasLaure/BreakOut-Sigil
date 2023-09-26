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

	void CreditsButtonCollisionCheck(Button& button, bool& isMousePressed);
	void ButtonCollisionCheck(Button& button, Scenes& scene, bool& isMousePressed);
	void ResetButtonCollisionCheck(Button& button, bool& restartGame, bool& isMousePressed);
};