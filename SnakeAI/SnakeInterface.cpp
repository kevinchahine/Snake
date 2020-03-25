#include "SnakeInterface.h"

SnakeInterface::SnakeInterface(size_t boardWidth, size_t boardHeight) :
	gameState{ boardWidth, boardHeight }
{
}

void SnakeInterface::start()
{
	image = cv::Mat::zeros(gameState.getNRows() * 40, gameState.getNCols() * 40, CV_8UC3);
	gameState.getSnakeBoard().print(image);
	cv::imshow("Snake AI", image);
	cv::waitKey(1);

	while (gameState.getGameState() == SnakeState::GAME_STATE::CONTINUE) {
		cv::rectangle(image, cv::Point(0, 0), cv::Point(image.rows, image.cols), cv::Scalar(0, 0, 0));

		char input = controllerPtr->getInput();
		
		gameState.update(input);
		
		gameState.getSnakeBoard().print(image);
		cv::imshow("Snake AI", image);
		cv::waitKey(1);
	}
}

void SnakeInterface::setController(std::unique_ptr<ControllerBase>&& controllerPtr)
{
	this->controllerPtr = std::move(controllerPtr);
}
