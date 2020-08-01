#include "Run.h"

void run()
{
	const size_t N_ROWS = 6;
	const size_t N_COLS = 6;

	SnakeInterface gameInterface{ N_ROWS, N_COLS };

	std::unique_ptr<SolverBase> solverPtr =
		//std::make_unique<DefaultSolver>(gameInterface.gameState);
		//std::make_unique<RandomSolver>(gameInterface.gameState);
		//std::make_unique<BestFirstSolver>(gameInterface.gameState);
		//std::make_unique<AStarSolver>(gameInterface.gameState);
		//std::make_unique<ReverseAStarSolver>(gameInterface.gameState);
		//std::make_unique<DepthFirstSearchSolver>(gameInterface.gameState);
		std::make_unique<HamiltonianSolver>(gameInterface.gameState);
		//std::make_unique<HamiltonianBFSSolver>(gameInterface.gameState);

	cout << "--- Using " << typeid(*solverPtr).name() << " ---\n";

	std::unique_ptr<ControllerBase> controllerPtr =
		std::make_unique<AIController>(gameInterface.gameState, std::move(solverPtr), 50);
		//std::make_unique<UserController>();

	cout << "--- " << typeid(*controllerPtr).name() << " ---\n";

	gameInterface.setController(move(controllerPtr));

	while (true) {
		gameInterface.run();
		std::cout << "Play again?";
		std::cin.get();
	}
}
