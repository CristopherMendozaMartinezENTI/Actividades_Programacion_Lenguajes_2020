#pragma once
#include <fstream>
#include "Scene.h"
#include "Player.h"
#include "Bomb.h"
#include "Block.h"
#include "Hud.h"
#include "PowerUp.h"
#include "Constants.h"
#include "DynText.h"
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"

class SceneGame :
	public Scene
{
private:

	enum class SceneState
	{
		RUNNING, GAME_OVER
	}; 

	SceneState inGameState;

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
	std::vector<PowerUp> powerUps;
	
	//HUD
	//Hud scoreboard;

	//Map
	
	clock_t lastTime;
	float timeDown, playTime;
	float deltaTime;

	float timeRef;

	Text winnerText;

	DynText playerWinText;

public:
	void LoadGameObjects(e_Levels _level);
	SceneGame(e_Levels _level);
	~SceneGame();
	void CheckWinnerInput(InputManager& _input);
	void CheckRanking();
	void Update(InputManager &input);
	void Draw();
	float UpdateDeltaTime();
};



