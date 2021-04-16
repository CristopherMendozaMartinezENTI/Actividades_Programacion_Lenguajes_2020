#pragma once
#include "Scene.h"
#include "Cursor.h"
#include "Button.h"

class SceneMenu :
    public Scene
{
private:
    Cursor cursor;
    Text tittleText;

    std::vector<Button> buttons;
    SpecialButton soundButton;

    std::map<std::string, Color> colors;

    bool mouseClicked, musicOff;

public:
    SceneMenu();
    ~SceneMenu();
    
    void Update(InputManager &_input);
    void Draw();
    float UpdateDeltaTime();
};

