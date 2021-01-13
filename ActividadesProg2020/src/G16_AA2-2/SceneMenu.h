#pragma once
#include "Scene.h"
#include "Cursor.h"
#include "Button.h"

class SceneMenu :
    public Scene
{
private:
    Cursor cursor;
    std::map<std::string, Color> colors;
    std::map<std::string, Text> texts;
    std::map<std::string, Rect> rectangles;

    bool mouseClicked, musicOff,
        playLevel1Hover, playLevel2Hover, rankingHover, sondOffHover, sondOnHover, exitHover;

public:
    SceneMenu();
    ~SceneMenu();
    
    void Update(InputManager &_input);
    void Draw();
    float UpdateDeltaTime();
};

