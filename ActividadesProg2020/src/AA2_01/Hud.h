#pragma once
#include "Types.h"
#include "GameObject.h"


class Hud : public GameObject
{
private:
	std::string Avatar[PLAYER_SIZE];
	int HP[PLAYER_SIZE];
	int score[PLAYER_SIZE];
	float gameTime;

public:

	Hud();
	Hud(std::string _avatar1, std::string _avatar2, int _hp1, int _hp2, float _time);
	~Hud();

	void Update(InputManager _input, float _deltaTime);
	void Reset();


	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	std::string GetTexture();

};