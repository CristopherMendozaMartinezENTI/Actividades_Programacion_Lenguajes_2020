#pragma once

#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "SceneMenu.h"
#include "SceneGame.h"

class GameManager
{
private:
	Scene* currentScene;
	e_GameStates state;
	InputManager inputs;
	AudioManager music;

public:
	GameManager();
	~GameManager();
	void Run();
};

