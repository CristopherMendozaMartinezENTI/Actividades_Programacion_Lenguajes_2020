#include "SceneRanking.h"

SceneRanking::SceneRanking()
{
	state = e_GameStates::RANKING;
	Renderer::Instance()->LoadFont(Font({ "Font", "../../res/ttf/game_over.ttf", 80 }));

	Renderer::Instance()->LoadTexture("bgTexture", "../../res/img/bgGame.jpg");
	Renderer::Instance()->LoadRect("bgRect", Rect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }));

	Text RankingTitle = { "titleRankingTexture", "RANKING ",  Color(0, 0, 0, 0)};
	Renderer::Instance()->LoadTextureText("Font", RankingTitle);
	Renderer::Instance()->LoadRect("titleRankingRect", Rect({ 300, 10, Renderer::Instance()->GetTextureSize("titleRankingTexture").x, Renderer::Instance()->GetTextureSize("titleRankingTexture").y }));
	SceneRanking::ReadBinaryFile();
}

SceneRanking::~SceneRanking()
{
}

void SceneRanking::ReadBinaryFile()
{
	std::multimap<int, std::string> ranking;
	std::string rankFile;
	size_t len;
	bool exists = true;

	//READ FILE
	std::ifstream inFile("../../res/files/ranking.bin", std::ios::out | std::ios::binary);
	inFile.read(reinterpret_cast<char*>(&len), sizeof(size_t));
	if (!(bool)inFile) exists = false;
	else {
		char* temp = new char[(int)len + 1];
		inFile.read(temp, len);
		temp[(int)len] = '\0';
		rankFile = temp;
		rankFile = rankFile.substr(0, rankFile.find(";") + 1);
		if (rankFile == FILE_CHECK) {
			rankFile.clear();
			rankFile = temp;
			while (rankFile.substr(rankFile.find(";") + 1) != "\0")
			{
				rankFile = rankFile.substr(rankFile.find(";") + 1);
				ranking.insert(std::pair<int, std::string>(atoi(rankFile.substr(rankFile.find("-") + 1, rankFile.find(";")).c_str()), rankFile.substr(0, rankFile.find("-"))));
			}
		}
		else exists = false;
	}
	rankFile = FILE_CHECK;
	inFile.close();

	//CREATE A NEW FILE IF IS WRONG
	if (!exists) {
		std::ofstream fsalida("../../res/files/ranking.bin", std::ios::out | std::ios::binary);
		len = rankFile.size();
		fsalida.write(reinterpret_cast<char*>(&len), sizeof(size_t));
		fsalida.write(rankFile.c_str(), rankFile.size());

		fsalida.close();
	}

	//PRINT
	int i = 0;
	Text textureText;
	for (auto it = ranking.crbegin(); it != ranking.crend(); ++it, i++) {
		rankFile = rankFile + it->second + "-" + std::to_string(it->first) + ";";
		textureText.text = std::to_string(i + 1) + "-" + it->second + " " + std::to_string(it->first) + " POINTS";
		textureText.id = "ranking-" + std::to_string(i + 1);
		textureText.color = { 255, 255, 255, 255 };
		Renderer::Instance()->OverwritteTextureText(textureText);
	}
}

void SceneRanking::Update(InputManager& _input)
{
	if (_input.returnKeyIsDown()[(int)EKeys::QUIT]) state = e_GameStates::QUIT;
	if (_input.returnKeyIsDown()[(int)EKeys::ESC])
	{
		state = e_GameStates::MENU;
		_input.returnKeyIsDown()[(int)EKeys::ESC] = false;
	}
}

void SceneRanking::Draw()
{
	Renderer::Instance()->Clear();
	Renderer::Instance()->PushImage("bgTexture", "bgRect");
	Renderer::Instance()->PushImage("titleRankingTexture", "titleRankingRect");
	for (int i = 0; i < 10; i++)
	{
		auto id = "ranking-" + std::to_string(i + 1);
		if (Renderer::Instance()->TextureExist(id)) Renderer::Instance()->PushImageToRect(id, { (SCREEN_WIDTH / 7), i * 35 + 175, 600, 25 });
	}
	Renderer::Instance()->Render();
}

float SceneRanking::UpdateDeltaTime()
{
	return 0.0f;
}

