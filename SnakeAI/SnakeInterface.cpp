#include "SnakeInterface.h"

using namespace std;

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

SnakeInterface::SnakeInterface(size_t boardWidth, size_t boardHeight) :
	m_gameState{ boardWidth, boardHeight }
{
}

void SnakeInterface::run()
{
	// 1.) --- Start from a clean game ---
	m_gameState.reset();
	controllerPtr->reset();

	// 2.) --- Print opening board ---
	image = cv::Mat::zeros(m_gameState.getNRows() * 40, m_gameState.getNCols() * 40, CV_8UC3);
	m_gameState.board().print(image);
	cv::imshow("Snake AI", image);
	cv::waitKey(1000);

	// 3.) --- Wait until user/ai makes a (valid) move to start the game ---
	//		-- User/AI should always be able to make a valid move at the --
	//		-- start of the game
	char input = NULL;
	do {
		input = controllerPtr->getInput();
	} while (!m_gameState.isMoveLegal(input) || !m_gameState.isMoveSafe(input));

	// 4.) --- Continue with game until its state becomes GAME_OVER or WIN ---
	bool isGameEnded = false;
	bool isWarningPrinted = false;
	while (isGameEnded == false) {
		// 4-1.) --- Create a base image ---
		cv::rectangle(image, cv::Point(0, 0), cv::Point(image.rows, image.cols), cv::Scalar(0, 0, 0));

		// 4-2.) --- Get user/ai move input ---
		char input = controllerPtr->getInput();

		// 4-3.) --- Apply move ---
		if (m_gameState.isMoveLegal(input)) {
			m_gameState.moveFast(input);
			isWarningPrinted = false;
		}
		else if (isWarningPrinted == false) {
			cout << "Move " << input << " is Illegal\n";
			isWarningPrinted = true;
		}

		// 4-4.) --- Check game state ---
		auto state = m_gameState.calcGameState();
		switch (state)
		{
		case SnakeGame::GAME_STATE::CONTINUE:														break;
		case SnakeGame::GAME_STATE::GAME_OVER:	std::cout << "GAME OVER\n";		isGameEnded = true;	break;
		case SnakeGame::GAME_STATE::WON:		std::cout << "YOU WON!!!\n";	isGameEnded = true;	break;
		case SnakeGame::GAME_STATE::ERROR:		std::cout << "ERROR STATE\n";	isGameEnded = true;	break;
		default:
			std::cout << "Error: " << __FUNCTION__ << " line " << __LINE__
				<< " new game state encountered: "
				<< static_cast<int>(state) << '\n';
			break;
		}

		// 4-4.) --- Show next frame ---
		m_gameState.board().print(image);
		cv::imshow("Snake AI", image);
		cv::waitKey(1);
	}
}

void SnakeInterface::setController(std::unique_ptr<ControllerBase>&& controllerPtr)
{
	this->controllerPtr = std::move(controllerPtr);
}
