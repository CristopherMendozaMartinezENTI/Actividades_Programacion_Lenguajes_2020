#pragma once
#include "Types.h"
#include "GameObject.h"

class Bomb : public GameObject
{
private:

	int range, damage;
	std::string explodingTexture;
	bool changed;
	float lifeTime, explosionTime;
	e_BombState state;

	std::vector<Vec2> explosionWave;

public:

	Bomb();
	Bomb(std::string _name, Rect _rect);
	~Bomb();

	void Update(InputManager _input, float _deltaTime);
	void Draw();
	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	std::string GetTexture();
	e_BombState GetBombState();
};