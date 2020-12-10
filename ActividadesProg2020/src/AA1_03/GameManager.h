#pragma once
#include "ScoreBoard.h"
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "SceneMenu.h"
#include "SceneGame.h"

class GameManager
{
private:
	Scene* currentScene;
	InputManager inputs;
	//ScoreBoards
	ScoreBoard boardP1;
	ScoreBoard boardP2;
	//Players
	PlayerClass playerClass1;
	PlayerClass playerClass2;
	gameStates state;
	bool isRunning;

public:
	GameManager();
	~GameManager();
	void Run();
};

