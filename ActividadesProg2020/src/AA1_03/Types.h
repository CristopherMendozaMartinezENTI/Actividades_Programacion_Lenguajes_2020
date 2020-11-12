#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include "Constants.h"

enum class gameStates {
	MENU, IN_GAME
};

enum class PlayerType {
	P1, P2
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

struct Color
{
	Uint8 r, g, b, a;
	Color() :r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {};
};

struct Font
{
	std::string path;
	std::string id;
	int size;
};

struct Text
{
	std::string text;
	std::string id;
	Color color;
	int x, y;
};


