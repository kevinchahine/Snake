#include "DepthFirstSearchSolver.h"

DepthFirstSearchSolver::DepthFirstSearchSolver(const SnakeEngine& engine) :
	SolverBase(engine) {}

char DepthFirstSearchSolver::solve()
{
	if (solution.empty()) {
		depthFirstSearch();
	}
	
	char nextMove = solution.front();
	solution.pop();
	return nextMove;
}

char DepthFirstSearchSolver::depthFirstSearch()
{
	pushValidMovesToOpenList();

	while (openList.empty() == false) {

	}

	return 'd';
}

void DepthFirstSearchSolver::pushValidMovesToOpenList()
{
	// Determine which moves are valid.
	if (engine.snake.isMoveUpValid()) {
		openList.push('w');
	}

	if (engine.snake.isMoveDownValid()) {
		openList.push('s');
	}

	if (engine.snake.isMoveLeftValid()) {
		openList.push('a');
	}

	if (engine.snake.isMoveRightValid()) {
		openList.push('d');
	}
}

