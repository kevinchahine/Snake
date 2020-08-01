#include "AIController.h"

using namespace std;

AIController::AIController(SnakeState& gameState, std::unique_ptr<SolverBase>&& solverPtr, int delayMilliSec) :
	gameState(gameState),
	solverPtr(std::move(solverPtr)),
	delayMilliSec(delayMilliSec) {}

void AIController::reset()
{
	solverPtr->reset();
}

char AIController::getInput()
{
	cv::waitKey(delayMilliSec);

	char selectedMove = solverPtr->solve();
		
	return selectedMove;
}
