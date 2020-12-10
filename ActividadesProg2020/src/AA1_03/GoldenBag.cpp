#include "GoldenBag.h"

GoldenBag::GoldenBag()
{
	gbPosition = Rect(0, 0, 0, 0);
	gbRect = Rect(0, 0, 0, 0);
}

GoldenBag::GoldenBag(Rect _position, Rect _rect)
{
	gbPosition = _position;
	gbRect = _rect;
}

GoldenBag :: ~GoldenBag()
{

}



void GoldenBag::SetPosition(Rect _position)
{
	gbPosition = _position;
}

void GoldenBag::SetPosition(int _x, int _y)
{
	gbPosition.x = _x;
	gbPosition.y = _y;
}

void GoldenBag::SetRect(Rect _rect)
{
	gbRect = _rect;
}

void GoldenBag::SetRect(int _x, int _y)
{
	gbRect.x = _x;
	gbRect.y = _y;
}

Rect GoldenBag :: GetPosition()
{
	return gbPosition;
}

Rect GoldenBag:: GetRect()
{
	return gbRect;
}
