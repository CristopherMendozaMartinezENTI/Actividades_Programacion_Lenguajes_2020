#pragma once
#include "Utilities.h"
#include "ScoreBoard.h"
class GameManager
{
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	float sec;

	//Textures
	SDL_Texture* bgTexture;
	SDL_Texture* gameBgTexture;
	SDL_Texture* cursorTexture;
	SDL_Texture* titleTexture;
	SDL_Texture* playTexture;
	SDL_Texture* playHover;
	SDL_Texture* playAux;
	SDL_Texture* soundOffTexture;
	SDL_Texture* soundOffHover;
	SDL_Texture* soundOffAux;
	SDL_Texture* soundOnTexture;
	SDL_Texture* soundOnHover;
	SDL_Texture* exitTexture;
	SDL_Texture* exitHover;
	SDL_Texture* exitAux;
	SDL_Texture* player1ScoreTexture;
	SDL_Texture* player2ScoreTexture;
	SDL_Texture* playerTexture;
	SDL_Texture* scoreTexture;
	SDL_Texture* coinTexture;
	SDL_Texture* timeTexture;

	//Variables para definir texturas
	int textWidth, textHeight, scoreWidth, scoreHeight;

	//Fuentes 
	TTF_Font* font;
	TTF_Font* inGameFont;

	//Rectangulos
	SDL_Rect bgRect;
	SDL_Rect gameBgRect;
	SDL_Rect cursorRect;
	SDL_Rect cursorTarget;
	SDL_Rect titleRect;
	SDL_Rect playButtonRect;
	SDL_Rect soundButtonRect;
	SDL_Rect exitButtonRect;
	SDL_Rect player1ScoreRect;
	SDL_Rect player2ScoreRect; 
	SDL_Rect player1Rect;  
	SDL_Rect player1Position; 
	SDL_Rect player2Rect; 
	SDL_Rect player2Position;
	SDL_Rect coinRect[AMOUNT_OF_COINS];
	SDL_Rect timeRect;

	//Puntuacion Player 1
	SDL_Rect scoreRectPlayer1Right, scorePositionPlayer1Right;
	SDL_Rect scoreRectPlayer1Center, scorePositionPlayer1Center;
	SDL_Rect scoreRectPlayer1Left, scorePositionPlayer1Left;

	//Puntuacion Player 2
	SDL_Rect scoreRectPlayer2Right, scorePositionPlayer2Right;
	SDL_Rect scoreRectPlayer2Center, scorePositionPlayer2Center;
	SDL_Rect scoreRectPlayer2Left, scorePositionPlayer2Left;

	//Surfaces
	SDL_Surface* tmpSurf;

	//Players 
	ScoreBoard boardP1;
	ScoreBoard boardP2;

	Mix_Music* menuMusic;

	char exactTime[5];

public:
	Uint32 frameStart, frameTime;
	PlayerClass playerClass1;
	PlayerClass playerClass2;
	gameStates state;
	Vec2 mouseAxis;
	bool isRunning;
	bool playMenuMusic;
	bool mouseClicked;

	GameManager(SDL_Window* _window, SDL_Renderer* _renderer);
	~GameManager();

	void SDLInit();
	void Update();
	void Draw();
	void Destroy();
};

