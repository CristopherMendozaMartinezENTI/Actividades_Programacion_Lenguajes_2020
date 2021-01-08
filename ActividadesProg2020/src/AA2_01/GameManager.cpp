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

		if (inputs.returnKeyIsDown()[(int)EKeys::QUIT]) state = e_GameStates::QUIT;
		if (inputs.returnKeyIsDown()[(int)EKeys::ESC])  state = e_GameStates::QUIT;
		
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
			case e_GameStates::IN_GAME:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneGame();
				currentScene->state = e_GameStates::IN_GAME;
				break;
			case e_GameStates::QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
			state = currentScene->state;
		}
		currentScene->Draw();
		currentScene->Update(inputs);
		
		Renderer::Instance()->EndFrameControl();
	}
}