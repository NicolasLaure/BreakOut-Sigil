#pragma once
#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "Objects/Brick.h"
#include "Objects/PowerUp.h"

namespace game
{
	struct GameData
	{
		bool areRulesBeingShown = false;
		bool isPaused = false;
		Paddle player{};
		Ball mainBall{};
		Ball secondBall{};
		Ball thirdBall{};

		bool isGameOver = false;
		bool justRestarted = false;
		bool objectsCanMove = false;

		bool isMouseRightPressed = false;
		bool isMouseLeftPressed = false;

		int score = 0;
		const int scoreMultiplier = 10;
		float scoreReductionTimer = 0;

		int lives = 3;
		int maxLives = 3;
		bool hasWon = false;

		int windowUpperLimit = 80;

		static const int bricksQty = 50;
		int brokenBricks = 0;

		bool hasTakenDamage = false;
		float hitFrameDuration = 0.5f;
		float hitTimer = 0;

		float powerUpRespawnCoolDown = 5.0f;
		float powerUpTimer = 0;

		SlowDown slowDownPowerUp = { 5,0,false };
		bool isMultiBallActive = false;
		int activeBalls = 1;
		Brick bricks[bricksQty];
	};

};