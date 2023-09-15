#pragma once
#include "GameManagement/Scenes.h"

struct SceneManager
{
	Scenes scene;
	Scenes prevScene;
	bool enteredNewScene;

	bool isSinglePlayer;
	bool isPaused = false;
};