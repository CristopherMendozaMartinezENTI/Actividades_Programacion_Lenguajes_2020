#include "SceneMenu.h"
SceneMenu::SceneMenu()
{
	music.PlayMenuMusic();
	Renderer::Instance()->LoadFont(Font({ "BomberFont", "../../res/ttf/game_over.ttf", 80 }));

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

	//Title Text
	tittleText = { "titleTexture", "SDL Bomberman ", colors["title_c"] };
	Renderer::Instance()->LoadTextureText("BomberFont", tittleText);
	Renderer::Instance()->LoadRect("titleRect", Rect({ 220, 200, Renderer::Instance()->GetTextureSize(tittleText.id).x, Renderer::Instance()->GetTextureSize(tittleText.id).y }));



	Button tmpButton;
	//Level 1 Button 
	tmpButton = { colors["button_c"], colors["button_hover_c"], "Level 1", Rect(SCREEN_WIDTH / 2, 300, 0, 0), "playButtonText" };
	buttons.push_back(tmpButton); //0
	//Level 2 Button
	tmpButton = { colors["button_c"], colors["button_hover_c"], "Level 2", Rect(SCREEN_WIDTH / 2, 350, 0, 0), "playButtonText2" };
	buttons.push_back(tmpButton); //1
	//Ranking Button
	tmpButton = { colors["button_c"], colors["button_hover_c"], "Ranking", Rect(SCREEN_WIDTH / 2, 450, 0, 0), "rankingButtonText" };
	buttons.push_back(tmpButton); //2
	//Exit Button
	tmpButton = { colors["button_c"], colors["button_hover_c"], "Exit", Rect(SCREEN_WIDTH / 2, 500, 0, 0), "exitButtonText" };
	buttons.push_back(tmpButton); //3

	soundButton = { colors["button_c"], colors["button_hover_c"], colors["button_c"], colors["button_hover_c"], "Sound Off", "Dale a tu cuerpo alegria macarena",  Rect(SCREEN_WIDTH / 2, 400, 0, 0), "soundButtonText" };

		//Sound Buttons
	musicOff = false;

#pragma endregion
}

SceneMenu::~SceneMenu()
{


}

void SceneMenu::Update(InputManager& input)
{

	cursor.SetPosition(input.returnMouseAxis());
	if (input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT]) mouseClicked = true;
	if (!input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT]) mouseClicked = false;
	if (input.returnKeyIsDown()[(int)EKeys::QUIT]) state = e_GameStates::QUIT;
	if (input.returnKeyIsDown()[(int)EKeys::ESC])  state = e_GameStates::QUIT;

#pragma region Button Logic

	for (int i = 0; i < buttons.size(); i++)
	{
		if (collisions::pointCollision(cursor.GetPosition(), buttons[i].GetRect())) {
			buttons[i].SetHover(true);
		}
		else {
			buttons[i].SetHover(false);
		}
	}
	//Play Button Logic
	if (collisions::pointCollision(cursor.GetPosition(), buttons[0].GetRect()))
	{
		if (mouseClicked) state = e_GameStates::IN_GAME_LEVEL1;
	}

	//Play Button Logic
	if (collisions::pointCollision(cursor.GetPosition(), buttons[1].GetRect()))
	{
		if (mouseClicked) state = e_GameStates::IN_GAME_LEVEL2;
	}

	//Ranking Button Logic
	if (collisions::pointCollision(cursor.GetPosition(), buttons[2].GetRect()))
	{
		if (mouseClicked) state = e_GameStates::RANKING;
	}

	//Exit Button Logic
	if (collisions::pointCollision(cursor.GetPosition(), buttons[3].GetRect()))
	{
		if (mouseClicked) state = e_GameStates::QUIT;
	}

#pragma endregion

#pragma region SuperButton Logic

	
	// Sound Off/On Logic
	if (collisions::pointCollision(cursor.GetPosition(), soundButton.GetRect()))
	{
		soundButton.SetHover(true);

		if (input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT])
		{
			input.returnKeyIsDown()[(int)EKeys::MOUSE_LEFT] = false;
			soundButton.SetPressed();
			musicOff = !musicOff;
		}
	}
	else {
		soundButton.SetHover(false);
	}
	
	if (musicOff) music.PauseMenuMusic();
	else music.ResumeMenuMusic();

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
	Renderer::Instance()->PushImage(tittleText.id, "titleRect");

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons.at(i).Draw();
	}

	soundButton.Draw();


	Renderer::Instance()->Render();
}

float SceneMenu::UpdateDeltaTime()
{
	deltaTime = (clock() - lastTime);
	lastTime = clock();
	deltaTime /= CLOCKS_PER_SEC;
	return deltaTime;
}
