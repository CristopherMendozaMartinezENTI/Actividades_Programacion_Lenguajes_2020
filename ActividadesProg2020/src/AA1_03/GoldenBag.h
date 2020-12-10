#pragma once
#include "Types.h"

class GoldenBag
{
private:
	Rect gbPosition;
	Rect gbRect;

public:

	GoldenBag();
	GoldenBag(Rect _position, Rect _rect);
	~GoldenBag();
	
	void SetPosition(Rect _position);
	void SetPosition(int _x, int _y);
	void SetRect(Rect _rect);
	void SetRect(int x, int y);
	Rect GetPosition();
	Rect GetRect();
};

