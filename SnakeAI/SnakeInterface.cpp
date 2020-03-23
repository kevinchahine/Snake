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
		clock_t start = clock();
		cv::rectangle(image, cv::Point(0, 0), cv::Point(image.rows, image.cols), cv::Scalar(0, 0, 0));

		std::cout << "1.) " << clock() - start << '\t';

		char input = controllerPtr->getInput();
		std::cout << clock() - start << '\t';

		engine.update(input);
		std::cout << clock() - start << '\t';

		engine.board.print(image);
		cv::imshow("Snake AI", image);
		//cv::waitKey(1);
		std::cout << clock() - start << '\n';
	}
}

void SnakeInterface::setController(std::unique_ptr<ControllerBase>&& controllerPtr)
{
	this->controllerPtr = std::move(controllerPtr);
}
