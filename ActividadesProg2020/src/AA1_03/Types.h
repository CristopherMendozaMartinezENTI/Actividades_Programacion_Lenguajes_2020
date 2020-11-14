#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdint.h>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <random>
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
	Rect(int _x, int _y, int _w, int _h) :x{ _x }, y{ _y }, w{ _w }, h{ _h } {};
};

struct Color
{
	uint8_t r, g, b, a;
	Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) :r{ _r }, g{ _g }, b{ _b }, a{ _a } {};
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
	Text(std::string _id, std::string _text, Color _color, int _x, int _y) :
		id{ _id }, text{ _text }, color{ _color }, x{ _x }, y{ _y } {};
	void UpdateColor(Color _color) { color = _color; }
};


