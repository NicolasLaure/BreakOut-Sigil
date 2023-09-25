#include "Objects/Hud.h"

#include <string>

#include "GameManagement/Utilities.h"

using namespace std;

namespace game
{

	void DrawHud(int playerLives, int score, int upperLimit)
	{
		int height = upperLimit - 10;
		int width = GetScreenWidth();
		float fontSize = height / 2;
		slSetForeColor(colorsData.DARK_GRAY.r, colorsData.DARK_GRAY.g, colorsData.DARK_GRAY.b, 1);
		slRectangleFill(0 + width / 2, static_cast<double>(GetScreenHeight()) - height / 2, width, height);

		slSetForeColor(colorsData.RED.r, colorsData.RED.g, colorsData.RED.b, 1);
		slSetFontSize(fontSize);
		string livesText = "Lives: " + to_string(playerLives);
		slText(15, static_cast<double>(GetScreenHeight()) - height / 2 - slGetTextHeight(livesText.c_str()) / 2, livesText.c_str());
		string scoreText = "Score: " + to_string(score);

		int scoreLength = slGetTextWidth("9999") + slGetTextWidth(scoreText.c_str());
		slText(width - scoreLength - 15, static_cast<double>(GetScreenHeight()) - height / 2 - slGetTextHeight(scoreText.c_str()) / 2, scoreText.c_str());
	}

};