#include "Objects/Brick.h"
#include "sl.h"

void BricksDraw(Brick bricks[], int bricksQty)
{
	for (int i = 0; i < bricksQty; i++)
	{
		if (bricks[i].isActive)
		{
			slSetForeColor(bricks[i].color.r, bricks[i].color.g, bricks[i].color.b, 1);
			slRectangleFill(bricks[i].rect.position.x, bricks[i].rect.position.y, bricks[i].rect.width, bricks[i].rect.height);
		}
	}
}

void BricksInit(Brick bricks[], int bricksQty)
{
	for (int i = 0; i < bricksQty; i++)
	{
		bricks[i].rect.position = { 0, 0 };
		bricks[i].rect.width = GetScreenWidth() / 11;
		bricks[i].rect.height = 20;
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

			bricks[j].rect.position.x = bricks[j].rect.width / 2 + windowLateralLimit + (horizontalDisplacement) * counter;
			bricks[j].rect.position.y = GetScreenHeight() - bricks[j].rect.height / 2 - windowUpperLimit - verticalDisplacement * i;

			switch (i)
			{
			case 0:
				bricks[j].color = colors.YELLOW;
				break;
			case 1:
				bricks[j].color = colors.ORANGE;
				break;
			case 2:
				bricks[j].color = colors.BRICK;
				break;
			case 3:
				bricks[j].color = colors.CYAN;
				break;
			case 4:
				bricks[j].color = colors.PURPLE;
				break;
			default:
				break;
			}
			
			counter++;
			if (counter >= 10)
				counter = 0;
		}
	}
}