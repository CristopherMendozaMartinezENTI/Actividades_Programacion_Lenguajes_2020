#include "GameManager.h"

GameManager::GameManager(SDL_Window* _window, SDL_Renderer* _renderer)
{
	m_window = _window;
	m_renderer = _renderer;

	// --- SPRITES ---
#pragma region Backgrounds

		//Main Menu Background
		bgTexture = { IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
		if (bgTexture == nullptr) throw std::exception("Error: bgTexture init");
		bgRect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

		//In game Backgroung
		gameBgTexture = { IMG_LoadTexture(m_renderer, "../../res/img/bgCastle.jpg") };
		if (bgTexture == nullptr) throw std::exception("Error: gameBgTexture init");
		gameBgRect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

#pragma endregion

#pragma region Cursor

		//Cursor
		cursorTexture = { IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
		if (cursorTexture == nullptr) throw std::exception("Error: platerTexture init");
		cursorRect = { 0, 0, 350, 190 };

#pragma endregion

#pragma region Title Text

		//Title Text
		font = { TTF_OpenFont("../../res/ttf/saiyan.ttf", 200) };
		if (font == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
		tmpSurf = { TTF_RenderText_Blended(font, "My First SDL Game", SDL_Color{255,210,10,0}) };
		if (tmpSurf == nullptr) throw std::exception("No es pot crear SDL surface");
		titleTexture = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		titleRect = { (SCREEN_WIDTH - tmpSurf->w) / 2, 200, tmpSurf->w, tmpSurf->h };
#pragma endregion

#pragma region Play Button 

		//Play Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,128,0,0 }) };
		playTexture = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		playButtonRect = { (SCREEN_WIDTH - tmpSurf->w) / 2, 400, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,0,0,0 }) };
		playHover = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		playAux = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound Off Button

		//Sound Off Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,128,0,0 }) };
		soundOffTexture = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		soundButtonRect = { (SCREEN_WIDTH - tmpSurf->w) / 2, 600, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,0,0,0 }) };
		soundOffHover = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		soundOffAux = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound On Button

		//Sound On Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,128,0,0 }) };
		soundOnTexture = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,0,0,0 }) };
		soundOnHover = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Exit Button

		//Exit Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,128,0,0 }) };
		exitTexture = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		exitButtonRect = { (SCREEN_WIDTH - tmpSurf->w) / 2, 800, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,0,0,0 }) };
		exitHover = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		exitAux = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Score Boards
		//Player 1 text
		inGameFont = { TTF_OpenFont("../../res/ttf/Arial.ttf", 80) };
		if (inGameFont == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
		tmpSurf = { TTF_RenderText_Blended(inGameFont, "PlayerOne: ", SDL_Color{ 0,0,0}) };
		player1ScoreTexture = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		player1ScoreRect = { 30, 30, tmpSurf->w, tmpSurf->h };

		//Player 2 text
		tmpSurf = { TTF_RenderText_Blended(inGameFont, "PlayerTwo: ", SDL_Color{ 0,0,0}) };
		player2ScoreTexture = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		player2ScoreRect = { 30, 120, tmpSurf->w, tmpSurf->h };
#pragma endregion

	//--- ANIMATED SPRITES ---
#pragma region Players Ands Scoreboards

			//Players
		playerTexture = { IMG_LoadTexture(m_renderer, "../../res/img/spCastle.png") };
		if (playerTexture == nullptr) throw std::exception("Error: playerTexture init");
		textWidth = 0;
		textHeight =  0;
		SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
		player1Rect = { 0 };
		player1Position = { 0 };
		player2Rect = { 0 }; 
		player2Position = { 0 };
		
		//ScoreBoard
		scoreTexture = { IMG_LoadTexture(m_renderer, "../../res/img/num.png") };
		if (scoreTexture == nullptr) throw std::exception("Error: scoreTexture init");

		SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreWidth, &scoreHeight);

		//Players
		playerClass1 = { textWidth, textHeight, PlayerType::P1 };
		playerClass2 = { textWidth, textHeight, PlayerType::P2 };

		//ScoreBoard Player 1
		boardP1 = { scoreWidth, scoreHeight, playerClass1 };

		//Puntuacion Player 2
		boardP2 = {scoreWidth, scoreHeight, playerClass2};
#pragma endregion

#pragma region Coins

		coinTexture = { IMG_LoadTexture(m_renderer, "../../res/img/gold.png") };
		if (coinTexture == nullptr) throw std::exception("Error: coinTexture init");
		for (int i = 0; i < AMOUNT_OF_COINS; i++)
			coinRect[i] = SDL_Rect{ (rand() % SCREEN_WIDTH) - 50, (rand() % 700) + 300, 100,100 };

#pragma endregion

#pragma region Audio

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			throw std::exception("Unable to open SDL_Mixer sound systems");
		}

		//Title Music
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		menuMusic = Mix_LoadMUS("../../res/au/mainTheme.mp3");
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
		Mix_PlayMusic(menuMusic, -1);

#pragma endregion 

	state = MENU;
	isRunning = true;
	mouseClicked = false;
	playMenuMusic = false;
	mouseAxis = { 0, 0 };
}

GameManager::~GameManager()
{
	Destroy();
}

void GameManager::Update()
{	

#pragma region Menu Interactions

				//Hide Mouse 
	SDL_ShowCursor(SDL_DISABLE);

	//Putting the Mouse at the center of the cursor 
	cursorRect.x += (((mouseAxis.x - (cursorRect.w / 2)) - cursorRect.x) / 10);
	cursorRect.y += (((mouseAxis.y - (cursorRect.h / 2)) - cursorRect.y) / 10);

	//Changing Play Button Texture
	if (pointCollision(mouseAxis, playButtonRect))
	{
		playAux = playHover;
		if (mouseClicked)
		{
			mouseClicked = false;
			state = IN_GAME;
			sec = 0;
			playerClass1.Reset();
			playerClass2.Reset();
			boardP1.Reset();
			boardP2.Reset();
		}
	}
	else
		playAux = playTexture;

	//Changing Sound Off Texture
	if (pointCollision(mouseAxis, soundButtonRect))
	{
		if (mouseClicked)
		{
			mouseClicked = false;
			playMenuMusic = !playMenuMusic;
			if (playMenuMusic) Mix_PauseMusic();
			else Mix_PlayMusic(menuMusic, 100);

		}
		if (playMenuMusic) soundOffAux = soundOnHover;
		else soundOffAux = soundOffHover;
	}
	else
	{
		if (playMenuMusic) soundOffAux = soundOnTexture;
		else soundOffAux = soundOffTexture;
	}

	//Changing Exit Button Texture
	if (pointCollision(mouseAxis, exitButtonRect))
	{
		exitAux = exitHover;
		if (mouseClicked) isRunning = false;
	}
	else exitAux = exitTexture;

#pragma endregion

#pragma region Players Movement and Scores

	//Player Movement
	if (state == IN_GAME) {
		playerClass1.Update();
		player1Rect = MyRect2SDL(&playerClass1.returnRect());
		player1Position = MyRect2SDL(&playerClass1.returnPos());

		playerClass2.Update();
		player2Rect = MyRect2SDL(&playerClass2.returnRect());
		player2Position = MyRect2SDL(&playerClass2.returnPos());
	}

	//If the two get the same item, P1 will always get it
	for (int i = 0; i < AMOUNT_OF_COINS; i++)
	{
		if (rectCollision(playerClass1.returnPos(), coinRect[i])) {
			coinRect[i].x = (rand() % SCREEN_WIDTH) - 50;
			coinRect[i].y = (rand() % 700) + 300;
			playerClass1.score++;
			playerClass1.setGetCoinsToTrue();

		}
		else if (rectCollision(playerClass2.returnPos(), coinRect[i])) {
			coinRect[i].x = (rand() % SCREEN_WIDTH) - 50;
			coinRect[i].y = (rand() % 700) + 300;
			playerClass2.score++;
			playerClass2.setGetCoinsToTrue();

		}
	}

	//Scoreboards Update
	boardP1.Update(playerClass1);
	scoreRectPlayer1Right = MyRect2SDL(&boardP1.returnScoreRectRight());
	scorePositionPlayer1Right = MyRect2SDL(&boardP1.returnScorePositionRight());
	scoreRectPlayer1Center = MyRect2SDL(&boardP1.returnScoreRectCenter());
	scorePositionPlayer1Center = MyRect2SDL(&boardP1.returnScorePositionCenter());
	scoreRectPlayer1Left = MyRect2SDL(&boardP1.returnScoreRectLeft());
	scorePositionPlayer1Left = MyRect2SDL(&boardP1.returnScorePositionLeft());

	boardP2.Update(playerClass2);
	scoreRectPlayer2Right = MyRect2SDL(&boardP2.returnScoreRectRight());
	scorePositionPlayer2Right = MyRect2SDL(&boardP2.returnScorePositionRight());
	scoreRectPlayer2Center = MyRect2SDL(&boardP2.returnScoreRectCenter());
	scorePositionPlayer2Center = MyRect2SDL(&boardP2.returnScorePositionCenter());
	scoreRectPlayer2Left = MyRect2SDL(&boardP2.returnScoreRectLeft());
	scorePositionPlayer2Left = MyRect2SDL(&boardP2.returnScorePositionLeft());

#pragma endregion 

#pragma region Time

	//Time 
	sec += DELAY_TIME;
	if (sec >= MAX_TIME) state = MENU;

	int timeLeft = (MAX_TIME - sec) / 1000;
	int size = sizeof(exactTime);
	SDL_snprintf(exactTime, size, "%i", timeLeft);

	tmpSurf = { TTF_RenderText_Blended(inGameFont, exactTime, SDL_Color{ 255,0,0,0 }) };
	if (tmpSurf == nullptr) throw std::exception("No es pot crear SDL surface");
	timeTexture = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	timeRect = { 1750, 65, tmpSurf->w, tmpSurf->h };
	SDL_FreeSurface(tmpSurf);

#pragma endregion 
}

void GameManager::Draw()
{
	// --- DRAW ---

#pragma region Game State Machine

	SDL_RenderClear(m_renderer);

	switch (state)
	{
	case MENU:
		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		//Cursor
		SDL_RenderCopy(m_renderer, cursorTexture, nullptr, &cursorRect);
		//Title
		SDL_RenderCopy(m_renderer, titleTexture, nullptr, &titleRect);
		//Play Button
		SDL_RenderCopy(m_renderer, playAux, nullptr, &playButtonRect);
		//Sound Botton
		SDL_RenderCopy(m_renderer, soundOffAux, nullptr, &soundButtonRect);
		//Exit
		SDL_RenderCopy(m_renderer, exitAux, nullptr, &exitButtonRect);
		break;
	case IN_GAME:
		//Background
		SDL_RenderCopy(m_renderer, gameBgTexture, nullptr, &gameBgRect);
		//Animated Player1 Sprite
		SDL_RenderCopy(m_renderer, playerTexture, &player1Rect, &player1Position);
		//Animated Player2 Sprite
		SDL_RenderCopy(m_renderer, playerTexture, &player2Rect, &player2Position);
		//Coins
		for (int i = 0; i < AMOUNT_OF_COINS; i++) {
			SDL_RenderCopy(m_renderer, coinTexture, nullptr, &coinRect[i]);
		}
		//Time
		SDL_RenderCopy(m_renderer, timeTexture, nullptr, &timeRect);
		//Score Board
		SDL_RenderCopy(m_renderer, player1ScoreTexture, nullptr, &player1ScoreRect);
		SDL_RenderCopy(m_renderer, player2ScoreTexture, nullptr, &player2ScoreRect);
		SDL_RenderCopy(m_renderer, scoreTexture, &scoreRectPlayer1Right, &scorePositionPlayer1Right);
		SDL_RenderCopy(m_renderer, scoreTexture, &scoreRectPlayer1Center, &scorePositionPlayer1Center);
		SDL_RenderCopy(m_renderer, scoreTexture, &scoreRectPlayer1Left, &scorePositionPlayer1Left);
		SDL_RenderCopy(m_renderer, scoreTexture, &scoreRectPlayer2Right, &scorePositionPlayer2Right);
		SDL_RenderCopy(m_renderer, scoreTexture, &scoreRectPlayer2Center, &scorePositionPlayer2Center);
		SDL_RenderCopy(m_renderer, scoreTexture, &scoreRectPlayer2Left, &scorePositionPlayer2Left);
		break;
	default:
		break;
	}

	//Update the screen
	SDL_RenderPresent(m_renderer);

	//Frame Control
	frameTime = SDL_GetTicks() - frameStart;
	if (frameTime < DELAY_TIME)
		SDL_Delay((int)(DELAY_TIME - frameTime));
}

void GameManager::Destroy()
{
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(cursorTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(soundOffTexture);
	SDL_DestroyTexture(soundOnTexture);
	SDL_DestroyTexture(exitTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(player1ScoreTexture);
	SDL_FreeSurface(tmpSurf);
	TTF_CloseFont(font);
	Mix_CloseAudio();
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	Mix_Quit();
}
