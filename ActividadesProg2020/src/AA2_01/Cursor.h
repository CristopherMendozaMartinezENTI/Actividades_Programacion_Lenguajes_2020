#pragma once
#include "Types.h"
#include "GameObject.h"


class Cursor : public GameObject
{
private: 


public:

	Cursor();
	Cursor(Vec2 _position, Rect _rect);
	~Cursor();

	void Update(InputManager _input);
	void SetPosition(Vec2 _position);
	void SetRect(Rect _rect);
	void SetRect(int x, int y);
	Rect GetRect();
	Rect GetFrame();
	Vec2 GetPosition();
	
};