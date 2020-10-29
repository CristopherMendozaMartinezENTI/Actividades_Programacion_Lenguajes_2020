#pragma once
#include "Types.h"
class PlayerClass
{
public:
	enum class PlayerType
	{
		P1, P2
	};

	Directions dir;

private:
	int textWidth, textHeight, frameWidth, frameHeight, frameTime, score;
	bool getCoins;
	bool isMoving;
	Rect playerRect, playerPosition;
	PlayerType type;

public:
	PlayerClass(int _textWidth, int _textHeight, int _frameWidth, int _frameHeight, Rect _playerRect, Rect _playerPosition, PlayerType _type);
	~PlayerClass();

	void Move();
	void Update();
	void ResetPlayer();
	
};

