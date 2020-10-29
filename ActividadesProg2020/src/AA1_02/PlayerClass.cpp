#include "PlayerClass.h"



PlayerClass::PlayerClass(int _textWidth, int _textHeight, int _frameWidth, int _frameHeight, Rect _playerRect, Rect _playerPosition, PlayerType _type)
{
	textWidth = _textWidth;
	textHeight = _textHeight;
	frameWidth = _frameWidth;
	frameHeight = _frameHeight;
	playerRect = _playerRect;
	playerPosition = _playerPosition;
	type = _type;
	score = 0;
	isMoving = false;
	getCoins = false;

	frameWidth = textWidth / 12;
	frameHeight = textHeight / 8;

	switch (type)
	{
	case PlayerClass::PlayerType::P1:
		playerPosition.x = 800;
		playerPosition.y = 800;
		playerRect.x = frameWidth * 3;
		playerRect.y = 0;

		break;
	case PlayerClass::PlayerType::P2:
		playerPosition.x = 1100;
		playerPosition.y = 800;
		playerRect.x = playerRect.y = 0;
		break;
	default:
		break;
	}

	playerPosition.w = playerRect.w = frameWidth;
	playerPosition.h = playerRect.h = frameHeight;
	playerPosition.h = frameHeight * PLAYER_SIZE;
	playerPosition.w = frameWidth * PLAYER_SIZE;
}

PlayerClass::~PlayerClass()
{
}

void PlayerClass::Move()
{
	if (dir.goUp || dir.goDown || dir.goRight || dir.goLeft) isMoving = true;
	if (!dir.goUp && !dir.goDown && !dir.goRight && !dir.goLeft) isMoving = false;
}

void PlayerClass::Update()
{
	if (isMoving) {
		if (dir.goUp && playerPosition.y > 300) {
			playerPosition.x += 0 * MOTION_SPEED;
			playerPosition.y += -1 * MOTION_SPEED;
			playerRect.y = frameHeight * 3;
		}
		if (dir.goDown && playerPosition.y < SCREEN_HEIGHT - 70) {
			playerPosition.x += 0 * MOTION_SPEED;
			playerPosition.y += 1 * MOTION_SPEED;
			playerRect.y = frameHeight * 0;
		}
		if (dir.goRight && playerPosition.x < SCREEN_WIDTH - 60) {
			playerPosition.x += 1 * MOTION_SPEED;
			playerPosition.y += 0 * MOTION_SPEED;
			playerRect.y = frameHeight * 2;
		}
		if (dir.goLeft && playerPosition.x > 0) {
			playerPosition.x += -1 * MOTION_SPEED;
			playerPosition.y += 0 * MOTION_SPEED;
			playerRect.y = frameHeight * 1;
		}

		switch (type)
		{
		case PlayerClass::PlayerType::P1:
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				playerRect.x += frameWidth;
				if (playerRect.x >= (frameWidth * 6)) playerRect.x = frameWidth * 3;
			}
			break;
		case PlayerClass::PlayerType::P2:
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				playerRect.x += frameWidth;
				if (playerRect.x >= (frameWidth * 3)) playerRect.x = 0;
			}
			break;
		default:
			break;
		}
	}
}

void PlayerClass::ResetPlayer()
{
	switch (type)
	{
	case PlayerClass::PlayerType::P1:
		playerPosition.x = 800;
		playerPosition.y = 800;
		playerRect.x = frameWidth * 3;
		playerRect.y = 0;
		break;
	case PlayerClass::PlayerType::P2:
		playerPosition.x = 1100;
		playerPosition.y = 800;
		playerRect.x = playerRect.y = 0;
		break;
	default:
		break;
	}

}

Rect PlayerClass::returnRect()
{
	return playerRect;
}

Rect PlayerClass::returnPos()
{
	return playerPosition;
}