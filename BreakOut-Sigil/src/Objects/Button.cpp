#include "Button.h"

namespace game
{

	void ButtonCollisionCheck(Button& button, Scenes& scene, bool& isMousePressed)
	{
		Vector2 mousePos = { slGetMouseX(), slGetMouseY() };

		if (mousePos.x > button.buttonRect.position.x
			&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
			&& mousePos.y > button.buttonRect.position.y
			&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
		{
			button.currentTextColor = colorsData.GRAY;
			if (slGetMouseButton(0))
			{
				isMousePressed = true;
				button.currentTextColor = colorsData.DARK_GRAY;
			}

			if (!slGetMouseButton(0) && isMousePressed)
			{
				isMousePressed = false;
				scene = button.sceneTo;
			}
		}
		else
			button.currentTextColor = button.textColor;
	}

	void CreditsButtonCollisionCheck(Button& button, bool& isMousePressed)
	{
		Vector2 mousePos = { slGetMouseX(), slGetMouseY() };

		if (mousePos.x > button.buttonRect.position.x
			&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
			&& mousePos.y > button.buttonRect.position.y
			&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
		{
			button.currentTextColor = colorsData.GRAY;

			//mouse down
			if (slGetMouseButton(0))
			{
				isMousePressed = true;
				button.currentTextColor = colorsData.DARK_GRAY;
			}
			//mouse release 
			if (!slGetMouseButton(0) && isMousePressed)
			{
				isMousePressed = false;
				system("start chrome \"https://nico-drake.itch.io/ \" ");
			}
		}
		else
			button.currentTextColor = button.textColor;
	}

	void ResetButtonCollisionCheck(Button& button, bool& restartGame, bool& isMousePressed)
	{
		Vector2 mousePos = { slGetMouseX(), slGetMouseY() };

		if (mousePos.x > button.buttonRect.position.x
			&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
			&& mousePos.y > button.buttonRect.position.y
			&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
		{
			button.currentTextColor = colorsData.GRAY;

			//mouse down
			if (slGetMouseButton(0))
			{
				isMousePressed = true;
				button.currentTextColor = colorsData.DARK_GRAY;
			}
			//mouse release 
			if (!slGetMouseButton(0) && isMousePressed)
			{
				isMousePressed = false;
				restartGame = true;
			}
		}
		else
			button.currentTextColor = button.textColor;
	}
};