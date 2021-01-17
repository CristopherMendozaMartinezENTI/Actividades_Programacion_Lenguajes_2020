#pragma once
#include "Scene.h"
#include "Cursor.h"
#include "Button.h"
#include <fstream>

class SceneRanking : public Scene {
private:
	//Button menuButton, exitButton;
	Cursor cursor;

public:
	void ReadBinaryFile();
	SceneRanking();
	~SceneRanking();
	void Update(InputManager& _input);
	void Draw();
	float UpdateDeltaTime();
};