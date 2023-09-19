#include "GameManagement/Screen.h"


static Screen mainScreen = { 1280,720 };

int GetScreenWidth()
{
	return mainScreen.screenWidth;
}
int GetScreenHeight()
{
	return mainScreen.screenHeight;
}