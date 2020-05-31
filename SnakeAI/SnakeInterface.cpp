#include "SnakeInterface.h"

using namespace std;

SnakeInterface::SnakeInterface(size_t boardWidth, size_t boardHeight) :
	gameState{ boardWidth, boardHeight }
{
}

void SnakeInterface::run()
{
	// 1.) --- Start from a clean game ---
	gameState.reset();

	// 2.) --- Print opening board ---
	image = cv::Mat::zeros(gameState.getNRows() * 40, gameState.getNCols() * 40, CV_8UC3);
	gameState.getBoard().print(image);
	cv::imshow("Snake AI", image);
	cv::waitKey(1);

	// 3.) --- Wait until user/ai makes a (valid) move to start the game ---
	//		-- User/AI should always be able to make a valid move at the --
	//		-- start of the game
	char input = NULL;
	do {
		input = controllerPtr->getInput();
	} while (!gameState.isMoveLegal(input) || !gameState.isMoveSafe(input));

	// 4.) --- Continue with game until its state becomes GAME_OVER or WIN ---
	while (gameState.getCurrentState() == SnakeState::GAME_STATE::CONTINUE) {
		// 4-1.) --- Create a base image ---
		cv::rectangle(image, cv::Point(0, 0), cv::Point(image.rows, image.cols), cv::Scalar(0, 0, 0));

		// 4-2.) --- Get user/ai move input ---
		char input = controllerPtr->getInput();

		// 4-3.) --- Apply move ---
		auto currGameState = gameState.moveSnake(input);

		// 4-4.) --- Check game state ---
		switch (gameState.getCurrentState())
		{
		case SnakeState::GAME_STATE::CONTINUE:
			break;
		case SnakeState::GAME_STATE::GAME_OVER:
			std::cout << "GAME OVER\n";
			return;
			break;
		case SnakeState::GAME_STATE::WON:
			std::cout << "YOU WON!!!\n";
			return;
			break;
		default:
			std::cout << "Error: " << __FUNCTION__ << " line " << __LINE__
				<< " new game state encountered: " 
				<< static_cast<int>(gameState.getCurrentState()) << '\n';
			break;
		}

		// 4-4.) --- Check if we ate the apple ---
		if (gameState.appleIsEaten()) {
			gameState.moveAppleRandomly();
		}

		// 4-4.) --- Print next frame ---
		gameState.getBoard().print(image);
		cv::imshow("Snake AI", image);
		cv::waitKey(1);
	}
}

void SnakeInterface::setController(std::unique_ptr<ControllerBase>&& controllerPtr)
{
	this->controllerPtr = std::move(controllerPtr);
}
