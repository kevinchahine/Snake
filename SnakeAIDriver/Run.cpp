#include "Run.h"

void run()
{
	const size_t N_ROWS = 4;
	const size_t N_COLS = 4;

	SnakeInterface gameInterface{ N_ROWS, N_COLS };

	std::unique_ptr<SolverBase> solverPtr =
		//std::make_unique<DefaultSolver>(gameInterface.m_gameState);
		//std::make_unique<RandomSolver>(gameInterface.m_gameState);
		//std::make_unique<BestFirstSolver>(gameInterface.m_gameState);
		//std::make_unique<AStarSolver>(gameInterface.m_gameState);
		//std::make_unique<ReverseAStarSolver>(gameInterface.m_gameState);
		//std::make_unique<DepthFirstSearchSolver>(gameInterface.m_gameState);
		std::make_unique<HamiltonianSolver>(gameInterface.m_gameState);
		//std::make_unique<HamiltonianBFSSolver>(gameInterface.m_gameState);

	cout << "--- Using " << typeid(*solverPtr).name() << " ---\n";

	std::unique_ptr<ControllerBase> controllerPtr =
		std::make_unique<AIController>(gameInterface.m_gameState, std::move(solverPtr), 50);
		//std::make_unique<UserController>();

	cout << "--- " << typeid(*controllerPtr).name() << " ---\n";

	gameInterface.setController(move(controllerPtr));

	while (true) {
		gameInterface.run();
		std::cout << "Play again?";
		//std::cin.get();
		cv::waitKey(1000);
	}
}
