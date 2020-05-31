#include "ReverseAStarSolver.h"

ReverseAStarSolver::ReverseAStarSolver(const SnakeState& gameState) :
	AStarSolverTemplate<std::less<CostlySnakePath>>(gameState) {}
