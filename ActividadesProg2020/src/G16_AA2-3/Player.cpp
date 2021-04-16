#include "Player.h"

Player::Player()
{
}

Player::Player(int _hp, Vec2 _position, int _nRows, int _nColumns, std::string _name, std::string _path, e_PlayerType _type)
{
	HP = _hp;
	invulnerabilityTime = 3.0;
	turboTime = 0;
	position.x = _position.x;
	position.y = _position.y;
	nRows = _nRows;
	nColumns = _nColumns;
	rectID = _name + "Rect";
	positionID = _name + "Position";
	textureID = _name + "Texture";
	texture = _path;
	type = _type;

	score = 0;
	bombCD = COOLDOWN;
	isMoving = false;
	speed = 9;
	speedMultiplier = 1; //1.3
	spawBomb = false;
	isColliding = false;


	Renderer::Instance()->LoadTexture(textureID, texture);
	Renderer::Instance()->LoadRect(rectID, Rect());
	Renderer::Instance()->LoadRect(positionID, Rect());
	textureWidth = Renderer::Instance()->GetTextureSize(textureID).x;
	textureHeight = Renderer::Instance()->GetTextureSize(textureID).y;

	frame.w = textureWidth / nColumns;
	frame.h = textureHeight / nRows;
	position.w = rect.w = frame.w;
	position.h = rect.h = frame.h;

	lastPosition = position;

	if (type == e_PlayerType::P1)
	{
		rect.y = frame.h * 2;
		rect.x = frame.w * 1;
	}
	else
	{
		rect.y = frame.h * 0;
		rect.x = frame.w * 1;
	}

}

Player::~Player()
{

}

void Player::Update(InputManager _input, float _deltaTime)
{
	bombCD -= _deltaTime;

	if (invulnerabilityTime <= 0) {
		canTakeDmg = true;
		invulnerabilityTime = 0;
	}	else {
		canTakeDmg = false;
		invulnerabilityTime -= _deltaTime;
	}

	if (turboTime <= 0) {
		speedMultiplier = 1.0f;
		turboTime = 0;
	}	else {
		turboTime -= _deltaTime;
	}

	switch (type)
	{
	case e_PlayerType::P1:
		//Key Press
		if (_input.returnKeyIsDown()[(int)EKeys::UP])  direction.goUp = true;
		if (_input.returnKeyIsDown()[(int)EKeys::DOWN]) direction.goDown = true;
		if (_input.returnKeyIsDown()[(int)EKeys::RIGHT]) direction.goRight = true;
		if (_input.returnKeyIsDown()[(int)EKeys::LEFT]) direction.goLeft = true;
		if (_input.returnKeyIsDown()[(int)EKeys::LCTRL]) SpawnBomb(true);
		//Key Release
		if (!_input.returnKeyIsDown()[(int)EKeys::UP]) direction.goUp = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::DOWN]) direction.goDown = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::RIGHT]) direction.goRight = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::LEFT]) direction.goLeft = false;
		if (!_input.returnKeyIsDown()[(int)EKeys::LCTRL]) SpawnBomb(false);

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

	if (isMoving && !isColliding) {
		lastPosition = position;
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

		//Limites de la pantalla.
		if (direction.goUp && position.y > 128) {
			position.x += 0 * MOTION_SPEED;
			position.y += -speedMultiplier * MOTION_SPEED;
			rect.y = frame.h * 0;
		}
		else if (direction.goDown && position.y < SCREEN_HEIGHT - 96) {
			position.x += 0 * MOTION_SPEED;
			position.y += speedMultiplier * MOTION_SPEED;
			rect.y = frame.h * 2;
		}
		else if (direction.goRight && position.x < SCREEN_WIDTH - 96) {
			position.x += speedMultiplier * MOTION_SPEED;
			position.y += 0 * MOTION_SPEED;
			rect.y = frame.h * 3;
		}
		else if (direction.goLeft && position.x > 48) {
			position.x += -speedMultiplier * MOTION_SPEED;
			position.y += 0 * MOTION_SPEED;
			rect.y = frame.h * 1;
		}
	}

	//Si el Pj no esta colisionando, todos los calculos hechos antes se aplican y el pj se mueve. Sino se queda todo igual.
	if (isColliding)
	{
		position.x = lastPosition.x;
		position.y = lastPosition.y;
		isColliding = false;
	}

	//Actualizacion de la hitbox (con ofset) que calcula las colisiones del personaje.
	collisionRect.x = position.x + 5;
	collisionRect.y = position.y + 5;
	collisionRect.w = position.w - 5;
	collisionRect.h = position.h - 5;

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

Rect Player::GetRectCollider()
{
	return collisionRect;
}

void Player::SetWinPosition()
{
	position.x = 500;
	position.y = 400;
	rect.y = frame.h * 2;
	rect.x = frame.w * 1;
	Renderer::Instance()->SetRect(rectID, rect);
	Renderer::Instance()->SetRect(positionID, position);
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

void Player::TakeDmg()
{
	HP -= 1;
	invulnerabilityTime = 5.0;
}

void Player::KilledEnemy()
{
	score += 100;
}

void Player::DestroyedBlock()
{
	score += 15;
}

void Player::SpeedUp()
{
	turboTime = 10.0f;
	speedMultiplier = 1.8;
}

void Player::ShieldUp()
{
	invulnerabilityTime = 10.0f;
}

bool Player::GetCanTakeDmg()
{
	return canTakeDmg;
}