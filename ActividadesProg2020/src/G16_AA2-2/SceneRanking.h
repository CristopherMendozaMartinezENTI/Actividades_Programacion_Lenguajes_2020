#pragma once
#include "Scene.h"
#include "Cursor.h"
#include "Button.h"

class SceneRanking : public Scene {
private:
	//Button menuButton, exitButton;
	Cursor cursor;

public:
	SceneRanking();
	~SceneRanking();

	void Update(InputManager input);
	void Draw();
	float UpdateDeltaTime();

};