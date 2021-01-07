#pragma once
#include "Scene.h"
#include "Player.h"
#include "Bomb.h"
#include "Hud.h"
#include "Constants.h"


class SceneGame :
	public Scene
{
private:

	//Players
	Player players[PLAYER_SIZE];

	//Bombs
	Bomb *testBomb;
	std::vector<Bomb*> bombs;
	int numBombs;
	
	//HUD
	//Hud scoreboard;

	//Map
	
	clock_t lastTime;
	int timeDown, playTime;
	float deltaTime;

public:
	SceneGame();
	~SceneGame();

	void Update(InputManager input);
	void Draw();
	float UpdateDeltaTime();
};



