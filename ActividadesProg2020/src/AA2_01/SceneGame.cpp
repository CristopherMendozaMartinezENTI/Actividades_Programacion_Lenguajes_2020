#include "SceneGame.h"
#include "Utils.h"

SceneGame::SceneGame()
{
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


void SceneGame::Update(InputManager _input)
{
#pragma region Players

	//Player Movement
	for (int i = 0; i < PLAYER_SIZE; i++)
	{
		players[i].Update(_input);

		if (players[i].GetSpawnBomb())
		{

			bombs.push_back(new Bomb(i + "Bomb" + numBombs, players[i].GetPosition()));
			numBombs++;

		}
	}

#pragma endregion

#pragma region Time

	if (timeDown <= 0)
	{
		//Exit GameScene!
		timeDown = playTime;
	}

#pragma endregion
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs.at(i)->Update(_input);
		bombs.at(i)->Update(deltaTime);

		if (bombs.at(i)->GetBombState() == e_BombState::GONE)
		{
			//std::cout << " hello" << std::endl;
			//delete bombs.at(i);
			//Aqui tendria que ir sacar la bomba del vector y hacer el delete, pero no se como manejarlo
		}
	}
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
	for (int i = 0; i < bombs.size(); i++)
	{
		bombs.at(i)->Draw();
	}

	Renderer::Instance()->Render();
}
