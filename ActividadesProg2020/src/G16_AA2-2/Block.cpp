#include "Block.h"

Block::Block()
{
}

Block::Block(e_BlockType _type, std::string _name, Rect _position)
{
	erase = false;

	nRows = 2;
	nColumns = 3;
	texture = "../../res/img/items.png";
	
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
}

void Block::Draw()
{
	if(erase ==  false) Renderer::Instance()->PushSprite(textureID, rectID, positionID);
}

Rect Block::GetPosition()
{
	return position;
}
