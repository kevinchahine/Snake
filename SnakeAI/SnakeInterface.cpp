#include "SnakeInterface.h"

SnakeInterface::SnakeInterface(size_t boardWidth, size_t boardHeight) :
	gameState{ boardWidth, boardHeight }
{
}

void SnakeInterface::run()
{
	image = cv::Mat::zeros(gameState.getNRows() * 40, gameState.getNCols() * 40, CV_8UC3);
	gameState.getBoard().print(image);
	cv::imshow("Snake AI", image);
	cv::waitKey(1);

	// --- Wait until user/ai makes a (valid) move to start the game ---
	char input = NULL;
	do {
		input = controllerPtr->getInput();
	} while (!gameState.isMoveLegal(input) || !gameState.isMoveSafe(input));
	
	// --- Continue with game until its state becomes GAME_OVER or WIN ---
	while (gameState.getCurrentState() == SnakeState::GAME_STATE::CONTINUE) {
		cv::rectangle(image, cv::Point(0, 0), cv::Point(image.rows, image.cols), cv::Scalar(0, 0, 0));

		char input = controllerPtr->getInput();
		
		gameState.moveSnake(input);
		
		gameState.getBoard().print(image);
		cv::imshow("Snake AI", image);
		cv::waitKey(1);
	}
}

void SnakeInterface::setController(std::unique_ptr<ControllerBase>&& controllerPtr)
{
	this->controllerPtr = std::move(controllerPtr);
}
