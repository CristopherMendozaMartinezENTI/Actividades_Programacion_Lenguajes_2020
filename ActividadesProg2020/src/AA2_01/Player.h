#pragma once
#include "Types.h"
#include "Collisions.h"
#include "GameObject.h"
#include "Bomb.h"

class Player : public GameObject
{
public:

	int score;
	int speed, speedMultiplier;

private:
	
	bool isMoving, spawBomb, canSpawn;
	Bomb newBomb;
	
	std::string test;
	
	Directions direction;
	
	e_PlayerType type;

public:

	Player();
	Player(int _nRows, int _nColumns, std::string _name, std::string _path, e_PlayerType _type);
	~Player();

	void Update(InputManager _input);

	void Draw();

	void Reset();
	
	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	e_PlayerType GetPlayerType();
	Directions GetDirection();
	std::string GetTexture();
	bool GetSpawnBomb();
	void SpawnBomb(bool _b);
	void CanSpawnBomb();

};
