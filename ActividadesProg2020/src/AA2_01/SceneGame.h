#pragma once
#include "Scene.h"
#include "Player.h"
#include "Constants.h"


class SceneGame :
	public Scene
{
private:

	//Players
	Player players[PLAYER_SIZE];
	clock_t lastTime;
	int timeDown, playTime;
	float deltaTime;

public:
	SceneGame();
	~SceneGame();

	void Update();
	void Draw();
	void UpdateDeltaTime();
};



