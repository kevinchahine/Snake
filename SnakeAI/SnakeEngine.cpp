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

void SnakeEngine::update()
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
		break;
	}

	cv::imshow("Snake AI", image);
	cv::waitKey(1);
}
