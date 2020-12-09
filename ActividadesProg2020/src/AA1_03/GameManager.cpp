#include "GameManager.h"

GameManager::GameManager()
{
	state = gameStates::MENU;
	isRunning = true;
	mouseClicked = false;
	playMenuMusic = false;
	mouseAxis = { 0, 0 };
	playTime = MAX_TIME;
	lastTime = clock();
	deltaTime = 0.f;
}

GameManager::~GameManager()
{

}

void GameManager::UpdateDeltaTime()
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
}

void GameManager::InitiateMenu()
{
	music.PlayMenuMusic();

	//------------- MENU ---------------
	// --- SPRITES ---
#pragma region Backgrounds

	//Main Menu Background
	Renderer::Instance()->LoadTexture("bgTexture", "../../res/img/bg.jpg");
	Renderer::Instance()->LoadRect("bgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

#pragma endregion

#pragma region Cursor

	//Cursor
	Renderer::Instance()->LoadTexture("cursorTexture", "../../res/img/kintoun.png");
	Renderer::Instance()->LoadRect("cursorRect", Rect({ 0, 0, 350, 190 }));
	rectangles["cursorRect"] = Rect({ 0, 0, 350, 190 });

#pragma endregion

	// --- TEXT --- 
#pragma region Title Text

	//All Colors
	colors["title_c"] = Color(250, 135, 20, 0);
	colors["button_c"] = Color(255, 188, 0, 0);
	colors["button_hover_c"] = Color(255, 0, 0, 0);

	//All Texts
	texts["titleTexture"] = { "titleTexture", "My first SDL Game", colors["title_c"], 200,200 };
	texts["playButtonText"] = { "playButtonText", "Play", colors["button_c"], SCREEN_WIDTH / 2, 400 };
	texts["playButtonText_hover"] = { "playButtonText_hover", "Play", colors["button_hover_c"], SCREEN_WIDTH / 2, 400 };
	texts["soundOffButtonText"] = { "soundOffButtonText", "Sound Off", colors["button_c"], SCREEN_WIDTH / 2, 600 };
	texts["soundOffButtonText_hover"] = { "soundOffButtonText_hover", "Sound Off", colors["button_hover_c"], SCREEN_WIDTH / 2, 600 };
	texts["soundOnButtonText"] = { "soundOnButtonText", "Sound On", colors["button_c"], SCREEN_WIDTH / 2, 600 };
	texts["soundOnButtonText_hover"] = { "soundOnButtonText_hover", "Sound On", colors["button_hover_c"], SCREEN_WIDTH / 2, 600 };
	texts["exitButtonText"] = { "exitButtonText", "Exit", colors["button_c"], SCREEN_WIDTH / 2, 800 };
	texts["exitButtonText_hover"] = { "exitButtonText_hover", "Exit", colors["button_hover_c"], SCREEN_WIDTH / 2, 800 };

	//All Flags
	 playHover = false;
	 sondOffHover = false;
	 sondOnHover = false;
	 exitHover = false;

	//Title Text
	Renderer::Instance()->LoadFont(Font({ "SaiyanFont", "../../res/ttf/saiyan.ttf", 200 }));
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["titleTexture"]);
	Renderer::Instance()->LoadRect("titleRect", Rect({ 300, 200, Renderer::Instance()->GetTextureSize("titleTexture").x, Renderer::Instance()->GetTextureSize("titleTexture").y }));

#pragma endregion

#pragma region Play Button 
	//Play Button (Menu)
	//normal surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["playButtonText"]);
	//hover surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["playButtonText_hover"]);
	Renderer::Instance()->LoadRect("playButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("playButtonText").x) / 2, 400, Renderer::Instance()->GetTextureSize("playButtonText").x, Renderer::Instance()->GetTextureSize("playButtonText").y }));
	rectangles["playButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("playButtonText").x) / 2, 400, Renderer::Instance()->GetTextureSize("playButtonText").x, Renderer::Instance()->GetTextureSize("playButtonText").y });

#pragma endregion

#pragma region Sound Off Button

	//Sound Off Button (Menu)
	//normal surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["soundOffButtonText"]);
	//hover surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["soundOffButtonText_hover"]);
	Renderer::Instance()->LoadRect("soundButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("soundOffButtonText").x) / 2, 600, Renderer::Instance()->GetTextureSize("soundOffButtonText").x, Renderer::Instance()->GetTextureSize("soundOffButtonText").y }));
	rectangles["soundButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("soundOffButtonText").x) / 2, 600, Renderer::Instance()->GetTextureSize("soundOffButtonText").x, Renderer::Instance()->GetTextureSize("soundOffButtonText").y });

#pragma endregion

#pragma region Sound On Button

	//Sound On Button (Menu)
	//normal surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["soundOnButtonText"]);
	//hover surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["soundOnButtonText_hover"]);

#pragma endregion

#pragma region Exit Button

	//Exit Button (Menu)
	//normal surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["exitButtonText"]);
	//hover surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["exitButtonText_hover"]);
	Renderer::Instance()->LoadRect("exitButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("exitButtonText").x) / 2, 800, Renderer::Instance()->GetTextureSize("exitButtonText").x, Renderer::Instance()->GetTextureSize("exitButtonText").y }));
	rectangles["exitButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("exitButtonText").x) / 2, 800, Renderer::Instance()->GetTextureSize("exitButtonText").x, Renderer::Instance()->GetTextureSize("exitButtonText").y });

#pragma endregion

}

void GameManager::UpdateMenu()
{
	
#pragma region Menu Interactions

	//Hide Mouse 
	Renderer::Instance()->HideCursor();

	//Putting the Mouse at the center of the cursor 
	rectangles["cursorRect"].x += (((mouseAxis.x - (rectangles["cursorRect"].w / 2)) - rectangles["cursorRect"].x) / 10);
	rectangles["cursorRect"].y += (((mouseAxis.y - (rectangles["cursorRect"].h / 2)) - rectangles["cursorRect"].y) / 10);
	
	Renderer::Instance()->SetRect("cursorRect", rectangles["cursorRect"]);

	//Changing Play Button Texture
	if (collisions::pointCollision(mouseAxis, rectangles["playButtonRect"]))
	{
		//Play Button = HOVER color.
		playHover = true;

		if (mouseClicked) //Start the game
		{
			state = gameStates::IN_GAME;
			mouseClicked = false;
			timeDown = playTime;
			playerClass1.Reset();
			playerClass2.Reset();
			boardP1.Reset();
			boardP2.Reset();
		}
	}
	else
	{
		//Play Button = NORMAL color.
		playHover = false;
	}

	//Changing Sound Off/On Texture
	if (collisions::pointCollision(mouseAxis, rectangles["soundButtonRect"]))
	{
		if (inputs.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT])
		{
			inputs.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT] = false;
			playMenuMusic = !playMenuMusic;
			if (playMenuMusic) music.PauseMenuMusic();
			else music.ResumeMenuMusic();

		}
		if (playMenuMusic)
		{
			//Sound On HOVER color.
			sondOnHover = true;
		}
		else
		{
			//Sound Off HOVER color.
			sondOffHover = true;
		}
	}
	else
	{
		if (playMenuMusic)
		{
			//Sound On NORMAL color.
			sondOnHover = false;
		}
		else
		{
			//Sound Off NORMAL color.
			sondOffHover = false;
		}
	}

	//Changing Exit Button Texture
	if (collisions::pointCollision(mouseAxis, rectangles["exitButtonRect"]))
	{
		//Exit button HOVER color
		exitHover = true;
		
		if (mouseClicked) isRunning = false;
	}
	else
	{
		//Exit button NORMAL color.
		exitHover = false;
	}

#pragma endregion

}

void GameManager::DrawMenu()
{
	Renderer::Instance()->Clear();

	//Background
	Renderer::Instance()->PushImage("bgTexture", "bgRect");
	//Cursor
	Renderer::Instance()->PushImage("cursorTexture", "cursorRect");
	//Title
	Renderer::Instance()->PushImage("titleTexture", "titleRect");
	Renderer::Instance()->PushImage("titleTexture_hover", "titleRect");
	//Pay Button
	// Renderer::Instance()->PushImage(playHover, "playButtonRect")
	if (playHover)	Renderer::Instance()->PushImage("playButtonText_hover", "playButtonRect");
	else Renderer::Instance()->PushImage("playButtonText", "playButtonRect");
	//Exit Button
	if(exitHover) Renderer::Instance()->PushImage("exitButtonText_hover", "exitButtonRect");
	else Renderer::Instance()->PushImage("exitButtonText", "exitButtonRect");
	//Sound Button
	if (playMenuMusic) 
		if (sondOnHover) Renderer::Instance()->PushImage("soundOnButtonText_hover", "soundButtonRect");
		else Renderer::Instance()->PushImage("soundOnButtonText", "soundButtonRect");
	else 
		if (sondOffHover) Renderer::Instance()->PushImage("soundOffButtonText_hover", "soundButtonRect");
		else Renderer::Instance()->PushImage("soundOnButtonText", "soundButtonRect");

	Renderer::Instance()->Render();

}

void GameManager::InitiateGame()
{

	//------------- INGAME ---------------
	// --- SPRITES ---
#pragma region Backgrounds

	//Game Background
	Renderer::Instance()->LoadTexture("gameBgTexture", "../../res/img/bgCastle.jpg");
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
	Renderer::Instance()->LoadTexture("playerTexture", "../../res/img/spCastle.png");
	Renderer::Instance()->LoadRect("player1Rect", Rect());
	Renderer::Instance()->LoadRect("player1Position", Rect());
	Renderer::Instance()->LoadRect("player2Rect", Rect());
	Renderer::Instance()->LoadRect("player2Position", Rect());

	//ScoreBoard
	Renderer::Instance()->LoadTexture("scoreTexture", "../../res/img/num.png");

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

	Renderer::Instance()->LoadTexture("coinTexture", "../../res/img/gold.png");

	for (int i = 0; i < AMOUNT_OF_COINS; i++)
	{
		coinRect[i] = Rect({ (rand() % SCREEN_WIDTH) - 10, (rand() % 700) + 300, 100,100 });
		Renderer::Instance()->LoadRect(std::to_string(i), Rect());
	}

#pragma endregion

}

void GameManager::UpdateGame()
{
	//Timer Update
	//std::string s = FloatToString(timeDown, 2);
	texts["timeText"].UpdateText(std::to_string(timeDown/100));
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
		Renderer::Instance()->SetRect(std::to_string(i), coinRect[i]);
		if (collisions::rectCollision(playerClass1.returnPos(), coinRect[i])) {
			coinRect[i].x = (rand() % SCREEN_WIDTH) - 10;
			coinRect[i].y = (rand() % 700) + 300;
			Renderer::Instance()->SetRect(std::to_string(i), coinRect[i]);
			playerClass1.score++;
			playerClass1.setGetCoinsToTrue();

		}
		else if (collisions::rectCollision(playerClass2.returnPos(), coinRect[i])) {
			coinRect[i].x = (rand() % SCREEN_WIDTH) - 10;
			coinRect[i].y = (rand() % 700) + 300;
			Renderer::Instance()->SetRect(std::to_string(i), coinRect[i]);
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
		timeDown = playTime;
	}

#pragma endregion

}

void GameManager::DrawGame()
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

void GameManager::Run()
{
	InitiateMenu();
	InitiateGame();
	
	while (isRunning) {

		Renderer::Instance()->StartFrameControl();
		//Realizamos el update de los inputs y los mapeamos
		inputs.Update();
		mouseAxis = inputs.returnMouseAxis();

		//Key Press
		if (inputs.returnKeyIsDown()[(int)EKeys::QUIT]) isRunning = false;
		if (inputs.returnKeyIsDown()[(int)EKeys::ESC])  isRunning = false;
		if (inputs.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT]) mouseClicked = true;
		if (inputs.returnKeyIsDown()[(int)EKeys::UP]) playerClass1.dir.goUp = true;
		if (inputs.returnKeyIsDown()[(int)EKeys::DOWN]) playerClass1.dir.goDown = true;
		if (inputs.returnKeyIsDown()[(int)EKeys::RIGHT]) playerClass1.dir.goRight = true;
		if (inputs.returnKeyIsDown()[(int)EKeys::LEFT]) playerClass1.dir.goLeft = true;
		if (inputs.returnKeyIsDown()[(int)EKeys::W]) playerClass2.dir.goUp = true;
		if (inputs.returnKeyIsDown()[(int)EKeys::S]) playerClass2.dir.goDown = true;
		if (inputs.returnKeyIsDown()[(int)EKeys::D]) playerClass2.dir.goRight = true;
		if (inputs.returnKeyIsDown()[(int)EKeys::A]) playerClass2.dir.goLeft = true;

		//Key Release
		if (!inputs.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT]) mouseClicked = false;
		if (!inputs.returnKeyIsDown()[(int)EKeys::UP]) playerClass1.dir.goUp = false;
		if (!inputs.returnKeyIsDown()[(int)EKeys::DOWN]) playerClass1.dir.goDown = false;
		if (!inputs.returnKeyIsDown()[(int)EKeys::RIGHT]) playerClass1.dir.goRight = false;
		if (!inputs.returnKeyIsDown()[(int)EKeys::LEFT]) playerClass1.dir.goLeft = false;
		if (!inputs.returnKeyIsDown()[(int)EKeys::W]) playerClass2.dir.goUp = false;
		if (!inputs.returnKeyIsDown()[(int)EKeys::S]) playerClass2.dir.goDown = false;
		if (!inputs.returnKeyIsDown()[(int)EKeys::D]) playerClass2.dir.goRight = false;
		if (!inputs.returnKeyIsDown()[(int)EKeys::A]) playerClass2.dir.goLeft = false;

		switch (state)
		{
		case gameStates::MENU:
			UpdateMenu();
			DrawMenu();

			break;
		case gameStates::IN_GAME:
			UpdateGame();
			DrawGame();

			break;
		default:
			break;
		}

		UpdateDeltaTime();
		timeDown -= deltaTime;
		Renderer::Instance()->EndFrameControl();

	}
}

