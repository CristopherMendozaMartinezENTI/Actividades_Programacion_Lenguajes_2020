#include "Cursor.h"
Cursor::Cursor()
{
	cursorPosition.x = 0;
	cursorPosition.y = 0;
	cursorRect = Rect(0, 0, 0, 0);
}

Cursor::Cursor(Vec2 _position, Rect _rect)
{
	cursorPosition = _position;
	cursorRect = _rect;
}

Cursor :: ~Cursor()
{

}

void Cursor::Update(InputManager _input, float _deltaTime)
{
}

void Cursor::Draw()
{
}

void Cursor :: SetPosition(Vec2 _position)
{
	cursorPosition = _position;
}

void Cursor :: SetRect(Rect _rect)
{
	cursorRect = _rect;
}

void Cursor :: SetRect(int x, int y)
{
	cursorRect.x += x;
	cursorRect.y += y;
}

Vec2 Cursor :: GetPosition()
{
	return cursorPosition;
}

Rect Cursor :: GetRect()
{
	return cursorRect;
}
