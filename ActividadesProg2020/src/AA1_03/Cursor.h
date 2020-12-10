#pragma once
#include "Types.h"


class Cursor
{
	Vec2 cursorPosition;
	Rect cursorRect;

public:

	Cursor();
	Cursor(Vec2 _position, Rect _rect);
	~Cursor();

	void SetPosition(Vec2 _position);
	void SetRect(Rect _rect);
	void SetRect(int x, int y);
	Vec2 GetPosition();
	Rect GetRect();
	
};