#include "Player.h"

Player::Player()
{
}

Player::Player(int _nRows, int _nColumns, std::string _name, std::string _path, e_PlayerType _type)
{
	nColumns = _nColumns;
	nRows = _nRows;
	type = _type;

	score = 0;
	bombCD = COOLDOWN;
	isMoving = false;
	speed = 9;
	speedMultiplier = 1; //1.3
	spawBomb = false;

	texture = _path;
	rectID = _name + "Rect";
	positionID = _name + "Position";
	textureID = _name + "Texture";

	switch (type)
	{
	case e_PlayerType::P1:
		position.x = SCREEN_WIDTH / 2;
		position.y = SCREEN_HEIGHT / 2;

		break;
	case e_PlayerType::P2:
		position.x = SCREEN_WIDTH / 2 + 100;
		position.y = SCREEN_HEIGHT / 2;

		break;
	default:
		break;
	}
	Renderer::Instance()->LoadTexture(textureID, texture);
	Renderer::Instance()->LoadRect(rectID, Rect());
	Renderer::Instance()->LoadRect(positionID, Rect());
	textureWidth = Renderer::Instance()->GetTextureSize(textureID).x;
	textureHeight = Renderer::Instance()->GetTextureSize(textureID).y;

	frame.w = textureWidth / nColumns;
	frame.h = textureHeight / nRows;
	position.w = rect.w = frame.w;
	position.h = rect.h = frame.h;

}

Player::~Player()
{

}

void Player::Update(InputManager _input, float _deltaTime)
{
	bombCD -= _deltaTime;

	switch (type)
	{
	case e_PlayerType::P1:
		//Key Press

		if (_input.returnKeyIsDown()[(int)EKeys::UP])  direction.goUp = true;
		if (_input.returnKeyIsDown()[(int)EKeys::DOWN]) direction.goDown = true;
		if (_input.returnKeyIsDown()[(int)EKeys::RIGHT]) direction.goRight = true;
		if (_input.returnKeyIsDown()[(int)EKeys::LEFT]) direction.goLeft = true;
		if (_input.returnKeyIsDown()[(int)EKeys::KEYPAD_0]) SpawnBomb(true);
		//Key Release
		if (!_input.returnKeyIsDown()[(int)EKeys::UP]) direction.goUp = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::DOWN]) direction.goDown = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::RIGHT]) direction.goRight = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::LEFT]) direction.goLeft = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::KEYPAD_0]) SpawnBomb(false);

		break;
	case e_PlayerType::P2:
		//Key Press		
		if (_input.returnKeyIsDown()[(int)EKeys::W]) direction.goUp = true;
		if (_input.returnKeyIsDown()[(int)EKeys::S]) direction.goDown = true;
		if (_input.returnKeyIsDown()[(int)EKeys::D]) direction.goRight = true;
		if (_input.returnKeyIsDown()[(int)EKeys::A]) direction.goLeft = true;
		if (_input.returnKeyIsDown()[(int)EKeys::SPACE]) SpawnBomb(true);
		//Key Release
		if (!_input.returnKeyIsDown()[(int)EKeys::W]) direction.goUp = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::S]) direction.goDown = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::D]) direction.goRight = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::A]) direction.goLeft = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::SPACE]) SpawnBomb(false);
		break;
	default:
		break;
	}

	if (direction.goUp || direction.goDown || direction.goRight || direction.goLeft) isMoving = true;
	if (!direction.goUp && !direction.goDown && !direction.goRight && !direction.goLeft) isMoving = false;



	if (isMoving) {
		frameUpdate++;
		if (FPS / frameUpdate <= speed * speedMultiplier)
		{
			frameUpdate = 0;
			rect.x += frame.w;
			if (rect.x >= (frame.w * nColumns))
			{
				rect.x = 0;
			}
		}

		//Limites de la pantalla. Esto tendria que ir en otro sitio?  En la zona de mapa alomejor
		if (direction.goUp) {
			position.x += 0 * MOTION_SPEED;
			position.y += -1 * MOTION_SPEED;
			rect.y = frame.h * 0;
		}
		if (direction.goDown) {
			position.x += 0 * MOTION_SPEED;
			position.y += 1 * MOTION_SPEED;
			rect.y = frame.h * 2;
		}
		if (direction.goRight) {
			position.x += 1 * MOTION_SPEED;
			position.y += 0 * MOTION_SPEED;
			rect.y = frame.h * 3;
		}
		if (direction.goLeft) {
			position.x += -1 * MOTION_SPEED;
			position.y += 0 * MOTION_SPEED;
			rect.y = frame.h * 1;
		}
	}

	Renderer::Instance()->SetRect(rectID, rect);
	Renderer::Instance()->SetRect(positionID, position);


}

void Player::Draw()
{
	//Player Sprites
	Renderer::Instance()->PushSprite(textureID, rectID, positionID);
}

void Player::Reset()
{
	switch (type)
	{
	case e_PlayerType::P1:
		position.x = SCREEN_WIDTH / 2;
		position.y = SCREEN_HEIGHT / 2;
		//rect.x = frame.w * 3;
		//rect.y = frame.h * 0;

		break;
	case e_PlayerType::P2:
		position.x = SCREEN_WIDTH / 2;
		position.y = SCREEN_HEIGHT / 2;
		//rect.x = rect.y = 0;
		break;
	default:
		break;
	}

}

Rect Player::GetRect()
{
	return rect;
}

Rect Player::GetFrame()
{
	return frame;
}
Rect Player::GetPosition()
{
	return position;
}

e_PlayerType Player::GetPlayerType()
{
	return type;
}

Directions Player::GetDirection()
{
	return direction;
}

std::string Player::GetTexture()
{
	return texture;
}

bool Player::GetSpawnBomb()
{
	return spawBomb;
}
float Player::GetBombCD()
{
	return bombCD;
}
void Player::ResetBombCD()
{
	bombCD = COOLDOWN;
}

void Player::CanSpawnBomb()
{
	canSpawn = true;
}

void Player::SpawnBomb(bool _b)
{
	if (canSpawn && _b)
	{
		spawBomb = true;
		canSpawn = false;
	}
	else
	{
		spawBomb = false;
	}
}
