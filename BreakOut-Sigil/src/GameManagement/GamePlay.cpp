#include "GameManagement/Gameplay.h"
#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"

static GameData gd;

void GameStart();
void GameUpdate();
void GameDraw();

void PauseUpdate(Scenes& scene);
void PauseDraw();

void ResetGameStats();

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
	BallInit(gd.ball);
	ResetGameStats();
}

void GameUpdate()
{
	if (gd.objectsCanMove)
	{
		Vector2 paddleNewPos = { Clampf(0 + gd.player.rect.width, GetScreenWidth() - gd.player.rect.width, slGetMouseX()),  gd.player.paddleSpacingFromBottom };
		PadTranslate(gd.player, paddleNewPos);

		if (slGetKey(SL_KEY_ESCAPE) && gd.isEscapePressed == false)
		{
			gd.isPaused = true;
			gd.isEscapePressed = true;
		}
		else if (!slGetKey(SL_KEY_ESCAPE))
			gd.isEscapePressed = false;

		BallUpdate(gd.ball);
	}
	else
	{
		if (slGetKey(32))
		{
			gd.objectsCanMove = true;
		}
		else
		{
			DirOscillation(gd.ball);
			DirDraw(gd.ball);
		}
	}
	/*if (IsKeyDown(KEY_D))
		PadMove(gd.paddle, { 1,0 });
	else if (IsKeyDown(KEY_A))
		PadMove(gd.paddle, { -1,0 });*/
}

void GameDraw()
{
	BallDraw(gd.ball);
	PaddleDraw(gd.player);
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
		if (slGetKey(SL_KEY_ESCAPE) && gd.isEscapePressed == false)
		{
			gd.isGameOver = false;
			gd.isEscapePressed = true;
			scene = Scenes::Menu;
		}
		else if (!slGetKey(SL_KEY_ESCAPE))
			gd.isEscapePressed = false;

		if (slGetKey(32))
		{
			gd.justRestarted = true;
		}
	}
	else
	{
		if (slGetKey(SL_KEY_ESCAPE) && gd.isEscapePressed == false)
		{
			gd.isPaused = false;
			gd.isEscapePressed = true;
		}
		else if (!slGetKey(SL_KEY_ESCAPE))
			gd.isEscapePressed = false;

		if (slGetKey(32))
			scene = Scenes::Menu;
	}
}

void PauseDraw()
{

	Color panelColor = colors.BLACK;
	slSetForeColor(panelColor.r, panelColor.g, panelColor.b, 1.0f);
	if (!gd.areRulesBeingShown)
		slSetForeColor(panelColor.r, panelColor.g, panelColor.b, 0.010f);

	slRectangleFill(gd.player.rect.position.x, gd.player.rect.position.y, gd.player.rect.width, gd.player.rect.height);

	int titleWindowLimitSpacing = 40;
	int pressKeyWindowLimitSpacing = 60;

	if (gd.areRulesBeingShown)
	{
		const char* rulesTitle = "Rules";
		int titleSize = 120;
		int rulesSize = 40;
		const char* winConditionText = "destroy all bricks to win";
		const char* pressAnyKeyText = "Press any key to start the game";

		int rulesPositionY = GetScreenHeight() / 3 - 120;

		slSetForeColor(colors.WHITE.r, colors.WHITE.g, colors.WHITE.b, 1);
		slSetFontSize(titleSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(rulesTitle) / 2, titleWindowLimitSpacing, rulesTitle);
		slSetFontSize(rulesSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(winConditionText) / 2, GetScreenWidth() / 2, winConditionText);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pressAnyKeyText) / 2, 0 + pressKeyWindowLimitSpacing, pressAnyKeyText);
	}
	else
	{
		const char* pauseTitle = "Game is Paused";
		int titleSize = 80;

		const char* backToMenuText = "Press Space to go to Main Menu";
		int backToMenuSize = 40;

		slSetForeColor(colors.WHITE.r, colors.WHITE.g, colors.WHITE.b, 1);
		slSetFontSize(titleSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pauseTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing - slGetTextHeight(pauseTitle) / 2, pauseTitle);
		slSetFontSize(backToMenuSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(backToMenuText) / 2, 0 + pressKeyWindowLimitSpacing, backToMenuText);
	}
}

void ResetGameStats()
{
	gd.score = 0;
	gd.isGameOver = false;
	gd.hasWon = false;
	gd.isPaused = false;
	gd.areRulesShown = true;
	//gd.isPowerUpSpawned = false;
	gd.ball.speed = gd.ball.baseSpeed;
	gd.objectsCanMove = false;
	//gd.powerUpTimer = GetTime() + gd.powerUpSpawnRate;
	ResetBall(gd.ball);
	ResetPlayer(gd.player);
}