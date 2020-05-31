#include "AIController.h"

using namespace std;

AIController::AIController(SnakeState& gameState, std::unique_ptr<SolverBase>&& solverPtr, int delayMilliSec) :
	gameState(gameState),
	solverPtr(std::move(solverPtr)),
	delayMilliSec(delayMilliSec) {}

char AIController::getInput()
{
	cv::waitKey(delayMilliSec);

	char selectedMove = solverPtr->solve();
		
	return selectedMove;
}
