#pragma once
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
class Scene
{
protected:
	 //Creemos que esto no tendria que ir aquí pero lo necesitamos para los inputs de los objetos.
	std::string backgoundTexture;
	Rect backgoundRect;	
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

