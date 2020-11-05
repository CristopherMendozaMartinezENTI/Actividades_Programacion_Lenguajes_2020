#pragma once
#include "Types.h"
#include "ScoreBoard.h"
class GameManager
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event event;

	//Textures
	std::map<std::string, SDL_Texture*> textures;

	//Surfaces
	SDL_Surface* tmpSurf;

	//Texture variables
	int textWidth, textHeight, scoreWidth, scoreHeight;

	//Fonts 
	TTF_Font* font;
	TTF_Font* inGameFont;

	//Rects
	std::map<std::string, SDL_Rect> rectangles;
	std::map<std::string, SDL_Rect> positions;
	SDL_Rect coinRect[AMOUNT_OF_COINS];

	//ScoreBoards
	ScoreBoard boardP1;
	ScoreBoard boardP2;

	Mix_Music* menuMusic;

	gameStates state;
	Uint32 frameTime;
	char exactTime[5];
	float sec;
	bool playMenuMusic;

public:
	Uint32 frameStart;
	PlayerClass playerClass1;
	PlayerClass playerClass2;
	Vec2 mouseAxis;
	bool isRunning;
	bool mouseClicked;

	GameManager();
	~GameManager();

	void Update();
	void Draw();
	void Run();
	void Destroy();
};

