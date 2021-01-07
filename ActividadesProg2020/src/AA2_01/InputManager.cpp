#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			keyIsDown[(int)EKeys::QUIT] = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) keyIsDown[(int)EKeys::ESC] = true;
			if (event.key.keysym.sym == SDLK_UP) keyIsDown[(int)EKeys::UP] = true;
			if (event.key.keysym.sym == SDLK_DOWN)  keyIsDown[(int)EKeys::DOWN] = true;
			if (event.key.keysym.sym == SDLK_RIGHT) keyIsDown[(int)EKeys::RIGHT] = true;
			if (event.key.keysym.sym == SDLK_LEFT) keyIsDown[(int)EKeys::LEFT] = true;
			if (event.key.keysym.sym == SDLK_w) keyIsDown[(int)EKeys::W] = true;
			if (event.key.keysym.sym == SDLK_s)  keyIsDown[(int)EKeys::S] = true;
			if (event.key.keysym.sym == SDLK_d)  keyIsDown[(int)EKeys::D] = true;
			if (event.key.keysym.sym == SDLK_a)  keyIsDown[(int)EKeys::A] = true;
			if (event.key.keysym.sym == SDLK_KP_0) keyIsDown[(int)EKeys::KEYPAD_0] = true;
			if (event.key.keysym.sym == SDLK_SPACE) keyIsDown[(int)EKeys::SPACE] = true;
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_UP) keyIsDown[(int)EKeys::UP] = false;
			if (event.key.keysym.sym == SDLK_DOWN)  keyIsDown[(int)EKeys::DOWN] = false;
			if (event.key.keysym.sym == SDLK_RIGHT) keyIsDown[(int)EKeys::RIGHT] = false;
			if (event.key.keysym.sym == SDLK_LEFT) keyIsDown[(int)EKeys::LEFT] = false;
			if (event.key.keysym.sym == SDLK_w) keyIsDown[(int)EKeys::W] = false;
			if (event.key.keysym.sym == SDLK_s) keyIsDown[(int)EKeys::S] = false;
			if (event.key.keysym.sym == SDLK_d) keyIsDown[(int)EKeys::D] = false;
			if (event.key.keysym.sym == SDLK_a)	keyIsDown[(int)EKeys::A] = false;
			if (event.key.keysym.sym == SDLK_KP_0) keyIsDown[(int)EKeys::KEYPAD_0] = false;
			if (event.key.keysym.sym == SDLK_SPACE) keyIsDown[(int)EKeys::SPACE] = false;
			break;
		case SDL_MOUSEMOTION:
			mouseAxis.x = event.motion.x;
			mouseAxis.y = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) keyIsDown[(int)EKeys::MOUSE_LEFT] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) keyIsDown[(int)EKeys::MOUSE_LEFT] = false;
		default:;
		}
	}
}

Vec2 InputManager::returnMouseAxis()
{
    return mouseAxis;
}

bool* InputManager::returnKeyIsDown()
{
	return keyIsDown;
}

