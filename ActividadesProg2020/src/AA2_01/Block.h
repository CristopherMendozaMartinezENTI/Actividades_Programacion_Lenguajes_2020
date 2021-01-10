#pragma once
#include "Types.h"
#include "GameObject.h"

class Block : public GameObject
{
private: 
	e_BlockType type;

public:
	bool erase;
	Block();
	Block(e_BlockType _type, std::string _name, Rect _position);
	~Block();

	void Update(InputManager _input, float _deltaTime);
	void Draw();
	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	std::string GetTexture();
	
};