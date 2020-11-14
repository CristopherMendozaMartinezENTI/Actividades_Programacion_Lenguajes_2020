#pragma once
#include "Types.h"
#include "ScoreBoard.h"
#include "Utils.h"
#include "Renderer.h"
class GameManager
{
private:
	Renderer renderer;

	SDL_Event event;

 	//Rects
	std::map<std::string, Rect> rectangles;
	SDL_Rect coinRect[AMOUNT_OF_COINS];

	//ScoreBoards
	ScoreBoard boardP1;
	ScoreBoard boardP2;

	//Players
	PlayerClass playerClass1;
	PlayerClass playerClass2;

	Mix_Music* menuMusic;

	gameStates state;
	Uint32 frameTime, frameStart;

	Vec2 mouseAxis;
	bool isRunning, mouseClicked, playMenuMusic;
	char exactTime[5];
	float sec;
	;
public:
	GameManager();
	~GameManager();

	void InitiateMenu();
	void UpdateMenu();
	void DrawMenu();

	void InitiateGame();
	void UpdateGame();
	void DrawGame();

	void Update();
	void Draw();
	void Run();
	void Destroy();
};

