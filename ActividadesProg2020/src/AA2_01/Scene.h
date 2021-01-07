#pragma once
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
class Scene
{
protected:
	 //Creemos que esto no tendria que ir aqu� pero lo necesitamos para los inputs de los objetos.
	std::string backgoundTexture;
	Rect backgoundRect;	
	clock_t lastTime;
	float deltaTime;

public:
	
	virtual void Update(InputManager input) = 0;
	virtual void Draw();
	virtual float UpdateDeltaTime();

};

