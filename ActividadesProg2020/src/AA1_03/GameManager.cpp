#include "GameManager.h"

GameManager::GameManager()
{
	currentScene = new SceneMenu();
	currentScene->state = gameStates::MENU;
	state = currentScene->state;

	isRunning = true;
}

GameManager::~GameManager()
{

}

void GameManager::Run()
{
	while (isRunning) {

		Renderer::Instance()->StartFrameControl();
		//Realizamos el update de los inputs y los mapeamos
		inputs.Update();
		
		if (state != currentScene->state)
		{
			switch (currentScene->state)
			{
			case gameStates::MENU:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneMenu();
				currentScene->state = gameStates::MENU;
				break;
			case gameStates::IN_GAME:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneGame();
				currentScene->state = gameStates::IN_GAME;
				break;
			case gameStates::QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
			state = currentScene->state;
		}

		currentScene->Update(inputs);
		currentScene->Draw();

		Renderer::Instance()->EndFrameControl();
	}
}

