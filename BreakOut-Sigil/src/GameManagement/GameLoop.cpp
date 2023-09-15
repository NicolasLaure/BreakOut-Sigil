#include "GameManagement/ProgramLoop.h"
#include "GameManagement/Menu.h"
#include "GameManagement/SceneManager.h"
#include "Game.h"
using namespace std;

static SceneManager sceneManager;

void Initialize();
void ProgramLoop();

void RunProgram()
{
	Initialize();
	ProgramLoop();
	CloseWindow();
}

void Initialize()
{
	InitWindow(1280, 720, "Elemental Pong");
	SetExitKey(NULL);
	SetRandomSeed(NULL);

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
	} while (sceneManager.scene != Scenes::GameQuit && !WindowShouldClose());
}