#include "GameManager.h"

GameManager::GameManager()
{
	state = gameStates::MENU;
	isRunning = true;
	mouseClicked = false;
	playMenuMusic = false;
	mouseAxis = { 0, 0 };

//------------- MENU ---------------
		// --- SPRITES ---
#pragma region Backgrounds

	//Main Menu Background
	renderer.LoadTexture("bgTexture", "../../res/img/bg.jpg");
	renderer.LoadRect("bgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

#pragma endregion

#pragma region Cursor

	//Cursor
	renderer.LoadTexture("cursorTexture", "../../res/img/kintoun.png");
	renderer.LoadRect("cursorRect", Rect({ 0, 0, 350, 190 }));
	rectangles["cursorRect"] = Rect({ 0, 0, 350, 190 });

#pragma endregion

		// --- TEXT --- 
#pragma region Title Text

	/*
	//All Colors
	Color c{ 255,210,10,0 };
	Color button_c{ 255, 128, 0, 0 };
	
	//All Texts
	texts["titleTexture"] = { "titleTexture", "My first SDL Game", c, 200,200 };
	texts["playButtonText"] = { "playButtonText", "Play", button_c, SCREEN_WIDTH / 2, 400 };
	texts["soundOffButtonText"] = { "soundOffButtonText", "Sound Off", button_c, SCREEN_WIDTH / 2, 600 };
	texts["soundOnButtonText"] = { "soundOnButtonText", "Sound On", button_c, SCREEN_WIDTH / 2, 600 };
	texts["exitButtonText"] = { "exitButtonText", "Exit", button_c, SCREEN_WIDTH / 2, 800 };

	*/

	//Title Text
	
	renderer.LoadFont(Font({ "SaiyanFont", "../../res/ttf/saiyan.ttf", 200 }));
	Color c{ 255,210,10,0 };
	Text titulo{ "titleTexture", "My First SDL Game", c, 200, 200 };
	renderer.LoadTextureText("SaiyanFont", titulo);
	renderer.LoadRect("titleRect", Rect({ 300, 200, renderer.GetTextureSize("titleTexture").x, renderer.GetTextureSize("titleTexture").y }));

#pragma endregion

#pragma region Play Button 
	//Play Button (Menu)

	Color button_c{ 255, 128, 0, 0 };

	Text playButtonText{ "playButtonTexture", "Play", button_c, SCREEN_WIDTH / 2, 400 };
	renderer.LoadTextureText("SaiyanFont", playButtonText);
	renderer.LoadRect("playButtonRect", Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("playButtonTexture").x) / 2, 400, renderer.GetTextureSize("playButtonTexture").x, renderer.GetTextureSize("playButtonTexture").y }));
	rectangles["playButtonRect"] = Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("playButtonTexture").x) / 2, 400, renderer.GetTextureSize("playButtonTexture").x, renderer.GetTextureSize("playButtonTexture").y });

#pragma endregion

#pragma region Sound Off Button

	//Sound Off Button (Menu)
	Text soundOffButtonText{ "soundOffButtonTexture", "Sound Off", button_c, SCREEN_WIDTH / 2, 600 };
	renderer.LoadTextureText("SaiyanFont", soundOffButtonText);
	renderer.LoadRect("soundButtonRect", Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("soundOffButtonTexture").x) / 2, 600, renderer.GetTextureSize("soundOffButtonTexture").x, renderer.GetTextureSize("soundOffButtonTexture").y }));
	rectangles["soundButtonRect"] = Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("soundOffButtonTexture").x) / 2, 600, renderer.GetTextureSize("soundOffButtonTexture").x, renderer.GetTextureSize("soundOffButtonTexture").y });

#pragma endregion

#pragma region Sound On Button

	//Sound On Button (Menu)
	Text soundOnButtonText{ "soundOnButtonTexture", "Sound On", button_c, SCREEN_WIDTH / 2, 600 };
	renderer.LoadTextureText("SaiyanFont", soundOnButtonText);

#pragma endregion

#pragma region Exit Button

	//Exit Button (Menu)

	Text exitButtonText{ "exitButtonTexture", "Exit", button_c, SCREEN_WIDTH / 2, 800 };
	renderer.LoadTextureText("SaiyanFont", exitButtonText);
	renderer.LoadRect("exitButtonRect", Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("exitButtonTexture").x) / 2, 800, renderer.GetTextureSize("exitButtonTexture").x, renderer.GetTextureSize("exitButtonTexture").y }));
	rectangles["exitButtonRect"] = Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("exitButtonTexture").x) / 2, 800, renderer.GetTextureSize("exitButtonTexture").x, renderer.GetTextureSize("exitButtonTexture").y });

#pragma endregion

//------------- INGAME ---------------
		// --- SPRITES ---
#pragma region Backgrounds

	//Game Background
	renderer.LoadTexture("gameBgTexture", "../../res/img/bgCastle.jpg");
	renderer.LoadRect("gameBgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

#pragma endregion

		// --- TEXT --- 
#pragma region Score Boards

	//Player 1 text

	renderer.LoadFont(Font({ "Arial", "../../res/ttf/Arial.ttf", 80 }));
	Color black{ 0,0,0,0 };
	Text playerOneScoreBoard{ "player1ScoreTexture", "PlayerOne:", black, 30, 30 };
	renderer.LoadTextureText("Arial", playerOneScoreBoard);
	renderer.LoadRect("player1ScoreRect", Rect({ 30,30,  renderer.GetTextureSize("player1ScoreTexture").x, renderer.GetTextureSize("player1ScoreTexture").y }));

	Text playerTwoScoreBoard{ "player2ScoreTexture", "PlayerTwo:", black, 30, 120 };
	renderer.LoadTextureText("Arial", playerTwoScoreBoard);
	renderer.LoadRect("player2ScoreRect", Rect({ 30, 120,  renderer.GetTextureSize("player2ScoreTexture").x, renderer.GetTextureSize("player2ScoreTexture").y }));

#pragma endregion

	//--- ANIMATED SPRITES ---
#pragma region Players Ands Scoreboards

			//Players
	renderer.LoadTexture("playerTexture", "../../res/img/spCastle.png");
	renderer.LoadRect("player1Rect", Rect());
	renderer.LoadRect("player1Position", Rect());
	renderer.LoadRect("player2Rect", Rect());
	renderer.LoadRect("player2Position", Rect());

	//ScoreBoard
	renderer.LoadTexture("scoreTexture", "../../res/img/num.png");

	//Players
	playerClass1 = { renderer.GetTextureSize("playerTexture").x, renderer.GetTextureSize("playerTexture").y, PlayerType::P1 };
	playerClass2 = { renderer.GetTextureSize("playerTexture").x, renderer.GetTextureSize("playerTexture").y, PlayerType::P2 };

	//Puntuacion Player 1 & Plyaer 2
	boardP1 = { renderer.GetTextureSize("scoreTexture").x, renderer.GetTextureSize("scoreTexture").y, playerClass1 };
	boardP2 = { renderer.GetTextureSize("scoreTexture").x, renderer.GetTextureSize("scoreTexture").y, playerClass2 };

	renderer.LoadRect("scoreRectPlayer1Right", Rect());
	renderer.LoadRect("scorePositionPlayer1Right", Rect());
	renderer.LoadRect("scoreRectPlayer1Center", Rect());
	renderer.LoadRect("scorePositionPlayer1Center", Rect());
	renderer.LoadRect("scoreRectPlayer1Left", Rect());
	renderer.LoadRect("scorePositionPlayer1Left", Rect());

	renderer.LoadRect("scoreRectPlayer2Right", Rect());
	renderer.LoadRect("scorePositionPlayer2Right", Rect());
	renderer.LoadRect("scoreRectPlayer2Center", Rect());
	renderer.LoadRect("scorePositionPlayer2Center", Rect());
	renderer.LoadRect("scoreRectPlayer2Left", Rect());
	renderer.LoadRect("scorePositionPlayer2Left", Rect());

#pragma endregion

#pragma region Coins

	renderer.LoadTexture("coinTexture", "../../res/img/gold.png");

	for (int i = 0; i < AMOUNT_OF_COINS; i++)
	{
		coinRect[i] = Rect({ (rand() % SCREEN_WIDTH) - 10, (rand() % 700) + 300, 100,100 });
		renderer.LoadRect(std::to_string(i), Rect()); 
	}

#pragma endregion

#pragma region Audio
	/*

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		throw std::exception("Unable to open SDL_Mixer sound systems");
	}

	//Title Music
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	menuMusic = Mix_LoadMUS("../../res/au/mainTheme.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	Mix_PlayMusic(menuMusic, -1);

	*/
#pragma endregion

}

GameManager::~GameManager()
{
	Destroy();
}

void GameManager::InitiateMenu()
{


}

void GameManager::UpdateMenu()
{
	Color button_hover_c{ 255,0,0,0 };
	Color button_c{ 255, 128, 0, 0 };

	Text playButtonText{ "playButtonTexture", "Play", button_c, SCREEN_WIDTH / 2, 400 };
	Text soundOffButtonText{ "soundOffButtonTexture", "Sound Off", button_c, SCREEN_WIDTH / 2, 600 };
	Text soundOnButtonText{ "soundOnButtonTexture", "Sound On", button_c, SCREEN_WIDTH / 2, 600 };
	Text exitButtonText{ "exitButtonTexture", "Exit", button_c, SCREEN_WIDTH / 2, 800 };

#pragma region Menu Interactions

	//Hide Mouse 
	SDL_ShowCursor(SDL_DISABLE);

	//Putting the Mouse at the center of the cursor 
	rectangles["cursorRect"].x += (((mouseAxis.x - (rectangles["cursorRect"].w / 2)) - rectangles["cursorRect"].x) / 10);
	rectangles["cursorRect"].y += (((mouseAxis.y - (rectangles["cursorRect"].h / 2)) - rectangles["cursorRect"].y) / 10);
	renderer.SetRect("cursorRect", rectangles["cursorRect"]);

	//Changing Play Button Texture
	if (collisions::pointCollision(mouseAxis, rectangles["playButtonRect"]))
	{
		playButtonText.UpdateColor(button_hover_c);
		renderer.LoadTextureText("SaiyanFont", playButtonText);

		if (mouseClicked)
		{
			state = gameStates::IN_GAME;
			mouseClicked = false;
			sec = 0;
			playerClass1.Reset();
			playerClass2.Reset();
			boardP1.Reset();
			boardP2.Reset();
		}
	}
	else
	{
		renderer.LoadTextureText("SaiyanFont", playButtonText);
	}
		
	//Changing Sound Off/On Texture
	if (collisions::pointCollision(mouseAxis, rectangles["soundButtonRect"]))
	{
		if (mouseClicked)
		{
			mouseClicked = false;
			playMenuMusic = !playMenuMusic;
			if (playMenuMusic) Mix_PauseMusic();
			else Mix_PlayMusic(menuMusic, 100);

		}
		if (playMenuMusic)
		{

			soundOnButtonText.UpdateColor(button_hover_c);
			renderer.LoadTextureText("SaiyanFont", soundOnButtonText);
		}
		else
		{
			soundOffButtonText.UpdateColor(button_hover_c);
			renderer.LoadTextureText("SaiyanFont", soundOffButtonText);
		}
	}
	else
	{
		if (playMenuMusic)
		{
			renderer.LoadTextureText("SaiyanFont", soundOnButtonText);
		}
		else
		{
			renderer.LoadTextureText("SaiyanFont", soundOffButtonText);
		}
	}

	//Changing Exit Button Texture
	if (collisions::pointCollision(mouseAxis, rectangles["exitButtonRect"]))
	{
		exitButtonText.UpdateColor(button_hover_c);
		renderer.LoadTextureText("SaiyanFont", exitButtonText);
		
		if (mouseClicked) isRunning = false;
	}
	else
	{
		renderer.LoadTextureText("SaiyanFont", exitButtonText);
	}

#pragma endregion

}

void GameManager::DrawMenu()
{
	renderer.Clear();

	//Background
	renderer.PushImage("bgTexture", "bgRect");
	//Cursor
	renderer.PushImage("cursorTexture", "cursorRect");
	//Title
	renderer.PushImage("titleTexture", "titleRect");
	//Play Button
	renderer.PushImage("playButtonTexture", "playButtonRect");
	//Exit Button
	renderer.PushImage("exitButtonTexture", "exitButtonRect");
	//Sound Button
	if (playMenuMusic) renderer.PushImage("soundOnButtonTexture", "soundButtonRect");
	else renderer.PushImage("soundOffButtonTexture", "soundButtonRect");

	renderer.Render();

}

void GameManager::InitiateGame()
{

}

void GameManager::UpdateGame()
{

#pragma region Players Movement and Scores

	//Player Movement
	if (state == gameStates::IN_GAME) {
		playerClass1.Update();
		renderer.SetRect("player1Rect", playerClass1.returnRect());
		renderer.SetRect("player1Position", playerClass1.returnPos());

		playerClass2.Update();
		renderer.SetRect("player2Rect", playerClass2.returnRect());
		renderer.SetRect("player2Position", playerClass2.returnPos());
	}

	/*
	//If the two get the same item, P1 will always get it
	for (int i = 0; i < AMOUNT_OF_COINS; i++)
	{
		renderer.SetRect(std::to_string(i), coinRect[i]);
		if (collisions::rectCollision(playerClass1.returnPos(), coinRect[i])) {
			coinRect[i].x = (rand() % SCREEN_WIDTH) - 10;
			coinRect[i].y = (rand() % 700) + 300;
			renderer.SetRect(std::to_string(i), coinRect[i]);
			playerClass1.score++;
			playerClass1.setGetCoinsToTrue();

		}
		else if (collisions::rectCollision(playerClass2.returnPos(), coinRect[i])) {
			coinRect[i].x = (rand() % SCREEN_WIDTH) - 10;
			coinRect[i].y = (rand() % 700) + 300;
			renderer.SetRect(std::to_string(i), coinRect[i]);
			playerClass2.score++;
			playerClass2.setGetCoinsToTrue();
		}
	}
	*/

	//Scoreboards Update
	boardP1.Update(playerClass1);
	renderer.SetRect("scoreRectPlayer1Right", boardP1.returnScoreRectRight());
	renderer.SetRect("scorePositionPlayer1Right", boardP1.returnScorePositionRight());
	renderer.SetRect("scoreRectPlayer1Center", boardP1.returnScoreRectCenter());
	renderer.SetRect("scorePositionPlayer1Center", boardP1.returnScorePositionCenter());
	renderer.SetRect("scoreRectPlayer1Left", boardP1.returnScoreRectLeft());
	renderer.SetRect("scorePositionPlayer1Left",  boardP1.returnScorePositionLeft());

	boardP2.Update(playerClass2);
	renderer.SetRect("scoreRectPlayer2Right" , boardP2.returnScoreRectRight());
	renderer.SetRect("scorePositionPlayer2Right" , boardP2.returnScorePositionRight());
	renderer.SetRect("scoreRectPlayer2Center" , boardP2.returnScoreRectCenter());
	renderer.SetRect("scorePositionPlayer2Center" , boardP2.returnScorePositionCenter());
	renderer.SetRect("scoreRectPlayer2Left", boardP2.returnScoreRectLeft());
	renderer.SetRect("scorePositionPlayer2Left", boardP2.returnScorePositionLeft());

#pragma endregion

#pragma region Time

	//Time
	sec += DELAY_TIME;
	if (sec >= MAX_TIME) state = gameStates::MENU;

	/*
	int timeLeft = (MAX_TIME - sec) / 1000;
	int size = sizeof(exactTime);
	SDL_snprintf(exactTime, size, "%i", timeLeft);

	tmpSurf = { TTF_RenderText_Blended(inGameFont, exactTime, SDL_Color{ 255,0,0,0 }) };
	if (tmpSurf == nullptr) throw std::exception("No es pot crear SDL surface");
	textures["timeTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	rectangles["timeRect"] = { SCREEN_WIDTH - 150, 65, tmpSurf->w, tmpSurf->h };
	*/
#pragma endregion
	
}

void GameManager::DrawGame()
{
	renderer.Clear();

	//Background
	renderer.PushImage("gameBgTexture", "gameBgRect");

	//Player Sprites
	renderer.PushSprite("playerTexture", "player1Rect", "player1Position");
	renderer.PushSprite("playerTexture", "player2Rect", "player2Position");
	
	//Scoreboard Text
	renderer.PushImage("player1ScoreTexture", "player1ScoreRect");
	renderer.PushImage("player2ScoreTexture", "player2ScoreRect");

	//Scoreboard Sprites
	renderer.PushSprite("scoreTexture", "scoreRectPlayer1Right", "scorePositionPlayer1Right");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer1Left", "scorePositionPlayer1Left");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer1Center", "scorePositionPlayer1Center");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer2Right", "scorePositionPlayer2Right");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer2Left", "scorePositionPlayer2Left");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer2Center", "scorePositionPlayer2Center");

	//Coin bags
	for (int i = 0; i < AMOUNT_OF_COINS; i++)
		renderer.PushImage("coinTexture", std::to_string(i));

	renderer.Render();
}

void GameManager::Run()
{
	while (isRunning) {
		frameStart = SDL_GetTicks();
		// HANDLE EVENTS
		while (SDL_PollEvent(&event))
		{
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
				if (event.key.keysym.sym == SDLK_UP) playerClass1.dir.goUp = true;
				if (event.key.keysym.sym == SDLK_DOWN) playerClass1.dir.goDown = true;
				if (event.key.keysym.sym == SDLK_RIGHT) playerClass1.dir.goRight = true;
				if (event.key.keysym.sym == SDLK_LEFT) playerClass1.dir.goLeft = true;
				if (event.key.keysym.sym == SDLK_w) playerClass2.dir.goUp = true;
				if (event.key.keysym.sym == SDLK_s) playerClass2.dir.goDown = true;
				if (event.key.keysym.sym == SDLK_d) playerClass2.dir.goRight = true;
				if (event.key.keysym.sym == SDLK_a) playerClass2.dir.goLeft = true;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP)  playerClass1.dir.goUp = false;
				if (event.key.keysym.sym == SDLK_DOWN)  playerClass1.dir.goDown = false;
				if (event.key.keysym.sym == SDLK_RIGHT) playerClass1.dir.goRight = false;
				if (event.key.keysym.sym == SDLK_LEFT) playerClass1.dir.goLeft = false;
				if (event.key.keysym.sym == SDLK_w) playerClass2.dir.goUp = false;
				if (event.key.keysym.sym == SDLK_s) playerClass2.dir.goDown = false;
				if (event.key.keysym.sym == SDLK_d)	playerClass2.dir.goRight = false;
				if (event.key.keysym.sym == SDLK_a)	playerClass2.dir.goLeft = false;
				break;
			case SDL_MOUSEMOTION:
				mouseAxis.x = event.motion.x;
				mouseAxis.y = event.motion.y;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
					mouseClicked = true;
				break;
			default:;
			}
		}

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

		//Frame Control
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
			SDL_Delay((int)(DELAY_TIME - frameTime));

	}
}

void GameManager::Destroy()
{
	//renderer.~Renderer();

	/*
	for (std::pair<std::string, SDL_Texture*> element : textures) {
		SDL_DestroyTexture(textures[element.first]);
	}

	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);
	TTF_CloseFont(inGameFont);
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	Mix_Quit();
	*/
}
