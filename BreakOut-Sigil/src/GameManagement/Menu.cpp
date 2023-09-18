#include "GameManagement/Menu.h"

#include <iostream>

static MenuData menuData;

void ButtonCollisionCheck(Button& button);
void ButtonCollisionCheck(Button& button, Scenes& scene);

void MenuStart()
{
	menuData.title = "Elemental Pong";
	Vector2 textSize;

	slSetFontSize(menuData.creditsSize);
	textSize = { static_cast<float>(slGetTextWidth(menuData.creditsButton.text)),  static_cast<float>(slGetTextHeight(menuData.creditsButton.text)) };
	menuData.creditsButton.buttonRect = { { static_cast<float>(GetScreenWidth() - slGetTextWidth(menuData.credits) - menuData.windowLimitSpacing), static_cast<float>(GetScreenHeight() - menuData.creditsSize - menuData.windowLimitSpacing) },textSize.y, textSize.x };

	slSetFontSize(menuData.scenesButtons[0].fontSize);
	for (int i = 0; i < menuData.buttonsQty; i++)
	{
		textSize = { static_cast<float>(slGetTextWidth(menuData.scenesButtons[i].text)),  static_cast<float>(slGetTextHeight(menuData.scenesButtons[i].text)) };
		menuData.scenesButtons[i].buttonRect = { {menuData.scenesButtons[i].textPositionX, static_cast<float>(GetScreenHeight()) / 3 + i * menuData.scenesButtons[i].fontSize * menuData.scenesButtons[i].textHeightSpacerMultiplier}, textSize.y, textSize.x };
	}
}
void MenuUpdate(Scenes& scene)
{
	ButtonCollisionCheck(menuData.creditsButton);
	for (Button& button : menuData.scenesButtons)
	{
		ButtonCollisionCheck(button, scene);
	}

	if (!slGetMouseButton(0))
		menuData.isMousePressed = false;
}

void ButtonCollisionCheck(Button& button, Scenes& scene)
{
	Vector2 mousePos = { slGetMouseX(), slGetMouseY() };
	if (mousePos.x > button.buttonRect.position.x
		&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
		&& mousePos.y > button.buttonRect.position.y
		&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
	{
		button.currentTextColor = colors::GRAY;
		if (slGetMouseButton(0))
		{
			menuData.isMousePressed = true;
			button.currentTextColor = colors::DARK_GRAY;
		}

		if (!slGetMouseButton(0) && menuData.isMousePressed)
		{
			menuData.isMousePressed = false;
			scene = button.sceneTo;
		}
	}
	else
		button.currentTextColor = button.textColor;
}

void ButtonCollisionCheck(Button& button)
{
	Vector2 mousePos = { slGetMouseX(), slGetMouseY() };


	if (mousePos.x > button.buttonRect.position.x
		&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
		&& mousePos.y > button.buttonRect.position.y
		&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
	{
		button.currentTextColor = colors::GRAY;

		//mouse down
		if (slGetMouseButton(0))
		{
			menuData.isMousePressed = true;
			button.currentTextColor = colors::DARK_GRAY;
		}
		//mouse release 
		if (!slGetMouseButton(0) && menuData.isMousePressed)
		{
			menuData.isMousePressed = false;
			system("Chrome https://nico-drake.itch.io/ ");
		}
	}
	else
		button.currentTextColor = button.textColor;
}

void MenuDraw()
{
	slSetBackColor(colors::BLACK.r, colors::BLACK.g, colors::BLACK.b);

	slSetFontSize(menuData.titleSize);
	slSetForeColor(colors::WHITE.r, colors::WHITE.g, colors::WHITE.b, 1);
	slText(GetScreenWidth() / 2 - slGetTextWidth(menuData.title) / 2, menuData.windowLimitSpacing, menuData.title);

	slSetFontSize(menuData.creditsSize);
	slSetForeColor(menuData.creditsButton.currentTextColor.r, menuData.creditsButton.currentTextColor.g, menuData.creditsButton.currentTextColor.b, 1);
	slText(menuData.creditsButton.buttonRect.position.x, menuData.creditsButton.buttonRect.position.y, menuData.credits);

	for (Button& button : menuData.scenesButtons)
	{
		slSetFontSize(button.fontSize);
		slSetBackColor(colors::BLACK.r, colors::BLACK.g, colors::BLACK.b);
		slRectangleFill(button.buttonRect.position.x, button.buttonRect.position.y, button.buttonRect.width, button.buttonRect.height);
		slSetForeColor(button.currentTextColor.r, button.currentTextColor.g, button.currentTextColor.b, 1);
		slText(button.buttonRect.position.x, button.buttonRect.position.y, button.text);
	}
}