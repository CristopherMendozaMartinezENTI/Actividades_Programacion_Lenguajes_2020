#pragma once
#include "Scene.h"
#include "Player.h"
#include "Bomb.h"
#include "Block.h"
#include "Hud.h"
#include "Constants.h"
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"

class SceneGame :
	public Scene
{
private:

	e_Levels level;

	//Players
	Player players[PLAYER_SIZE];

	//Bombs
	Bomb* P1Bomb = nullptr;
	Bomb* P2Bomb = nullptr;
	std::vector<Bomb*> bombs;
	int numBombs;
	Hud hud;

	std::vector<Block> blocks;
	
	//HUD
	//Hud scoreboard;

	//Map
	
	clock_t lastTime;
	float timeDown, playTime;
	float deltaTime;

public:
	void LoadGameObjects(e_Levels _level);
	SceneGame(e_Levels _level);
	~SceneGame();
	void Update(InputManager &input);
	void Draw();
	float UpdateDeltaTime();
};



