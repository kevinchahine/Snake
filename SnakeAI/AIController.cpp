#include "AIController.h"

AIController::AIController(SnakeEngine& engine) :
	engine(engine) {}

char AIController::getInput()
{
	cv::waitKey(400);
	
	// Can we move UP?
	if (engine.snake.isMoveUpValid()) {
		return 'w';
	}
	// Can we move DOWN?
	if (engine.snake.isMoveDownValid()) {
		return 's';
	}
	// Can we move LEFT?
	if (engine.snake.isMoveLeftValid()) {
		return 'a';
	}
	// Can we move RIGHT?
	if (engine.snake.isMoveRightValid()) {
		return 'd';
	}
		
	return 'x';
}
