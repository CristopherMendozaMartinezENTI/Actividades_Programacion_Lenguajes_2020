#pragma once
#include "Utilities.h"
class PlayerClass
{

private:
	int textWidth, textHeight, frameWidth, frameHeight, frameTime;
	bool isMoving, getCoin;
	Rect playerRect, playerPosition;
	PlayerType type;

public:
	Directions dir;
	int score;

	PlayerClass();
	PlayerClass(int _textWidth, int _textHeight, PlayerType _type);
	~PlayerClass();

	void Update();
	void Reset();
	void setGetCoinsToTrue();
	void setGetCoinsToFalse();
	bool getCoinState();
	PlayerType getPlayerType();
	Rect returnRect();
	Rect returnPos();

};

