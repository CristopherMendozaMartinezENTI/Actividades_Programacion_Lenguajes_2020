#pragma once
#include "ScoreBoard.h"
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"

class GameManager
{
private:
	Renderer renderer;

	InputManager inputs;

	SDL_Event event;

	//Colors
	std::map<std::string, Color> colors;

	//Texts
	std::map<std::string, Text> texts;
			
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
	Vec2 mouseAxis;
	bool isRunning, mouseClicked, playMenuMusic;
	int timeDown, playTime;

	clock_t lastTime;
	float deltaTime;

public:
	GameManager();
	~GameManager();

	void UpdateDeltaTime();

	void InitiateMenu();
	void UpdateMenu();
	void DrawMenu();

	void InitiateGame();
	void UpdateGame();
	void DrawGame();

	void Run();
};

