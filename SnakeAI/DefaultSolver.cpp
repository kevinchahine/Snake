#include "DefaultSolver.h"

DefaultSolver::DefaultSolver(const SnakeGame& m_gameState) :
	SolverBase(m_gameState) {}

void DefaultSolver::reset()
{
}

char DefaultSolver::solve()
{
	// Can we direction UP?
	if (m_gameState.isMoveUpLegal()) {
		return 'w';
	}
	// Can we direction DOWN?
	if (m_gameState.isMoveDownLegal()) {
		return 's';
	}
	// Can we direction LEFT?
	if (m_gameState.isMoveLeftLegal()) {
		return 'a';
	}
	// Can we direction RIGHT?
	if (m_gameState.isMoveRightLegal()) {
		return 'd';
	}
	// Then were do we move?
	return 'x';
}
