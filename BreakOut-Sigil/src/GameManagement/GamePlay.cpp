#include "GameManagement/Gameplay.h"
#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"

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
	slSetBackColor(colors::WHITE.r, colors::WHITE.g, colors::WHITE.b);
	const int paddleSpacingFromBottom = 40;
	gd.paddle.rect.position = { GetScreenWidth() / 2 - gd.paddle.rect.width / 2, 0 + paddleSpacingFromBottom };
}

void GameUpdate()
{
	Vector2 paddleNewPos = { Clampf(0, GetScreenWidth(), slGetMouseX()), 0 };
	PadTranslate(gd.paddle, paddleNewPos);
	/*if (IsKeyDown(KEY_D))
		PadMove(gd.paddle, { 1,0 });
	else if (IsKeyDown(KEY_A))
		PadMove(gd.paddle, { -1,0 });*/
}

void GameDraw()
{
	BallDraw(gd.ball);
	PaddleDraw(gd.paddle);
}

void PauseUpdate(Scenes& scene)
{
	if (gd.areRulesBeingShown)
	{
		if (slGetKey(SL_KEY_ENTER))
		{
			gd.isPaused = false;
			gd.areRulesBeingShown = false;
		}
	}
	else if (gd.isGameOver)
	{
		if (slGetKey(SL_KEY_ESCAPE))
		{
			gd.isGameOver = false;
			scene = Scenes::Menu;
		}
		else if (slGetKey(32))
		{
			gd.justRestarted = true;
		}
	}
	else
	{
		if (slGetKey(SL_KEY_ESCAPE))
			gd.isPaused = false;

		if (slGetKey(32))
			scene = Scenes::Menu;
	}
}
void PauseDraw()
{

	Color panelColor = colors::BLACK;
	slSetForeColor(panelColor.r, panelColor.g, panelColor.b, 1.0f);
	if (!gd.areRulesBeingShown)
		slSetForeColor(panelColor.r, panelColor.g, panelColor.b, 0.010f);

	slRectangleFill(gd.paddle.rect.position.x, gd.paddle.rect.position.y, gd.paddle.rect.width, gd.paddle.rect.height);

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

		slSetForeColor(colors::WHITE.r, colors::WHITE.g, colors::WHITE.b, 1);
		slSetFontSize(titleSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(rulesTitle) / 2, titleWindowLimitSpacing, rulesTitle);
		slSetFontSize(rulesSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(winConditionText) / 2, GetScreenWidth() / 2, winConditionText);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pressAnyKeyText) / 2, GetScreenHeight() - pressKeyWindowLimitSpacing, pressAnyKeyText);
	}
	else
	{
		const char* pauseTitle = "Game is Paused";
		int titleSize = 120;

		const char* backToMenuText = "Press Space to go to Main Menu";
		int backToMenuSize = 60;

		slSetForeColor(colors::WHITE.r, colors::WHITE.g, colors::WHITE.b, 1);
		slSetFontSize(titleSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pauseTitle) / 2, titleWindowLimitSpacing, pauseTitle);
		slSetFontSize(backToMenuSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(backToMenuText) / 2, GetScreenWidth() - pressKeyWindowLimitSpacing, backToMenuText);
	}
}