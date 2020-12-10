#pragma once
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
class Scene
{
protected:
	//Colors
	std::map<std::string, Color> colors;
	//Texts
	std::map<std::string, Text> texts;
	//Rects
	std::map<std::string, Rect> rectangles;
	AudioManager music;
private:
public:
	gameStates state;
	bool isRuning;
	virtual void Update(InputManager& _inputs) = 0;
	virtual void Draw() = 0;
};

