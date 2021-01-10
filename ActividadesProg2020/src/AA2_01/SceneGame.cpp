#include "SceneGame.h"
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"

void SceneGame::LoadGameObjects(e_Levels _level)
{
	rapidxml::xml_document<> config;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	config.parse<0>(&content[0]);

	//Root
	rapidxml::xml_node<>* pRoot = config.first_node();
	//---->Estamos en el Level1
	rapidxml::xml_node<>* pLevel1 = pRoot->first_node("Level1");

	switch (_level)
	{
		case e_Levels::LEVEL_1:
		{
			//---->Estamos en Players de Level1
			rapidxml::xml_node<>* pLevel1Players = pLevel1->first_node("Players");

			//---->Estamos en Player1 de Level1
			rapidxml::xml_node<>* pLevel1Player1 = pLevel1Players->first_node("Player1");
			rapidxml::xml_attribute<>* level1Player1Vidas = pLevel1Player1->first_attribute("lives");
			int vidas1 = atoi(level1Player1Vidas->value());
			rapidxml::xml_node<>* pLevel1Player1Position = pLevel1Player1->first_node("Positon");
			rapidxml::xml_attribute<>* level1Player1PositionAttribute = pLevel1Player1Position->first_attribute("x");
			int pos1X = atoi(level1Player1PositionAttribute->value());
			level1Player1PositionAttribute = pLevel1Player1Position->first_attribute("y");
			int pos1Y = atoi(level1Player1PositionAttribute->value());

			players[0] = { vidas1, Vec2(((pos1X * 48) + 48), ((pos1Y * 48) + 128)), 4, 3, "Player1" , "../../res/img/player1.png", e_PlayerType::P1 };

			//---->Estamos en Player2 de Level1
			rapidxml::xml_node<>* pLevel1Player2 = pLevel1Player1->next_sibling();
			rapidxml::xml_attribute<>* level1Player2Vidas = pLevel1Player2->first_attribute("lives");
			int vidas2 = atoi(level1Player2Vidas->value());
			rapidxml::xml_node<>* pPlayer2Position = pLevel1Player2->first_node("Positon");
			rapidxml::xml_attribute<>* level1Player2PositionAtributte = pPlayer2Position->first_attribute("x");
			int pos2X = atoi(level1Player2PositionAtributte->value());
			level1Player2PositionAtributte = pPlayer2Position->first_attribute("y");
			int pos2Y = atoi(level1Player2PositionAtributte->value());

			players[1] = { vidas2, Vec2(((pos2X * 48) + 48), ((pos2Y * 48) + 128)), 4, 3, "Player2" , "../../res/img/player2.png", e_PlayerType::P2 };

			//---->Estamos en Mapa de Level1
			rapidxml::xml_node<>* pLevel1Map = pLevel1Players->next_sibling();
			//Recorrer el contenido del mapa mediante un for
			int i = 0;
			for (pLevel1Map = pLevel1Map->first_node("Wall"); pLevel1Map; pLevel1Map = pLevel1Map->next_sibling())
			{
				Vec2 WallPos;
				bool Walldestructible;
				rapidxml::xml_attribute<>* pWallData = pLevel1Map->first_attribute("destructible");
				std::string destructible = pWallData->value();
				pWallData = pLevel1Map->first_attribute("x");
				WallPos.x = atoi(pWallData->value());
				pWallData = pLevel1Map->first_attribute("y");
				WallPos.y = atoi(pWallData->value());
				e_BlockType tmpType;
				if (destructible == "false") tmpType = e_BlockType::WALL;
				if (destructible == "true") tmpType = e_BlockType::BLOCK;
				Block tmpBlock = { tmpType, std::to_string(i), Rect((WallPos.x * 48 + 48),((WallPos.y * 48) + 128),48,48) };
				blocks.push_back(tmpBlock);
				i++;
			}
			break;
		}
		case e_Levels::LEVEL_2:
		{
			//---->Estamos en el Level2
			rapidxml::xml_node<>* pLevel2 = pLevel1->next_sibling();
			//---->Estamos en Players de Level2
			rapidxml::xml_node<>* pLevel2Players = pLevel2->first_node("Players");

			//---->Estamos en Player1 de Level2
			rapidxml::xml_node<>* pLevel2Player1 = pLevel2Players->first_node("Player1");
			rapidxml::xml_attribute<>* level2Player1Vidas = pLevel2Player1->first_attribute("lives");
			int vidas1 = atoi(level2Player1Vidas->value());
			rapidxml::xml_node<>* pLevel2Player1Position = pLevel2Player1->first_node("Positon");
			rapidxml::xml_attribute<>* level2Player1PositionAttribute = pLevel2Player1Position->first_attribute("x");
			int pos1X = atoi(level2Player1PositionAttribute->value());
			level2Player1PositionAttribute = pLevel2Player1Position->first_attribute("y");
			int pos1Y = atoi(level2Player1PositionAttribute->value());

			players[0] = { vidas1, Vec2(((pos1X * 48) + 48), ((pos1Y * 48) + 128)), 4, 3, "Player1" , "../../res/img/player1.png", e_PlayerType::P1 };

			//---->Estamos en Player2 de Level2
			rapidxml::xml_node<>* pLevel2Player2 = pLevel2Player1->next_sibling();
			rapidxml::xml_attribute<>* level2Player2Vidas = pLevel2Player2->first_attribute("lives");
			int vidas2 = atoi(level2Player2Vidas->value());
			rapidxml::xml_node<>* pPlayer2Position = pLevel2Player2->first_node("Positon");
			rapidxml::xml_attribute<>* level2Player2PositionAtributte = pPlayer2Position->first_attribute("x");
			int pos2X = atoi(level2Player2PositionAtributte->value());
			level2Player2PositionAtributte = pPlayer2Position->first_attribute("y");
			int pos2Y = atoi(level2Player2PositionAtributte->value());

			players[1] = { vidas2, Vec2(((pos2X * 48) + 48), ((pos2Y * 48) + 128)), 4, 3, "Player2" , "../../res/img/player2.png", e_PlayerType::P2 };

			//---->Estamos en Mapa de Level2
			rapidxml::xml_node<>* pMapLevel2 = pLevel2Players->next_sibling();
			//Recorrer el contenido del mapa mediante un for
			int i = 0;
			for (pMapLevel2 = pMapLevel2->first_node("Wall"); pMapLevel2; pMapLevel2 = pMapLevel2->next_sibling())
			{
				rapidxml::xml_attribute<>* pWallData = pMapLevel2->first_attribute("destructible");
				std::string destructible = pWallData->value();
				pWallData = pMapLevel2->first_attribute("x");
				Vec2 WallPos;
				WallPos.x = atoi(pWallData->value());
				pWallData = pMapLevel2->first_attribute("y");
				WallPos.y = atoi(pWallData->value());
				e_BlockType tmpType;
				if (destructible == "false") tmpType = e_BlockType::WALL;
				if (destructible == "true") tmpType = e_BlockType::BLOCK;
				Block tmpBlock = { tmpType, std::to_string(i), Rect((WallPos.x * 48 + 48),((WallPos.y * 48) + 128),48,48) };
				blocks.push_back(tmpBlock);
				i++;
			}
			break;
		}

		default:
			break;
	}
}

SceneGame::SceneGame(e_Levels _level)
{
	music.PlayGameMusic();
	lastTime = clock();
	deltaTime = 0.f;
	timeDown = MAX_TIME;

	Renderer::Instance()->LoadTexture("gameBgTexture", "../../res/img/bgGame.jpg");
	Renderer::Instance()->LoadRect("gameBgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

	LoadGameObjects(_level);
	
	hud = { players[0].GetTexture() , players[1].GetTexture(), players[0].HP, players[1].HP, timeDown };
	std::cout << blocks[10].GetPosition().x << std::endl;
	std::cout << blocks[10].GetPosition().y << std::endl;
	std::cout << blocks[10].GetPosition().w << std::endl;
	std::cout << blocks[10].GetPosition().h << std::endl;

	std::cout << players[0].GetPosition().x << std::endl;
	std::cout << players[0].GetPosition().y << std::endl;
	std::cout << players[0].GetPosition().w << std::endl;
	std::cout << players[0].GetPosition().h << std::endl;
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

void SceneGame::Update(InputManager& _input)
{
	std::cout << players[0].GetPosition().x << std::endl;
	std::cout << players[0].GetPosition().y << std::endl;
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
	hud.UpdateHPPlayer(players[0].HP, players[1].HP);

	hud.UpdateScorePlayer(players[0].score, players[1].score);

	for (int i = 0; i < blocks.size(); i++)
	{
		if (collisions::rectCollision(blocks[i].GetPosition(), players[0].GetPosition()))
		{
			blocks[i].erase = true;
		}

		if (collisions::rectCollision(blocks[i].GetPosition(), players[1].GetPosition()))
		{
			blocks[i].erase = true;
		}
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
	hud.Update(_input, deltaTime);
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

	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].Draw();
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
	hud.Draw();

	Renderer::Instance()->Render();
}

