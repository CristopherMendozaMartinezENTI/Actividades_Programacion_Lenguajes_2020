#include "SceneGame.h"
#include "Utils.h"
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"

void SceneGame::LoadXML()
{
	rapidxml::xml_document<> config;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	config.parse<0>(&content[0]);

	Vec2 WallPos;
	bool Walldestructible;

	//Root
	rapidxml::xml_node<>* pRoot = config.first_node();
	//---->Estamos en el Level1
	rapidxml::xml_node<>* pLevel1 = pRoot->first_node("Level1");

	//---->Estamos en Players de Level1
	rapidxml::xml_node<>* pPlayers = pLevel1->first_node("Players");

	//---->Estamos en Player1 de Level1
	rapidxml::xml_node<>* pPlayer1 = pPlayers->first_node("Player1");
	rapidxml::xml_attribute<>* level1Player1Vidas = pPlayer1->first_attribute("lives");
	int vidas = atoi(level1Player1Vidas->value());
	rapidxml::xml_node<>* pPlayer1Position = pPlayer1->first_node("Positon");
	rapidxml::xml_attribute<>* level1Player1Posicion = pPlayer1Position->first_attribute("x");
	int posX = atoi(level1Player1Posicion->value());
	level1Player1Posicion = pPlayer1Position->first_attribute("y");
	int posY = atoi(level1Player1Posicion->value());

	std::cout << "Player 1" << std::endl;
	std::cout << "Vidas: " << vidas << std::endl;
	std::cout << "PosX: " << posX << std::endl;
	std::cout << "PosY: " << posY << std::endl;
	std::cout << std::endl;

	//---->Estamos en Player2 de Level1
	rapidxml::xml_node<>* pPlayer2 = pPlayer1->next_sibling();
	rapidxml::xml_attribute<>* level1Player2Vidas = pPlayer2->first_attribute("lives");
	int vidas2 = atoi(level1Player2Vidas->value());
	rapidxml::xml_node<>* pPlayer2Position = pPlayer2->first_node("Positon");
	rapidxml::xml_attribute<>* level1Player2Posicion = pPlayer2Position->first_attribute("x");
	int pos2X = atoi(level1Player2Posicion->value());
	level1Player2Posicion = pPlayer2Position->first_attribute("y");
	int pos2Y = atoi(level1Player2Posicion->value());

	std::cout << "Player 2" << std::endl;
	std::cout << "Vidas: " << vidas2 << std::endl;
	std::cout << "PosX: " << pos2X << std::endl;
	std::cout << "PosY: " << pos2Y << std::endl;
	std::cout << std::endl;

	//---->Estamos en Mapa de Level1
	rapidxml::xml_node<>* pMap = pPlayers->next_sibling();
	//Recorrer el contenido del mapa mediante un for
	int i = 0;
	for (pMap = pMap->first_node("Wall"); pMap; pMap = pMap->next_sibling())
	{
		rapidxml::xml_attribute<>* pWallData = pMap->first_attribute("destructible");
		std::string destructible = pWallData->value();
		pWallData = pMap->first_attribute("x");
		WallPos.x = atoi(pWallData->value());
		pWallData = pMap->first_attribute("y");
		WallPos.y = atoi(pWallData->value());
		
		std::cout << "Wall " << i << std::endl;
		std::cout << "Destructible: " << destructible << std::endl;
		std::cout << "WallPosX: " << WallPos.x << std::endl;
		std::cout << "WallPosY: " << WallPos.y << std::endl;
		std::cout << std::endl;
		i++;
	}

	//---->Estamos en el Level2
	rapidxml::xml_node<>* pLevel2 = pLevel1->next_sibling();
	//---->Estamos en Players de Level2
	rapidxml::xml_node<>* pLevel2Players = pLevel2->first_node("Players");
	//---->Estamos en Player1 de Level2
	rapidxml::xml_node<>* pLevel2Player1 = pLevel2Players->first_node("Player1");
	//---->Estamos en Player2 de Level2
	rapidxml::xml_node<>* pLevel2Player2 = pLevel2Player1->next_sibling();
	//---->Estamos en Mapa de Level2
	rapidxml::xml_node<>* pMapLevel1 = pLevel2Players->next_sibling();
	//Recorrer el contenido del mapa mediante un for

}

SceneGame::SceneGame()
{
	LoadXML();
	music.PlayGameMusic();
	lastTime = clock();
	deltaTime = 0.f;
	timeDown = MAX_TIME;

	//------------- INGAME ---------------

	// --- SPRITES ---
#pragma region Backgrounds

	Renderer::Instance()->LoadTexture("gameBgTexture", "../../res/img/bgGame.jpg");
	Renderer::Instance()->LoadRect("gameBgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

#pragma endregion

#pragma region Objects

	//Bombas, PowerUp & Walls 


#pragma endregion 
	// --- TEXT --- 


	//--- ANIMATED SPRITES ---

#pragma region Players

	//Players
	players[0] = { 3, Vec2(50,124), 4, 3, "Player1" , "../../res/img/player1.png", e_PlayerType::P1 };
	players[1] = { 3, Vec2(620,604), 4, 3, "Player2" , "../../res/img/player2.png", e_PlayerType::P2 };

#pragma endregion

}

SceneGame::~SceneGame()
{

}

float SceneGame::UpdateDeltaTime()
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	return deltaTime;
}

void SceneGame::Update(InputManager &_input)
{
	if (_input.returnKeyIsDown()[(int)EKeys::QUIT]) state = e_GameStates::QUIT;
	if (_input.returnKeyIsDown()[(int)EKeys::ESC])
	{
		state = e_GameStates::MENU;
		_input.returnKeyIsDown()[(int)EKeys::ESC] = false;
	}

#pragma region Players

	//Player Movement
	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		players[i].Update(_input, deltaTime);
		
		if (players[0].GetSpawnBomb())	P1Bomb = new Bomb("P1Bomb" + numBombs, players[0].GetPosition());
		if (players[1].GetSpawnBomb())  P2Bomb = new Bomb("P2Bomb" + numBombs, players[1].GetPosition());
		
		/*if (players[i].GetSpawnBomb())
		{
			//bombs.push_back(new Bomb(i + "Bomb" + numBombs, players[i].GetPosition()));
			numBombs++;
		}*/
	}

#pragma endregion

#pragma region Time

	if (timeDown <= 0)
	{
		//Exit GameScene!
		timeDown = playTime;
	}

	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		if (players[i].GetBombCD() <= 0)
		{
			players[i].CanSpawnBomb();
			players[i].ResetBombCD();
		}
	}

#pragma endregion
	
	if (P1Bomb != nullptr && P1Bomb->GetBombState() != e_BombState::GONE)
	{
		P1Bomb->Update(_input, deltaTime);
	}
	if (P2Bomb != nullptr && P2Bomb->GetBombState() != e_BombState::GONE)
	{
		P2Bomb->Update(_input, deltaTime);
	}
	
	/*
	for (int i = 0; i < bombs.size(); i++)
	{
		if (bombs.at(i)->GetBombState() != e_BombState::GONE)
		{
			bombs.at(i)->Update(_input, deltaTime);
		}

	}
	*/
	timeDown -= UpdateDeltaTime();
}

void SceneGame::Draw()
{

	Renderer::Instance()->Clear();

	//Background
	Renderer::Instance()->PushImage("gameBgTexture", "gameBgRect");
	
	if (P1Bomb != nullptr && P1Bomb->GetBombState() != e_BombState::GONE)
	{
		P1Bomb->Draw();
	}
	if (P2Bomb != nullptr && P2Bomb->GetBombState() != e_BombState::GONE)
	{
		P2Bomb->Draw();
	}

	//Player Sprites
	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		players[i].Draw();
	}
	
	/*
	for (int j = 0; j < bombs.size(); j++)
	{
		if (bombs.at(j)->GetBombState() != e_BombState::GONE)
		{
			bombs.at(j)->Draw();
		}
	}
	*/


	Renderer::Instance()->Render();
}

