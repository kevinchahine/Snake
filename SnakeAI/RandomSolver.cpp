#include "RandomSolver.h"

RandomSolver::RandomSolver(const SnakeState& gameState) :
	SolverBase(gameState) {}

void RandomSolver::reset()
{
}

char RandomSolver::solve()
{
	std::vector<char> validMoves;
	validMoves.reserve(3);

	// Determine which moves are safe.
	if (this->gameState.isMoveUpLegal() && this->gameState.isMoveUpSafe()) {
		validMoves.push_back('w');
	}

	if (this->gameState.isMoveDownLegal() && this->gameState.isMoveDownSafe()) {
		validMoves.push_back('s');
	}

	if (this->gameState.isMoveLeftLegal() && this->gameState.isMoveLeftSafe()) {
		validMoves.push_back('a');
	}

	if (this->gameState.isMoveRightLegal() && this->gameState.isMoveRightSafe()) {
		validMoves.push_back('d');
	}

	// If there are no valid moves, then we are either in a coil or a dead end
	if (validMoves.size() == 0) {
		std::cout << __FUNCTION__ << ": No valid moves\n";
		return 'w';	// Return direction up because we have to return something.
	}

	int ranNum = rand() % validMoves.size();
	char m = validMoves.at(ranNum);

	// Randomly pick one of the valid moves
	return validMoves.at(ranNum);
}
