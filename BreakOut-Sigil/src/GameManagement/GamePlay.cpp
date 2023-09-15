#include "GameManagement/Gameplay.h"
#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"
#include "GameManagement/Screen.h"

static GameData gd;

void GameStart();
void GameUpdate();
void GameDraw();

void PauseUpdate(Scenes& scene);
void PauseDraw();


void GameLoop(bool enteredNewScene, Scenes& scene)
{

	if (enteredNewScene || gd.justRestarted)
	{
		GameStart();
		gd.justRestarted = false;
	}

	if (!gd.isPaused)
	{
		GameUpdate();
		GameDraw();
	}
	else
	{
		PauseUpdate(scene);
		PauseDraw();
	}
}

void GameStart()
{
	const int paddleSpacingFromBottom = 40;
	gd.paddle.rect.position = { mainScreen.screenWidth / 2 - gd.paddle.rect.width / 2, 0 + paddleSpacingFromBottom };
}

void GameUpdate()
{
	if (IsKeyDown(KEY_D))
		PadMove(gd.paddle, { 1,0 });
	else if (IsKeyDown(KEY_A))
		PadMove(gd.paddle, { -1,0 });
}

void GameDraw()
{
	BeginDrawing();

	ClearBackground(WHITE);

	DrawCircle(gd.ball.position.x + gd.ball.size / 2, gd.ball.position.y + gd.ball.size / 2, gd.ball.size, gd.ball.color);
	DrawRectangleRounded({ gd.paddle.rect.position.x, gd.paddle.rect.position.y,  gd.paddle.rect.width,  gd.paddle.rect.height }, 0.5f, 0, gd.paddle.color);

	EndDrawing();
}

void PauseUpdate(Scenes& scene)
{
	if (gd.areRulesBeingShown)
	{
		if (GetKeyPressed())
		{
			gd.isPaused = false;
			gd.areRulesBeingShown = false;
		}
	}
	else if (gd.isGameOver)
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			gd.isGameOver = false;
			scene = Scenes::Menu;
		}
		else if (IsKeyPressed(KEY_SPACE))
		{
			gd.justRestarted = true;
		}
	}
	else
	{
		if (IsKeyPressed(KEY_ESCAPE))
			gd.isPaused = false;

		if (IsKeyPressed(KEY_SPACE))
			scene = Scenes::Menu;
	}
}
void PauseDraw()
{
	BeginDrawing();

	Color panelColor = BLACK;
	if (!gd.areRulesBeingShown)
		panelColor = ColorAlpha(panelColor, 0.010f);
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), panelColor);

	int titleWindowLimitSpacing = 20;
	int pressKeyWindowLimitSpacing = 80;

	if (gd.areRulesBeingShown)
	{
		const char* rulesTitle = "Rules";
		int titleSize = 120;
		int rulesSize = 40;
		const char* winConditionText = "destroy all bricks to win";
		const char* pressAnyKeyText = "Press any key to start the game";


		int rulesPositionY = GetScreenHeight() / 3 + 120;

		DrawText(rulesTitle, GetScreenWidth() / 2 - MeasureText(rulesTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);
		DrawText(winConditionText, GetScreenWidth() / 2 - MeasureText(winConditionText, rulesSize) / 2, GetScreenHeight() / 2, rulesSize, WHITE);
		DrawText(pressAnyKeyText, GetScreenWidth() / 2 - MeasureText(pressAnyKeyText, rulesSize) / 2, GetScreenHeight() - pressKeyWindowLimitSpacing, rulesSize, WHITE);
	}
	else
	{
		const char* pauseTitle = "Game is Paused";
		int titleSize = 120;

		const char* backToMenuText = "Press Space to go to Main Menu";
		int backToMenuSize = 60;
		DrawText(pauseTitle, GetScreenWidth() / 2 - MeasureText(pauseTitle, titleSize) / 2, titleWindowLimitSpacing, titleSize, WHITE);
		DrawText(backToMenuText, GetScreenWidth() / 2 - MeasureText(backToMenuText, backToMenuSize) / 2, GetScreenHeight() - pressKeyWindowLimitSpacing, backToMenuSize, WHITE);
	}

	EndDrawing();
}