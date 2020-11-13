#include "GameManager.h"

GameManager::GameManager()
{
	/*
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw std::exception("No es pot inicialitzar SDL subsystems");

	// --- WINDOW ---
	m_window = { SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr)
		throw std::exception("No es pot inicialitzar SDL_Window");

	// --- RENDERER ---
	m_renderer = { SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr)
		throw std::exception("No es pot inicialitzar SDL_Renderer");

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw std::exception("Error: SDL_image init");

	//-->SDL_TTF
	if (TTF_Init() != 0) throw std::exception("No es pot inicialitzar SDL_ttf");

	//-->SDL_Mix
	const Uint8 soundFlags{ MIX_INIT_MP3 };
	if (!(Mix_Init(soundFlags) & soundFlags)) throw std::exception("Error: SDL_image init");
	*/

	state = gameStates::MENU;
	isRunning = true;
	mouseClicked = false;
	playMenuMusic = false;
	mouseAxis = { 0, 0 };

	/*
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

	*/
}

GameManager::~GameManager()
{
	Destroy();
}

void GameManager::InitiateMenu()
{
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
	rectangles["cursorRect"] = { 0, 0, 350, 190 };

#pragma endregion

#pragma region Title Text

	//Title Text
	renderer.LoadFont(Font({ "SaiyanFont", "../../res/ttf/saiyan.ttf", 200 }));

	Color c{ 255,210,10,0 };

	Text titulo{ "titleTexture", "My First SDL Game", c, 200, 200 };
	renderer.LoadTextureText("SaiyanFont", titulo);
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

	Color button_c{ 255, 128, 0, 0 };

	Text playButtonText{ "playButtonTexture", "Play", button_c, SCREEN_WIDTH / 2, 400 };
	renderer.LoadTextureText("SaiyanFont", playButtonText);
	renderer.LoadRect("playButtonRect", Rect({ SCREEN_WIDTH / 2, 400, renderer.GetTextureSize("playButtonTexture").x, renderer.GetTextureSize("playButtonTexture").y }));
	rectangles["playButtonRect"] = { SCREEN_WIDTH / 2, 400, renderer.GetTextureSize("playButtonTexture").x, renderer.GetTextureSize("playButtonTexture").y };

	//tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,128,0,0 }) };
	//textures["playTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//rectangles["playButtonRect"] = { (SCREEN_WIDTH - tmpSurf->w) / 2, 400, tmpSurf->w, tmpSurf->h };
	//tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,0,0,0 }) };
	//textures["playHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//textures["playAux"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound Off Button

	//Sound Off Button (Menu)
	Text soundOffButtonText{ "soundOffButtonTexture", "Sound Off", button_c, SCREEN_WIDTH / 2, 600 };
	renderer.LoadTextureText("SaiyanFont", soundOffButtonText);
	renderer.LoadRect("soundButtonRect", Rect({ SCREEN_WIDTH / 2, 600, renderer.GetTextureSize("soundOffButtonTexture").x, renderer.GetTextureSize("soundOffButtonTexture").y }));
	rectangles["soundButtonRect"] = { SCREEN_WIDTH / 2, 600, renderer.GetTextureSize("soundOffButtonTexture").x, renderer.GetTextureSize("soundOffButtonTexture").y };

	//tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,128,0,0 }) };
	//textures["soundOffTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,0,0,0 }) };
	//textures["soundOffHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//textures["soundOffAux"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound On Button

	//Sound On Button (Menu)
	Text soundOnButtonText{ "soundOnButtonTexture", "Sound On", button_c, SCREEN_WIDTH / 2, 600 };
	renderer.LoadTextureText("SaiyanFont", soundOnButtonText);

	//tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,128,0,0 }) };
	//textures["soundOnTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,0,0,0 }) };
	//textures["soundOnHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Exit Button

	//Exit Button (Menu)

	Text exitButtonText{ "exitButtonTexture", "Exit", button_c, SCREEN_WIDTH / 2, 800 };
	renderer.LoadTextureText("SaiyanFont", exitButtonText);
	renderer.LoadRect("exitButtonRect", Rect({ SCREEN_WIDTH / 2, 800, renderer.GetTextureSize("exitButtonTexture").x, renderer.GetTextureSize("exitButtonTexture").y }));
	rectangles["exitButtonRect"] = { SCREEN_WIDTH / 2, 800, renderer.GetTextureSize("exitButtonTexture").x, renderer.GetTextureSize("exitButtonTexture").y };

	//tmpSurf = { TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,128,0,0 }) };
	//textures["exitTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//rectangles["exitButtonRect"] = { (SCREEN_WIDTH - tmpSurf->w) / 2, 800, tmpSurf->w, tmpSurf->h };
	//tmpSurf = { TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,0,0,0 }) };
	//textures["exitHover"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	//textures["exitAux"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

}
	
void GameManager::UpdateMenu()
{
	Color button_hovered_c{ 255,0,0,0 };
	Color button_c{ 255, 128, 0, 0 };

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
		Text hover_playButtonText{ "playButtonTexture", "Play", button_hovered_c, SCREEN_WIDTH / 2, 400 };
		renderer.LoadTextureText("SaiyanFont", hover_playButtonText);
		
		//textures["playAux"] = textures["playHover"];
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
		Text playBtnText{ "playButtonTexture", "Play", button_c, SCREEN_WIDTH / 2, 400 };
		renderer.LoadTextureText("SaiyanFont", playBtnText);
		
		//textures["playAux"] = textures["playTexture"];
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
			Text hover_soundOnButtonText{ "soundOnButtonTexture", "Sound On", button_hovered_c, SCREEN_WIDTH / 2, 600 };
			renderer.LoadTextureText("SaiyanFont", hover_soundOnButtonText);
			//textures["soundOffAux"] = textures["soundOnHover"];
		}
		else
		{
			Text hover_soundOffButtonText{ "soundOffButtonTexture", "Sound Off", button_hovered_c, SCREEN_WIDTH / 2, 600 };
			renderer.LoadTextureText("SaiyanFont", hover_soundOffButtonText);
			//textures["soundOffAux"] = textures["soundOffHover"];
		}
	}
	else
	{
		if (playMenuMusic)
		{
			Text soundOnButtonText{ "soundOnButtonTexture", "Sound On", button_c, SCREEN_WIDTH / 2, 600 };
			renderer.LoadTextureText("SaiyanFont", soundOnButtonText);
			//textures["soundOffAux"] = textures["soundOnTexture"];
		}
		else
		{
			Text soundOffButtonText{ "soundOffButtonTexture", "Sound Off", button_c, SCREEN_WIDTH / 2, 600 };
			renderer.LoadTextureText("SaiyanFont", soundOffButtonText);
			//textures["soundOffAux"] = textures["soundOffTexture"];
		}
	}

	//Changing Exit Button Texture
	if (collisions::pointCollision(mouseAxis, rectangles["exitButtonRect"]))
	{
		Text hover_exitButtonText{ "exitButtonTexture", "Exit", button_hovered_c, SCREEN_WIDTH / 2, 800 };
		renderer.LoadTextureText("SaiyanFont", hover_exitButtonText);
		//textures["exitAux"] = textures["exitHover"];
		
		if (mouseClicked) isRunning = false;
	}
	else
	{
		Text exitButtonText{ "exitButtonTexture", "Exit", button_c, SCREEN_WIDTH / 2, 800 };
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
	renderer.PushImage("playButtonTexture", "playButtonRect");
	renderer.PushImage("exitButtonTexture", "exitButtonRect");
	if (playMenuMusic) renderer.PushImage("soundOnButtonTexture", "soundButtonRect");
	else renderer.PushImage("soundOffButtonTexture", "soundButtonRect");

	
	renderer.Render();
	/*
	SDL_RenderClear(m_renderer);
	//SDL_RenderCopy(m_renderer, textures["bgTexture"], nullptr, &rectangles["bgRect"]);
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
	SDL_RenderPresent(m_renderer);
	*/

}


void GameManager::InitiateGame()
{
	// --- SPRITES ---
#pragma region Backgrounds

	//Game Background
	renderer.LoadTexture("gameBgTexture", "../../res/img/bgCastle.jpg");
	renderer.LoadRect("gameBgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

#pragma endregion

	//Text
#pragma region Score Boards
	//Player 1 text
	 
	/*
	inGameFont = { TTF_OpenFont("../../res/ttf/Arial.ttf", 80) };
	if (inGameFont == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
	tmpSurf = { TTF_RenderText_Blended(inGameFont, "PlayerOne: ", SDL_Color{ 0,0,0}) };
	textures["player1ScoreTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	rectangles["player1ScoreRect"] = { 30, 30, tmpSurf->w, tmpSurf->h };

	//Player 2 text
	tmpSurf = { TTF_RenderText_Blended(inGameFont, "PlayerTwo: ", SDL_Color{ 0,0,0}) };
	textures["player2ScoreTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	rectangles["player2ScoreRect"] = { 30, 120, tmpSurf->w, tmpSurf->h };
	*/

#pragma endregion

	//--- ANIMATED SPRITES ---
#pragma region Players Ands Scoreboards

			//Players
	renderer.LoadTexture("playerTexture", "../../res/img/spCastle.png");

	//textures["playerTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/spCastle.png") };
	//if (textures["playerTexture"] == nullptr) throw std::exception("Error: playerTexture init");
	//SDL_QueryTexture(textures["playerTexture"], NULL, NULL, &textWidth, &textHeight);

	//ScoreBoard
	renderer.LoadTexture("scoreTexture", "../../res/img/num.png");
	
	//textures["scoreTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/num.png") };
	//if (textures["scoreTexture"] == nullptr) throw std::exception("Error: scoreTexture init");
	//SDL_QueryTexture(textures["scoreTexture"], NULL, NULL, &scoreWidth, &scoreHeight);

	//Players
	playerClass1 = { renderer.GetTextureSize("playerTexture").x, renderer.GetTextureSize("playerTexture").y, PlayerType::P1 };
	playerClass2 = { renderer.GetTextureSize("playerTexture").x, renderer.GetTextureSize("playerTexture").y, PlayerType::P2 };

	//Puntuacion Player 1 & Plyaer 2
	boardP1 = { renderer.GetTextureSize("scoreTexture").x, renderer.GetTextureSize("scoreTexture").x, playerClass1 };
	boardP2 = { renderer.GetTextureSize("scoreTexture").x, renderer.GetTextureSize("scoreTexture").x, playerClass2 };

#pragma endregion

#pragma region Coins

	renderer.LoadTexture("coinTexture", "../../res/img/gold.png");
	//textures["coinTexture"] = { IMG_LoadTexture(m_renderer, "../../res/img/gold.png") };
	//if (textures["coinTexture"] == nullptr) throw std::exception("Error: coinTexture init");
	for (int i = 0; i < AMOUNT_OF_COINS; i++)
		coinRect[i] = SDL_Rect{ (rand() % SCREEN_WIDTH) - 50, (rand() % 700) + 300, 100,100 };

#pragma endregion

}

void GameManager::UpdateGame()
{
	/*
#pragma region Players Movement and Scores

	//Player Movement
	if (state == gameStates::IN_GAME) {
		playerClass1.Update();
		rectangles["player1Rect"] = MyRect2SDL(&playerClass1.returnRect());
		rectangles["player1Position"] = MyRect2SDL(&playerClass1.returnPos());

		playerClass2.Update();
		rectangles["player2Rect"] = MyRect2SDL(&playerClass2.returnRect());
		rectangles["player2Position"] = MyRect2SDL(&playerClass2.returnPos());
	}

	//If the two get the same item, P1 will always get it
	for (int i = 0; i < AMOUNT_OF_COINS; i++)
	{
		if (collisions::rectCollision(playerClass1.returnPos(), coinRect[i])) {
			coinRect[i].x = (rand() % SCREEN_WIDTH) - 50;
			coinRect[i].y = (rand() % 700) + 300;
			playerClass1.score++;
			playerClass1.setGetCoinsToTrue();

		}
		else if (collisions::rectCollision(playerClass2.returnPos(), coinRect[i])) {
			coinRect[i].x = (rand() % SCREEN_WIDTH) - 50;
			coinRect[i].y = (rand() % 700) + 300;
			playerClass2.score++;
			playerClass2.setGetCoinsToTrue();

		}
	}

	//Scoreboards Update
	boardP1.Update(playerClass1);
	rectangles["scoreRectPlayer1Right"] = MyRect2SDL(&boardP1.returnScoreRectRight());
	rectangles["scorePositionPlayer1Right"] = MyRect2SDL(&boardP1.returnScorePositionRight());
	rectangles["scoreRectPlayer1Center"] = MyRect2SDL(&boardP1.returnScoreRectCenter());
	rectangles["scorePositionPlayer1Center"] = MyRect2SDL(&boardP1.returnScorePositionCenter());
	rectangles["scoreRectPlayer1Left"] = MyRect2SDL(&boardP1.returnScoreRectLeft());
	rectangles["scorePositionPlayer1Left"] = MyRect2SDL(&boardP1.returnScorePositionLeft());

	boardP2.Update(playerClass2);
	rectangles["scoreRectPlayer2Right"] = MyRect2SDL(&boardP2.returnScoreRectRight());
	rectangles["scorePositionPlayer2Right"] = MyRect2SDL(&boardP2.returnScorePositionRight());
	rectangles["scoreRectPlayer2Center"] = MyRect2SDL(&boardP2.returnScoreRectCenter());
	rectangles["scorePositionPlayer2Center"] = MyRect2SDL(&boardP2.returnScorePositionCenter());
	rectangles["scoreRectPlayer2Left"] = MyRect2SDL(&boardP2.returnScoreRectLeft());
	rectangles["scorePositionPlayer2Left"] = MyRect2SDL(&boardP2.returnScorePositionLeft());

#pragma endregion 

#pragma region Time

	//Time 
	sec += DELAY_TIME;
	if (sec >= MAX_TIME) state = gameStates::MENU;

	int timeLeft = (MAX_TIME - sec) / 1000;
	int size = sizeof(exactTime);
	SDL_snprintf(exactTime, size, "%i", timeLeft);

	tmpSurf = { TTF_RenderText_Blended(inGameFont, exactTime, SDL_Color{ 255,0,0,0 }) };
	if (tmpSurf == nullptr) throw std::exception("No es pot crear SDL surface");
	textures["timeTexture"] = { SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
	rectangles["timeRect"] = { SCREEN_WIDTH - 150, 65, tmpSurf->w, tmpSurf->h };

#pragma endregion 
	*/

}

void GameManager::DrawGame()
{
	/*
	SDL_RenderClear(m_renderer);

	//Background
	SDL_RenderCopy(m_renderer, textures["gameBgTexture"], nullptr, &rectangles["gameBgRect"]);
	//Animated Player1 Sprite
	SDL_RenderCopy(m_renderer, textures["playerTexture"], &rectangles["player1Rect"], &rectangles["player1Position"]);
	//Animated Player2 Sprite
	SDL_RenderCopy(m_renderer, textures["playerTexture"], &rectangles["player2Rect"], &rectangles["player2Position"]);
	//Coins
	for (int i = 0; i < AMOUNT_OF_COINS; i++) {
		SDL_RenderCopy(m_renderer, textures["coinTexture"], nullptr, &coinRect[i]);
	}
	//Time
	SDL_RenderCopy(m_renderer, textures["timeTexture"], nullptr, &rectangles["timeRect"]);
	//Score Board
	SDL_RenderCopy(m_renderer, textures["player1ScoreTexture"], nullptr, &rectangles["player1ScoreRect"]);
	SDL_RenderCopy(m_renderer, textures["player2ScoreTexture"], nullptr, &rectangles["player2ScoreRect"]);
	SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer1Right"], &rectangles["scorePositionPlayer1Right"]);
	SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer1Center"], &rectangles["scorePositionPlayer1Center"]);
	SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer1Left"], &rectangles["scorePositionPlayer1Left"]);
	SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer2Right"], &rectangles["scorePositionPlayer2Right"]);
	SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer2Center"], &rectangles["scorePositionPlayer2Center"]);
	SDL_RenderCopy(m_renderer, textures["scoreTexture"], &rectangles["scoreRectPlayer2Left"], &rectangles["scorePositionPlayer2Left"]);

	SDL_RenderPresent(m_renderer);
	*/
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
			InitiateMenu();
			UpdateMenu();
			DrawMenu();

			break;
		case gameStates::IN_GAME:
			InitiateGame();
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
