#include "SceneGame.h"

SceneGame::SceneGame()
{
	lastTime = clock();
	deltaTime = 0.f;
	timeDown = MAX_TIME;

	//------------- INGAME ---------------
// --- SPRITES ---
#pragma region Backgrounds

	//Game Background
	Renderer::Instance()->LoadTexture("gameBgTexture", "../../res/img/GodenBags/bgCastle.jpg");
	Renderer::Instance()->LoadRect("gameBgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

#pragma endregion

	// --- TEXT --- 
#pragma region Score Boards

	//Text
	Renderer::Instance()->LoadFont(Font({ "Arial", "../../res/ttf/Arial.ttf", 80 }));
	colors["black"] = { 0,0,0,0 };
	texts["playerOneScoreBoardText"] = { "playerOneScoreBoardText", "PlayerOne:", colors["black"], 30, 30 };
	Renderer::Instance()->LoadTextureText("Arial", texts["playerOneScoreBoardText"]);
	Renderer::Instance()->LoadRect("player1ScoreRect", Rect({ 30,30,  Renderer::Instance()->GetTextureSize("playerOneScoreBoardText").x, Renderer::Instance()->GetTextureSize("playerOneScoreBoardText").y }));

	texts["playerTwoScoreBoardText"] = { "playerTwoScoreBoardText", "PlayerTwo:", colors["black"], 30, 120 };
	Renderer::Instance()->LoadTextureText("Arial", texts["playerTwoScoreBoardText"]);
	Renderer::Instance()->LoadRect("player2ScoreRect", Rect({ 30, 120,  Renderer::Instance()->GetTextureSize("playerTwoScoreBoardText").x, Renderer::Instance()->GetTextureSize("playerTwoScoreBoardText").y }));

#pragma endregion

	//--- ANIMATED SPRITES ---
#pragma region Players Ands Scoreboards

			//Players
	Renderer::Instance()->LoadTexture("playerTexture", "../../res/img/GodenBags/spCastle.png");
	Renderer::Instance()->LoadRect("player1Rect", Rect());
	Renderer::Instance()->LoadRect("player1Position", Rect());
	Renderer::Instance()->LoadRect("player2Rect", Rect());
	Renderer::Instance()->LoadRect("player2Position", Rect());

	//ScoreBoard
	Renderer::Instance()->LoadTexture("scoreTexture", "../../res/img/GodenBags/num.png");

	//Players
	playerClass1 = { Renderer::Instance()->GetTextureSize("playerTexture").x, Renderer::Instance()->GetTextureSize("playerTexture").y, PlayerType::P1 };
	playerClass2 = { Renderer::Instance()->GetTextureSize("playerTexture").x, Renderer::Instance()->GetTextureSize("playerTexture").y, PlayerType::P2 };

	//Puntuacion Player 1 & Plyaer 2
	boardP1 = { Renderer::Instance()->GetTextureSize("scoreTexture").x, Renderer::Instance()->GetTextureSize("scoreTexture").y, playerClass1 };
	boardP2 = { Renderer::Instance()->GetTextureSize("scoreTexture").x, Renderer::Instance()->GetTextureSize("scoreTexture").y, playerClass2 };

	Renderer::Instance()->LoadRect("scoreRectPlayer1Right", Rect());
	Renderer::Instance()->LoadRect("scorePositionPlayer1Right", Rect());
	Renderer::Instance()->LoadRect("scoreRectPlayer1Center", Rect());
	Renderer::Instance()->LoadRect("scorePositionPlayer1Center", Rect());
	Renderer::Instance()->LoadRect("scoreRectPlayer1Left", Rect());
	Renderer::Instance()->LoadRect("scorePositionPlayer1Left", Rect());

	Renderer::Instance()->LoadRect("scoreRectPlayer2Right", Rect());
	Renderer::Instance()->LoadRect("scorePositionPlayer2Right", Rect());
	Renderer::Instance()->LoadRect("scoreRectPlayer2Center", Rect());
	Renderer::Instance()->LoadRect("scorePositionPlayer2Center", Rect());
	Renderer::Instance()->LoadRect("scoreRectPlayer2Left", Rect());
	Renderer::Instance()->LoadRect("scorePositionPlayer2Left", Rect());

	//TIME
	texts["timeText"] = { "timeText", "Time: ", colors["black"], SCREEN_WIDTH - 300 , 20 };
	Renderer::Instance()->LoadTextureText("Arial", texts["timeText"]);
	Renderer::Instance()->LoadRect("timeRect", Rect({ SCREEN_WIDTH - 300 , 20,  Renderer::Instance()->GetTextureSize("timeText").x, Renderer::Instance()->GetTextureSize("timeText").y }));
	rectangles["timeRect"] = Rect({ SCREEN_WIDTH - 300 , 20,  Renderer::Instance()->GetTextureSize("timeText").x, Renderer::Instance()->GetTextureSize("timeText").y });

#pragma endregion

#pragma region Coins

	Renderer::Instance()->LoadTexture("coinTexture", "../../res/img/GodenBags/gold.png");

	for (int i = 0; i < AMOUNT_OF_COINS; i++)
	{
		goldenBags[i].SetRect(Rect({ (rand() % SCREEN_WIDTH) - 60, (rand() % 700) + 300, 100,100 }));
		Renderer::Instance()->LoadRect(std::to_string(i), Rect());
	}

#pragma endregion
}

SceneGame::~SceneGame()
{

}

void SceneGame::UpdateDeltaTime()
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
}


void SceneGame::Update(InputManager& _inputs)
{
	//Key Press
	if (_inputs.returnKeyIsDown()[(int)EKeys::QUIT]) state = gameStates::QUIT;
	if (_inputs.returnKeyIsDown()[(int)EKeys::ESC])  state = gameStates::QUIT;
	if (_inputs.returnKeyIsDown()[(int)EKeys::UP]) playerClass1.dir.goUp = true;
	if (_inputs.returnKeyIsDown()[(int)EKeys::DOWN]) playerClass1.dir.goDown = true;
	if (_inputs.returnKeyIsDown()[(int)EKeys::RIGHT]) playerClass1.dir.goRight = true;
	if (_inputs.returnKeyIsDown()[(int)EKeys::LEFT]) playerClass1.dir.goLeft = true;
	if (_inputs.returnKeyIsDown()[(int)EKeys::W]) playerClass2.dir.goUp = true;
	if (_inputs.returnKeyIsDown()[(int)EKeys::S]) playerClass2.dir.goDown = true;
	if (_inputs.returnKeyIsDown()[(int)EKeys::D]) playerClass2.dir.goRight = true;
	if (_inputs.returnKeyIsDown()[(int)EKeys::A]) playerClass2.dir.goLeft = true;

	//Key Release
	if (!_inputs.returnKeyIsDown()[(int)EKeys::UP]) playerClass1.dir.goUp = false;
	if (!_inputs.returnKeyIsDown()[(int)EKeys::DOWN]) playerClass1.dir.goDown = false;
	if (!_inputs.returnKeyIsDown()[(int)EKeys::RIGHT]) playerClass1.dir.goRight = false;
	if (!_inputs.returnKeyIsDown()[(int)EKeys::LEFT]) playerClass1.dir.goLeft = false;
	if (!_inputs.returnKeyIsDown()[(int)EKeys::W]) playerClass2.dir.goUp = false;
	if (!_inputs.returnKeyIsDown()[(int)EKeys::S]) playerClass2.dir.goDown = false;
	if (!_inputs.returnKeyIsDown()[(int)EKeys::D]) playerClass2.dir.goRight = false;
	if (!_inputs.returnKeyIsDown()[(int)EKeys::A]) playerClass2.dir.goLeft = false;

	//Timer Update
	texts["timeText"].UpdateText(std::to_string(timeDown / 100));
	Renderer::Instance()->LoadTextureText("Arial", texts["timeText"]);


	rectangles["timeRect"] = { SCREEN_WIDTH - 150, 20, Renderer::Instance()->GetTextureSize("timeText").x, Renderer::Instance()->GetTextureSize("timeText").y };
	Renderer::Instance()->SetRect("timeRect", rectangles["timeRect"]);

#pragma region Players Movement and Scores

	//Player Movement
	if (state == gameStates::IN_GAME) {
		playerClass1.Update();
		Renderer::Instance()->SetRect("player1Rect", playerClass1.returnRect());
		Renderer::Instance()->SetRect("player1Position", playerClass1.returnPos());

		playerClass2.Update();
		Renderer::Instance()->SetRect("player2Rect", playerClass2.returnRect());
		Renderer::Instance()->SetRect("player2Position", playerClass2.returnPos());
	}

	//If the two get the same item, P1 will always get it
	for (int i = 0; i < AMOUNT_OF_COINS; i++)
	{
		Renderer::Instance()->SetRect(std::to_string(i), goldenBags[i].GetRect());
		if (collisions::rectCollision(playerClass1.returnPos(), goldenBags[i].GetRect())) {
			goldenBags[i].SetRect((rand() % SCREEN_WIDTH) - 60, (rand() % 700) + 300);
			Renderer::Instance()->SetRect(std::to_string(i), goldenBags[i].GetRect());
			playerClass1.score++;
			playerClass1.setGetCoinsToTrue();


		}
		else if (collisions::rectCollision(playerClass2.returnPos(), goldenBags[i].GetRect())) {
			goldenBags[i].SetRect((rand() % SCREEN_WIDTH) - 60, (rand() % 700) + 300);
			Renderer::Instance()->SetRect(std::to_string(i), goldenBags[i].GetRect());
			playerClass2.score++;
			playerClass2.setGetCoinsToTrue();

		}
	}

	//Scoreboards Update
	boardP1.Update(playerClass1);
	Renderer::Instance()->SetRect("scoreRectPlayer1Right", boardP1.returnScoreRectRight());
	Renderer::Instance()->SetRect("scorePositionPlayer1Right", boardP1.returnScorePositionRight());
	Renderer::Instance()->SetRect("scoreRectPlayer1Center", boardP1.returnScoreRectCenter());
	Renderer::Instance()->SetRect("scorePositionPlayer1Center", boardP1.returnScorePositionCenter());
	Renderer::Instance()->SetRect("scoreRectPlayer1Left", boardP1.returnScoreRectLeft());
	Renderer::Instance()->SetRect("scorePositionPlayer1Left", boardP1.returnScorePositionLeft());

	boardP2.Update(playerClass2);
	Renderer::Instance()->SetRect("scoreRectPlayer2Right", boardP2.returnScoreRectRight());
	Renderer::Instance()->SetRect("scorePositionPlayer2Right", boardP2.returnScorePositionRight());
	Renderer::Instance()->SetRect("scoreRectPlayer2Center", boardP2.returnScoreRectCenter());
	Renderer::Instance()->SetRect("scorePositionPlayer2Center", boardP2.returnScorePositionCenter());
	Renderer::Instance()->SetRect("scoreRectPlayer2Left", boardP2.returnScoreRectLeft());
	Renderer::Instance()->SetRect("scorePositionPlayer2Left", boardP2.returnScorePositionLeft());

#pragma endregion

#pragma region Time

	if (timeDown <= 0)
	{
		state = gameStates::MENU;
		timeDown = MAX_TIME;
	}

#pragma endregion
	UpdateDeltaTime();
	timeDown -= deltaTime;
}

void SceneGame::Draw()
{
	Renderer::Instance()->Clear();

	//Background
	Renderer::Instance()->PushImage("gameBgTexture", "gameBgRect");

	//Player Sprites
	Renderer::Instance()->PushSprite("playerTexture", "player1Rect", "player1Position");
	Renderer::Instance()->PushSprite("playerTexture", "player2Rect", "player2Position");

	//Scoreboard Text
	Renderer::Instance()->PushImage("playerOneScoreBoardText", "player1ScoreRect");
	Renderer::Instance()->PushImage("playerTwoScoreBoardText", "player2ScoreRect");

	//Scoreboard Sprites
	Renderer::Instance()->PushSprite("scoreTexture", "scoreRectPlayer1Right", "scorePositionPlayer1Right");
	Renderer::Instance()->PushSprite("scoreTexture", "scoreRectPlayer1Left", "scorePositionPlayer1Left");
	Renderer::Instance()->PushSprite("scoreTexture", "scoreRectPlayer1Center", "scorePositionPlayer1Center");
	Renderer::Instance()->PushSprite("scoreTexture", "scoreRectPlayer2Right", "scorePositionPlayer2Right");
	Renderer::Instance()->PushSprite("scoreTexture", "scoreRectPlayer2Left", "scorePositionPlayer2Left");
	Renderer::Instance()->PushSprite("scoreTexture", "scoreRectPlayer2Center", "scorePositionPlayer2Center");

	//Time
	Renderer::Instance()->PushImage("timeText", "timeRect");

	//Coin bags
	for (int i = 0; i < AMOUNT_OF_COINS; i++)
		Renderer::Instance()->PushImage("coinTexture", std::to_string(i));

	Renderer::Instance()->Render();
}
