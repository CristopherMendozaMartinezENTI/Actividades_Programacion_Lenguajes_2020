#pragma once
#include "GameObject.h"
//#include "Collisions.h"

class Cursor : public GameObject
{
private: 
	Vec2 cursorPosition;
	Rect cursorRect;

public:

	Cursor();
	Cursor(Vec2 _position, Rect _rect);
	~Cursor();

	void Update(InputManager _input, float _deltaTime);
	void Draw();
	void SetPosition(Vec2 _position);
	void SetRect(Rect _rect);
	void SetRect(int x, int y);
	Rect GetRect();
	Rect GetFrame();
	Vec2 GetPosition();
	std::string GetTexture();
	
};