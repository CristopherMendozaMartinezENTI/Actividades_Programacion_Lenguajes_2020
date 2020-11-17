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
			windowIsOpen = false;
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
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_UP) keyIsUp[(int)EKeys::UP] = false;
			if (event.key.keysym.sym == SDLK_DOWN)  keyIsUp[(int)EKeys::DOWN] = false;
			if (event.key.keysym.sym == SDLK_RIGHT) keyIsUp[(int)EKeys::RIGHT] = false;
			if (event.key.keysym.sym == SDLK_LEFT) keyIsUp[(int)EKeys::LEFT] = false;
			if (event.key.keysym.sym == SDLK_w) keyIsUp[(int)EKeys::W] = false;
			if (event.key.keysym.sym == SDLK_s) keyIsUp[(int)EKeys::S] = false;
			if (event.key.keysym.sym == SDLK_d) keyIsUp[(int)EKeys::D] = false;
			if (event.key.keysym.sym == SDLK_a)	keyIsUp[(int)EKeys::A] = false;
			break;
		case SDL_MOUSEMOTION:
			mouseAxis.x = event.motion.x;
			mouseAxis.y = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				keyIsDown[(int)EKeys::MOUSE_LEFT] = true;
			break;
		default:;
		}
	}
}

Vec2 InputManager::returnMouseAxis()
{
    return mouseAxis;
}

bool InputManager::returnwindowIsOpen()
{
    return windowIsOpen;
}

bool InputManager::returnKeyIsDown()
{
	return keyIsDown;
}

bool InputManager::returnKeyIsUp()
{
	return keyIsUp;
}

bool InputManager::wasPressed(EKeys k) { //Si se hace un return de cualquier numero que no sea 0 el valor sera true.
	return keyIsUp[(int)k];
}

bool InputManager::isPressed(EKeys k) {//Si se hace un return de cualquier numero que no sea 0 el valor sera true.
	return keyIsDown[(int)k];
}

void InputManager::SetValue(EKeys k, bool value) {

	if (!wasPressed(k)) {
		keyIsDown[(int)k] = value;
	}
	else {
		keyIsDown[(int)k] = false;
	}
	keyIsUp[(int)k] = value;

	keyIsDown[(int)k] = value;

}

void InputManager::SetToFalse() {
	for (int i = 0; i < (int)EKeys::TOTAL; i++) {
		keyIsDown[i] = false;
	}
}
