#pragma once
#include "Scene.h"
#include "ScoreBoard.h"

class SceneMenu :
    public Scene
{
private:
	Vec2 mouseAxis;
	bool mouseClicked, playMenuMusic,
		playHover, sondOffHover, sondOnHover, exitHover;

public:
    SceneMenu();
    ~SceneMenu();
    void Update(InputManager _inputs);
    void Draw();
};

