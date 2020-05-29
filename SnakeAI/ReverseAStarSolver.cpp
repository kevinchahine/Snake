#include "ReverseAStarSolver.h"

ReverseAStarSolver::ReverseAStarSolver(const SnakeState& gameState) :
	AStarSolverTemplate<std::greater<CostlySnakePath>>(gameState) {}
