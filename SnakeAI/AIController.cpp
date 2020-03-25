#include "AIController.h"

AIController::AIController(SnakeState& gameState, std::unique_ptr<SolverBase>&& solverPtr) :
	gameState(gameState),
	solverPtr(std::move(solverPtr)) {}

char AIController::getInput()
{
	cv::waitKey(50);
	
	char selectedMove = solverPtr->solve();
		
	return selectedMove;
}
