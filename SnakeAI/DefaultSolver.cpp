#include "DefaultSolver.h"

DefaultSolver::DefaultSolver(const SnakeState& gameState) :
	SolverBase(gameState) {}

void DefaultSolver::reset()
{
}

char DefaultSolver::solve()
{
	// Can we direction UP?
	if (gameState.isMoveUpLegal()) {
		return 'w';
	}
	// Can we direction DOWN?
	if (gameState.isMoveDownLegal()) {
		return 's';
	}
	// Can we direction LEFT?
	if (gameState.isMoveLeftLegal()) {
		return 'a';
	}
	// Can we direction RIGHT?
	if (gameState.isMoveRightLegal()) {
		return 'd';
	}
}
