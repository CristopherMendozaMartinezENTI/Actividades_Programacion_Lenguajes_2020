#pragma once
#include "ScoreBoard.h"
#include "Input.h"
#include "Renderer.h"
#include "AudioManager.h"


class GameManager
{
private:
	Renderer renderer;

	InputInfo input;

	SDL_Event event;

	//Textures
	std::map<std::string, SDL_Texture*> textures;

	//Surfaces
	SDL_Surface* tmpSurf;

	//Texture variables
	int textWidth, textHeight, scoreWidth, scoreHeight;

	//Colors
	std::map<std::string, Color> colors;

	//Texts
	std::map<std::string, Text> texts;
			
	//Fonts 
	TTF_Font* font;
	TTF_Font* inGameFont;

	//Rects
	std::map<std::string, Rect> rectangles;
	Rect coinRect[AMOUNT_OF_COINS];

	//ScoreBoards
	ScoreBoard boardP1;
	ScoreBoard boardP2;

	//Music
	AudioManager music;

	//Players
	PlayerClass playerClass1;
	PlayerClass playerClass2;

	gameStates state;
	Uint32 frameTime, frameStart;

	Vec2 mouseAxis;
	bool isRunning, mouseClicked, playMenuMusic;
	char exactTime[5];
	int timeDown, playTime;

public:
	GameManager();
	~GameManager();

	void InitiateMenu();
	void UpdateMenu();
	void DrawMenu();

	void InitiateGame();
	void UpdateGame();
	void DrawGame();

	void UpdateInputs();
	void Draw();
	void Run();
	void Destroy();
};

