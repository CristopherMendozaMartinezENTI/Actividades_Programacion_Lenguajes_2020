#pragma once
#include "PlayerClass.h"
class ScoreBoard
{
private:
	int scoreWidth, scoreHeight, 
		frameWidthScoreRight, 
		frameHeightScoreRight, 
		frameWidthScoreCenter,
		frameHeightScoreCenter,
		frameWidthScoreLeft,
		frameHeightScoreLeft,
		frameTimeRight,
		frameTimeCenter,
		frameTimeLeft;

	Rect scoreRectRight, scorePositionRight,
		 scoreRectCenter, scorePositionCenter,
		 scoreRectLeft, scorePositionLeft;

	PlayerClass _player;

public:
	ScoreBoard();
	ScoreBoard(int _scoreWidth, int _scoreHeight, PlayerClass _player);
	~ScoreBoard();

	void Update(PlayerClass &_player);
	void Reset();
	Rect returnScoreRectRight();
	Rect returnScoreRectCenter();
	Rect returnScoreRectLeft();
	Rect returnScorePositionRight();
	Rect returnScorePositionCenter();
	Rect returnScorePositionLeft();

};

