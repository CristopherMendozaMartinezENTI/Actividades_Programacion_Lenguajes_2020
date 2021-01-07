#include "GameManager.h"

GameManager::GameManager()
{
	currentScene = new SceneGame();
	state = lastState = e_GameStates::IN_GAME;
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
		
		if (state != lastState)
		{
			switch (state)
			{
			/*
			case e_GameStates::MENU:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneMenu();
				break;
			*/
			
			case e_GameStates::IN_GAME:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneGame();
				break;
			/*
			case e_GameStates::RANKING:
				delete currentScene;
				Renderer::Instance()->ClearScene();
				currentScene = new SceneRanking();
			*/
			case e_GameStates::QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
			lastState = state;
		}
		currentScene->Draw();
		currentScene->Update(inputs);
		

		Renderer::Instance()->EndFrameControl();
	}
}