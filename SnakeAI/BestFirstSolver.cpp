#include "BestFirstSolver.h"

BestFirstSolver::BestFirstSolver(const SnakeState& gameState) :
	SolverBase(gameState) {}

void BestFirstSolver::reset()
{
}

char BestFirstSolver::solve()
{
	// 1.) Where is the apple?
	const Apple& apple = gameState.getApple();

	// 2.) Where is the snakes head?
	const Position& head = gameState.getSnake().head();

	// 3.) What "legal" move will get us to the apple the fastest?
	char nextMove = NULL;

	// 3-1.) Is the apple UP?
	if (apple.row() < head.row()) {
		// Yes Move UP
		nextMove = 'w';
	}
	// 3-2.) Is the apple DOWN?
	else if (apple.row() > head.row()) {
		// Yes Move DOWN
		nextMove = 's';
	}
	// 3-3.) Is the apple straight to the LEFT?
	else if (apple.col() < head.col()) {
		// Yes Move LEFT
		nextMove = 'a';
	}
	// 3-4.) Is the apple straight to the RIGHT?
	else if (apple.col() > head.col()) {
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
	if (gameState.isMoveLegal(nextMove) && gameState.isMoveSafe(nextMove)) {
		// Yes we can return it.
		return nextMove;
	}
	else {
		return gameState.getAnyLegalAndSafeMove();
	}
}
