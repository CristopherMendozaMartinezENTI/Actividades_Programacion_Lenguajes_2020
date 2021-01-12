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
	spriteSpeed = 9;
	range = 8;

	rect = Rect(0, 0, 0, 0);
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

	rectColision[0] = { position.x + 1, position.y - 48 + 1 , position.x + 48 - 1 , position.y };
	rectColision[1] = { position.x + 48, position.y + 1 , position.x + (48 * 2) - 1 , position.y + 48 - 1 };
	rectColision[2] = { position.x + 1, position.y + 48 , position.x + 48 - 1  , position.y + (48 * 2) - 1 };
	rectColision[3] = { position.x - 48 + 1, position.y + 1 , position.x , position.y + 48 - 1 };
	rectColision[4] = { position.x + 1, (position.y - (48 * 2)) + 1 , position.x + 48 - 1 , position.y - 48 };
	rectColision[5] = { position.x + (48 * 2), position.y + 1 , position.x + (48 * 3) - 1 , position.y + 48 - 1 };
	rectColision[6] = { position.x + 1, position.y + (48 * 2), position.x + 48 - 1  , position.y + (48 * 3) - 1 };
	rectColision[7] = { position.x - (48 * 2) + 1, position.y + 1 , position.x - 48  , position.y + 48 - 1 };

	
	for (int j = 0; j < 8; j++)
	{
		if (j == 2 || j == 3)
		{
			positionExplosion[j] = { rectColision[j].x , rectColision[j].y - 1, frame.w, frame.h };
		}
		else if (j == 4 || j == 5)
		{
			positionExplosion[j] = { rectColision[j].x - 1, rectColision[j].y, frame.w, frame.h };
		}
		else {
			positionExplosion[j] = { rectColision[j].x - 1, rectColision[j].y - 1, frame.w, frame.h };
		}


		positionExplosionID[j] = "positionExplosionID" + j;
		Renderer::Instance()->LoadRect(positionExplosionID[j], positionExplosion[j]);
	}
	for (int i = 0; i < 8; i++)
	{
		Renderer::Instance()->LoadRect(rectSpriteExplosionID[i], Rect());
	}

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

			for (int i = 0; i < 8; i++)
			{
				rectSpriteExplosion[i].w = frame.w;
				rectSpriteExplosion[i].h = frame.h;
			} 
			rectSpriteExplosion[0].y = frame.h * 6;
			rectSpriteExplosion[1].y = frame.h * 5;
			rectSpriteExplosion[2].y = frame.h * 6;
			rectSpriteExplosion[3].y = frame.h * 5;
			rectSpriteExplosion[4].y = frame.h * 3;
			rectSpriteExplosion[5].y = frame.h * 2;
			rectSpriteExplosion[6].y = frame.h * 4;
			rectSpriteExplosion[7].y = frame.h * 1;

			// Colocacion del "sprite"
			changed = true;
		}

		explosionTime -= _deltaTime;

		frameUpdate++;
		if (FPS / frameUpdate <= spriteSpeed)
		{
			frameUpdate = 0;
			rect.x += frame.w;
			for (int i = 0; i < 8; i++)
			{
				rectSpriteExplosion[i].x += frame.w;
			}

			if (rect.x >= (frame.w * nColumns))
			{
				rect.x = 0;
				for (int i = 0; i < 8; i++)
				{
					rectSpriteExplosion[i].x = 0;
				}
			}
		}

		if (explosionTime <= 0)
		{
			state = e_BombState::GONE;
		}

		for (int i = 0; i < 8; i++)
		{

		}
		break;

	case e_BombState::GONE:
		break;
	default:
		break;
	}

	Renderer::Instance()->SetRect(rectID, rect);
	Renderer::Instance()->SetRect(positionID, position);
	for (int i = 0; i < 8; i++)
	{
		Renderer::Instance()->SetRect(rectSpriteExplosionID[i], rectSpriteExplosion[i]);
	}
}

void Bomb::Draw()
{
	//Bomb Draw Sprites
	Renderer::Instance()->PushSprite(textureID, rectID, positionID);
	if (state == e_BombState::EXPLODING)
	{
		for (int i = 0; i < 8; i++)
		{
			Renderer::Instance()->PushSprite(textureID, rectSpriteExplosionID[i], positionExplosionID[i]);
		}
	}
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

Rect* Bomb::GetExplosionRects()
{
	return rectColision;
}

int Bomb::GetRange()
{
	return range;
}

