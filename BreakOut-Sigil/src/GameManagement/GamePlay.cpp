#include "GameManagement/Gameplay.h"

#include "GameManagement/Utilities.h"
#include "GameManagement/GameData.h"
#include "GameManagement/TextureManager.h"
#include "Objects/Hud.h"
#include "Objects/PowerUp.h"

static GameData gd;

void GameStart();
void GameUpdate();
void GameDraw();

void PauseUpdate(Scenes& scene);
void PauseDraw();


void CollisionUpdate();
void BallBorderCollision(Ball& ball);
void BallPaddleCollision(Ball& ball, Paddle& player);
void BallBrickCollision(Ball& ball, Brick bricks[], int bricksQty);

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
	BallInit(gd.mainBall);
	BricksInit(gd.bricks, gd.bricksQty);
	ResetGameStats();
}

void GameUpdate()
{
	if (gd.objectsCanMove)
	{
		Vector2 paddleNewPos = { Clampf(0 + gd.player.rect.width / 2, GetScreenWidth() - gd.player.rect.width / 2, slGetMouseX()),  gd.player.paddleSpacingFromBottom };
		PadTranslate(gd.player, paddleNewPos);
		BallUpdate(gd.mainBall);
		if (gd.isMultiBallActive)
		{
			BallUpdate(gd.secondBall);
			BallUpdate(gd.thirdBall);
		}
	}
	else
	{
		DirOscillation(gd.mainBall);
		if (slGetMouseButton(0) && !gd.isMouseLeftPressed)
		{
			gd.objectsCanMove = true;
		}
		else if (!slGetMouseButton(0))
		{
			gd.isMouseLeftPressed = false;
		}
	}

	if (slGetMouseButton(1) && gd.isMouseRightPressed == false)
	{
		gd.isPaused = true;
		gd.isMouseRightPressed = true;
	}
	else if (!slGetMouseButton(1))
		gd.isMouseRightPressed = false;

	gd.powerUpTimer += slGetDeltaTime();

	if (gd.powerUpTimer >= gd.powerUpRespawnCoolDown)
	{
		gd.powerUpTimer = 0;
		SetPowerUp(gd.bricks, gd.bricksQty, gd.bricksQty - gd.brokenBricks, gd.isMultiBallActive);
	}

	if (gd.hasTakenDamage)
	{
		if (gd.hitTimer >= slGetTime())
			gd.hasTakenDamage = false;
	}
	if (gd.isMultiBallActive)
		PowerUpsUpdate(gd.slowDownPowerUp, gd.mainBall, gd.secondBall, gd.thirdBall);
	else
		PowerUpsUpdate(gd.slowDownPowerUp, gd.mainBall);

	CollisionUpdate();

	if (gd.lives <= 0)
	{
		gd.isGameOver = true;
		gd.isPaused = true;
	}
	if (gd.brokenBricks >= gd.bricksQty)
	{
		gd.isPaused = true;
		gd.hasWon = true;
	}
}

void GameDraw()
{
	//slSetBackColor(colors.LIGHT_GRAY.r, colors.LIGHT_GRAY.g, colors.LIGHT_GRAY.b);
	slSetForeColor(colors.WHITE.r, colors.WHITE.g, colors.WHITE.b, 1);
	slSprite(GetTexture(TextureIdentifier::BackGround), 0 + GetScreenWidth() / 2, 0 + GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight());

	if (gd.isMultiBallActive)
	{
		if (gd.mainBall.isActive)
			BallDraw(gd.mainBall);

		if (gd.secondBall.isActive)
			BallDraw(gd.secondBall);

		if (gd.thirdBall.isActive)
			BallDraw(gd.thirdBall);
	}
	else
		BallDraw(gd.mainBall);

	if (!gd.objectsCanMove)
		DirDraw(gd.mainBall);

	PaddleDraw(gd.player);
	BricksDraw(gd.bricks, gd.bricksQty);
	DrawHud(gd.lives, gd.score, gd.windowUpperLimit);
	if (gd.hasTakenDamage)
		slSprite(GetTexture(TextureIdentifier::PlayerHpHitted), GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight());
}

void PauseUpdate(Scenes& scene)
{
	if (gd.areRulesBeingShown)
	{
		if (slGetMouseButton(0) && !gd.isMouseLeftPressed)
		{
			gd.isMouseLeftPressed = true;
			gd.isPaused = false;
			gd.areRulesBeingShown = false;
		}
		else if (!slGetMouseButton(0))
			gd.isMouseLeftPressed = false;
	}
	else if (gd.isGameOver || gd.hasWon)
	{
		if (slGetMouseButton(1) && !gd.isMouseRightPressed)
		{
			gd.isGameOver = false;
			gd.isMouseRightPressed = true;
			scene = Scenes::Menu;
		}
		else if (!slGetMouseButton(1))
			gd.isMouseRightPressed = false;

		if (slGetKey(32) && !gd.isMouseLeftPressed)
		{
			gd.isMouseLeftPressed = true;
			gd.justRestarted = true;
		}
		else if (!slGetKey(32))
			gd.isMouseLeftPressed = false;

	}
	else
	{
		if (slGetMouseButton(1) && gd.isMouseRightPressed == false)
		{
			gd.isPaused = false;
			gd.isMouseRightPressed = true;
		}
		else if (!slGetMouseButton(1))
			gd.isMouseRightPressed = false;

		if (slGetKey(32) && !gd.isMouseLeftPressed)
		{
			gd.isMouseLeftPressed = true;
			scene = Scenes::Menu;
		}
		else if (!slGetKey(32))
			gd.isMouseLeftPressed = false;
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
		const char* pressAnyKeyText = "Click anywhere to start the game";

		int rulesPositionY = GetScreenHeight() / 2 + 50;
		slSetForeColor(colors.WHITE.r, colors.WHITE.g, colors.WHITE.b, 1);
		slSetFontSize(titleSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(rulesTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing, rulesTitle);
		slSetFontSize(rulesSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(winConditionText) / 2, rulesPositionY, winConditionText);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pressAnyKeyText) / 2, 0 + pressKeyWindowLimitSpacing, pressAnyKeyText);
	}
	else if (gd.isGameOver)
	{
		const char* gameOverTitle = "Game Over";
		int titleSize = 130;
		int gameOverSize = 40;
		const char* pressEscapeKeyText = "escape to go back to main menu";
		const char* pressSpaceKeyText = "space to restart the game";

		int rulesPositionY = GetScreenHeight() / 2 + 50;
		slSetForeColor(colors.WHITE.r, colors.WHITE.g, colors.WHITE.b, 1);
		slSetFontSize(titleSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(gameOverTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing, gameOverTitle);
		slSetFontSize(gameOverSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pressEscapeKeyText) / 2, 0 + pressKeyWindowLimitSpacing, pressEscapeKeyText);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pressSpaceKeyText) / 2, 0 + pressKeyWindowLimitSpacing / 2, pressSpaceKeyText);
	}
	else if (gd.hasWon)
	{
		const char* gameOverTitle = "Congratulations You Win!";
		int titleSize = 130;
		int gameOverSize = 40;
		const char* pressEscapeKeyText = "escape to go back to main menu";
		const char* pressSpaceKeyText = "space to restart the game";

		int rulesPositionY = GetScreenHeight() / 2 + 50;
		slSetForeColor(colors.WHITE.r, colors.WHITE.g, colors.WHITE.b, 1);
		slSetFontSize(titleSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(gameOverTitle) / 2, GetScreenHeight() - titleWindowLimitSpacing, gameOverTitle);
		slSetFontSize(gameOverSize);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pressEscapeKeyText) / 2, 0 + pressKeyWindowLimitSpacing, pressEscapeKeyText);
		slText(GetScreenWidth() / 2 - slGetTextWidth(pressSpaceKeyText) / 2, 0 + pressKeyWindowLimitSpacing / 2, pressSpaceKeyText);
	}
	else
	{
		const char* pauseTitle = "Game is Paused";
		int titleSize = 80;

		const char* backToMenuText = "Press Right click to go Unpause";
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

	if (gd.isMultiBallActive)
	{
		if (gd.mainBall.isActive)
		{
			BallBorderCollision(gd.mainBall);
			BallPaddleCollision(gd.mainBall, gd.player);
			BallBrickCollision(gd.mainBall, gd.bricks, gd.bricksQty);
		}
		if (gd.secondBall.isActive)
		{
			BallBorderCollision(gd.secondBall);
			BallPaddleCollision(gd.secondBall, gd.player);
			BallBrickCollision(gd.secondBall, gd.bricks, gd.bricksQty);
		}

		if (gd.thirdBall.isActive)
		{
			BallBorderCollision(gd.thirdBall);
			BallPaddleCollision(gd.thirdBall, gd.player);
			BallBrickCollision(gd.thirdBall, gd.bricks, gd.bricksQty);
		}

		if (!gd.mainBall.isActive && !gd.secondBall.isActive && !gd.thirdBall.isActive)
		{
			gd.isMultiBallActive = false;
			ResetBall(gd.mainBall);
			ResetPlayer(gd.player);
			gd.objectsCanMove = false;
		}
	}
	else
	{
		BallBorderCollision(gd.mainBall);
		BallPaddleCollision(gd.mainBall, gd.player);
		BallBrickCollision(gd.mainBall, gd.bricks, gd.bricksQty);
	}
}

void BallBorderCollision(Ball& ball)
{
	if (ball.position.y <= 0)
	{
		if (!gd.isMultiBallActive)
		{
			ResetBall(gd.mainBall);
			ResetPlayer(gd.player);
			gd.objectsCanMove = false;
		}
		else
		{
			ball.isActive = false;
		}
		gd.lives--;
		gd.hasTakenDamage = true;
		gd.hitTimer = slGetTime() + gd.hitFrameDuration;

		if (gd.lives <= 0)
		{
			gd.isGameOver = true;
			return;
		}
	}
	else if (ball.position.y + ball.radius >= GetScreenHeight() - gd.windowUpperLimit)
	{
		ball.position.y = GetScreenHeight() - gd.windowUpperLimit - ball.radius;
		BallSwitchDirY(ball);
	}

	if (ball.position.x - ball.radius <= 0)
	{
		ball.position.x = 0 + ball.radius;
		BallSwitchDirX(ball);
	}
	else if (ball.position.x >= GetScreenWidth())
	{
		ball.position.x = GetScreenWidth() - ball.radius;
		BallSwitchDirX(ball);
	}
}

void BallPaddleCollision(Ball& ball, Paddle& player)
{
	player.isColliding = false;

	if (ball.position.x + ball.radius >= player.rect.position.x - player.rect.width / 2 &&
		ball.position.x <= player.rect.position.x + player.rect.width / 2 &&
		ball.position.y + ball.radius >= player.rect.position.y - player.rect.height / 2 &&
		ball.position.y <= player.rect.position.y + player.rect.height / 2)
	{
		ball.position.y = player.rect.position.y + (player.rect.height / 2) + ball.radius;
		float angle = atanf((ball.position.x - player.rect.position.x) / (player.rect.height / 2 - player.rect.position.y)) + deg2rad(90);

		float maxAngle = 175.0f;
		float minAngle = 5.0f;

		angle = Clampf(deg2rad(minAngle), deg2rad(maxAngle), angle);

		ball.dir = { cosf(angle), sinf(angle) };

		if (!ball.isSlowedDown)
			BallSpeedUp(ball);

		player.isColliding = true;
	}
}

void BallBrickCollision(Ball& ball, Brick bricks[], int bricksQty)
{
	for (int i = 0; i < bricksQty; i++)
	{
		float brickLeft = bricks[i].rect.position.x - bricks[i].rect.width / 2;
		float brickRight = bricks[i].rect.position.x + bricks[i].rect.width / 2;
		float brickUp = bricks[i].rect.position.y + bricks[i].rect.height / 2;
		float brickDown = bricks[i].rect.position.y - bricks[i].rect.height / 2;

		if (ball.position.x + ball.radius >= brickLeft &&
			ball.position.x - ball.radius <= brickRight &&
			ball.position.y + ball.radius >= brickDown &&
			ball.position.y - ball.radius <= brickUp && bricks[i].isActive)
		{
			if (ball.position.x - ball.radius < brickLeft && ball.position.y < brickUp && ball.position.y > brickDown)
			{
				ball.position.x = brickLeft - ball.radius;
				if (ball.dir.x > 0)
					BallSwitchDirX(ball);
			}
			else if (ball.position.x + ball.radius > brickRight && ball.position.y < brickUp && ball.position.y > brickDown)
			{
				ball.position.x = brickRight + ball.radius;
				if (ball.dir.x < 0)
					BallSwitchDirX(ball);
			}
			else if (ball.position.y + ball.radius > brickUp && ball.position.x < brickRight && ball.position.x > brickLeft)
			{
				ball.position.y = brickUp + ball.radius;
				if (ball.dir.y < 0)
					BallSwitchDirY(ball);
			}
			else if (ball.position.y - ball.radius < brickDown && ball.position.x < brickRight && ball.position.x > brickLeft)
			{
				ball.position.y = brickDown - ball.radius;
				if (ball.dir.y > 0)
					BallSwitchDirY(ball);
			}
			else
			{
				if (ball.position.y - ball.radius < brickDown && ball.dir.y > 0)
					BallSwitchDirY(ball);
				else if (ball.position.y + ball.radius < brickUp && ball.dir.y < 0)
					BallSwitchDirY(ball);
			}

			switch (bricks[i].powerUp)
			{
			case PowerUpType::MultiBall:
				MultiBall(gd.isMultiBallActive, gd.mainBall, gd.secondBall, gd.thirdBall);
				break;
			case PowerUpType::SlowDown:
				if (gd.isMultiBallActive)
					SpeedDown(gd.slowDownPowerUp, gd.mainBall, gd.secondBall, gd.thirdBall);
				else
					SpeedDown(gd.slowDownPowerUp, gd.mainBall);
				break;
			case PowerUpType::HpUp:
				HpUp(gd.lives);
				break;
			case PowerUpType::None:
			default:

				break;
			}
			bricks[i].isActive = false;
			gd.brokenBricks++;
			break;
		}
	}
}

void ResetGameStats()
{
	gd.score = 0;
	gd.isGameOver = false;
	gd.lives = gd.maxLives;
	gd.hasWon = false;
	gd.isPaused = true;
	gd.areRulesBeingShown = true;
	gd.hasTakenDamage = false;
	//gd.isPowerUpSpawned = false;
	gd.mainBall.speed = gd.mainBall.baseSpeed;
	gd.isMultiBallActive = false;
	gd.objectsCanMove = false;
	gd.brokenBricks = 0;
	//gd.powerUpTimer = GetTime() + gd.powerUpSpawnRate;
	ResetBall(gd.mainBall);
	ResetPlayer(gd.player);
	ResetBricks(gd.bricks, gd.bricksQty, gd.windowUpperLimit);
}