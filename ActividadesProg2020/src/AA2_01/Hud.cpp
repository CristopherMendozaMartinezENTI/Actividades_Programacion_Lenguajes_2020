#include "Hud.h"
#include <math.h>

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

	//Vidas Player 1
	posAvatar[0].x = 158;
	posAvatar[0].y = 30;
	posAvatar[1].x = 192;
	posAvatar[1].y = 30;
	posAvatar[2].x = 226;
	posAvatar[2].y = 30;

	//Vidas Player 2
	posAvatar[3].x = SCREEN_WIDTH - 274;
	posAvatar[3].y = 30;
	posAvatar[4].x = SCREEN_WIDTH - 240;
	posAvatar[4].y = 30;
	posAvatar[5].x = SCREEN_WIDTH - 206;
	posAvatar[5].y = 30;

	//Textos Score P1, Score P2, Tiempo
	Renderer::Instance()->LoadFont(Font({ "BomberFont", "../../res/ttf/game_over.ttf", 80 }));
	scoreRectID[0] = "scoreRect1";
	scoreText1 = { "scoreText1", "Score: ", Color(0,0,0,0) };
	Renderer::Instance()->LoadTextureText("BomberFont", scoreText1);
	Renderer::Instance()->LoadRect(scoreRectID[0], Rect({ 30, 30, Renderer::Instance()->GetTextureSize("scoreText1").x, Renderer::Instance()->GetTextureSize("scoreText1").y }));

	scoreRectID[1] = "scoreRect2";
	scoreText2 = { "scoreText2", "Score: 13", Color(0,0,0,0) };
	Renderer::Instance()->LoadTextureText("BomberFont", scoreText2);
	Renderer::Instance()->LoadRect(scoreRectID[1], Rect({ SCREEN_WIDTH - 148, 30, Renderer::Instance()->GetTextureSize("scoreText2").x, Renderer::Instance()->GetTextureSize("scoreText2").y }));

	std::string times = "Time: " + std::to_string(gameTime / 100);
	gameTimeRectID = "gameTimeRect";
	gameTimeText = { "gameTimeText", "Time: ", Color(0,0,0,0) };
	Renderer::Instance()->LoadTextureText("BomberFont", gameTimeText);
	Renderer::Instance()->LoadRect(gameTimeRectID, Rect({ SCREEN_WIDTH / 2 - (Renderer::Instance()->GetTextureSize("gameTimeText").x / 2) , 30, Renderer::Instance()->GetTextureSize("gameTimeText").x , Renderer::Instance()->GetTextureSize("scoreText2").y }));

	lastScore1.text = ".";
	lastScore2.text = ".";
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

	//Update Score Player 1
	scoreText1.UpdateText("Score: " + std::to_string(score[1]));
	if (scoreText1.text != lastScore1.text)
	{
		Renderer::Instance()->LoadTextureText("BomberFont", scoreText1);
		Renderer::Instance()->SetRect(scoreRectID[0], Rect({ 30, 30, Renderer::Instance()->GetTextureSize("scoreText1").x , Renderer::Instance()->GetTextureSize("scoreText2").y }));
	}
	//Update Score Player 2
	scoreText2.UpdateText("Score: " + std::to_string(score[1]));
	if (scoreText2.text != lastScore2.text)
	{
		Renderer::Instance()->LoadTextureText("BomberFont", scoreText2);
		Renderer::Instance()->SetRect(scoreRectID[1], Rect({ SCREEN_WIDTH - 148, 30, Renderer::Instance()->GetTextureSize("scoreText2").x , Renderer::Instance()->GetTextureSize("scoreText2").y }));
	}

	//Update Game Time
	
	gameTimeText.UpdateText("Time: " + FloatToString(gameTime, 2));
	if (gameTimeText.text != lastTime.text)
	{
		Renderer::Instance()->LoadTextureText("BomberFont", gameTimeText);
		Renderer::Instance()->SetRect(gameTimeRectID, Rect({ SCREEN_WIDTH / 2 - (Renderer::Instance()->GetTextureSize("gameTimeText").x / 2) , 30, Renderer::Instance()->GetTextureSize("gameTimeText").x , Renderer::Instance()->GetTextureSize("scoreText2").y }));
	}
	

	gameTime -= _deltaTime;
	lastScore1.text = scoreText1.text;
	lastScore2.text = scoreText2.text;
	lastTime.text = gameTimeText.text;
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

	Renderer::Instance()->PushImage("scoreText1", scoreRectID[0]);
	Renderer::Instance()->PushImage("scoreText2", scoreRectID[1]);
	Renderer::Instance()->PushImage("gameTimeText", gameTimeRectID);
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

void Hud::UpdateScorePlayer(int _score1, int _score2)
{
	score[0] = _score1;
	score[1] = _score2;
}

std::string Hud::FloatToString(float num, int _precision)
{
	// Create an output string stream
	std::ostringstream streamObj3;
	int minutes, seconds;
	minutes = num / 60;
	seconds = fmod(num, 60);

	// Set Fixed -Point Notation
	streamObj3 << std::fixed;
	// Set precision 
	streamObj3 << std::setprecision(_precision);
	//Add double to stream
	streamObj3 << minutes << ":" << seconds;
	// Get string from output string stream
	std::string strObj3 = streamObj3.str();

	return strObj3;
}


