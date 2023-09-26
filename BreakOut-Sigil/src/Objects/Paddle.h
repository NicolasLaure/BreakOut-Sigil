#pragma once
#include "GameManagement/Utilities.h"
#include "GameManagement/Color.h"

namespace game
{
	using namespace colors;

	struct Paddle
	{
	public:
		bool isPlayer1{};
		Rect rect = { {}, 200, 25 };
		float baseSpeed = 1000;
		float speed = 1000;
		Color color = colorsData.WHITE;
		bool isModified = false;

		bool isColliding = false;
		const int paddleSpacingFromBottom = 40;
	};

	void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne);
	void PadMove(Paddle& paddle, Vector2 dir);
	void PadTranslate(Paddle& paddle, Vector2 newPosition);
	void PaddleDraw(Paddle paddle);

	void ResetPlayer(Paddle& player);

};