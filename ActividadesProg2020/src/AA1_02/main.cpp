#include "GameManager.h"

int main(int, char* [])
{
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

		GameManager game(m_window, m_renderer);

		SDL_Event event;

		while (game.isRunning) {
			game.frameStart = SDL_GetTicks();
			// HANDLE EVENTS
			while (SDL_PollEvent(&event))
			{
				switch (event.type) {
				case SDL_QUIT:
					game.isRunning = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) game.isRunning = false;
					if (event.key.keysym.sym == SDLK_UP) game.playerClass1.dir.goUp = true;
					if (event.key.keysym.sym == SDLK_DOWN) game.playerClass1.dir.goDown = true;
					if (event.key.keysym.sym == SDLK_RIGHT) game.playerClass1.dir.goRight = true;
					if (event.key.keysym.sym == SDLK_LEFT) game.playerClass1.dir.goLeft = true;
					if (event.key.keysym.sym == SDLK_w) game.playerClass2.dir.goUp = true;
					if (event.key.keysym.sym == SDLK_s) game.playerClass2.dir.goDown = true;
					if (event.key.keysym.sym == SDLK_d) game.playerClass2.dir.goRight = true;
					if (event.key.keysym.sym == SDLK_a) game.playerClass2.dir.goLeft = true;
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_UP)  game.playerClass1.dir.goUp = false;
					if (event.key.keysym.sym == SDLK_DOWN)  game.playerClass1.dir.goDown = false;
					if (event.key.keysym.sym == SDLK_RIGHT) game.playerClass1.dir.goRight = false;
					if (event.key.keysym.sym == SDLK_LEFT)  game.playerClass1.dir.goLeft = false;
					if (event.key.keysym.sym == SDLK_w)  game.playerClass2.dir.goUp = false;
					if (event.key.keysym.sym == SDLK_s)  game.playerClass2.dir.goDown = false;
					if (event.key.keysym.sym == SDLK_d)	 game.playerClass2.dir.goRight = false;
					if (event.key.keysym.sym == SDLK_a)	 game.playerClass2.dir.goLeft = false;
					break;
				case SDL_MOUSEMOTION:
					game.mouseAxis.x = event.motion.x;
					game.mouseAxis.y = event.motion.y;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
						game.mouseClicked = true;
					break;
				default:;
				}
			}

			// --- UPDATE --
			game.Update();

			// --- DRAW ---
			game.Draw();
		}

	}

	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
