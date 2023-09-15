#include "GameManagement/GameLoop.h"
#include "GameManagement/Menu.h"
#include "GameManagement/SceneManager.h"
#include "Gameplay.h"
#include "GameManagement/Screen.h"
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
	slWindow(mainScreen.screenWidth, mainScreen.screenHeight, "Elemental Pong", 0);

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
		slRender();
		/*sceneManager.enteredNewScene = sceneManager.scene != sceneManager.prevScene;
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
		}*/
	} while (sceneManager.scene != Scenes::GameQuit && !slShouldClose());
}