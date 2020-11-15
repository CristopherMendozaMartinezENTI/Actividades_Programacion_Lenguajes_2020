#include "GameManager.h"

GameManager::GameManager()
{
	state = gameStates::MENU;
	isRunning = true;
	mouseClicked = false;
	playMenuMusic = false;
	mouseAxis = { 0, 0 };
	playTime = 10.f;

}

GameManager::~GameManager()
{
	Destroy();
}

void GameManager::InitiateMenu()
{

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

	//All Colors

	colors["title_c"] = Color(250, 135, 20, 0);
	colors["button_c"] = Color(255, 188, 0, 0);
	colors["button_hover_c"] = Color(255, 0, 0, 0);

	//All Texts
	texts["titleTexture"] = { "titleTexture", "My first SDL Game", colors["title_c"], 200,200 };
	texts["playButtonText"] = { "playButtonText", "Play", colors["button_c"], SCREEN_WIDTH / 2, 400 };
	texts["soundOffButtonText"] = { "soundOffButtonText", "Sound Off", colors["button_c"], SCREEN_WIDTH / 2, 600 };
	texts["soundOnButtonText"] = { "soundOnButtonText", "Sound On", colors["button_c"], SCREEN_WIDTH / 2, 600 };
	texts["exitButtonText"] = { "exitButtonText", "Exit", colors["button_c"], SCREEN_WIDTH / 2, 800 };

	//Title Text

	renderer.LoadFont(Font({ "SaiyanFont", "../../res/ttf/saiyan.ttf", 200 }));
	renderer.LoadTextureText("SaiyanFont", texts["titleTexture"]);
	renderer.LoadRect("titleRect", Rect({ 300, 200, renderer.GetTextureSize("titleTexture").x, renderer.GetTextureSize("titleTexture").y }));

	//font = { TTF_OpenFont("../../res/ttf/saiyan.ttf", 200) };
	//if (font == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
	//tmpSurf = { TTF_RenderText_Blended(font, "My First SDL Game", SDL_Color{255,210,10,0}) };
	//if (tmpSurf == nullptr) throw std::exception("No es pot crear SDL surface");
	//rectangles["titleRect"] = { (SCREEN_WIDTH - tmpSurf->w) / 2, 200, tmpSurf->w, tmpSurf->h };
	//textures["titleTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Play Button 
	//Play Button (Menu)

	renderer.LoadTextureText("SaiyanFont", texts["playButtonText"]);
	renderer.LoadRect("playButtonRect", Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("playButtonText").x) / 2, 400, renderer.GetTextureSize("playButtonText").x, renderer.GetTextureSize("playButtonText").y }));
	rectangles["playButtonRect"] = Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("playButtonText").x) / 2, 400, renderer.GetTextureSize("playButtonText").x, renderer.GetTextureSize("playButtonText").y });

	//tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,128,0,0 }) };
	//textures["playTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//rectangles["playButtonRect"] = { (SCREEN_WIDTH - tmpSurf->w) / 2, 400, tmpSurf->w, tmpSurf->h };
	//tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,0,0,0 }) };
	//textures["playHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//textures["playAux"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound Off Button

	//Sound Off Button (Menu)
	renderer.LoadTextureText("SaiyanFont", texts["soundOffButtonText"]);
	renderer.LoadRect("soundButtonRect", Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("soundOffButtonText").x) / 2, 600, renderer.GetTextureSize("soundOffButtonText").x, renderer.GetTextureSize("soundOffButtonText").y }));
	rectangles["soundButtonRect"] = Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("soundOffButtonText").x) / 2, 600, renderer.GetTextureSize("soundOffButtonText").x, renderer.GetTextureSize("soundOffButtonText").y });

	//tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,128,0,0 }) };
	//textures["soundOffTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,0,0,0 }) };
	//textures["soundOffHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//textures["soundOffAux"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound On Button

	//Sound On Button (Menu)
	renderer.LoadTextureText("SaiyanFont", texts["soundOnButtonText"]);

	//tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,128,0,0 }) };
	//textures["soundOnTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,0,0,0 }) };
	//textures["soundOnHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Exit Button

	//Exit Button (Menu)

	renderer.LoadTextureText("SaiyanFont", texts["exitButtonText"]);
	renderer.LoadRect("exitButtonRect", Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("exitButtonText").x) / 2, 800, renderer.GetTextureSize("exitButtonText").x, renderer.GetTextureSize("exitButtonText").y }));
	rectangles["exitButtonRect"] = Rect({ (SCREEN_WIDTH - renderer.GetTextureSize("exitButtonText").x) / 2, 800, renderer.GetTextureSize("exitButtonText").x, renderer.GetTextureSize("exitButtonText").y });

#pragma endregion

}

void GameManager::UpdateMenu()
{
	
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
		//Play Button = HOVER color.
		texts["playButtonText"].UpdateColor(colors["button_hover_c"]);
		renderer.LoadTextureText("SaiyanFont", texts["playButtonText"]);

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
		texts["playButtonText"].UpdateColor(colors["button_c"]);
		renderer.LoadTextureText("SaiyanFont", texts["playButtonText"]);
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
			//Sound On HOVER color.
			texts["soundOnButtonText"].UpdateColor(colors["button_hover_c"]);
			renderer.LoadTextureText("SaiyanFont", texts["soundOnButtonText"]);
		}
		else
		{
			//Sound Off HOVER color.
			texts["soundOffButtonText"].UpdateColor(colors["button_hover_c"]);
			renderer.LoadTextureText("SaiyanFont", texts["soundOffButtonText"]);
		}
	}
	else
	{
		if (playMenuMusic)
		{
			//Sound On NORMAL color.
			texts["soundOnButtonText"].UpdateColor(colors["button_c"]);
			renderer.LoadTextureText("SaiyanFont", texts["soundOnButtonText"]);
		}
		else
		{
			//Sound Off NORMAL color.
			texts["soundOffButtonText"].UpdateColor(colors["button_c"]);
			renderer.LoadTextureText("SaiyanFont", texts["soundOffButtonText"]);
		}
	}

	//Changing Exit Button Texture
	if (collisions::pointCollision(mouseAxis, rectangles["exitButtonRect"]))
	{
		//Exit button HOVER color
		texts["exitButtonText"].UpdateColor(colors["button_hover_c"]);
		renderer.LoadTextureText("SaiyanFont", texts["exitButtonText"]);
		
		if (mouseClicked) isRunning = false;
	}
	else
	{
		//Exit button NORMAL color.
		texts["exitButtonText"].UpdateColor(colors["button_c"]);
		renderer.LoadTextureText("SaiyanFont", texts["exitButtonText"]);
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
	renderer.PushImage("playButtonText", "playButtonRect");
	//Exit Button
	renderer.PushImage("exitButtonText", "exitButtonRect");
	//Sound Button
	if (playMenuMusic) renderer.PushImage("soundOnButtonText", "soundButtonRect");
	else renderer.PushImage("soundOffButtonText", "soundButtonRect");

	renderer.Render();

}

void GameManager::InitiateGame()
{

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
	colors["black"] = { 0,0,0,0 };
	texts["playerOneScoreBoardText"] = { "playerOneScoreBoardText", "PlayerOne:", colors["black"], 30, 30 };
	renderer.LoadTextureText("Arial", texts["playerOneScoreBoardText"]);
	renderer.LoadRect("player1ScoreRect", Rect({ 30,30,  renderer.GetTextureSize("playerOneScoreBoardText").x, renderer.GetTextureSize("playerOneScoreBoardText").y }));

	texts["playerTwoScoreBoardText"] = { "playerTwoScoreBoardText", "PlayerTwo:", colors["black"], 30, 120 };
	renderer.LoadTextureText("Arial", texts["playerTwoScoreBoardText"]);
	renderer.LoadRect("player2ScoreRect", Rect({ 30, 120,  renderer.GetTextureSize("playerTwoScoreBoardText").x, renderer.GetTextureSize("playerTwoScoreBoardText").y }));

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

	//TIME
	texts["timeText"] = { "timeText", "Time: ", colors["black"], SCREEN_WIDTH - 300 , 20 };
	renderer.LoadTextureText("Arial", texts["timeText"]);
	renderer.LoadRect("timeRect", Rect({ SCREEN_WIDTH - 300 , 20,  renderer.GetTextureSize("timeText").x, renderer.GetTextureSize("timeText").y }));
	rectangles["timeRect"] = Rect({ SCREEN_WIDTH - 300 , 20,  renderer.GetTextureSize("timeText").x, renderer.GetTextureSize("timeText").y });

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

void GameManager::UpdateGame()
{
	//Timer Update
	//std::string s = FloatToString(timeDown, 2);
	texts["timeText"].UpdateText(std::to_string(timeDown));
	renderer.LoadTextureText("Arial", texts["timeText"]);
	rectangles["timeRect"] = { SCREEN_WIDTH - 300, 20, renderer.GetTextureSize("timeText").x, renderer.GetTextureSize("timeText").y };
	renderer.SetRect("timeRect", rectangles["timeRect"]);


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

	//Scoreboards Update
	boardP1.Update(playerClass1);
	renderer.SetRect("scoreRectPlayer1Right", boardP1.returnScoreRectRight());
	renderer.SetRect("scorePositionPlayer1Right", boardP1.returnScorePositionRight());
	renderer.SetRect("scoreRectPlayer1Center", boardP1.returnScoreRectCenter());
	renderer.SetRect("scorePositionPlayer1Center", boardP1.returnScorePositionCenter());
	renderer.SetRect("scoreRectPlayer1Left", boardP1.returnScoreRectLeft());
	renderer.SetRect("scorePositionPlayer1Left", boardP1.returnScorePositionLeft());

	boardP2.Update(playerClass2);
	renderer.SetRect("scoreRectPlayer2Right", boardP2.returnScoreRectRight());
	renderer.SetRect("scorePositionPlayer2Right", boardP2.returnScorePositionRight());
	renderer.SetRect("scoreRectPlayer2Center", boardP2.returnScoreRectCenter());
	renderer.SetRect("scorePositionPlayer2Center", boardP2.returnScorePositionCenter());
	renderer.SetRect("scoreRectPlayer2Left", boardP2.returnScoreRectLeft());
	renderer.SetRect("scorePositionPlayer2Left", boardP2.returnScorePositionLeft());

#pragma endregion

#pragma region Time


	input.UpdateDeltaTime();
	timeDown -= *input.GetDeltaTime();

	if (timeDown <= 0)
	{
		state = gameStates::MENU;
		timeDown = playTime;
	}


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
	renderer.PushImage("playerOneScoreBoardText", "player1ScoreRect");
	renderer.PushImage("playerTwoScoreBoardText", "player2ScoreRect");

	//Scoreboard Sprites
	renderer.PushSprite("scoreTexture", "scoreRectPlayer1Right", "scorePositionPlayer1Right");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer1Left", "scorePositionPlayer1Left");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer1Center", "scorePositionPlayer1Center");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer2Right", "scorePositionPlayer2Right");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer2Left", "scorePositionPlayer2Left");
	renderer.PushSprite("scoreTexture", "scoreRectPlayer2Center", "scorePositionPlayer2Center");

	//Time
	renderer.PushImage("timeText", "timeRect");

	//Coin bags
	for (int i = 0; i < AMOUNT_OF_COINS; i++)
		renderer.PushImage("coinTexture", std::to_string(i));

	renderer.Render();
}

void GameManager::Run()
{
	InitiateMenu();
	InitiateGame();
	
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
