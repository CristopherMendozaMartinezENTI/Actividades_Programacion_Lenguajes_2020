#pragma once
#include <SDL.h>
#define SCREEN_WIDTH 1980
#define SCREEN_HEIGHT 1080
#define FPS  60
#define DELAY_TIME 1000.0f / FPS
#define MAX_TIME 20000
#define AMOUNT_OF_COINS 10
#define PLAYER_SIZE 2
#define MOTION_SPEED 5

enum gameStates {
	MENU,
	IN_GAME
};

struct Directions
{
	bool goUp, goDown, goLeft, goRight;
	Directions() : goUp{ false }, goDown{ false }, goRight{ false }, goLeft{ false } {};
};

struct Vec2
{
	int x, y;
};

struct Rect
{
	int x, y, w, h;
	Rect() :x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 } {};
	Rect(SDL_Rect rect) :x{ rect.x }, y{ rect.y }, w{ rect.w }, h{ rect.h } {};
};

inline bool pointCollision(Vec2 vec, Rect rect)
{
	return vec.x > rect.x && vec.y > rect.y && vec.x < rect.w + rect.x && vec.y < rect.h + rect.y;
}

inline bool rectCollision(Rect rect1, Rect rect2)
{
	return (pointCollision(Vec2{ rect1.x, rect1.y }, rect2)
		|| pointCollision(Vec2{ rect1.x + rect1.w, rect1.y }, rect2)
		|| pointCollision(Vec2{ rect1.x,rect1.y + rect1.h }, rect2)
		|| pointCollision(Vec2{ rect1.x + rect1.w, rect1.y + rect1.h }, rect2));
}

struct Player
{
	int score;
	bool getCoins;
	//Directions
	bool goUp, goDown, goLeft, goRight;
	Player() :score{ 0 }, getCoins{ false }, goUp{ false }, goDown{ false }, goRight{ false }, goLeft{ false } {};
};

static SDL_Rect MyRect2SDL(const Rect* r) { return { r->x, r->y, r->w, r->h }; }
