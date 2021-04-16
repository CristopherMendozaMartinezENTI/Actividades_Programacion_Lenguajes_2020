#pragma once
#include "Types.h"
#include "GameObject.h"
#include "Bomb.h"

class Player : public GameObject
{
public:
	int HP;
	int score;
	bool isMoving;

private:
	float speed, speedMultiplier;
	float bombCD, turboTime, invulnerabilityTime;
	bool spawBomb, canSpawn, canTakeDmg;
	std::string test;
	Directions direction;
	e_PlayerType type;
	Rect collisionRect;
	Rect lastPosition;

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
	Rect GetRectCollider();
	void SetWinPosition();
	e_PlayerType GetPlayerType();
	Directions GetDirection();
	std::string GetTexture();
	bool GetSpawnBomb();
	float GetBombCD();
	void ResetBombCD();
	void SpawnBomb(bool _b);
	void CanSpawnBomb();
	void TakeDmg();
	void KilledEnemy();
	void DestroyedBlock();
	void SpeedUp();
	void ShieldUp();
	bool GetCanTakeDmg();
};

