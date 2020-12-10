#pragma once
#include "Scene.h"
#include "ScoreBoard.h"
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

	Rect coinRect[AMOUNT_OF_COINS];

	Vec2 mouseAxis;

	int timeDown;

	clock_t lastTime;
	float deltaTime;

public:
    SceneGame();
    ~SceneGame();
	void UpdateDeltaTime();
    void Update(InputManager _inputs);
    void Draw();
};

