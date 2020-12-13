#pragma once
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
class Scene
{
protected:
	
	std::string backgoundTexture;
	Rect backgoundRect;	
	clock_t lastTime;
	float deltaTime;

public:
	
	virtual void Update() = 0;
	void Draw(){}
	void UpdateDeltaTime(){}

};

