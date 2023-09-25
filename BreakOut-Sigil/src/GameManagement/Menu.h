#pragma once
#include "Objects/Button.h"
#include "GameManagement/Scenes.h"

namespace game
{
	void MenuStart();
	void MenuUpdate(Scenes& scene);
	void MenuDraw();

	struct MenuData
	{
		const char* title = "Breakout";
		int titleSize = 80;
		int titleLimitSpacing = 70;

		const char* credits = "Created By Nico Laure";
		int creditsSize = 30;

		static const int buttonsQty = 2;
		Button scenesButtons[buttonsQty] = {
			{{0,0}, Scenes::Game, "Play"},
			{{0,0}, Scenes::GameQuit,"Exit Game"}
		};

		bool isMousePressed = false;
		int windowLimitSpacing = 20;
		Button creditsButton = { {0,0}, Scenes::Menu, credits };
	};

};