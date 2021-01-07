/*
#include "SceneMenu.h"

SceneMenu::SceneMenu()
{
	isRuning = true;
	playMenuMusic = true;
	//music.PlayMenuMusic();

	//------------- MENU ---------------
	// --- SPRITES ---
#pragma region Backgrounds

	//Main Menu Background
	Renderer::Instance()->LoadTexture("bgTexture", "../../res/img/bg.jpg");
	Renderer::Instance()->LoadRect("bgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

#pragma endregion

#pragma region Cursor

	//Cursor
	Renderer::Instance()->LoadTexture("cursorTexture", "../../res/img/kintoun.png");
	Renderer::Instance()->LoadRect("cursorRect", Rect({ 0, 0, 350, 190 }));
	cursor.SetRect(Rect({ 0,0,350,190 }));
	rectangles["cursorRect"] = cursor.GetRect();

#pragma endregion

	// --- TEXT --- 
#pragma region Title Text

	//All Colors
	colors["title_c"] = Color(250, 135, 20, 0);
	colors["button_c"] = Color(255, 188, 0, 0);
	colors["button_hover_c"] = Color(255, 0, 0, 0);

	//All Texts
	texts["titleTexture"] = { "titleTexture", "My first SDL Game", colors["title_c"], 200,200 };
	texts["playButtonText"] = { "playButtonText", "Play", colors["button_c"], SCREEN_WIDTH / 2, 400 };
	texts["playButtonText_hover"] = { "playButtonText_hover", "Play", colors["button_hover_c"], SCREEN_WIDTH / 2, 400 };
	texts["soundOffButtonText"] = { "soundOffButtonText", "Sound Off", colors["button_c"], SCREEN_WIDTH / 2, 600 };
	texts["soundOffButtonText_hover"] = { "soundOffButtonText_hover", "Sound Off", colors["button_hover_c"], SCREEN_WIDTH / 2, 600 };
	texts["soundOnButtonText"] = { "soundOnButtonText", "Sound On", colors["button_c"], SCREEN_WIDTH / 2, 600 };
	texts["soundOnButtonText_hover"] = { "soundOnButtonText_hover", "Sound On", colors["button_hover_c"], SCREEN_WIDTH / 2, 600 };
	texts["exitButtonText"] = { "exitButtonText", "Exit", colors["button_c"], SCREEN_WIDTH / 2, 800 };
	texts["exitButtonText_hover"] = { "exitButtonText_hover", "Exit", colors["button_hover_c"], SCREEN_WIDTH / 2, 800 };

	//All Flags
	playHover = false;
	sondOffHover = false;
	sondOnHover = false;
	exitHover = false;

	//Title Text
	Renderer::Instance()->LoadFont(Font({ "SaiyanFont", "../../res/ttf/saiyan.ttf", 200 }));
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["titleTexture"]);
	Renderer::Instance()->LoadRect("titleRect", Rect({ 300, 200, Renderer::Instance()->GetTextureSize("titleTexture").x, Renderer::Instance()->GetTextureSize("titleTexture").y }));

#pragma endregion

#pragma region Play Button 
	//Play Button (Menu)
	//normal surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["playButtonText"]);
	//hover surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["playButtonText_hover"]);
	Renderer::Instance()->LoadRect("playButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("playButtonText").x) / 2, 400, Renderer::Instance()->GetTextureSize("playButtonText").x, Renderer::Instance()->GetTextureSize("playButtonText").y }));
	rectangles["playButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("playButtonText").x) / 2, 400, Renderer::Instance()->GetTextureSize("playButtonText").x, Renderer::Instance()->GetTextureSize("playButtonText").y });

#pragma endregion

#pragma region Sound Off Button

	//Sound Off Button (Menu)
	//normal surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["soundOffButtonText"]);
	//hover surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["soundOffButtonText_hover"]);
	Renderer::Instance()->LoadRect("soundButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("soundOffButtonText").x) / 2, 600, Renderer::Instance()->GetTextureSize("soundOffButtonText").x, Renderer::Instance()->GetTextureSize("soundOffButtonText").y }));
	rectangles["soundButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("soundOffButtonText").x) / 2, 600, Renderer::Instance()->GetTextureSize("soundOffButtonText").x, Renderer::Instance()->GetTextureSize("soundOffButtonText").y });

#pragma endregion

#pragma region Sound On Button

	//Sound On Button (Menu)
	//normal surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["soundOnButtonText"]);
	//hover surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["soundOnButtonText_hover"]);

#pragma endregion

#pragma region Exit Button

	//Exit Button (Menu)
	//normal surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["exitButtonText"]);
	//hover surface
	Renderer::Instance()->LoadTextureText("SaiyanFont", texts["exitButtonText_hover"]);
	Renderer::Instance()->LoadRect("exitButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("exitButtonText").x) / 2, 800, Renderer::Instance()->GetTextureSize("exitButtonText").x, Renderer::Instance()->GetTextureSize("exitButtonText").y }));
	rectangles["exitButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("exitButtonText").x) / 2, 800, Renderer::Instance()->GetTextureSize("exitButtonText").x, Renderer::Instance()->GetTextureSize("exitButtonText").y });

#pragma endregion
}

SceneMenu::~SceneMenu()
{


}

void SceneMenu::Update(InputManager &input)
{
	cursor.SetPosition(input.returnMouseAxis());
	if (input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT]) mouseClicked = true;
	if (!input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT]) mouseClicked = false;
	if (input.returnKeyIsDown()[(int)EKeys::QUIT]) state = gameStates::QUIT;
	if (input.returnKeyIsDown()[(int)EKeys::ESC])  state = gameStates::QUIT;

#pragma region Menu Interactions

	//Hide Mouse 
	Renderer::Instance()->HideCursor();

	//Putting the Mouse at the center of the cursor 
	cursor.SetRect(((cursor.GetPosition().x - (cursor.GetRect().w / 2)) - cursor.GetRect().x) / 10,
		((cursor.GetPosition().y - (cursor.GetRect().h / 2)) - cursor.GetRect().y) / 10);

	rectangles["cursorRect"] = cursor.GetRect();

	Renderer::Instance()->SetRect("cursorRect", rectangles["cursorRect"]);

	//Changing Play Button Texture
	if (collisions::pointCollision(cursor.GetPosition(), rectangles["playButtonRect"]))
	{
		//Play Button = HOVER color.
		playHover = true;

		if (mouseClicked) //Start the game
		{
			state = gameStates::IN_GAME;
		}
	}
	else
	{
		//Play Button = NORMAL color.
		playHover = false;
	}

	//Changing Sound Off/On Texture
	if (collisions::pointCollision(cursor.GetPosition(), rectangles["soundButtonRect"]))
	{
		if (input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT])
		{
			input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT] = false;
			playMenuMusic = !playMenuMusic;
			if (playMenuMusic) music.PauseMenuMusic();
			else music.ResumeMenuMusic();
		}
		if (playMenuMusic)
		{
			//Sound On HOVER color.
			sondOnHover = true;
		}
		else if(!playMenuMusic)
		{
			//Sound Off HOVER color.
			sondOffHover = true;
		}
	}
	else
	{
		if (playMenuMusic)
		{
			//Sound On NORMAL color.
			sondOnHover = false;
		}
		else if(!playMenuMusic)
		{
			//Sound Off NORMAL color.
			sondOffHover = false;
		}
	}

	//Changing Exit Button Texture
	if (collisions::pointCollision(cursor.GetPosition(), rectangles["exitButtonRect"]))
	{
		//Exit button HOVER color
		exitHover = true;

		if (mouseClicked) state = gameStates::QUIT;
	}
	else
	{
		//Exit button NORMAL color.
		exitHover = false;
	}

#pragma endregion

}

void SceneMenu::Draw()
{
	Renderer::Instance()->Clear();

	//Background
	Renderer::Instance()->PushImage("bgTexture", "bgRect");
	//Cursor
	Renderer::Instance()->PushImage("cursorTexture", "cursorRect");
	//Title
	Renderer::Instance()->PushImage("titleTexture", "titleRect");
	Renderer::Instance()->PushImage("titleTexture_hover", "titleRect");
	//Pay Button
	if (playHover)	Renderer::Instance()->PushImage("playButtonText_hover", "playButtonRect");
	else Renderer::Instance()->PushImage("playButtonText", "playButtonRect");
	//Exit Button
	if (exitHover) Renderer::Instance()->PushImage("exitButtonText_hover", "exitButtonRect");
	else Renderer::Instance()->PushImage("exitButtonText", "exitButtonRect");
	//Sound Button
	if (playMenuMusic)
		if (sondOnHover) Renderer::Instance()->PushImage("soundOnButtonText_hover", "soundButtonRect");
		else Renderer::Instance()->PushImage("soundOnButtonText", "soundButtonRect");
	else
		if (sondOffHover) Renderer::Instance()->PushImage("soundOffButtonText_hover", "soundButtonRect");
		else Renderer::Instance()->PushImage("soundOffButtonText", "soundButtonRect");

	Renderer::Instance()->Render();

}

*/