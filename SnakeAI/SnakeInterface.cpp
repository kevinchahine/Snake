#include "SnakeInterface.h"

SnakeInterface::SnakeInterface(size_t boardWidth, size_t boardHeight) :
	engine{ boardWidth, boardHeight }
{
}

void SnakeInterface::start()
{
	image = cv::Mat::zeros(engine.board.getNRows() * 40, engine.board.getNCols() * 40, CV_8UC3);
	engine.board.print(image);
	cv::imshow("Snake AI", image);
	cv::waitKey(1);

	while (engine.currGameState == SnakeEngine::GAME_STATE::CONTINUE) {
		image = cv::Mat::zeros(engine.board.getNRows() * 40, engine.board.getNCols() * 40, CV_8UC3);
		
		char input = controllerPtr->getInput();

		engine.update(input);

		engine.board.print(image);
		cv::imshow("Snake AI", image);
		cv::waitKey(1);
	}
}

void SnakeInterface::setController(std::unique_ptr<ControllerBase>&& controllerPtr)
{
	this->controllerPtr = std::move(controllerPtr);
}
