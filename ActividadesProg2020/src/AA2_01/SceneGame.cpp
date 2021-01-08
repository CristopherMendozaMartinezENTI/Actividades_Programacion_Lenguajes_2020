#include "SceneGame.h"
#include "Utils.h"

SceneGame::SceneGame()
{
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
	players[0] = { 4, 3, "Player1" , "../../res/img/player1.png", e_PlayerType::P1 };
	players[1] = { 4, 3, "Player2" , "../../res/img/player2.png", e_PlayerType::P2 };

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
	if (_input.returnKeyIsDown()[(int)EKeys::ESC])  state = e_GameStates::QUIT;

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

	//Player Sprites
	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		players[i].Draw();
	}
	
	if (P1Bomb != nullptr && P1Bomb->GetBombState() != e_BombState::GONE)
	{
		P1Bomb->Draw();
	}
	if (P2Bomb != nullptr && P2Bomb->GetBombState() != e_BombState::GONE)
	{
		P2Bomb->Draw();
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
