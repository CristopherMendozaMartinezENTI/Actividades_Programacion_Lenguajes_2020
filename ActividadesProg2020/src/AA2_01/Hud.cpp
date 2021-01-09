#include "Hud.h"

Hud::Hud()
{

}

Hud::Hud(std::string _avatar1, std::string _avatar2, int _hp1, int _hp2, float _time)
{
	//std::cout << ("NewBomb Created") << std::endl;
	Avatar[0] = _avatar1;
	Avatar[1] = _avatar2;
	HP[0] = _hp1;
	HP[1] = _hp2;
	score[0] = 0;
	score[1] = 0;
	gameTime = _time;

	nRows = 4;
	nColumns = 3;




	//Avatar PLAYER ONE!!
	avatarTextureID[0] = "P1AvatarText";
	avatarRectID[0] = "P1AvatarRect";
	avatarPositionID[0] = "P1AvatarPosition1";
	avatarPositionID[1] = "P1AvatarPosition2";
	avatarPositionID[2] = "P1AvatarPosition3";
	Renderer::Instance()->LoadTexture(textureID, Avatar[0]);
	Renderer::Instance()->LoadTexture(avatarTextureID[0], Avatar[0]);
	Renderer::Instance()->LoadRect(avatarRectID[0], Rect());
	Renderer::Instance()->LoadRect(avatarPositionID[0], Rect());
	Renderer::Instance()->LoadRect(avatarPositionID[2], Rect());
	textureWidth = Renderer::Instance()->GetTextureSize(textureID).x;
	textureHeight = Renderer::Instance()->GetTextureSize(textureID).y;

	frameAvatar[0].w = textureWidth / nColumns;				//Fijando la anchura de la textura del sprite
	frameAvatar[0].h = textureHeight / nRows;				//Fijando la anchura de la textura del sprite
	posAvatar[0].w = rectAvatar[0].w = frameAvatar[0].w;	//Fijando la anchura de la textura del sprite y la hitbox.
	posAvatar[0].h = rectAvatar[0].h = frameAvatar[0].h;	//Fijando la anchura de la textura del sprite y la hitbox.
	rectAvatar[0].x = frameAvatar[0].w;		// Colocacion del "sprite"
	rectAvatar[0].y = frameAvatar[0].h * 2; // Colocacion del "sprite"

	std::cout << " " << avatarTextureID[0] << std::endl;
	std::cout << " " << avatarRectID[0] << std::endl;
	std::cout << " " << avatarPositionID[0] << std::endl;
	std::cout << " " << Avatar[0] << std::endl;
	//AVATAR PLAYER TWO!!
	avatarTextureID[1] = "P2AvatarText";
	avatarRectID[1] = "P2AvatarRect";

	Renderer::Instance()->LoadTexture(avatarTextureID[1], Avatar[1]);
	Renderer::Instance()->LoadRect(avatarRectID[1], Rect());
	Renderer::Instance()->LoadRect(avatarPositionID[1], Rect());
	textureWidth = Renderer::Instance()->GetTextureSize(textureID).x;
	textureHeight = Renderer::Instance()->GetTextureSize(textureID).y;

	frameAvatar[1].w = textureWidth / nColumns;				//Fijando la anchura de la textura del sprite
	frameAvatar[1].h = textureHeight / nRows;				//Fijando la anchura de la textura del sprite
	posAvatar[1].w = rectAvatar[1].w = frameAvatar[1].w;	//Fijando la anchura de la textura del sprite y la hitbox.
	posAvatar[1].h = rectAvatar[1].h = frameAvatar[1].h;	//Fijando la anchura de la textura del sprite y la hitbox.
	rectAvatar[1].x = frameAvatar[1].w;		// Colocacion del "sprite"
	rectAvatar[1].y = frameAvatar[1].h * 2; // Colocacion del "sprite"

	posAvatar[2].w = frameAvatar[1].w;	//Fijando la anchura de la textura del sprite y la hitbox.
	posAvatar[2].h = frameAvatar[1].h;
	posAvatar[3].w = rectAvatar[1].w = frameAvatar[1].w;	//Fijando la anchura de la textura del sprite y la hitbox.
	posAvatar[3].h = rectAvatar[1].h = frameAvatar[1].h;
	posAvatar[4].w = rectAvatar[1].w = frameAvatar[1].w;	//Fijando la anchura de la textura del sprite y la hitbox.
	posAvatar[4].h = rectAvatar[1].h = frameAvatar[1].h;
	posAvatar[5].w = rectAvatar[1].w = frameAvatar[1].w;	//Fijando la anchura de la textura del sprite y la hitbox.
	posAvatar[5].h = rectAvatar[1].h = frameAvatar[1].h;

	avatarPositionID[3] = "P2AvatarPosition1";
	Renderer::Instance()->LoadRect(avatarPositionID[3], Rect());
	avatarPositionID[4] = "P2AvatarPosition2";
	Renderer::Instance()->LoadRect(avatarPositionID[4], Rect());
	avatarPositionID[5] = "P2AvatarPosition3";
	Renderer::Instance()->LoadRect(avatarPositionID[5], Rect());

	posAvatar[0].x = 100;
	posAvatar[0].y = 30;
	posAvatar[1].x = 158;
	posAvatar[1].y = 30;
	posAvatar[2].x = 216;
	posAvatar[2].y = 30;
	posAvatar[3].x = 500;
	posAvatar[3].y = 30;
	posAvatar[4].x = 558;
	posAvatar[4].y = 30;
	posAvatar[5].x = 616;
	posAvatar[5].y = 30;

	/*
Renderer::Instance()->LoadFont(Font({ "Arial", "../../res/ttf/Arial.ttf", 80 }));
colors["black"] = { 0,0,0,0 };
texts["playerOneScoreBoardText"] = { "playerOneScoreBoardText", "PlayerOne:", colors["black"], 30, 30 };
Renderer::Instance()->LoadTextureText("Arial", texts["playerOneScoreBoardText"]);
Renderer::Instance()->LoadRect("player1ScoreRect", Rect({ 30,30,  Renderer::Instance()->GetTextureSize("playerOneScoreBoardText").x, Renderer::Instance()->GetTextureSize("playerOneScoreBoardText").y }));
*/

}

Hud::~Hud()
{

}

void Hud::Update(InputManager _input, float _deltaTime)
{
	Renderer::Instance()->SetRect(avatarRectID[0], rectAvatar[0]);
	Renderer::Instance()->SetRect(avatarRectID[1], rectAvatar[1]);

	Renderer::Instance()->SetRect(avatarPositionID[0], posAvatar[0]);
	Renderer::Instance()->SetRect(avatarPositionID[1], posAvatar[1]);

	Renderer::Instance()->SetRect(avatarPositionID[2], posAvatar[2]);

	Renderer::Instance()->SetRect(avatarPositionID[3], posAvatar[3]);
	Renderer::Instance()->SetRect(avatarPositionID[4], posAvatar[4]);
	Renderer::Instance()->SetRect(avatarPositionID[5], posAvatar[5]);
}

void Hud::Reset()
{

}

void Hud::Draw()
{
	if (HP[0] == 3)
	{
		Renderer::Instance()->PushSprite(avatarTextureID[0], avatarRectID[0], avatarPositionID[0]);
		Renderer::Instance()->PushSprite(avatarTextureID[0], avatarRectID[0], avatarPositionID[1]);
		Renderer::Instance()->PushSprite(avatarTextureID[0], avatarRectID[0], avatarPositionID[2]);
	}
	else if (HP[0] == 2)
	{
		Renderer::Instance()->PushSprite(avatarTextureID[0], avatarRectID[0], avatarPositionID[0]);
		Renderer::Instance()->PushSprite(avatarTextureID[0], avatarRectID[0], avatarPositionID[1]);
	}
	else if (HP[0] == 1)
	{
		Renderer::Instance()->PushSprite(avatarTextureID[0], avatarRectID[0], avatarPositionID[0]);
	}
	else {}

	if (HP[1] == 3)
	{
		Renderer::Instance()->PushSprite(avatarTextureID[1], avatarRectID[1], avatarPositionID[3]);
		Renderer::Instance()->PushSprite(avatarTextureID[1], avatarRectID[1], avatarPositionID[4]);
		Renderer::Instance()->PushSprite(avatarTextureID[1], avatarRectID[1], avatarPositionID[5]);
	}
	else if (HP[1] == 2)
	{
		Renderer::Instance()->PushSprite(avatarTextureID[1], avatarRectID[1], avatarPositionID[4]);
		Renderer::Instance()->PushSprite(avatarTextureID[1], avatarRectID[1], avatarPositionID[5]);
	}
	else if (HP[1] == 1)
	{
		Renderer::Instance()->PushSprite(avatarTextureID[1], avatarRectID[1], avatarPositionID[5]);
	}
	else {}
}


Rect Hud::GetRect()
{
	return rect;
}

Rect Hud::GetFrame()
{
	return frame;
}

Rect Hud::GetPosition()
{
	return position;
}

std::string Hud::GetTexture()
{
	return texture;
}

void Hud::UpdateHPPlayer(int _hp1, int _hp2)
{
	HP[0] = _hp1;
	HP[1] = _hp2;
}