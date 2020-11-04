#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
}

ScoreBoard::ScoreBoard(int _scoreWidth, int _scoreHeight, PlayerClass _player)
{
	scoreWidth = _scoreWidth;
	scoreHeight = _scoreHeight;

	PlayerType type;
	type = _player.getPlayerType();

	frameWidthScoreRight = scoreWidth / 10;
	frameHeightScoreRight = scoreHeight / 1;

	frameWidthScoreCenter = scoreWidth / 10;
	frameHeightScoreCenter = scoreHeight / 1;

	frameWidthScoreLeft = scoreWidth / 10;
	frameHeightScoreLeft = scoreHeight / 1;

	frameTimeRight = 0;
	frameTimeCenter = 0;
	frameTimeLeft = 0;

	switch (type)
	{
	case PlayerType::P1:
		scorePositionRight.x = 650;
		scorePositionRight.y = 40;

		scorePositionCenter.x = 550;
		scorePositionCenter.y = 40;

		scorePositionLeft.x = 450;
		scorePositionLeft.y = 40;

		break;
	case PlayerType::P2:
		scorePositionRight.x = 650;
		scorePositionRight.y = 130;

		scorePositionCenter.x = 550;
		scorePositionCenter.y = 130;

		scorePositionLeft.x = 450;
		scorePositionLeft.y = 130;

		break;
	default:
		break;
	}


	scoreRectRight.x = scoreRectRight.y = 0;
	scorePositionRight.w = scoreRectRight.w = frameWidthScoreRight;
	scorePositionRight.h = scoreRectRight.h = frameHeightScoreRight;

	scoreRectCenter.x = scoreRectCenter.y = 0;
	scorePositionCenter.w = scoreRectCenter.w = frameWidthScoreCenter;
	scorePositionCenter.h = scoreRectCenter.h = frameHeightScoreCenter;

	scoreRectLeft.x = scoreRectLeft.y = 0;
	scorePositionLeft.w = scoreRectLeft.w = frameWidthScoreLeft;
	scorePositionLeft.h = scoreRectLeft.h = frameHeightScoreLeft;

}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Update(PlayerClass &_player)
{
	if (_player.getCoinState())
	{
		frameTimeRight++;
		if (FPS / frameTimeRight <= 9) {
			_player.setGetCoinsToFalse();
			frameTimeRight = 0;
			scoreRectRight.x += frameWidthScoreRight;
			if (scoreRectRight.x >= (scoreWidth)) {
				scoreRectRight.x = 0;
				scoreRectCenter.x += frameWidthScoreCenter;
				if (scoreRectCenter.x >= (scoreWidth)) {
					scoreRectCenter.x = 0;
					scoreRectRight.x = 0;
					scoreRectLeft.x += frameWidthScoreLeft;
					if (scoreRectLeft.x >= (scoreWidth)) scoreRectLeft.x = 0;
				}
			}
		}
	
	}
}

void ScoreBoard::Reset()
{
	scoreRectRight.x = 0;
	scoreRectCenter.x = 0;
	scoreRectLeft.x = 0;
}

Rect ScoreBoard::returnScoreRectRight()
{
	return scoreRectRight;
}

Rect ScoreBoard::returnScoreRectCenter()
{
	return scoreRectCenter;
}

Rect ScoreBoard::returnScoreRectLeft()
{
	return scoreRectLeft;
}

Rect ScoreBoard::returnScorePositionRight()
{
	return scorePositionRight;
}

Rect ScoreBoard::returnScorePositionCenter()
{
	return scorePositionCenter;
}

Rect ScoreBoard::returnScorePositionLeft()
{
	return scorePositionLeft;
}
