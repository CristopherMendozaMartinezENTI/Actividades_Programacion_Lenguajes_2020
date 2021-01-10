#pragma once
#include "Types.h"
#include "GameObject.h"

class PowerUp: public GameObject
{
private:

	e_PowerupType type;
public:
	bool erase;
	PowerUp();
	PowerUp(e_PowerupType _type, std::string _name, Rect _position);
	~PowerUp();

	void Update(InputManager _input, float _deltaTime);
	void Draw();
	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	std::string GetTexture();
};

