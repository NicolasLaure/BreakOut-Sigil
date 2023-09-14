#include "GameManagement/GameLoop.h"
#include "sl.h"
void RunGame()
{
	const char* title = "Breakout";
	int width = 1280;
	int height = 720;
	int fullScreen = 0;

	slWindow(width, height, title, fullScreen);

	while (!slShouldClose() && !slGetKey(SL_KEY_DELETE))
	{
		slRender();
	}
	slClose();
}