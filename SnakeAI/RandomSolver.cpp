#include "RandomSolver.h"

RandomSolver::RandomSolver(const SnakeGame& m_gameState) :
	SolverBase(m_gameState) {}

void RandomSolver::reset()
{
}

char RandomSolver::solve()
{
	std::vector<char> validMoves;
	validMoves.reserve(3);

	// Determine which moves are safe.
	if (this->m_gameState.isMoveUpLegal() && this->m_gameState.isMoveUpSafe()) {
		validMoves.push_back('w');
	}

	if (this->m_gameState.isMoveDownLegal() && this->m_gameState.isMoveDownSafe()) {
		validMoves.push_back('s');
	}

	if (this->m_gameState.isMoveLeftLegal() && this->m_gameState.isMoveLeftSafe()) {
		validMoves.push_back('a');
	}

	if (this->m_gameState.isMoveRightLegal() && this->m_gameState.isMoveRightSafe()) {
		validMoves.push_back('d');
	}

	// If there are no legal and safe moves, then we must be in a coil
	if (validMoves.empty() == true) {
		// Return any legal move
		std::cout << ":::legal and safe move was found :::\n";
		return m_gameState.getAnyLegalMove();	
	}

	int ranNum = rand() % validMoves.size();
	char m = validMoves.at(ranNum);

	// Randomly pick one of the valid moves
	return validMoves.at(ranNum);
}
