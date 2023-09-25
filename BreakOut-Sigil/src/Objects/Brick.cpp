#include "Objects/Brick.h"

#include "sl.h"

#include "GameManagement/TextureManager.h"

namespace game
{
	void BricksDraw(Brick bricks[], int bricksQty)
	{
		for (int i = 0; i < bricksQty; i++)
		{
			if (bricks[i].isActive)
			{
				slSetForeColor(bricks[i].color.r, bricks[i].color.g, bricks[i].color.b, 1);
				switch (bricks[i].powerUp)
				{
				case PowerUpType::MultiBall:
					slSprite(GetTexture(TextureIdentifier::BrickMultiBall), bricks[i].rect.position.x, bricks[i].rect.position.y, bricks[i].rect.width, bricks[i].rect.height);
					break;
				case PowerUpType::SlowDown:
					slSprite(GetTexture(TextureIdentifier::BrickSlowDown), bricks[i].rect.position.x, bricks[i].rect.position.y, bricks[i].rect.width, bricks[i].rect.height);
					break;
				case PowerUpType::HpUp:
					slSprite(GetTexture(TextureIdentifier::BrickHpUp), bricks[i].rect.position.x, bricks[i].rect.position.y, bricks[i].rect.width, bricks[i].rect.height);
					break;
				case PowerUpType::None:
				default:
					slSprite(GetTexture(TextureIdentifier::Brick), bricks[i].rect.position.x, bricks[i].rect.position.y, bricks[i].rect.width, bricks[i].rect.height);
					break;
				}
				//slRectangleFill(bricks[i].rect.position.x, bricks[i].rect.position.y, bricks[i].rect.width, bricks[i].rect.height);
			}
		}
	}

	void BricksInit(Brick bricks[], int bricksQty)
	{
		for (int i = 0; i < bricksQty; i++)
		{
			bricks[i].rect.position = { 0, 0 };
			bricks[i].rect.width = 116;
			bricks[i].rect.height = 30;
		}
	}

	void ResetBricks(Brick bricks[], int bricksQty, int windowUpperLimit)
	{
		int windowLateralLimit = 15;
		int verticalDisplacement = bricks->rect.height + 10;
		int horizontalDisplacement = bricks->rect.width + 10;

		int counter = 0;
		for (int i = 0; i < bricksQty / 10; i++)
		{
			for (int j = i * 10; j < (i + 1) * 10; j++)
			{
				bricks[j].isActive = true;

				bricks[j].rect.position.x = bricks[j].rect.width / 2 + windowLateralLimit + (horizontalDisplacement)*counter;
				bricks[j].rect.position.y = GetScreenHeight() - bricks[j].rect.height / 2 - windowUpperLimit - verticalDisplacement * i;

				switch (i)
				{
				case 0:
					bricks[j].color = colorsData.YELLOW;
					break;
				case 1:
					bricks[j].color = colorsData.ORANGE;
					break;
				case 2:
					bricks[j].color = colorsData.BRICK;
					break;
				case 3:
					bricks[j].color = colorsData.CYAN;
					break;
				case 4:
					bricks[j].color = colorsData.PURPLE;
					break;
				default:
					break;
				}
				bricks[j].powerUp = PowerUpType::None;
				counter++;
				if (counter >= 10)
					counter = 0;
			}
		}
	}
};