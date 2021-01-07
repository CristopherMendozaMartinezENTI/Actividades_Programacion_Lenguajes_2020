#pragma once
#include "Types.h"
#include "GameObject.h"


class PowerUp: public GameObject
{
private:

	e_PowerupType type;

public:

	PowerUp();
	~PowerUp();

	void Update(InputManager _input);
	Rect GetRect();
	Rect GetFrame();
	Vec2 GetPosition();
	e_PowerupType GetType();
	std::string GetTexture();

};