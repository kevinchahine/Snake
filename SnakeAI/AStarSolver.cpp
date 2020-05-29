#include "AStarSolver.h"

using namespace std;

AStarSolver::AStarSolver(const SnakeState& gameState) :
	AStarSolverTemplate<std::less<CostlySnakePath>>(gameState) {}
