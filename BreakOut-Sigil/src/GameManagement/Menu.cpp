#include "GameManagement/Menu.h"
static MenuData menuData;

void ButtonCollisionCheck(Button& button);
void ButtonCollisionCheck(Button& button, Scenes& scene);

void MenuStart()
{
	menuData.title = "Elemental Pong";
	Vector2 textSize;

	textSize = MeasureTextEx(GetFontDefault(), menuData.creditsButton.text, menuData.creditsButton.fontSize, menuData.creditsButton.fontSize * 0.1f);
	menuData.creditsButton.buttonRect = { { static_cast<float>(GetScreenWidth() - MeasureText(menuData.credits, menuData.creditsSize) - menuData.windowLimitSpacing), static_cast<float>(GetScreenHeight() - menuData.creditsSize - menuData.windowLimitSpacing) },textSize.y, textSize.x };

	for (int i = 0; i < menuData.buttonsQty; i++)
	{
		textSize = MeasureTextEx(GetFontDefault(), menuData.scenesButtons[i].text, menuData.scenesButtons[i].fontSize, menuData.scenesButtons[i].fontSize * 0.1f);
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
}

void ButtonCollisionCheck(Button& button, Scenes& scene)
{
	Vector2 mousePos = GetMousePosition();
	if (mousePos.x > button.buttonRect.position.x
		&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
		&& mousePos.y > button.buttonRect.position.y
		&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
	{
		button.currentTextColor = GRAY;
		if (IsMouseButtonDown(0))
		{
			button.currentTextColor = DARKGRAY;
		}
		if (IsMouseButtonReleased(0))
		{
			scene = button.sceneTo;
		}
	}
	else
		button.currentTextColor = button.textColor;
}

void ButtonCollisionCheck(Button& button)
{
	Vector2 mousePos = GetMousePosition();

	if (mousePos.x > button.buttonRect.position.x
		&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
		&& mousePos.y > button.buttonRect.position.y
		&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
	{
		button.currentTextColor = GRAY;
		if (IsMouseButtonDown(0))
		{
			button.currentTextColor = DARKGRAY;
		}
		if (IsMouseButtonReleased(0))
		{
			OpenURL("https://nico-drake.itch.io/");
		}
	}
	else
		button.currentTextColor = button.textColor;
}

void MenuDraw()
{
	BeginDrawing();

	ClearBackground(BLACK);
	DrawText(menuData.title, GetScreenWidth() / 2 - MeasureText(menuData.title, menuData.titleSize) / 2, menuData.windowLimitSpacing, menuData.titleSize, WHITE);
	DrawText(menuData.credits, menuData.creditsButton.buttonRect.position.x, menuData.creditsButton.buttonRect.position.y, menuData.creditsSize, menuData.creditsButton.currentTextColor);

	for (Button& button : menuData.scenesButtons)
	{
		DrawRectangle(button.buttonRect.position.x, button.buttonRect.position.y, button.buttonRect.width, button.buttonRect.height, BLACK);
		DrawText(button.text, button.buttonRect.position.x, button.buttonRect.position.y, button.fontSize, button.currentTextColor);
	}
	EndDrawing();
}