#pragma once
#include "GameManagement/Scenes.h"

namespace game
{
	struct SceneManager
	{
		Scenes scene;
		Scenes prevScene;
		bool enteredNewScene;

		bool isSinglePlayer;
		bool isPaused = false;
	};
};