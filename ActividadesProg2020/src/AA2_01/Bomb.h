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

	Rect rectColision[8]; // 0-1 para arriba , 2-3 para derecha, 4-5 para abajo, 6-7 para izquierda
	
	int spriteSpeed;
	Rect rectSpriteExplosion[8];
	std::string rectSpriteExplosionID[8];
	
	Rect positionExplosion[8]; //0 - 1 para arriba, 2 - 3 para derecha, 4 - 5 para abajo, 6 - 7 para izquierda
	std::string positionExplosionID[8];

public:

	Bomb();
	Bomb(std::string _name, Rect _rect);
	~Bomb();

	void Update(InputManager _input, float _deltaTime);
	void Draw();
	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	Rect* GetExplosionRects();
	std::string GetTexture();
	e_BombState GetBombState();
	int GetRange();
};