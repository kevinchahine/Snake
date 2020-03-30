#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "SnakeInterface.h"
#include "ControllerBase.h"
#include "UserController.h"
#include "AIController.h"

#include "Solvers.hpp"

int main()
{
	// Initialize random number generator
	srand(time(NULL));

	try {
		const size_t N_ROWS = 4;
		const size_t N_COLS = 4;
		SnakeInterface gameInterface{ N_ROWS, N_COLS };
		
		std::unique_ptr<SolverBase> solverPtr =
			//std::make_unique<DefaultSolver>(gameInterface.gameState);
			std::make_unique<RandomSolver>(gameInterface.gameState);
			//std::make_unique<AStarSolver>(gameInterface.gameState);
			//std::make_unique<DepthFirstSearchSolver>(gameInterface.gameState);

		gameInterface.setController(std::make_unique<AIController>(gameInterface.gameState, std::move(solverPtr)));
		//gameInterface.setController(std::make_unique<UserController>());

		gameInterface.run();
	}
	catch (std::exception & e) {
		cout << "Exception caught in " << __FUNCTION__ << ": "
			<< e.what() << '\n';
	}

	cv::waitKey(000);
	//cout << "Press any key to continue . . .";
	//cin.get();
	//cin.get();
	return 0;
}
