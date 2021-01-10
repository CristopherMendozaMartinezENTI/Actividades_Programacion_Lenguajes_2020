#pragma once
#include "Types.h"
#include "GameObject.h"
#include "Bomb.h"

class Player : public GameObject
{
public:
	int score;
	int speed, speedMultiplier;
	int HP;
	bool isMoving;

private:
	float bombCD;
	bool spawBomb, canSpawn;

	std::string test;

	Directions direction;

	e_PlayerType type;

public:
	bool isColliding;
	Player();
	Player(int _hp, Vec2 _position, int _nRows, int _nColumns, std::string _name, std::string _path, e_PlayerType _type);
	~Player();

	void Update(InputManager _input, float _deltaTime);

	void Draw();

	void Reset();

	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	e_PlayerType GetPlayerType();
	Directions GetDirection();
	std::string GetTexture();
	bool GetSpawnBomb();
	float GetBombCD();
	void ResetBombCD();
	void SpawnBomb(bool _b);
	void CanSpawnBomb();

};

