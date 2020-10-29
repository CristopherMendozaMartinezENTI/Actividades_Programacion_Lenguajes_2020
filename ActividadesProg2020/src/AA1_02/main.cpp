#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <exception>
#include <iostream>
#include <string>
#include "ScoreBoard.h"

int main(int, char* [])
{
	// --- Init ---
#pragma region InitSDL

	try {
		// --- INIT SDL ---
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw std::exception("No es pot inicialitzar SDL subsystems");

		// --- WINDOW ---
		SDL_Window* m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
		if (m_window == nullptr)
			throw std::exception("No es pot inicialitzar SDL_Window");

		// --- RENDERER ---
		SDL_Renderer* m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
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

		//-->Time
		Uint32 frameStart, frameTime;
		float sec = 0;

#pragma endregion 	

		// --- SPRITES ---
#pragma region Backgrounds

	//Main Menu Background
		SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
		if (bgTexture == nullptr) throw std::exception("Error: bgTexture init");
		SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

		//In game Backgroung
		SDL_Texture* gameBgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bgCastle.jpg") };
		if (bgTexture == nullptr) throw std::exception("Error: gameBgTexture init");
		SDL_Rect gameBgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

#pragma endregion

#pragma region Cursor

		//Cursor
		SDL_Texture* cursorTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
		if (cursorTexture == nullptr) throw std::exception("Error: platerTexture init");
		SDL_Rect cursorRect{ 0, 0, 350, 190 };
		SDL_Rect cursorTarget{ 0, 0, 100, 100 };

#pragma endregion

#pragma region Title Text

		//Title Text
		TTF_Font* font{ TTF_OpenFont("../../res/ttf/saiyan.ttf", 200) };
		if (font == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
		SDL_Surface* tmpSurf{ TTF_RenderText_Blended(font, "My First SDL Game", SDL_Color{255,210,10,0}) };
		if (tmpSurf == nullptr) throw std::exception("No es pot crear SDL surface");
		SDL_Texture* titleTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Rect titleRect{ (SCREEN_WIDTH - tmpSurf->w) / 2, 200, tmpSurf->w, tmpSurf->h };

#pragma endregion

#pragma region Play Button 

		//Play Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,128,0,0 }) };
		SDL_Texture* playTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Rect playButtonRect{ (SCREEN_WIDTH - tmpSurf->w) / 2, 400, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Play", SDL_Color{ 255,0,0,0 }) };
		SDL_Texture* playHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Texture* playAux{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound Button

		//Sound Off Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,128,0,0 }) };
		SDL_Texture* soundOffTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Rect soundButtonRect{ (SCREEN_WIDTH - tmpSurf->w) / 2, 600, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Sound Off", SDL_Color{ 255,0,0,0 }) };
		SDL_Texture* soundOffHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Texture* soundOffAux{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Sound Button

		//Sound On Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,128,0,0 }) };
		SDL_Texture* soundOnTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		tmpSurf = { TTF_RenderText_Blended(font, "Sound On", SDL_Color{ 255,0,0,0 }) };
		SDL_Texture* soundOnHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Exit Button

		//Exit Button (Menu)
		tmpSurf = { TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,128,0,0 }) };
		SDL_Texture* exitTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Rect exitButtonRect{ (SCREEN_WIDTH - tmpSurf->w) / 2, 800, tmpSurf->w, tmpSurf->h };
		tmpSurf = { TTF_RenderText_Blended(font, "Exit", SDL_Color{ 255,0,0,0 }) };
		SDL_Texture* exitHover{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Texture* exitAux{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };

#pragma endregion

#pragma region Score Boards
		//Player 1 text
		TTF_Font* inGameFont{ TTF_OpenFont("../../res/ttf/Arial.ttf", 80) };
		if (inGameFont == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
		tmpSurf = { TTF_RenderText_Blended(inGameFont, "PlayerOne: ", SDL_Color{ 0,0,0}) };
		SDL_Texture* player1ScoreTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Rect player1ScoreRect{ 30, 30, tmpSurf->w, tmpSurf->h };

		//Player 2 text
		tmpSurf = { TTF_RenderText_Blended(inGameFont, "PlayerTwo: ", SDL_Color{ 0,0,0}) };
		SDL_Texture* player2ScoreTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
		SDL_Rect player2ScoreRect{ 30, 120, tmpSurf->w, tmpSurf->h };
#pragma endregion

#pragma region Coins

		SDL_Texture* coinTexture{ IMG_LoadTexture(m_renderer, "../../res/img/gold.png") };
		if (coinTexture == nullptr) throw std::exception("Error: coinTexture init");
		SDL_Rect coinRect[AMOUNT_OF_COINS];
		for (int i = 0; i < AMOUNT_OF_COINS; i++)
			coinRect[i] = SDL_Rect{ (rand() % SCREEN_WIDTH) - 50, (rand() % 700) + 300, 100,100 };

#pragma endregion

#pragma region Animated Sprites

		//-->Animated Sprite ---
			//Players
		SDL_Texture* playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/spCastle.png") };
		if (playerTexture == nullptr) throw std::exception("Error: playerTexture init");
		int textWidth{ 0 }, textHeight{ 0 }, frameWidth{ 0 }, frameHeight{ 0 };
		SDL_QueryTexture(playerTexture, NULL, NULL, &textWidth, &textHeight);
		SDL_Rect player1Rect{ 0 }, player1Position{ 0 }, player2Rect{ 0 }, player2Position{ 0 };
		
		PlayerClass playerClass1(textWidth, textHeight, PlayerType::P1);
		PlayerClass playerClass2(textWidth, textHeight, PlayerType::P2);

		//ScoreBoard
		SDL_Texture* scoreTexture{ IMG_LoadTexture(m_renderer, "../../res/img/num.png") };
		if (scoreTexture == nullptr) throw std::exception("Error: scoreTexture init");
		int scoreWidth, scoreHeight, frameWidthScore1Right, frameHeightScore1Right;
		SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreWidth, &scoreHeight);

		//ScoreBoard Player 1
		SDL_Rect scoreRectPlayer1Right, scorePositionPlayer1Right;
		SDL_Rect scoreRectPlayer1Center, scorePositionPlayer1Center;
		SDL_Rect scoreRectPlayer1Left, scorePositionPlayer1Left;
		ScoreBoard boardP1(scoreWidth, scoreHeight, playerClass1);

		//Puntuacion Player 2
		SDL_Rect scoreRectPlayer2Right, scorePositionPlayer2Right;
		SDL_Rect scoreRectPlayer2Center, scorePositionPlayer2Center;
		SDL_Rect scoreRectPlayer2Left, scorePositionPlayer2Left;
		ScoreBoard boardP2(scoreWidth, scoreHeight, playerClass2);

#pragma endregion

#pragma region Audio

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			throw std::exception("Unable to open SDL_Mixer sound systems");
		}

		//Title Music
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		Mix_Music* menuMusic = Mix_LoadMUS("../../res/au/mainTheme.mp3");
		if (menuMusic == NULL) return false;
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
		Mix_PlayMusic(menuMusic, -1);

#pragma endregion 

		// --- GAME LOOP ---
		SDL_Event event;
		gameStates state = MENU;
		Vec2 mouseAxis{ 0, 0 };
		char exactTime[5];
		bool isRunning = true;
		bool mouseClicked = false;
		bool playMenuMusic = false;

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
					if (event.key.keysym.sym == SDLK_UP) playerClass1.dir.goUp = false;
					if (event.key.keysym.sym == SDLK_DOWN) playerClass1.dir.goDown = false;
					if (event.key.keysym.sym == SDLK_RIGHT) playerClass1.dir.goRight = false;
					if (event.key.keysym.sym == SDLK_LEFT)playerClass1.dir.goLeft = false;
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

			// --- UPDATE --
				//Hide Mouse 
			SDL_ShowCursor(SDL_DISABLE);

			//Putting the Mouse at the center of the cursor 
			cursorRect.x += (((mouseAxis.x - (cursorRect.w / 2)) - cursorRect.x) / 10);
			cursorRect.y += (((mouseAxis.y - (cursorRect.h / 2)) - cursorRect.y) / 10);


#pragma region Menu: Button Colliders

			//Changing Play Button Texture
			if (pointCollision(mouseAxis, playButtonRect))
			{
				playAux = playHover;
				if (mouseClicked)
				{
					mouseClicked = false;
					state = IN_GAME;
					sec = 0;
					playerClass1.ResetPlayer();
					playerClass2.ResetPlayer();
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

#pragma region Players Animations, Movement and Score

			playerClass1.Move();
			playerClass2.Move();

			//Movement
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
			boardP2.Update(playerClass2);

			scoreRectPlayer1Right = MyRect2SDL(&boardP1.returnScoreRectRight());
			scorePositionPlayer1Right = MyRect2SDL(&boardP1.returnScorePositionRight());
			scoreRectPlayer1Center = MyRect2SDL(&boardP1.returnScoreRectCenter());
			scorePositionPlayer1Center = MyRect2SDL(&boardP1.returnScorePositionCenter());
			scoreRectPlayer1Left = MyRect2SDL(&boardP1.returnScoreRectLeft());
			scorePositionPlayer1Left = MyRect2SDL(&boardP1.returnScorePositionLeft());

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

			float timeLeft = (MAX_TIME - sec) / 1000;
			int size = sizeof(exactTime);
			SDL_snprintf(exactTime, size, "%f", timeLeft);

			for (int i = 0; i < size; i++) {
				if (exactTime[i] == '.') exactTime[i] == ':';
			}

			tmpSurf = { TTF_RenderText_Blended(inGameFont, exactTime, SDL_Color{ 255,0,0,0 }) };
			if (tmpSurf == nullptr) throw std::exception("No es pot crear SDL surface");
			SDL_Texture* timeTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf) };
			SDL_Rect timeRect{ 1750, 65, tmpSurf->w, tmpSurf->h };

#pragma endregion 

			// --- DRAW ---
			SDL_RenderClear(m_renderer);

#pragma region Game State Machine

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
				}
				break;
			default:
				break;
			}

#pragma endregion 

			//Update the screen
			SDL_RenderPresent(m_renderer);

			//Frame Control
			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME)
				SDL_Delay((int)(DELAY_TIME - frameTime));
		}

#pragma region Close SDL

		// --- DESTROY ---
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

#pragma endregion 

	}

	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
