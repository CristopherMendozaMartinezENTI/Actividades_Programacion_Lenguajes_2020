#pragma once
#include "Types.h"
#include <time.h>

enum class EKeys { DEFAULT, ESC, UP, DOWN, LEFT, RIGHT, W, A, S, D, MOUSE_LEFT, MOUSE_RIGHT, SPACE, P, TOTAL };

struct InputInfo {
private:
	bool keyPressed[(int)EKeys::TOTAL] = {};
	bool keyIsDown[(int)EKeys::TOTAL] = {};
	Vec2 mouseCoords;
	Vec2 screenSize;

	//TimeControl
	clock_t lastTime = clock();
	float deltaTime = 0.f;

public:
	void UpdateDeltaTime() 
	{
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
	}
	const float* GetDeltaTime() const { return &deltaTime; }


	bool wasPressed(EKeys k) { //Si se hace un return de cualquier numero que no sea 0 el valor sera true.
		return keyPressed[(int)k];
	}
	bool isPressed(EKeys k) {//Si se hace un return de cualquier numero que no sea 0 el valor sera true.
		return keyIsDown[(int)k];
	}
	void SetValue(EKeys k, bool value) {

		if (!wasPressed(k)) {
			keyIsDown[(int)k] = value;
		}
		else {
			keyIsDown[(int)k] = false;
		}
		keyPressed[(int)k] = value;

		keyIsDown[(int)k] = value;

	}
	void SetToFalse() {
		for (int i = 0; i < (int)EKeys::TOTAL; i++) {
			keyIsDown[i] = false;
		}
	}
	void SetMouseCoords(Vec2 _mouseCoords)
	{
		mouseCoords = _mouseCoords;
	}
	void SetScreenSize(Vec2 _screenSize)
	{
		screenSize = _screenSize;
	}
	Vec2 GetScreenSize()
	{
		return screenSize;
	}
};


