#include "SnakeEngine.h"

SnakeEngine::SnakeEngine(size_t boardHeight, size_t boardWidth) :
	currGameState{ GAME_STATE::CONTINUE },
	board{ boardHeight, boardWidth },
	snake{ boardHeight, boardWidth },
	apple{ boardHeight, boardWidth }
{
	init();
}

bool SnakeEngine::operator==(const SnakeEngine& left) const
{
	return snake == left.snake && apple == left.apple;
}

void SnakeEngine::init()
{
	reset();
}

void SnakeEngine::reset()
{
	currGameState = GAME_STATE::CONTINUE;
	board.clear();
	snake.resetHeadRandom();
	apple.moveRandom();
}

SnakeEngine::GAME_STATE SnakeEngine::update(char controlInput)
{
	board.clear();
	board.paste(snake);
	board.paste(apple);

	controlInput = tolower(controlInput);
	
	switch (controlInput) {
	case 'w':	
		// Can we move UP?
		if (snake.isMoveUpValid()) {
			// Yes. Did we eat an apple?
			if (snake.head().upOne() == apple) {
				// Yes
				snake.growUpFast();
			}
			else {
				snake.moveUpFast();
			}
		}
		else {
			std::cout << "Hit wall\n";
			currGameState = GAME_STATE::GAME_OVER;
			return currGameState;
		}
		break;

	case 's':	
		// Can we move DOWN?
		if (snake.isMoveDownValid()) {
			// Yes. Did we eat an apple?
			if (snake.head().downOne() == apple) {
				// Yes
				snake.growDownFast();
			}
			else {
				snake.moveDownFast();
			}
		}
		else {
			std::cout << "Hit wall\n";
			currGameState = GAME_STATE::GAME_OVER;
			return currGameState;
		}
		break;

	case 'a':	
		// Can we move LEFT?
		if (snake.isMoveLeftValid()) {
			// Yes. Did we eat an apple?
			if (snake.head().leftOne() == apple) {
				// Yes
				snake.growLeftFast();
			}
			else {
				snake.moveLeftFast();
			}
		}
		else {
			std::cout << "Hit wall\n";
			currGameState = GAME_STATE::GAME_OVER;
			return currGameState;
		}
		break;

	case 'd':	
		// Can we move RIGHT?
		if (snake.isMoveRightValid()) {
			// Yes. Did we eat an apple?
			if (snake.head().rightOne() == apple) {
				// Yes
				snake.growRightFast();
			}
			else {
				snake.moveRightFast();
			}
		}
		else {
			std::cout << "Hit wall\n";
			currGameState = GAME_STATE::GAME_OVER;
			return currGameState;
		}
		break;
	}

	// Did we bite our selves?
	if (snake.bitItself()) {
		std::cout << "Ouch. Game over\n";
		currGameState = GAME_STATE::GAME_OVER;
		return currGameState;
	}

	// Did we win? Did we cover every cell?
	if (snake.size() == board.num_elements()) {
		// Yes we won.
		std::cout << "Congratulations you won.\n";
		currGameState = GAME_STATE::WON;
		return currGameState;
	}

	// Did we eat the apple?
	if (snake.head() == apple) {
		// Yes. We need to move apple to a random location 
		// but not on the snake itself. 
		// TODO: This will not be efficient for big boards.
		do {
			apple.moveRandom();
		} while (snake == apple);
	}

	return currGameState;
}
