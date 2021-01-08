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
	rect = Rect(0, 0, 0, 0);
	frame = Rect(0, 0, 0, 0);
	position;

	rectID = "HudRect";
	positionID = "HudPosition";
	textureID = "HudTexture";

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

}

void Hud::Reset()
{

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