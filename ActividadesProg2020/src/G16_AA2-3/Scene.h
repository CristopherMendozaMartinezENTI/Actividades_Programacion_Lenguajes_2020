#pragma once
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
class Scene
{
protected:
	clock_t lastTime;
	float deltaTime;
	AudioManager music;

public:
	e_GameStates state;
	bool isRuning;
	virtual void Update(InputManager& _inputs) = 0;
	virtual void Draw();
	virtual float UpdateDeltaTime();
};

