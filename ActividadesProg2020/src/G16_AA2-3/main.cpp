#include "GameManager.h"

int main(int, char* [])
{

	try {

		GameManager game;
		game.Run();

	}

	catch (std::exception e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
