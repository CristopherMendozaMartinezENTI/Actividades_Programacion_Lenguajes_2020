#pragma once

#include "Types.h"
#include "InputManager.h"
#include "Renderer.h"

class GameObject
{
protected:
	Rect rect;
	Rect frame;
	Rect position;
	std::string texture, rectID, positionID, textureID;
	
	int textureWidth, textureHeight, nColumns, nRows;
	int frameUpdate;

public:
	virtual void Update(InputManager _input, float _deltaTime) = 0;
	Rect GetRect(){}
	Rect GetFrame(){}
	Vec2 GetPosition(){}
	std::string GetTexture(){}


};