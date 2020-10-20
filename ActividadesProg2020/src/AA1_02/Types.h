#pragma once
#define SCREEN_WIDTH 1980
#define SCREEN_HEIGHT 1080
#define FPS  60
#define DELAY_TIME 1000.0f / FPS
#define MAX_TIME 200000
#define AMOUNT_OF_COINS 20
#define PLAYER_SIZE 2
#define MOTION_SPEED 5

enum gameStates {
	MENU,
	IN_GAME,
};

struct Rect
{
	int x, y, w, h;
	Rect(SDL_Rect rect) :x{ rect.x }, y{ rect.y }, w{ rect.w }, h{ rect.h } {};
};

struct Player
{
	int score;
	bool getCoins;
	bool goUp, goDown, goLeft, goRight;
	Player() :score{ 0 }, getCoins{ false }, goUp{ false }, goDown{ false }, goRight{ false }, goLeft{ false } {};
};

