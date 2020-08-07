#include "BestFirstSolver.h"

BestFirstSolver::BestFirstSolver(const SnakeGame& m_gameState) :
	SolverBase(m_gameState) {}

void BestFirstSolver::reset()
{
}

char BestFirstSolver::solve()
{
	// 1.) Where is the m_apple?
	const Apple& m_apple = m_gameState.getApple();

	// 2.) Where is the snakes head?
	const Position& head = m_gameState.snake().head();

	// 3.) What "legal" move will get us to the m_apple the fastest?
	char nextMove = NULL;

	// 3-1.) Is the m_apple UP?
	if (m_apple.row() < head.row()) {
		// Yes Move UP
		nextMove = 'w';
	}
	// 3-2.) Is the m_apple DOWN?
	else if (m_apple.row() > head.row()) {
		// Yes Move DOWN
		nextMove = 's';
	}
	// 3-3.) Is the m_apple straight to the LEFT?
	else if (m_apple.col() < head.col()) {
		// Yes Move LEFT
		nextMove = 'a';
	}
	// 3-4.) Is the m_apple straight to the RIGHT?
	else if (m_apple.col() > head.col()) {
		// Yes Move RIGHT
		nextMove = 'd';
	}
	else {
		std::stringstream ss;
		ss << "Direction to apple could not be determined";
		throw std::exception(ss.str().c_str());
	}

	// -- We still need to know if the move is legal and safe --

	// Was the move legal and safe?
	if (m_gameState.isMoveLegal(nextMove) && m_gameState.isMoveSafe(nextMove)) {
		// Yes we can return it.
		return nextMove;
	}
	else {
		return m_gameState.getAnyLegalAndSafeMove();
	}
}
