#pragma once
#include "Types.h"
#include "GameObject.h"


class Block : public GameObject
{
private: 
	
	e_BlockType type;

public:

	Block();
	~Block();

	void Update(InputManager _input);
	Rect GetRect();
	Rect GetFrame();
	Vec2 GetPosition();
	std::string GetTexture();
	
};