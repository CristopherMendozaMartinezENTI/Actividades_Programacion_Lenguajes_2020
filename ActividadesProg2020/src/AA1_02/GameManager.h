#pragma once
#include "Utilities.h"
#include "ScoreBoard.h"
class GameManager
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

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

	char exactTime[5];
	float sec;

public:
	Uint32 frameStart, frameTime;
	PlayerClass playerClass1;
	PlayerClass playerClass2;
	gameStates state;
	Vec2 mouseAxis;
	bool isRunning;
	bool playMenuMusic;
	bool mouseClicked;

	GameManager(SDL_Window* _window, SDL_Renderer* _renderer);
	~GameManager();

	void Update();
	void Draw();
	void Destroy();
};

