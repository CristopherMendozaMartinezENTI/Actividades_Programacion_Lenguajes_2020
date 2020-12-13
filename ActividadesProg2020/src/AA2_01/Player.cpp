#include "Player.h"



Player::Player()
{
}

Player::Player(int _textWidth, int _textHeight, e_PlayerType _type)
{
	textWidth = _textWidth;
	textHeight = _textHeight;
	type = _type;
	score = 0;
	isMoving = false;
	getCoin = false;

	frameWidth = textWidth / 12;
	frameHeight = textHeight / 8;

	switch (type)
	{
	case PlayerType::P1:
		playerPosition.x = 800;
		playerPosition.y = 800;
		playerRect.x = frameWidth * 3;
		playerRect.y = 0;

		break;
	case PlayerType::P2:
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

Player::~Player()
{
}

void Player::Update()
{
	if (dir.goUp || dir.goDown || dir.goRight || dir.goLeft) isMoving = true;
	if (!dir.goUp && !dir.goDown && !dir.goRight && !dir.goLeft) isMoving = false;

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
		case PlayerType::P1:
			frameTime++;
			if (FPS / frameTime <= 9)
			{
				frameTime = 0;
				playerRect.x += frameWidth;
				if (playerRect.x >= (frameWidth * 6)) playerRect.x = frameWidth * 3;
			}
			break;
		case PlayerType::P2:
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

void Player::Reset()
{
	switch (type)
	{
	case PlayerType::P1:
		playerPosition.x = 800;
		playerPosition.y = 800;
		playerRect.x = frameWidth * 3;
		playerRect.y = 0;
		break;
	case PlayerType::P2:
		playerPosition.x = 1100;
		playerPosition.y = 800;
		playerRect.x = playerRect.y = 0;
		break;
	default:
		break;
	}

}

void Player::setGetCoinsToTrue()
{
	getCoin = true;
}

void Player::setGetCoinsToFalse()
{
	getCoin = false;
}

bool Player::getCoinState()
{
	return getCoin;
}

PlayerType Player::getPlayerType()
{
	return type;
}

Rect Player::returnRect()
{
	return playerRect;
}

Rect Player::returnPos()
{
	return playerPosition;
}
