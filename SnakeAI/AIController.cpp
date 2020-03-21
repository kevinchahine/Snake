#include "AIController.h"

AIController::AIController(SnakeEngine& engine, std::unique_ptr<SolverBase>&& solverPtr) :
	engine(engine),
	solverPtr(std::move(solverPtr)) {}

char AIController::getInput()
{
	cv::waitKey(200);
	
	char selectedMove = solverPtr->solve();
		
	return selectedMove;
}
