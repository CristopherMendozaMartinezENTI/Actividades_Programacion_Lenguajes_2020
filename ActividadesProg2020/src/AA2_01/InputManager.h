#pragma once
#include "Types.h"

class InputManager
{
private:
	SDL_Event event;
	bool keyIsDown[(int)EKeys::TOTAL] = {};
	Vec2 mouseAxis;

public:
	InputManager();
	~InputManager();

	void Update();
	Vec2 returnMouseAxis();
	bool* returnKeyIsDown();
};

