#include "Block.h"

Block::Block()
{
}

Block::Block(e_BlockType _type, std::string _name, Rect _position)
{
	erase = false;
	hasPowerUp = false;
	destoyTime = 1.0f;
	nRows = 2;
	nColumns = 3;
	texture = "../../res/img/items.png";
	spriteSpeed = 15;

	rect = Rect(0, 0, 0, 0);
	frame = Rect(0, 0, 0, 0);
	position = _position;

	rectID = _name + "Rect";
	positionID = _name + "Position";
	textureID = _name + "Texture";
	type = _type;

	Renderer::Instance()->LoadTexture(textureID, texture);

	textureWidth = Renderer::Instance()->GetTextureSize(textureID).x;
	textureHeight = Renderer::Instance()->GetTextureSize(textureID).y;

	frame.w = textureWidth / nColumns;
	frame.h = textureHeight / nRows;
	position.w = rect.w = frame.w;
	position.h = rect.h = frame.h;

	switch (_type)
	{
	case e_BlockType::BLOCK:
		rect.x = frame.w * 1;
		rect.y = frame.h * 0;
		break;
	case e_BlockType::WALL:
		rect.x = frame.w * 0;
		rect.y = frame.h * 0;
		break;
	default:
		break;
	}

	//Que el bloque tenga o no power up, es completamente random en cada bloque, hay un 30% de que tenga un power up o no.

	int offset = 5;
	collisionRect.x = _position.x + offset;
	collisionRect.y = _position.y + offset;
	collisionRect.w = rect.w - offset;
	collisionRect.h = rect.h - offset;

	Renderer::Instance()->LoadRect(rectID, Rect());
	Renderer::Instance()->LoadRect(positionID, Rect());

	Renderer::Instance()->SetRect(rectID, rect);
	Renderer::Instance()->SetRect(positionID, position);
}

Block::~Block()
{
}

void Block::Update(InputManager _input, float _deltaTime)
{
	if (type == e_BlockType::DESTROYED)
	{
		rect.x = frame.w * 2;
		destoyTime -= _deltaTime;
		if (destoyTime <= 0)
		{
			type = e_BlockType::DEFAULT;
		}
	}
	Renderer::Instance()->SetRect(rectID, rect);
}

void Block::Draw()
{
	if (type != e_BlockType::DEFAULT)
	{
		Renderer::Instance()->PushSprite(textureID, rectID, positionID);
	}
}

Rect Block::GetPosition()
{
	return position;
}

Rect Block::GetCollisions()
{
	if (type != e_BlockType::DEFAULT)
	{
		return collisionRect;
	}
	else
		return Rect(0, 0, 0, 0);
}

e_BlockType Block::GetBlockType()
{
	return type;
}

void Block::Destroy()
{
	int random = rand() % 3 + 1;
	if (random == 2 && type == e_BlockType::BLOCK)
	{
		hasPowerUp = true;
	}
	type = e_BlockType::DESTROYED;
}

bool Block::GetHasPowerUp()
{
	return hasPowerUp;
}