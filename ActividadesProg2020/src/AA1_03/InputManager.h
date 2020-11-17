#pragma once
#include "Types.h"

class InputManager
{
private:
	SDL_Event event;
	bool keyIsDown[(int)EKeys::TOTAL] = {};
	bool keyIsUp[(int)EKeys::TOTAL] = {};
	Vec2 mouseAxis;
	bool windowIsOpen;

public:
	InputManager();
	~InputManager();

	void Update();
	Vec2 returnMouseAxis();
	bool returnwindowIsOpen();
	bool returnKeyIsDown();
	bool returnKeyIsUp();

	bool wasPressed(EKeys k);
	bool isPressed(EKeys k);
	void SetValue(EKeys k, bool value);
	void SetToFalse();
};

