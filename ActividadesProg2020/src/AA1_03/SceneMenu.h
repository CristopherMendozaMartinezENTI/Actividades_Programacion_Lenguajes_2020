#pragma once
#include "Scene.h"
#include "Cursor.h"
#include "ScoreBoard.h"

class SceneMenu :
    public Scene
{
private:
    Cursor cursor;
    bool mouseClicked, playMenuMusic,
        playHover, sondOffHover, sondOnHover, exitHover;

public:
    SceneMenu();
    ~SceneMenu();
    void Update(InputManager _inputs);
    void Draw();
};

