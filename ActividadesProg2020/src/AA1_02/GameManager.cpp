#include "GameManager.h"

GameManager::GameManager(SDL_Window* _window, SDL_Renderer* _renderer)
{
	m_window = _window;
	m_renderer = _renderer;
	state = gameStates::MENU;
	isRunning = true;
	mouseClicked = false;
	playMenuMusic = false;
	mouseAxis = { 0, 0 };

// --- SPRITES ---
#pragma region Backgrounds

		//Main Menu Background
		textures["bgTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
		if (textures["bgTexture"] == nullptr) throw std::exception("Error: bgTexture init");
		rectangles["bgRect"] = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };


		//In game Backgroung
		textures["gameBgTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/bgCastle.jpg") };
		if (textures["gameBgTexture"] == nullptr) throw std::exception("Error: gameBgTexture init");
		rectangles["gameBgRect"] = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

#pragma endregion

#pragma region Cursor

		//Cursor
		textures["cursorTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
		if (textures["cursorTexture"] == nullptr) throw std::exception("Error: platerTexture init");
		rectangles["cursorRect"] = { 0, 0, 350, 190 };

#pragma endregion

#pragma region Title Text

		//Title Text
		font = { TTF_OpenFont("../../res/ttf/saiyan.ttf", 200) };
		if (font == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
		tmpSurf = { TTF_RenderText_Blended(font, "My First SDL Game", SDL_Color{255,210,10,0}) };
		if (tmpSurf == nullptr) throw std::exception("No es pot crear SDL surface");
		textures["titleTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		rectangles["titleRect"] = { (SCREEN_WIDTH - tmpSurf->w) / 2, 200, tmpSurf->w, tmpSurf->h };

#pragma endregion

#pragma region Play Button 

		//Play Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,128,0,0 }) };
		textures["playTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		rectangles["playButtonRect"] = { (SCREEN_WIDTH - tmpSurf->w) / 2, 400, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,0,0,0 }) };
		textures["playHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		textures["playAux"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound Off Button

		//Sound Off Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,128,0,0 }) };
		textures["soundOffTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		rectangles["soundButtonRect"] = { (SCREEN_WIDTH - tmpSurf->w) / 2, 600, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,0,0,0 }) };
		textures["soundOffHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		textures["soundOffAux"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound On Button

		//Sound On Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,128,0,0 }) };
		textures["soundOnTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,0,0,0 }) };
		textures["soundOnHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Exit Button

		//Exit Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,128,0,0 }) };
		textures["exitTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		rectangles["exitButtonRect"] = { (SCREEN_WIDTH - tmpSurf->w) / 2, 800, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,0,0,0 }) };
		textures["exitHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		textures["exitAux"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Score Boards

		//Player 1 text
		inGameFont = { TTF_OpenFont("../../res/ttf/Arial.ttf", 80) };
		if (inGameFont == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
		tmpSurf = { TTF_RenderText_Blended(inGameFont, "PlayerOne: ", SDL_Color{ 0,0,0}) };
		textures["player1ScoreTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		rectangles["player1ScoreRect"] = { 30, 30, tmpSurf->w, tmpSurf->h };

		//Player 2 text
		tmpSurf = { TTF_RenderText_Blended(inGameFont, "PlayerTwo: ", SDL_Color{ 0,0,0}) };
		textures["player2ScoreTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		rectangles["player2ScoreRect"] = { 30, 120, tmpSurf->w, tmpSurf->h };

#pragma endregion

//--- ANIMATED SPRITES ---
#pragma region Players Ands Scoreboards

			//Players
		textures["playerTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/spCastle.png") };
		if (textures["playerTexture"] == nullptr) throw std::exception("Error: playerTexture init");
		SDL_QueryTexture(textures["playerTexture"], NULL, NULL, &textWidth, &textHeight);
		
		//ScoreBoard
		textures["scoreTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/num.png") };
		if (textures["scoreTexture"] == nullptr) throw std::exception("Error: scoreTexture init");
		SDL_QueryTexture(textures["scoreTexture"], NULL, NULL, &scoreWidth, &scoreHeight);

		//Players
		playerClass1 = { textWidth, textHeight, PlayerType::P1 };
		playerClass2 = { textWidth, textHeight, PlayerType::P2 };

		//ScoreBoard Player 1
		boardP1 = { scoreWidth, scoreHeight, playerClass1 };

		//Puntuacion Player 2
		boardP2 = {scoreWidth, scoreHeight, playerClass2};

#pragma endregion

#pragma region Coins

		textures["coinTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/gold.png") };
		if (textures["coinTexture"] == nullptr) throw std::exception("Error: coinTexture init");
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
	rectangles["cursorRect"].x += (((mouseAxis.x - (rectangles["cursorRect"].w / 2)) - rectangles["cursorRect"].x) / 10);
	rectangles["cursorRect"].y += (((mouseAxis.y - (rectangles["cursorRect"].h / 2)) - rectangles["cursorRect"].y) / 10);

	//Changing Play Button Texture
	if (pointCollision(mouseAxis, rectangles["playButtonRect"]))
	{
		textures["playAux"] = textures["playHover"];
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
		textures["playAux"] = textures["playTexture"];

	//Changing Sound Off Texture
	if (pointCollision(mouseAxis, rectangles["soundButtonRect"]))
	{
		if (mouseClicked)
		{
			mouseClicked = false;
			playMenuMusic = !playMenuMusic;
			if (playMenuMusic) Mix_PauseMusic();
			else Mix_PlayMusic(menuMusic, 100);

		}
		if (playMenuMusic) textures["soundOffAux"] = textures["soundOnHover"];
		else textures["soundOffAux"] = textures["soundOffHover"];
	}
	else
	{
		if (playMenuMusic) textures["soundOffAux"] = textures["soundOnTexture"];
		else textures["soundOffAux"] = textures["soundOffTexture"];
	}

	//Changing Exit Button Texture
	if (pointCollision(mouseAxis, rectangles["exitButtonRect"]))
	{
		textures["exitAux"] = textures["exitHover"];
		if (mouseClicked) isRunning = false;
	}
	else textures["exitAux"] = textures["exitTexture"];

#pragma endregion

#pragma region Players Movement and Scores

	//Player Movement
	if (state == IN_GAME) {
		playerClass1.Update();
		rectangles["player1Rect"] = MyRect2SDL(&playerClass1.returnRect());
		positions["player1Position"] = MyRect2SDL(&playerClass1.returnPos());

		playerClass2.Update();
		rectangles["player2Rect"] = MyRect2SDL(&playerClass2.returnRect());
		positions["player2Position"] = MyRect2SDL(&playerClass2.returnPos());
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
	rectangles["scoreRectPlayer1Right"] = MyRect2SDL(&boardP1.returnScoreRectRight());
	positions["scorePositionPlayer1Right"] = MyRect2SDL(&boardP1.returnScorePositionRight());
	rectangles["scoreRectPlayer1Center"] = MyRect2SDL(&boardP1.returnScoreRectCenter());
	positions["scorePositionPlayer1Center"] = MyRect2SDL(&boardP1.returnScorePositionCenter());
	rectangles["scoreRectPlayer1Left"] = MyRect2SDL(&boardP1.returnScoreRectLeft());
	positions["scorePositionPlayer1Left"] = MyRect2SDL(&boardP1.returnScorePositionLeft());

	boardP2.Update(playerClass2);
	rectangles["scoreRectPlayer2Right"] = MyRect2SDL(&boardP2.returnScoreRectRight());
	positions["scorePositionPlayer2Right"] = MyRect2SDL(&boardP2.returnScorePositionRight());
	rectangles["scoreRectPlayer2Center"] = MyRect2SDL(&boardP2.returnScoreRectCenter());
	positions["scorePositionPlayer2Center"] = MyRect2SDL(&boardP2.returnScorePositionCenter());
	rectangles["scoreRectPlayer2Left"] = MyRect2SDL(&boardP2.returnScoreRectLeft());
	positions["scorePositionPlayer2Left"] = MyRect2SDL(&boardP2.returnScorePositionLeft());

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
	textures["timeTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	rectangles["timeRect"] = { SCREEN_WIDTH - 150, 65, tmpSurf->w, tmpSurf->h };

#pragma endregion 

}

void GameManager::Draw()
{

	SDL_RenderClear(m_renderer);

	switch (state)
	{
	case MENU:
		//Background
		SDL_RenderCopy(m_renderer, textures["bgTexture"], nullptr, &rectangles["bgRect"]);
		//Cursor
		SDL_RenderCopy(m_renderer, textures["cursorTexture"], nullptr, &rectangles["cursorRect"]);
		//Title
		SDL_RenderCopy(m_renderer, textures["titleTexture"], nullptr, &rectangles["titleRect"]);
		//Play Button
		SDL_RenderCopy(m_renderer, textures["playAux"], nullptr, &rectangles["playButtonRect"]);
		//Sound Botton
		SDL_RenderCopy(m_renderer, textures["soundOffAux"], nullptr, &rectangles["soundButtonRect"]);
		//Exit
		SDL_RenderCopy(m_renderer, textures["exitAux"], nullptr, &rectangles["exitButtonRect"]);
		break;
	case IN_GAME:
		//Background
		SDL_RenderCopy(m_renderer, textures["gameBgTexture"], nullptr, &rectangles["gameBgRect"]);
		//Animated Player1 Sprite
		SDL_RenderCopy(m_renderer, textures["playerTexture"], &rectangles["player1Rect"], &positions["player1Position"]);
		//Animated Player2 Sprite
		SDL_RenderCopy(m_renderer, textures["playerTexture"], &rectangles["player2Rect"], &positions["player2Position"]);
		//Coins
		for (int i = 0; i < AMOUNT_OF_COINS; i++) {
			SDL_RenderCopy(m_renderer, textures["coinTexture"], nullptr, &coinRect[i]);
		}
		//Time
		SDL_RenderCopy(m_renderer, textures["timeTexture"], nullptr, &rectangles["timeRect"]);
		//Score Board
		SDL_RenderCopy(m_renderer, textures["player1ScoreTexture"], nullptr, &rectangles["player1ScoreRect"]);
		SDL_RenderCopy(m_renderer, textures["player2ScoreTexture"], nullptr, &rectangles["player2ScoreRect"]);
		SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer1Right"], &positions["scorePositionPlayer1Right"]);
		SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer1Center"], &positions["scorePositionPlayer1Center"]);
		SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer1Left"], &positions["scorePositionPlayer1Left"]);
		SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer2Right"], &positions["scorePositionPlayer2Right"]);
		SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer2Center"], &positions["scorePositionPlayer2Center"]);
		SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer2Left"], &positions["scorePositionPlayer2Left"]);
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
}
