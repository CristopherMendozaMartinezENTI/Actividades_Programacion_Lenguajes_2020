#pragma once
#include "Types.h"
#include "Collisions.h"
#include "GameObject.h"
class Player : public GameObject
{
public:

	int score;
	int speed;

private:
	
	bool isMoving;
	
	std::string avatarTexure;
	
	Directions direction;
	
	e_PlayerType type;

public:

	Player();
	Player(e_PlayerType _type);
	~Player();

	void Update(InputManager _input);
	void Reset();
	
	Rect GetRect();
	Rect GetFrame();
	Vec2 GetPosition();
	e_PlayerType GetPlayerType();
	Directions GetDirection();
	std::string GetAvatar();
};

