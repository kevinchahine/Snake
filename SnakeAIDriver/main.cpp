#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include <SnakeAI/SnakeInterface.h>
#include <SnakeAI/ControllerBase.h>
#include <SnakeAI/UserController.h>
#include <SnakeAI/AIController.h>

#include <SnakeAI/Solvers.hpp>

int main()
{
	// Initialize random number generator
	srand(time(NULL));

	try {
		const size_t N_ROWS = 4;
		const size_t N_COLS = 4;
		
	//	SnakeInterface gameInterface{ N_ROWS, N_COLS };

	//	std::unique_ptr<SolverBase> solverPtr =
	//		//std::make_unique<DefaultSolver>(gameInterface.gameState);
	//		std::make_unique<RandomSolver>(gameInterface.gameState);
	//	//std::make_unique<AStarSolver>(gameInterface.gameState);
	//	//std::make_unique<DepthFirstSearchSolver>(gameInterface.gameState);

	//	gameInterface.setController(std::make_unique<AIController>(gameInterface.gameState, std::move(solverPtr)));
	//	//gameInterface.setController(std::make_unique<UserController>());

	//	gameInterface.start();
	}
	catch (std::exception & e) {
		cout << "Exception caught in " << __FUNCTION__ << ": "
			<< e.what() << '\n';
	}

	cv::waitKey(0);
	//cout << "Press any key to continue . . .";
	//cin.get();
	cin.get();
	return 0;
}
