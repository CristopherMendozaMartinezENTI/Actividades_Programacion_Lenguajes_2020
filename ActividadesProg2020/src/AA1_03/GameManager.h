#pragma once
#include "ScoreBoard.h"
#include "Renderer.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "SceneMenu.h"
#include "SceneGame.h"

class GameManager
{
private:
	Scene* currentScene;
	Scene* LastScene;

	//Music
	AudioManager music;

	InputManager inputs;

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

	//Players
	PlayerClass playerClass1;
	PlayerClass playerClass2;

	gameStates state;
	Vec2 mouseAxis;
	bool isRunning, mouseClicked, playMenuMusic;
	bool playHover, sondOffHover, sondOnHover, exitHover;

	int timeDown, playTime;

	clock_t lastTime;
	float deltaTime;

public:
	GameManager();
	~GameManager();
	void Run();
};

