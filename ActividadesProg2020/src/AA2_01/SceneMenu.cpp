#include "SceneMenu.h"
SceneMenu::SceneMenu()
{
	music.PlayMenuMusic();

	//------------- MENU ---------------
	// --- SPRITES ---
#pragma region Backgrounds

	//Main Menu Background
	Renderer::Instance()->LoadTexture("bgTexture", "../../res/img/bgGame.jpg");
	Renderer::Instance()->LoadRect("bgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

#pragma endregion

	// --- TEXT --- 
#pragma region Title Text

	//All Colors
	colors["title_c"] = Color(255, 255, 255, 0);
	colors["button_c"] = Color(255, 188, 0, 0);
	colors["button_hover_c"] = Color(255, 0, 0, 0);
	colors["button_no_avalible"] = Color(130, 130, 130, 0);

	//All Texts
	texts["titleTexture"] = { "titleTexture", "SDL Bomberman ", colors["title_c"]};
	texts["playButtonText"] = { "playButtonText", "Level 1", colors["button_c"]};
	texts["playButtonText_hover"] = { "playButtonText_hover", "Level 1", colors["button_hover_c"]};
	texts["playButtonText2"] = { "playButtonText2", "Level 2", colors["button_c"]};
	texts["playButtonText_hover2"] = { "playButtonText_hover2", "Level 2", colors["button_hover_c"]};
	texts["soundOffButtonText"] = { "soundOffButtonText", "Sound Off", colors["button_c"]};
	texts["soundOffButtonText_hover"] = { "soundOffButtonText_hover", "Sound Off", colors["button_hover_c"]};
	texts["soundOnButtonText"] = { "soundOnButtonText", "Sound On", colors["button_c"]};
	texts["soundOnButtonText_hover"] = { "soundOnButtonText_hover", "Sound On", colors["button_hover_c"]};
	texts["rankingButtonText"] = { "rankingButtonText", "Ranking", colors["button_c"]};
	texts["rankingButtonText_hover"] = { "rankingButtonText_hover", "Ranking", colors["button_hover_c"]};
	texts["exitButtonText"] = { "exitButtonText", "Exit", colors["button_c"]};
	texts["exitButtonText_hover"] = { "exitButtonText_hover", "Exit", colors["button_hover_c"]};

	//All Flags
	playLevel1Hover = false;
	playLevel2Hover = false;
	sondOffHover = false;
	sondOnHover = false;
	exitHover = false;
	musicOff = false;

	//Title Text
	Renderer::Instance()->LoadFont(Font({ "Font", "../../res/ttf/game_over.ttf", 100 }));
	Renderer::Instance()->LoadFont(Font({ "FontHover", "../../res/ttf/game_over.ttf", 200 }));
	Renderer::Instance()->LoadTextureText("Font", texts["titleTexture"]);
	Renderer::Instance()->LoadRect("titleRect", Rect({ 220, 200, Renderer::Instance()->GetTextureSize("titleTexture").x, Renderer::Instance()->GetTextureSize("titleTexture").y }));

#pragma endregion

#pragma region Play Button 

	//Play Button (Menu)
	//Level 1
	Renderer::Instance()->LoadTextureText("Font", texts["playButtonText"]);
	Renderer::Instance()->LoadTextureText("FontHover", texts["playButtonText_hover"]);
	Renderer::Instance()->LoadRect("playButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("playButtonText").x) / 2, 300, Renderer::Instance()->GetTextureSize("playButtonText").x, Renderer::Instance()->GetTextureSize("playButtonText").y }));
	rectangles["playButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("playButtonText").x) / 2, 300, Renderer::Instance()->GetTextureSize("playButtonText").x, Renderer::Instance()->GetTextureSize("playButtonText").y });

	//Level 2
	Renderer::Instance()->LoadTextureText("Font", texts["playButtonText2"]);
	Renderer::Instance()->LoadTextureText("FontHover", texts["playButtonText_hover2"]);
	Renderer::Instance()->LoadRect("playButtonRect2", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("playButtonText2").x) / 2, 350, Renderer::Instance()->GetTextureSize("playButtonText2").x, Renderer::Instance()->GetTextureSize("playButtonText2").y }));
	rectangles["playButtonRect2"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("playButtonText2").x) / 2, 350, Renderer::Instance()->GetTextureSize("playButtonText2").x, Renderer::Instance()->GetTextureSize("playButtonText2").y });

#pragma endregion

#pragma region Sound Off Button

	//Sound Off Button (Menu)
	Renderer::Instance()->LoadTextureText("Font", texts["soundOffButtonText"]);
	Renderer::Instance()->LoadTextureText("FontHover", texts["soundOffButtonText_hover"]);
	Renderer::Instance()->LoadRect("soundButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("soundOffButtonText").x) / 2, 400, Renderer::Instance()->GetTextureSize("soundOffButtonText").x, Renderer::Instance()->GetTextureSize("soundOffButtonText").y }));
	rectangles["soundButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("soundOffButtonText").x) / 2, 400, Renderer::Instance()->GetTextureSize("soundOffButtonText").x, Renderer::Instance()->GetTextureSize("soundOffButtonText").y });

#pragma endregion

#pragma region Sound On Button

	//Sound On Button (Menu)
	Renderer::Instance()->LoadTextureText("Font", texts["soundOnButtonText"]);
	Renderer::Instance()->LoadTextureText("FontHover", texts["soundOnButtonText_hover"]);

#pragma endregion

#pragma region Ranking Button

	//Ranking Button (Menu)
	Renderer::Instance()->LoadTextureText("Font", texts["rankingButtonText"]);
	Renderer::Instance()->LoadTextureText("FontHover", texts["rankingButtonText_hover"]);
	Renderer::Instance()->LoadRect("rankingButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("rankingButtonText").x) / 2, 450, Renderer::Instance()->GetTextureSize("rankingButtonText").x, Renderer::Instance()->GetTextureSize("rankingButtonText").y }));
	rectangles["rankingButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("rankingButtonText").x) / 2, 450, Renderer::Instance()->GetTextureSize("rankingButtonText").x, Renderer::Instance()->GetTextureSize("rankingButtonText").y });

#pragma endregion

#pragma region Exit Button

	//Exit Button (Menu)
	Renderer::Instance()->LoadTextureText("Font", texts["exitButtonText"]);
	Renderer::Instance()->LoadTextureText("FontHover", texts["exitButtonText_hover"]);
	Renderer::Instance()->LoadRect("exitButtonRect", Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("exitButtonText").x) / 2, 500, Renderer::Instance()->GetTextureSize("exitButtonText").x, Renderer::Instance()->GetTextureSize("exitButtonText").y }));
	rectangles["exitButtonRect"] = Rect({ (SCREEN_WIDTH - Renderer::Instance()->GetTextureSize("exitButtonText").x) / 2, 500, Renderer::Instance()->GetTextureSize("exitButtonText").x, Renderer::Instance()->GetTextureSize("exitButtonText").y });

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
	if (input.returnKeyIsDown()[(int)EKeys::QUIT]) state = e_GameStates::QUIT;
	if (input.returnKeyIsDown()[(int)EKeys::ESC])  state = e_GameStates::QUIT;

#pragma region Menu Interactions
	
	//Changing Play Button Texture
	if (collisions::pointCollision(cursor.GetPosition(), rectangles["playButtonRect"]))
	{
		//Play Button = HOVER color.
		playLevel1Hover = true;
		if (mouseClicked) state = e_GameStates::IN_GAME_LEVEL1;
	}
	else
		playLevel1Hover = false;

	//Changing Play Button Texture
	if (collisions::pointCollision(cursor.GetPosition(), rectangles["playButtonRect2"]))
	{
		//Play Button = HOVER color.
		playLevel2Hover = true;
		if (mouseClicked) state = e_GameStates::IN_GAME_LEVEL2;
	}
	else
		playLevel2Hover = false;

	if (collisions::pointCollision(cursor.GetPosition(), rectangles["rankingButtonRect"]))
	{
		//Play Button = HOVER color.
		rankingHover = true;
		if (mouseClicked) state = e_GameStates::RANKING;
	}
	else
		rankingHover = false;

	//Changing Sound Off/On Texture
	if (collisions::pointCollision(cursor.GetPosition(), rectangles["soundButtonRect"]))
	{
		if (input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT])
		{
			input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT] = false;
			musicOff = !musicOff;
		}
		if (musicOff)
		{
			//Sound On HOVER color.
			sondOnHover = true;
		}
		else if(!musicOff)
		{
			//Sound Off HOVER color.
			sondOffHover = true;
		}
	}
	else
	{
		if (musicOff)
		{
			//Sound On NORMAL color.
			sondOnHover = false;
		}
		else if(!musicOff)
		{
			//Sound Off NORMAL color.
			sondOffHover = false;
		}
	}

	if (musicOff) music.PauseMenuMusic();
	else music.ResumeMenuMusic();

	//Changing Exit Button Texture
	if (collisions::pointCollision(cursor.GetPosition(), rectangles["exitButtonRect"]))
	{
		//Exit button HOVER color
		exitHover = true;
		if (mouseClicked) state = e_GameStates::QUIT;
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
	//Play Level Button
	if (playLevel1Hover)	Renderer::Instance()->PushImage("playButtonText_hover", "playButtonRect");
	else Renderer::Instance()->PushImage("playButtonText", "playButtonRect");
	//Play Level Button
	if (playLevel2Hover)	Renderer::Instance()->PushImage("playButtonText_hover2", "playButtonRect2");
	else Renderer::Instance()->PushImage("playButtonText2", "playButtonRect2");
	//Ranking Button
	if (rankingHover)	Renderer::Instance()->PushImage("rankingButtonText_hover", "rankingButtonRect");
	else Renderer::Instance()->PushImage("rankingButtonText", "rankingButtonRect");
	//Exit Button
	if (exitHover) Renderer::Instance()->PushImage("exitButtonText_hover", "exitButtonRect");
	else Renderer::Instance()->PushImage("exitButtonText", "exitButtonRect");
	//Sound Button
	if (musicOff)
		if (sondOnHover) Renderer::Instance()->PushImage("soundOnButtonText_hover", "soundButtonRect");
		else Renderer::Instance()->PushImage("soundOnButtonText", "soundButtonRect");
	else
		if (sondOffHover) Renderer::Instance()->PushImage("soundOffButtonText_hover", "soundButtonRect");
		else Renderer::Instance()->PushImage("soundOffButtonText", "soundButtonRect");

	Renderer::Instance()->Render();
}

float SceneMenu::UpdateDeltaTime()
{
	return 0.0f;
}
