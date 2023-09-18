#include "GameManagement/Screen.h"


static Screen mainScreen = { 640,480 };

int GetScreenWidth()
{
	return mainScreen.screenWidth;
}
int GetScreenHeight()
{
	return mainScreen.screenHeight;
}