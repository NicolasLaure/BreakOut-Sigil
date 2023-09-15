#pragma once
#include "Objects/Button.h"
#include "GameManagement/Scenes.h"

void MenuStart();
void MenuUpdate(Scenes& scene);
void MenuDraw();

struct MenuData
{
	const char* title = "Elemental Pong";
	int titleSize = 120;

	const char* credits = "Created By Nico Laure";
	int creditsSize = 30;

	static const int buttonsQty = 3;
	Button scenesButtons[buttonsQty] = {
		{{0,0}, Scenes::Game, "Play"},
		{{0,0}, Scenes::GameQuit,"Exit Game"}
	};

	int windowLimitSpacing = 20;
	Button creditsButton = { {0,0}, Scenes::Menu, credits };
};