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

	// If there are no legal and safe moves, then we must be in a coil
	if (validMoves.empty() == true) {
		// Return any legal move
		std::cout << ":::legal and safe move was found :::\n";
		return gameState.getAnyLegalMove();	
	}

	int ranNum = rand() % validMoves.size();
	char m = validMoves.at(ranNum);

	// Randomly pick one of the valid moves
	return validMoves.at(ranNum);
}
