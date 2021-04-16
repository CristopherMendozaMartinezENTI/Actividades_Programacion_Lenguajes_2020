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
	
	positionExplosion[0] = { position.x, position.y - 48, rect.w, rect.h };
	positionExplosion[4] = { position.x, position.y - (48 * 2) , rect.w , rect.h };
	
	positionExplosion[1] = { position.x + 48, position.y, rect.w, rect.h };
	positionExplosion[5] = { position.x + (48 * 2), position.y,rect.w, rect.h };
	
	positionExplosion[2] = { position.x , position.y + 48 , rect.w, rect.h };
	positionExplosion[6] = { position.x , position.y + (48 * 2), rect.w, rect.h };
	
	positionExplosion[3] = { position.x - 48, position.y, rect.w, rect.h };
	positionExplosion[7] = { position.x - (48 * 2), position.y, rect.w, rect.h };

	int offset = 5;

	rectColision[0] = { position.x + offset, position.y - 48 + offset, rect.w - offset , rect.h - offset };
	rectColision[4] = { position.x + offset, position.y - (48 * 2) + offset , rect.w - offset , rect.h - offset };
	
	rectColision[1] = { position.x + 48 + offset , position.y + offset , rect.w - offset , rect.h - offset };
	rectColision[5] = { position.x + (48 * 2) + offset, position.y + offset , rect.w - offset , rect.h - offset };
	
	rectColision[2] = { position.x + offset, position.y + 48 + offset, rect.w - offset  , rect.h - offset };
	rectColision[6] = { position.x + offset, position.y + (48 * 2) + offset, rect.w - offset  , rect.h - offset };
	
	rectColision[3] = { position.x - 48 + offset, position.y + offset , rect.w - offset, rect.h - offset };
	rectColision[7] = { position.x - (48 * 2) + offset, position.y + offset , rect.w - offset, rect.h - offset };

	//Esta variable es necesaria porque lso RECt que utiliza la bomba cuando esta explotando se tienen que diferenciar entre ellos y entre los players. String solo te permite añadir 2 valores entre ellos con el +.
	std::stringstream ss;

	for (int j = 0; j < 8; j++)
	{
		explosionIsActive[j] = true;
		ss << _name << "positionExplosionID" << j;
		positionExplosionID[j] = ss.str();
		Renderer::Instance()->LoadRect(positionExplosionID[j], positionExplosion[j]);
	}
	for (int i = 0; i < 8; i++)
	{
		ss << _name << "rectSpriteExplosionID" << i;
		rectSpriteExplosionID[i] = ss.str();
		Renderer::Instance()->LoadRect(rectSpriteExplosionID[i], Rect());
	}

}

Bomb::~Bomb()
{
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
			if (rectColision[i].y < 128) { explosionIsActive[i] = false; }

			else if (rectColision[i].y > SCREEN_HEIGHT - 91) { explosionIsActive[i] = false; }

			else if (rectColision[i].x > SCREEN_WIDTH - 91) { explosionIsActive[i] = false; }

			else if (rectColision[i].x < 48) { explosionIsActive[i] = false; }
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
			if (explosionIsActive[i])
			{
				Renderer::Instance()->PushSprite(textureID, rectSpriteExplosionID[i], positionExplosionID[i]);
			}
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

void Bomb::SetExplosionInactive(int n)
{
	switch (n)
	{
	case 0:
		explosionIsActive[4] = false;
		break;
	case 1:
		explosionIsActive[5] = false;
		break;
	case 2:
		explosionIsActive[6] = false;
		break;
	case 3:
		explosionIsActive[7] = false;
		break;

	}
}

bool* Bomb::GetExplosionActive()
{
	return explosionIsActive;
}

