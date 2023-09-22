#include "GameManagement/Gameplay.h"
#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"
#include "GameManagement/TextureManager.h"

static GameData gd;

void GameStart();
void GameUpdate();
void GameDraw();

void PauseUpdate(Scenes& scene);
void PauseDraw();

void ResetGameStats();

void CollisionUpdate();
void BallBorderCollision();
void BallPaddleCollision(Ball& ball, Paddle& player);
void BallBrickCollision(Ball& ball, Brick bricks[], int bricksQty);

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
	BricksInit(gd.bricks, gd.bricksQty);
	ResetGameStats();
}

void GameUpdate()
{
	if (gd.objectsCanMove)
	{
		Vector2 paddleNewPos = { Clampf(0 + gd.player.rect.width / 2, GetScreenWidth() - gd.player.rect.width / 2, slGetMouseX()),  gd.player.paddleSpacingFromBottom };
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
		if (slGetMouseButton(0))
		{
			gd.objectsCanMove = true;
		}
		else
		{
			DirOscillation(gd.ball);
		}
	}

	CollisionUpdate();
}

void GameDraw()
{
	//slSetBackColor(colors.LIGHT_GRAY.r, colors.LIGHT_GRAY.g, colors.LIGHT_GRAY.b);
	slSetForeColor(colors.WHITE.r, colors.WHITE.g, colors.WHITE.b, 1);
	slSprite(GetTexture(TextureIdentifier::BackGround), 0 + GetScreenWidth() / 2, 0 + GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight());
	BallDraw(gd.ball);
	if (!gd.objectsCanMove)
		DirDraw(gd.ball);

	PaddleDraw(gd.player);
	BricksDraw(gd.bricks, gd.bricksQty);
}

void PauseUpdate(Scenes& scene)
{
	if (gd.areRulesBeingShown)
	{
		if (slGetKey(32))
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
	slSetForeColor(colors.BLACK.r, colors.BLACK.g, colors.BLACK.b, 0.10);

	if (!gd.areRulesBeingShown)
		slSetForeColor(colors.BLACK.r, colors.BLACK.g, colors.BLACK.b, 0.10);

	slRectangleFill(GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight());

	int titleWindowLimitSpacing = 120;
	int pressKeyWindowLimitSpacing = 60;

	if (gd.areRulesBeingShown)
	{
		const char* rulesTitle = "Rules";
		int titleSize = 150;
		int rulesSize = 40;
		const char* winConditionText = "destroy all bricks to win";
		const char* pressAnyKeyText = "Press space to start the game";

		int rulesPositionY = GetScreenHeight() / 2 + 50;
		slSetForeColor(colors.WHITE.r, colors.WHITE.g, colors.WHITE.b, 1);
		slSetFontSize(titleSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(rulesTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing, rulesTitle);
		slSetFontSize(rulesSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(winConditionText) / 2, rulesPositionY, winConditionText);
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

void CollisionUpdate()
{
	BallBorderCollision();
	BallPaddleCollision(gd.ball, gd.player);
	BallBrickCollision(gd.ball, gd.bricks, gd.bricksQty);
	/*if (gd.isPowerUpSpawned)
		BallPowerUpCollision();*/
}

void BallBorderCollision()
{
	if (gd.ball.position.y <= 0)
	{
		ResetBall(gd.ball);
		ResetPlayer(gd.player);
		gd.objectsCanMove = false;
		gd.lives--;
		if (gd.lives <= 0)
		{
			gd.isGameOver = true;
			return;
		}

		BallSwitchDirY(gd.ball);
	}
	else if (gd.ball.position.y + gd.ball.size >= GetScreenHeight())
	{
		gd.ball.position.y = GetScreenHeight() - gd.ball.size;
		BallSwitchDirY(gd.ball);
	}

	if (gd.ball.position.x - gd.ball.size <= 0)
	{
		gd.ball.position.x = 0 + gd.ball.size;
		BallSwitchDirX(gd.ball);
	}
	else if (gd.ball.position.x >= GetScreenWidth())
	{
		gd.ball.position.x = GetScreenWidth() - gd.ball.size;
		BallSwitchDirX(gd.ball);
	}
}

void BallPaddleCollision(Ball& ball, Paddle& player)
{
	if (ball.position.x + ball.size >= player.rect.position.x - player.rect.width / 2
		&& ball.position.x <= player.rect.position.x + player.rect.width / 2
		&& ball.position.y + ball.size >= player.rect.position.y - player.rect.height / 2
		&& ball.position.y <= player.rect.position.y + player.rect.height / 2)
	{
		ball.position.y = player.rect.position.y + (player.rect.height / 2) + ball.size;
		float angle = atanf((ball.position.x - player.rect.position.x) / (player.rect.height / 2 - player.rect.position.y)) + deg2rad(90);

		float maxAngle = 175.0f;
		float minAngle = 5.0f;

		angle = Clampf(deg2rad(minAngle), deg2rad(maxAngle), angle);

		ball.dir = { cosf(angle), sinf(angle) };

		BallSpeedUp(ball);
		player.isColliding = true;
	}
	else
		player.isColliding = false;

}

void BallBrickCollision(Ball& ball, Brick bricks[], int bricksQty)
{
	for (int i = 0; i < bricksQty; i++)
	{
		if (ball.position.x + ball.size >= bricks[i].rect.position.x - bricks[i].rect.width / 2
			&& ball.position.x <= bricks[i].rect.position.x + bricks[i].rect.width / 2
			&& ball.position.y + ball.size >= bricks[i].rect.position.y - bricks[i].rect.height / 2
			&& ball.position.y <= bricks[i].rect.position.y + bricks[i].rect.height / 2 && bricks[i].isActive)
		{
			bricks[i].isActive = false;
			BallSwitchDirY(ball);
		}
	}
}

void ResetGameStats()
{
	gd.score = 0;
	gd.isGameOver = false;
	gd.hasWon = false;
	gd.isPaused = true;
	gd.areRulesBeingShown = true;
	//gd.isPowerUpSpawned = false;
	gd.ball.speed = gd.ball.baseSpeed;
	gd.objectsCanMove = false;
	//gd.powerUpTimer = GetTime() + gd.powerUpSpawnRate;
	ResetBall(gd.ball);
	ResetPlayer(gd.player);
	ResetBricks(gd.bricks, gd.bricksQty);
}