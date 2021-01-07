#pragma once
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "SceneMenu.h"
#include "SceneGame.h"
#include "SceneRanking.h"

class GameManager
{
private:
	Scene* currentScene;
	e_GameStates state, lastState;
	InputManager inputs;
	AudioManager music;
	bool isRunning;

public:
	GameManager();
	~GameManager();
	void Run();
};

