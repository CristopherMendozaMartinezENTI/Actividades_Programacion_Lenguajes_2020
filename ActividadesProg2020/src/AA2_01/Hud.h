#pragma once
#include "Types.h"
#include "GameObject.h"


class Hud : public GameObject
{
private:
	//Variables needed to print the HP (icons) that each player has. Avatars are threaded as sprites.
	std::string Avatar[PLAYER_SIZE];
	Rect rectAvatar[PLAYER_SIZE];
	Rect posAvatar[PLAYER_SIZE*3];
	Rect frameAvatar[PLAYER_SIZE];
	int HP[PLAYER_SIZE];
	std::string avatarTextureID[PLAYER_SIZE], avatarRectID[PLAYER_SIZE], avatarPositionID[PLAYER_SIZE*3];

	//Variables needed to print the score that each player has (a number)
	int score[PLAYER_SIZE];
	Rect rectScore[PLAYER_SIZE];
	std::string scoreRectID[PLAYER_SIZE];

	//Varibales needed to print the Game Time left
	float gameTime;
	Rect rectGameTime[PLAYER_SIZE];
	Rect positionGameTime[PLAYER_SIZE];
	Rect frameGameTime[PLAYER_SIZE];
	std::string gameTimeRectID;

public:

	Hud();
	Hud(std::string _avatar1, std::string _avatar2, int _hp1, int _hp2, float _time);
	~Hud();

	void Update(InputManager _input, float _deltaTime);
	void Draw();
	void Reset();


	Rect GetRect();
	Rect GetFrame();
	Rect GetPosition();
	std::string GetTexture();
	void UpdateHPPlayer(int _hp1, int _hp2);

};