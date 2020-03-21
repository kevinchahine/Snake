#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "SnakeEngine.h"

int main()
{
	// Initialize random number generator
	srand(time(NULL));

	try {
		SnakeEngine engine{ 3, 3 };

		engine.init();

		SnakeEngine::GAME_STATE gameState = SnakeEngine::GAME_STATE::CONTINUE;

		while (gameState == SnakeEngine::GAME_STATE::CONTINUE) {
			gameState = engine.update();
		}
	}
	catch (std::exception & e) {
		cout << "Exception caught in " << __FUNCTION__ << ": "
			<< e.what() << '\n';
	}

	cout << "Press any key to continue . . .";
	cin.get();
	cin.get();
	return 0;
}
