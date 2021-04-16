#pragma once
#include "Types.h"
#include "Constants.h"

class InputManager
{
private:
	SDL_Event event;
	bool keyIsDown[(int)EKeys::TOTAL] = {};
	Vec2 mouseAxis;

public:
	std::string keyInput;
	InputManager();
	~InputManager();

	void Update();
	Vec2 returnMouseAxis();
	bool* returnKeyIsDown();
};

