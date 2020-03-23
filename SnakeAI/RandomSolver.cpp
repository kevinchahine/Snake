#include "RandomSolver.h"

RandomSolver::RandomSolver(const SnakeEngine& engine) :
	SolverBase(engine) {}

char RandomSolver::solve()
{
	std::vector<char> validMoves;
	validMoves.reserve(4);

	// Determine which moves are safe.
	if (this->isMoveUpSafe()) {
		validMoves.push_back('w');
	}

	if (this->isMoveDownSafe()) {
		validMoves.push_back('s');
	}

	if (this->isMoveLeftSafe()) {
		validMoves.push_back('a');
	}

	if (this->isMoveRightSafe()) {
		validMoves.push_back('d');
	}

	// If there are no valid moves, then we are either in a coil or a dead end
	if (validMoves.size() == 0) {
		return 'w';	// Return direction up because we have to return something.
	}

	// Randomly pick one of the valid moves
	return validMoves[rand() % validMoves.size()];
}
