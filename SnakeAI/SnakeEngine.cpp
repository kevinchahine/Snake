#include "SnakeEngine.h"

SnakeEngine::SnakeEngine(size_t boardHeight, size_t boardWidth) :
	board{ boardHeight, boardWidth },
	snake{ boardHeight, boardWidth },
	apple{ boardHeight, boardWidth }
{}

void SnakeEngine::init()
{
	reset();
}

void SnakeEngine::reset()
{
	board.clear();
	snake.resetHeadRandom();
	apple.moveRandom();
}

SnakeEngine::GAME_STATE SnakeEngine::update()
{
	image = cv::Mat::zeros(board.getNRows() * 40, board.getNCols() * 40, CV_8UC3);

	board.clear();
	board.paste(snake);
	board.paste(apple);
	board.print(image);
	
	cv::imshow("Snake AI", image);
	cv::waitKey(1);

	std::cout << "Enter move: ";
	char input;
	std::cin >> input;
	input = tolower(input);

	switch (input) {
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
			return GAME_STATE::GAME_OVER;
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
			return GAME_STATE::GAME_OVER;
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
			return GAME_STATE::GAME_OVER;
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
			return GAME_STATE::GAME_OVER;
		}
		break;
	}

	// Did we bit our selves?
	if (snake.bitItself()) {
		std::cout << "Ouch. Game over\n";
		return GAME_STATE::GAME_OVER;
	}

	// Did we win? Did we cover every cell?
	if (snake.size() == board.num_elements()) {
		// Yes we won.
		std::cout << "Congratulations you won.\n";
		return GAME_STATE::WON;
	}

	// Did we eat the apple?
	if (snake.head() == apple) {
		// Yes. We need to move it to a random location not on the snake itself.
		do
		{
			apple.moveRandom();
		} while (snake == apple);
	}

	cv::imshow("Snake AI", image);
	cv::waitKey(1);

	return GAME_STATE::CONTINUE;
}
