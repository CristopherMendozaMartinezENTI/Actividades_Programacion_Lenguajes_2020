#pragma once
#include "Scene.h"
#include "Cursor.h"
#include "Button.h"

class SceneMenu :
    public Scene
{
private:
    Cursor cursor;
    Button playButton, rankingButton, soundButton, exitButton;
    Button lvlButton[MAX_LEVEL];

public:
    SceneMenu();
    ~SceneMenu();
    
    void Update(InputManager& _inputs);
    void Draw();
    float UpdateDeltaTime();
};

