#pragma once
#include "Scene.h"

#include "ScoreBoard.h"

class SceneMenu :
    public Scene
{
private:

	Vec2 mouseAxis;
	gameStates state;

	bool isRunning, mouseClicked, playMenuMusic,
		playHover, sondOffHover, sondOnHover, exitHover;

public:
    SceneMenu();
    ~SceneMenu();
    void Update();
    void Draw();
};

