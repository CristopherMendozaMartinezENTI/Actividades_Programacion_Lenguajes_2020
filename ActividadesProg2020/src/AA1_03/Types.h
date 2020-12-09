#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdint.h>
#include <exception>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <time.h>
#include <string.h>
#include <unordered_map>
#include "Constants.h"

enum class gameStates {
	MENU, IN_GAME
};

enum class PlayerType {
	P1, P2
};
enum class EKeys {
	DEFAULT, ESC, UP, DOWN, LEFT, RIGHT, 
	W, A, S, D, MOUSE_LEFT, MOUSE_RIGHT, 
	SPACE, P, QUIT, TOTAL 
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
	Rect(int _x, int _y, int _w, int _h) :x{ _x }, y{ _y }, w{ _w }, h{ _h } {};
};

struct Color
{
	Uint8 r, g, b, a;
	Color(): r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {};
	Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a) :r{ _r }, g{ _g }, b{ _b }, a{ _a } {};
};

struct Font
{
	std::string id;
	std::string path;
	int size;
	Font(std::string _id, std::string _path, int _size) : id{ _id }, path{ _path }, size{ _size } {};
};

struct Text
{
	std::string id;
	std::string text;
	Color color;
	int x, y;
	Text() : id{ "0" }, text{ "#" }, color{ Color(0,0,0,0) }, x{ 0 }, y{ 0 } {};
	Text(std::string _id, std::string _text, Color _color, int _x, int _y) :
		id{ _id }, text{ _text }, color{ _color }, x{ _x }, y{ _y } {};
	void UpdateColor(Color _color) 
	{ 
		color = _color; 
	}
	void UpdateText(std::string _text)
	{
		text = _text;
	}
};


