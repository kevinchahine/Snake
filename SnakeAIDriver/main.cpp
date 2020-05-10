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
		const size_t N_ROWS = 10;
		const size_t N_COLS = 10;
	
		SnakeInterface gameInterface{ N_ROWS, N_COLS };
	
		std::unique_ptr<SolverBase> solverPtr =
			//std::make_unique<DefaultSolver>(gameInterface.gameState);
			//std::make_unique<RandomSolver>(gameInterface.gameState);
			//std::make_unique<BestFirstSolver>(gameInterface.gameState);
			std::make_unique<AStarSolver>(gameInterface.gameState);
			//std::make_unique<DepthFirstSearchSolver>(gameInterface.gameState);
			//std::make_unique<HamiltonianSolver>(gameInterface.gameState);
			//std::make_unique<HamiltonianBFSSolver>(gameInterface.gameState);
		
		std::unique_ptr<ControllerBase> controllerPtr =
			std::make_unique<AIController>(gameInterface.gameState, std::move(solverPtr));
			//std::make_unique<UserController>();
	
		gameInterface.setController(move(controllerPtr));
	
		while (true) {
			gameInterface.run();
			std::cout << "Play again?";
			std::cin.get();
		}
	}
	catch (std::exception & e) {
		cout << "Exception caught in " << __FUNCTION__ << ": "
			<< e.what() << '\n';
	}
	
	cout << "Press any key to continue . . .";
	cv::waitKey(0);	// keeps display window open
	cin.get();
	return 0;
}
