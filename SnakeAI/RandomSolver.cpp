#include "RandomSolver.h"

RandomSolver::RandomSolver(const SnakeEngine& engine) :
	SolverBase(engine) {}

char RandomSolver::solve()
{
	std::vector<char> validMoves;
	validMoves.reserve(4);

	// Determine which moves are valid.
	if (engine.snake.isMoveUpValid()) {
		validMoves.push_back('w');
	}

	if (engine.snake.isMoveDownValid()) {
		validMoves.push_back('s');
	}

	if (engine.snake.isMoveLeftValid()) {
		validMoves.push_back('a');
	}

	if (engine.snake.isMoveRightValid()) {
		validMoves.push_back('d');
	}

	// If there are no valid moves, then we are either in a coil or a dead end
	if (validMoves.size() == 0) {
		return 'w';	// Return direction up because we have to return something.
	}

	// Randomly pick one of the valid moves
	return validMoves[rand() % validMoves.size()];
}
