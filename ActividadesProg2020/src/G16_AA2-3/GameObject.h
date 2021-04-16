#pragma once
#include "Renderer.h"
#include "Collisions.h"

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
	virtual void Draw() = 0;
	Rect GetRect(){}
	Rect GetFrame(){}
	Rect GetPosition(){}
	std::string GetTexture(){}

};