#pragma once
#include "Scene.h"
#include "Cursor.h"
#include "Button.h"

class SceneMenu :
    public Scene
{
private:
    Cursor cursor;
    //Button playButton, rankingButton, soundButton, exitButton;
    //Button lvlButton[MAX_LEVEL];

    bool mouseClicked, playMenuMusic,
        playLevel1Hover, playLevel2Hover, rankingHover, sondOffHover, sondOnHover, exitHover;

public:
    SceneMenu();
    ~SceneMenu();
    
    void Update(InputManager &_input);
    void Draw();
    float UpdateDeltaTime();
};

