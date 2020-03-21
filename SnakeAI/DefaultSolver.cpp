#include "DefaultSolver.h"

DefaultSolver::DefaultSolver(const SnakeEngine& engine) :
	SolverBase(engine) {}

char DefaultSolver::solve()
{
	// Can we direction UP?
	if (engine.snake.isMoveUpValid()) {
		return 'w';
	}
	// Can we direction DOWN?
	if (engine.snake.isMoveDownValid()) {
		return 's';
	}
	// Can we direction LEFT?
	if (engine.snake.isMoveLeftValid()) {
		return 'a';
	}
	// Can we direction RIGHT?
	if (engine.snake.isMoveRightValid()) {
		return 'd';
	}
}
