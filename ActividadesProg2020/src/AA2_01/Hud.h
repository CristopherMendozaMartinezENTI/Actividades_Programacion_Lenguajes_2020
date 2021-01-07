#pragma once
#include "Types.h"
#include "GameObject.h"


class Hud : public GameObject
{
private:


public:

	Hud();
	~Hud();

	void Update(InputManager _input);
	void Reset();


	Rect GetRect();
	Rect GetFrame();
	Vec2 GetPosition();
	std::string GetTexture();

};