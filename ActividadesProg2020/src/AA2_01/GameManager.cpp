#include "GameManager.h"

GameManager::GameManager()
{
	currentScene = new SceneMenu();
	state = lastState = e_GameStates::MENU;
	isRunning = true;
}

GameManager::~GameManager()
{
	delete currentScene;
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
			case e_GameStates::MENU:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneMenu();
				currentScene->state = e_GameStates::MENU;
				break;
			case e_GameStates::IN_GAME_LEVEL1:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneGame(e_Levels::LEVEL_1);
				currentScene->state = e_GameStates::IN_GAME_LEVEL1;
				break;
			case e_GameStates::IN_GAME_LEVEL2:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneGame(e_Levels::LEVEL_2);
				currentScene->state = e_GameStates::IN_GAME_LEVEL2;
				break;
			case e_GameStates::RANKING:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneRanking();
				currentScene->state = e_GameStates::RANKING;
				break;
			case e_GameStates::QUIT:
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