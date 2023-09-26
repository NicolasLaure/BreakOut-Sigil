#include "GameManagement/Menu.h"

#include <iostream>

namespace game
{
	MenuData menuData;


	void MenuStart()
	{
		Vector2 textSize = { 0,0 };

		slSetFontSize(menuData.creditsSize);
		textSize = { static_cast<float>(slGetTextWidth(menuData.creditsButton.text)),  static_cast<float>(slGetTextHeight(menuData.creditsButton.text)) };
		menuData.creditsButton.buttonRect = { { static_cast<float>(GetScreenWidth() - slGetTextWidth(menuData.credits) - menuData.windowLimitSpacing), 0.0f + menuData.creditsSize + menuData.windowLimitSpacing },textSize.x, textSize.y };

		slSetFontSize(menuData.scenesButtons[0].fontSize);
		for (int i = 0; i < menuData.buttonsQty; i++)
		{
			textSize = { static_cast<float>(slGetTextWidth(menuData.scenesButtons[i].text)),  static_cast<float>(slGetTextHeight(menuData.scenesButtons[i].text)) };
			menuData.scenesButtons[i].buttonRect = { {menuData.scenesButtons[i].textPositionX, static_cast<float>(GetScreenHeight()) / 2 - i * menuData.scenesButtons[i].fontSize * menuData.scenesButtons[i].textHeightSpacerMultiplier}, textSize.x, textSize.y };
		}
	}
	void MenuUpdate(Scenes& scene)
	{
		CreditsButtonCollisionCheck(menuData.creditsButton, menuData.isMousePressed);
		for (Button& button : menuData.scenesButtons)
		{
			ButtonCollisionCheck(button, scene, menuData.isMousePressed);
		}

		if (!slGetMouseButton(0))
			menuData.isMousePressed = false;
	}

	

	void MenuDraw()
	{
		slSetBackColor(colorsData.BLACK.r, colorsData.BLACK.g, colorsData.BLACK.b);
		slSetFontSize(menuData.titleSize);
		slSetForeColor(colorsData.WHITE.r, colorsData.WHITE.g, colorsData.WHITE.b, 1);
		slText(GetScreenWidth() / 2 - slGetTextWidth(menuData.title) / 2, GetScreenHeight() - menuData.titleLimitSpacing, menuData.title);

		slSetFontSize(menuData.creditsSize);
		slSetForeColor(menuData.creditsButton.currentTextColor.r, menuData.creditsButton.currentTextColor.g, menuData.creditsButton.currentTextColor.b, 1);
		slText(menuData.creditsButton.buttonRect.position.x, menuData.creditsButton.buttonRect.position.y, menuData.credits);

		for (Button& button : menuData.scenesButtons)
		{
			slSetFontSize(button.fontSize);
			slSetForeColor(button.currentTextColor.r, button.currentTextColor.g, button.currentTextColor.b, 1);
			slText(button.buttonRect.position.x, button.buttonRect.position.y, button.text);
		}
	}

};