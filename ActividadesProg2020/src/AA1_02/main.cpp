#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <exception>
#include <iostream>
#include <string>
#include "Collisions.h"

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

#pragma endregion 	

	// --- SPRITES ---

#pragma region Backgrounds

	//Main Menu Background
		SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
		if (bgTexture == nullptr) throw std::exception("Error: bgTexture init");
		SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };
#pragma endregion

#pragma region Cursor

		//Cursor
		SDL_Texture* cursorTexture{ IMG_LoadTexture(m_renderer, "../../res/img/kintoun.png") };
		if (cursorTexture == nullptr) throw std::exception("Error: platerTexture init");
		SDL_Rect cursorRect{ 0, 0, 350, 190 };
		SDL_Point cursorPos{ 0, 0};

#pragma endregion

#pragma region Title Text

		//Title Text
		TTF_Font* font{ TTF_OpenFont("../../res/ttf/saiyan.ttf", 200) };
		if (font == nullptr) throw std::exception("No es pot inicialitzar SDL_ttf");
		SDL_Surface* tmpSurf{ TTF_RenderText_Blended(font, "My first SDL Game", SDL_Color{255,210,10,0}) };
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

#pragma region Audio

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			throw "No s'ha pogut inicialitzar SDL_Mixer";
		}

		Mix_Music* soundtrack{ Mix_LoadMUS("../../res/au/mainTheme.mp3") };
		if (!soundtrack) throw "No s'ha pogut carregar l'audio";
		Mix_PlayMusic(soundtrack, -1);
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

#pragma endregion 

		// --- GAME LOOP ---
		SDL_Event event;
		gameStates state = MENU;
		Player player1;
		Player player2;
		char exactTime[5];
		bool player1OnMove = false;
		bool player2OnMove = false;
		bool isRunning = true;
		bool mouseClicked = false;
		bool playMenuMusic = false;

		while (isRunning) {
			// HANDLE EVENTS
			while (SDL_PollEvent(&event))
			{
				switch (event.type) {
				case SDL_QUIT:
					isRunning = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
					break;
				case SDL_KEYUP:
					break;
				case SDL_MOUSEMOTION:
					cursorPos.x = event.motion.x;
					cursorPos.y = event.motion.y;
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
			cursorRect.x += (((cursorPos.x - (cursorRect.w / 2)) - cursorRect.x) / 10);
			cursorRect.y += (((cursorPos.y - (cursorRect.h / 2)) - cursorRect.y) / 10);

#pragma region Menu: Button Colliders
			//Changing Play Button Texture
			if (Collision(cursorPos, playButtonRect))
			{
				playAux = playHover;
				if (mouseClicked)
				{
					mouseClicked = false;
				}
			}
			else
				playAux = playTexture;

			//Changing Sound Off Texture
			if (Collision(cursorPos, soundButtonRect))
			{
				if (mouseClicked)
				{
					mouseClicked = false;
					playMenuMusic = !playMenuMusic;
					if (playMenuMusic) Mix_PauseMusic();
					else Mix_PlayMusic(soundtrack, 100);

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
			if (Collision(cursorPos, exitButtonRect))
			{
				exitAux = exitHover;
				if (mouseClicked) isRunning = false;
			}
			else exitAux = exitTexture;

			// --- DRAW ---
			SDL_RenderClear(m_renderer);

#pragma endregion 

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
				break;
			default:
				break;
			}

#pragma endregion 

			//Update the screen
			SDL_RenderPresent(m_renderer);

		}

#pragma region Close SDL

		// --- DESTROY ---
		SDL_DestroyTexture(bgTexture);
		SDL_DestroyTexture(cursorTexture);
		SDL_DestroyTexture(titleTexture);
		SDL_DestroyTexture(soundOffTexture);
		SDL_DestroyTexture(soundOnTexture);
		SDL_DestroyTexture(exitTexture);
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
