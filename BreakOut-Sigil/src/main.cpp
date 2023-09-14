#include "sl.h"

void main()
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