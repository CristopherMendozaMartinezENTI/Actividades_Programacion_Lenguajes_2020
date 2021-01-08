#include "Bomb.h"

Bomb::Bomb()
{

}
Bomb::Bomb(std::string _name, Rect _position)
{
	//std::cout << ("NewBomb Created") << std::endl;
	nRows = 2;
	nColumns = 3;
	texture = "../../res/img/items.png";
	explodingTexture = "../../res/img/explosion.png";
	state = e_BombState::ARMED;
	lifeTime = 2.5;
	explosionTime = 1.0;
	changed = false;

	rect = Rect(0,0,0,0);
	frame = Rect(0, 0, 0, 0);
	position = _position;

	rectID = _name + "Rect";
	positionID = _name + "Position";
	textureID = _name + "Texture";

	Renderer::Instance()->LoadTexture(textureID, texture);

	textureWidth = Renderer::Instance()->GetTextureSize(textureID).x;
	textureHeight = Renderer::Instance()->GetTextureSize(textureID).y;

	
	frame.w = textureWidth / nColumns;
	frame.h = textureHeight / nRows;
	position.w = rect.w = frame.w;
	position.h = rect.h = frame.h;

	rect.y = frame.h; // Colocacion del "sprite"

	Renderer::Instance()->LoadRect(rectID, Rect());
	Renderer::Instance()->LoadRect(positionID, Rect());

}

Bomb::~Bomb() //iMPORTANTE MIRAR ESTO A VER SI DA PROBLMEAS CON LA MEMORIA,  AUNQUE SEGURAMENTE ME VA A CRASHEAR PORQUE SOY UN TROZO DE BASURA HUMANA QUE NO SABE ESCRIBIR MAS DE 3 LINIAS DE CODIGO SI EQUIVOCARSE.
{
	//Renderer::Instance()->DeleteObject(textureID, rectName, positionName);
}

void Bomb::Update(InputManager _input, float _deltaTime)
{
	switch (state)
	{
	case e_BombState::ARMED:
		lifeTime -= _deltaTime;
		if (lifeTime <= 0)
		{
			state = e_BombState::EXPLODING;
		}
		break;
	case e_BombState::EXPLODING:
		if (!changed)
		{
			texture = explodingTexture;
			Renderer::Instance()->LoadTexture(textureID, texture);
			textureWidth = Renderer::Instance()->GetTextureSize(textureID).x;
			textureHeight = Renderer::Instance()->GetTextureSize(textureID).y;
			nRows = 7;
			nColumns = 4;

			frame.w = textureWidth / nColumns;
			frame.h = textureHeight / nRows;
			position.w = rect.w = frame.w;
			position.h = rect.h = frame.h;

			rect.x = frame.w * 0;
			rect.y = frame.h * 0;
			 // Colocacion del "sprite"
			changed = true;
		}
		explosionTime -= _deltaTime;
		if (explosionTime <= 0)
		{
			state = e_BombState::GONE;
		}
		break;

	case e_BombState::GONE:
			break;
	default:
		break;
	}

	Renderer::Instance()->SetRect(rectID, rect);
	Renderer::Instance()->SetRect(positionID, position);
}

void Bomb::Draw()
{
	//Bomb Draw Sprites
	Renderer::Instance()->PushSprite(textureID, rectID, positionID);
}

Rect Bomb::GetRect()
{
	return rect;
}

Rect Bomb::GetFrame()
{
	return frame;
}

Rect Bomb::GetPosition()
{
	return position;
}

std::string Bomb::GetTexture()
{
	return texture;
}
e_BombState Bomb::GetBombState()
{
	return state;
}