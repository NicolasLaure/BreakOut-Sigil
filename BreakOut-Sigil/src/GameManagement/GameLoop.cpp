#include "GameManagement/GameLoop.h"

#include <iostream>

#include "GameManagement/Menu.h"
#include "GameManagement/SceneManager.h"
#include "GameManagement/Gameplay.h"
#include "GameManagement/Screen.h"
#include "GameManagement/TextureManager.h"

using namespace std;

static SceneManager sceneManager;

void Initialize();
void ProgramLoop();

void RunGame()
{
	Initialize();
	ProgramLoop();
	slClose();
}

void Initialize()
{
	slWindow(GetScreenWidth(), GetScreenHeight(), "Elemental Pong", 0);
	srand(time(nullptr));
	SetTextures();

	int font = slLoadFont("assets/ZenDots-Regular.ttf");
	slSetFont(font, 20);
	sceneManager.scene = Scenes::Menu;
	sceneManager.prevScene = Scenes::GameQuit;
	sceneManager.enteredNewScene = false;

	sceneManager.isSinglePlayer = false;
	sceneManager.isPaused = false;
}

void ProgramLoop()
{
	do
	{
		sceneManager.enteredNewScene = sceneManager.scene != sceneManager.prevScene;
		sceneManager.prevScene = sceneManager.scene;

		switch (sceneManager.scene)
		{
		case Scenes::GameQuit:
			break;
		case Scenes::Menu:
			if (sceneManager.enteredNewScene)
				MenuStart();

			MenuUpdate(sceneManager.scene);
			MenuDraw();
			break;
		case Scenes::Game:
			GameLoop(sceneManager.enteredNewScene, sceneManager.scene);
			break;
		default:
			break;
		}

		slRender();

	} while (sceneManager.scene != Scenes::GameQuit && !slShouldClose());
}
