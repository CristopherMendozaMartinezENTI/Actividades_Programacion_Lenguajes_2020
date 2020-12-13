#pragma once

#include "Types.h"

class InputManager {};

class GameObject
{
private:
	Rect rect;
	Rect frame;
	Vec2 position;
	std::string texture;

	int textureWidth, textureHeight, nColumns, nRows;
	int frameUpdate;

public:
	virtual void Update(InputManager _input) = 0;
	Rect GetRect(){}
	Rect GetFrame(){}
	Vec2 GetPosition(){}


};