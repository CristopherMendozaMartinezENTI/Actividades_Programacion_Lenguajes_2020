#pragma once
#include "Types.h"
#include "GameObject.h"


class Bomb : public GameObject
{
private:

	int range, damage;

public:

	Bomb();
	~Bomb();

	void Update(InputManager _input);
	Rect GetRect();
	Rect GetFrame();
	Vec2 GetPosition();

};