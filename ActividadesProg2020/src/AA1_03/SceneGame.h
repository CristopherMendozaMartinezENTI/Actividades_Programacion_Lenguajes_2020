#pragma once
#include "Scene.h"
#include "ScoreBoard.h"
#include "GoldenBag.h"

class SceneGame :
	public Scene
{
private:
	//ScoreBoards
	ScoreBoard boardP1;
	ScoreBoard boardP2;
	//Players
	PlayerClass playerClass1;
	PlayerClass playerClass2;
	GoldenBag goldenBags[AMOUNT_OF_COINS];
	clock_t lastTime;
	int timeDown;
	float deltaTime;

public:
	SceneGame();
	~SceneGame();
	void UpdateDeltaTime();
	void Update(InputManager& _inputs);
	void Draw();
};



