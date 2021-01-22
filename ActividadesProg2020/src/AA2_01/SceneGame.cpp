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
			Block tmpBlock = { tmpType, std::to_string(i), Rect(((WallPos.x * 48) + 48),((WallPos.y * 48) + 128),48,48) };
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


		//---->Estamos en Player2 de Level2
		rapidxml::xml_node<>* pLevel2Player2 = pLevel2Player1->next_sibling();
		rapidxml::xml_attribute<>* level2Player2Vidas = pLevel2Player2->first_attribute("lives");
		int vidas2 = atoi(level2Player2Vidas->value());
		rapidxml::xml_node<>* pPlayer2Position = pLevel2Player2->first_node("Positon");
		rapidxml::xml_attribute<>* level2Player2PositionAtributte = pPlayer2Position->first_attribute("x");
		int pos2X = atoi(level2Player2PositionAtributte->value());
		level2Player2PositionAtributte = pPlayer2Position->first_attribute("y");
		int pos2Y = atoi(level2Player2PositionAtributte->value());

		players[0] = { vidas1, Vec2(((pos2X * 48) + 48), ((pos2Y * 48) + 128)), 4, 3, "Player1" , "../../res/img/player1.png", e_PlayerType::P1 };
		players[1] = { vidas2, Vec2(((pos1X * 48) + 48), ((pos1Y * 48) + 128)), 4, 3, "Player2" , "../../res/img/player2.png", e_PlayerType::P2 };

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
			Block tmpBlock = { tmpType, std::to_string(i), Rect(((WallPos.x * 48) + 48),((WallPos.y * 48) + 128),48,48) };
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
	inGameState = SceneState::RUNNING;

	music.PlayGameMusic();
	lastTime = clock();
	deltaTime = 0.f;
	timeDown = MAX_TIME;

	winnerText = { "winner", " ", {255, 255, 255, 255} };

	playerWinText = DynText({ 125, 400, 300, 50 });

	Renderer::Instance()->LoadFont(Font({ "Font", "../../res/ttf/game_over.ttf", 80 }));
	Renderer::Instance()->LoadTexture("gameBgTexture", "../../res/img/bgGame.jpg");
	Renderer::Instance()->LoadRect("gameBgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));


	Text winText = { "winTextTexture", "YOU WIN, INTRODUCE YOUR NAME",  Color(255, 255, 255, 0) };
	Renderer::Instance()->LoadTextureText("Font", winText);
	Renderer::Instance()->LoadRect("winTextRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("winTextTexture").x) / 2, 300, Renderer::Instance()->GetTextureSize("winTextTexture").x, Renderer::Instance()->GetTextureSize("winTextTexture").y }));

	LoadGameObjects(_level);
	hud = { players[0].GetTexture() , players[1].GetTexture(), players[0].HP, players[1].HP, timeDown };
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

void SceneGame::CheckWinnerInput(InputManager& input)
{
	if (input.keyInput != "NONE") {
		if (input.keyInput == "Return" && winnerText.text != " ") CheckRanking();
		else if (input.keyInput == "Backspace") {
			if (winnerText.text.length() > 1)winnerText.text = winnerText.text.substr(0, winnerText.text.size() - 1);
			else if (winnerText.text.length() == 1) winnerText.text = " ";
		}
		else if (input.keyInput == "Space") {
			if (winnerText.text.length() <= 5 && winnerText.text.length() > 1)winnerText.text = winnerText.text + " ";
		}
		else if (winnerText.text.length() <= 5 && input.keyInput != "Return") {
			if (winnerText.text.length() == 1 && winnerText.text == " ")winnerText.text = input.keyInput;
			else winnerText.text = winnerText.text + input.keyInput;
		}
	}
}

void SceneGame::CheckRanking()
{
	Renderer* myRenderer = Renderer::Instance();
	std::map<std::string, int> ranking;
	std::string rankFile;
	size_t len;
	bool exsists = true;

	//READ FILE

	std::ifstream inFile("../../res/files/ranking.bin", std::ios::out | std::ios::binary);
	inFile.read(reinterpret_cast<char*>(&len), sizeof(size_t));
	if (!(bool)inFile) exsists = false;
	else {

		char* temp = new char[(int)len + 1];
		inFile.read(temp, len);
		temp[(int)len] = '\0';
		rankFile = temp;
		rankFile = rankFile.substr(0, rankFile.find(";") + 1);
		if (rankFile == FILE_CHECK) {
			rankFile.clear();
			rankFile = temp;
			while (rankFile.substr(rankFile.find(";") + 1) != "\0")
			{
				rankFile = rankFile.substr(rankFile.find(";") + 1);
				ranking[rankFile.substr(0, rankFile.find("-"))] = atoi(rankFile.substr(rankFile.find("-") + 1, rankFile.find(";")).c_str());
			}
		}
		else exsists = false;
	}
	rankFile = FILE_CHECK;
	inFile.close();

	//CREATE A NEW FILE IF IS WRONG
	if (!exsists) {
		std::ofstream fsalida("../../res/files/ranking.bin", std::ios::out | std::ios::binary);
		len = rankFile.size();
		fsalida.write(reinterpret_cast<char*>(&len), sizeof(size_t));
		fsalida.write(rankFile.c_str(), rankFile.size());

		fsalida.close();
	}

	//INSERT WINNER SCORE
	if (players[0].score > players[1].score)
	{
		if (ranking.find(winnerText.text) == ranking.end())
			ranking[winnerText.text] = players[0].score;
		else if (ranking[winnerText.text] < players[0].score) {
			ranking[winnerText.text] = players[0].score;
		}
	}
	else
	{
		if (ranking.find(winnerText.text) == ranking.end())
			ranking[winnerText.text] = players[1].score;
		else if (ranking[winnerText.text] < players[1].score) {
			ranking[winnerText.text] = players[1].score;
		}
	}

	//ORDER RANKING
	std::multimap<int, std::string> orderedRanking;

	for (auto const& pair : ranking) {
		orderedRanking.insert(std::make_pair(pair.second, pair.first));
	}

	//CHECK RANKING SIZE
	if (orderedRanking.size() == 11) orderedRanking.erase(orderedRanking.begin());

	//PRINT
	int i = 0;
	Text textureText;
	for (auto it = orderedRanking.crbegin(); it != orderedRanking.crend(); ++it, i++) {
		rankFile = rankFile + it->second + "-" + std::to_string(it->first) + ";";
		textureText.text = std::to_string(i + 1) + "-" + it->second + " " + std::to_string(it->first) + " POINTS";
		textureText.id = "ranking-" + std::to_string(i + 1);
		textureText.color = { 255, 255, 255, 255 };
		myRenderer->OverwritteTextureText(textureText);
	}

	//SAVE
	std::ofstream fsalida("../../res/files/ranking.bin", std::ios::out | std::ios::binary);
	len = rankFile.size();
	fsalida.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	fsalida.write(rankFile.c_str(), rankFile.size());

	fsalida.close();

	state = e_GameStates::RANKING;
}

void SceneGame::Update(InputManager& _input)
{
	switch (inGameState)
	{
	case SceneState::RUNNING:
	{
		if (_input.returnKeyIsDown()[(int)EKeys::QUIT]) state = e_GameStates::QUIT;
		if (_input.returnKeyIsDown()[(int)EKeys::ESC])
		{
			state = e_GameStates::MENU;
			_input.returnKeyIsDown()[(int)EKeys::ESC] = false;
		}
		if (timeDown <= 0)
		{
			//Exit GameScene!
			timeDown = playTime;
			inGameState = SceneState::GAME_OVER;
		}

#pragma region Players
		//Player Movement and Updates
		for (int i = 0; i < PLAYER_SIZE; i++)
		{
			players[i].Update(_input, deltaTime);
			if (players[0].GetSpawnBomb())	P1Bomb = new Bomb("P1Bomb" + numBombs, players[0].GetPosition());
			if (players[1].GetSpawnBomb())  P2Bomb = new Bomb("P2Bomb" + numBombs, players[1].GetPosition());
		}
		//Update some values at hud were are needed players variables
		hud.UpdateHPPlayer(players[0].HP, players[1].HP);
		hud.UpdateScorePlayer(players[0].score, players[1].score);

		//Colisions between the players and the blocs.
		for (int i = 0; i < blocks.size(); i++)
		{
			if (collisions::isColliding(blocks[i].GetCollisions(), players[0].GetRectCollider()))
			{
				players[0].isColliding = true;
			}

			if (collisions::isColliding(blocks[i].GetCollisions(), players[1].GetRectCollider()))
			{
				players[1].isColliding = true;
			}
		}

		for (int i = 0; i < powerUps.size(); i++)
		{
			if (collisions::isColliding(powerUps[i].GetPosition(), players[0].GetRectCollider()))
			{
				if (powerUps.at(i).GetType() == e_PowerupType::ROLLER_SKATER) { players[0].SpeedUp(); }
				else if (powerUps.at(i).GetType() == e_PowerupType::SHIELD) { players[0].ShieldUp(); }
				powerUps.at(i).Destroy();
			}
			if (collisions::isColliding(powerUps[i].GetPosition(), players[1].GetRectCollider()))
			{
				if (powerUps.at(i).GetType() == e_PowerupType::ROLLER_SKATER) { players[1].SpeedUp(); }
				else if (powerUps.at(i).GetType() == e_PowerupType::SHIELD) { players[1].ShieldUp(); }
				powerUps.at(i).Destroy();
			}
		}
		//Coldown of the bombs (player variable)
		for (int i = 0; i < PLAYER_SIZE; i++)
		{
			if (players[i].GetBombCD() <= 0)
			{
				players[i].CanSpawnBomb();
				players[i].ResetBombCD();
			}

			if (players[i].HP <= 0)
			{
				inGameState = SceneState::GAME_OVER;
			}
		}

		
#pragma endregion	

#pragma region Bombas

		//------ BOMBAS ----- //
		if (P1Bomb != nullptr && P1Bomb->GetBombState() != e_BombState::GONE)
		{
			//UPDATE DE LA PRIMERA BOMBA.
			P1Bomb->Update(_input, deltaTime);
			//CALCULO DE LAS COLISIONES DE LA 1A BOMBA CON LOS 2 PLAYERS
			if (P1Bomb->GetBombState() == e_BombState::EXPLODING)
			{
				Rect* a = P1Bomb->GetExplosionRects();
				for (int i = 0; i < P1Bomb->GetRange(); i++)
				{
					for (int j = 0; j < blocks.size(); j++)
					{
						if (collisions::isColliding(a[i], blocks[j].GetCollisions()))
						{
							P1Bomb->SetExplosionInactive(i);
						}
					}
				}
				//Divido el for P1Bomb->GetRange en 2 porque necesito coger los valores de la de actividad (true o false) cuando ya se ha actualizado (P1Bomb->SetExplosionInactive).
				//Daño al jugador.
				bool* d = P1Bomb->GetExplosionActive();	//Cojo el valor de cada explosion.
				for (int i = 0; i < P1Bomb->GetRange(); i++)
				{
					for (int k = 0; k < blocks.size(); k++)
					{
						if (collisions::isColliding(a[i], blocks[k].GetCollisions()) && blocks[k].GetBlockType() == e_BlockType::BLOCK && d[i] == true)
						{
							blocks[k].Destroy();
							if (blocks[k].GetHasPowerUp())
							{
								PowerUp tmpPowerUp = { "PowerUp" + k , blocks[k].GetPosition() };
								powerUps.push_back(tmpPowerUp);
							}
							players[0].DestroyedBlock();

						}
					}
					for (int j = 0; j < PLAYER_SIZE; j++)
					{
						if (d[i] == true)
						{
							if (collisions::isColliding(a[i], players[j].GetRectCollider()) && players[j].GetCanTakeDmg())
							{
								players[j].TakeDmg();
								if (players[j].GetPlayerType() == e_PlayerType::P2)
								{
									players[0].KilledEnemy();
								}
							}
						}
					}
				}
			}
		}
		if (P2Bomb != nullptr && P2Bomb->GetBombState() != e_BombState::GONE)
		{
			//UPDATE DE LA PRIMERA BOMBA.
			P2Bomb->Update(_input, deltaTime);
			//CALCULO DE LAS COLISIONES DE LA 1A BOMBA CON LOS 2 PLAYERS
			if (P2Bomb->GetBombState() == e_BombState::EXPLODING)
			{
				Rect* b = P2Bomb->GetExplosionRects();
				for (int i = 0; i < P2Bomb->GetRange(); i++)
				{
					for (int j = 0; j < blocks.size(); j++)
					{
						if (collisions::isColliding(b[i], blocks[j].GetCollisions()))
						{
							P2Bomb->SetExplosionInactive(i);
						}
					}
				}
				//Divido el for P2Bomb->GetRange en 2 porque necesito coger los valores de la de actividad (true o false) cuando ya se ha actualizado (P2Bomb->SetExplosionInactive).
				//Daño al jugador.
				bool* c = P2Bomb->GetExplosionActive();	//Cojo el valor de cada explosion.
				for (int i = 0; i < P2Bomb->GetRange(); i++)
				{
					for (int k = 0; k < blocks.size(); k++)
					{
						if (collisions::isColliding(b[i], blocks[k].GetCollisions()) && blocks[k].GetBlockType() == e_BlockType::BLOCK && c[i] == true)
						{
							blocks[k].Destroy();
							if (blocks[k].GetHasPowerUp() == true)
							{
								PowerUp tmpPowerUp = { "PowerUp" + k , blocks[k].GetPosition() };
								powerUps.push_back(tmpPowerUp);
							}
							players[1].DestroyedBlock();

						}
					}
					for (int j = 0; j < PLAYER_SIZE; j++)
					{
						if (c[i] == true)
						{
							if (collisions::isColliding(b[i], players[j].GetRectCollider()) && players[j].GetCanTakeDmg())
							{
								players[j].TakeDmg();
								if (players[j].GetPlayerType() == e_PlayerType::P1)
								{
									players[1].KilledEnemy();
								}
							}
						}
					}
				}
			}
		}
#pragma endregion

#pragma region Blocks

		for (int i = 0; i < blocks.size(); i++)
		{
			blocks[i].Update(_input, deltaTime);
		}

#pragma endregion 

		hud.Update(_input, deltaTime);
	}
	break;
	case SceneState::GAME_OVER:
	{
		if (_input.returnKeyIsDown()[(int)EKeys::QUIT]) state = e_GameStates::QUIT;
		if (_input.returnKeyIsDown()[(int)EKeys::ESC])
		{
			state = e_GameStates::MENU;
			_input.returnKeyIsDown()[(int)EKeys::ESC] = false;
		}
		for (int i = 0; i < 2; i++)
		{
			players[i].SetWinPosition();
		}
		CheckWinnerInput(_input);
		playerWinText.UpdateText(winnerText, 50);
	}
	break;
	default:
		break;
	}
	timeDown -= UpdateDeltaTime();
}
void SceneGame::Draw()
{
	Renderer::Instance()->Clear();
	//Background
	Renderer::Instance()->PushImage("gameBgTexture", "gameBgRect");
	switch (inGameState)
	{
	case SceneState::RUNNING:
	{
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

		for (int i = 0; i < powerUps.size(); i++)
		{
			powerUps.at(i).Draw();
		}

		hud.Draw();
	}
	break;
	case SceneState::GAME_OVER:
	{
		if (players[0].score > players[1].score) players[0].Draw();
		if (players[0].score < players[1].score) players[1].Draw();
		if (players[0].score == players[1].score) players[1].Draw();
		Renderer::Instance()->PushImage("winTextTexture", "winTextRect");
		playerWinText.Draw();
	}
	break;
	default:
		break;
	}

	Renderer::Instance()->Render();
}