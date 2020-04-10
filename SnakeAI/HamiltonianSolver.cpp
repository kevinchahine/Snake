#include "HamiltonianSolver.h"

using namespace std;

HamiltonianSolver::HamiltonianSolver(const SnakeState& gameState) :
	SolverBase(gameState),
	hamiltonianCycle(gameState.getBoard().getNRows(), gameState.getBoard().getNCols())
{
	initializeCycle();

	hamiltonianCycle.print(cout);
}

void HamiltonianSolver::reset()
{

}

char HamiltonianSolver::solve()
{
	// 1.) Get the snake heads current position
	Position head = gameState.getSnake().head();

	// 2.) Match it up which the hamiltonian cycle and get the next move
	char nextMove = hamiltonianCycle(head);

	// 3.) Is it a valid move?
	if (gameState.isMoveLegal(nextMove) && gameState.isMoveSafe(nextMove)) {
		// Yes its legal and safe
		return nextMove;
	}
	else {
		// No, so make any legal and safe move instead
		return gameState.getAnyLegalAndSafeMove();
	}
}

void HamiltonianSolver::initializeCycle()
{
	// alias hamiltonianCycle to make its name shorter
	BoardTemplate<char> & c = hamiltonianCycle;	

	// 1.) Start one cell below the upper left corner (1, 0)
	//Position pos(1, 0);

	const size_t NCOLS = c.getNCols();
	const size_t NROWS = c.getNRows();

	// 2.) Zig-zag up and down from right to left
	for (size_t col = 0; col < c.getNCols(); col++) {

		// 2-1.) Move up to down (Move snake DOWN in these cells)
		for (size_t row = 1; row < c.getNRows(); row++) {
			c[row][col] = 's';	// snake moves DOWN
		}

		// 2-2.) At the bottom, move right
		c[NROWS - 1][col] = 'd';

		// 2-3.) Move one to the right
		col++; 

		// 2-4.) Move down to up (Move snake UP in theses cells)
		for (size_t row = NROWS - 1; row > 0; row--) {
			c[row][col] = 'w'; // snake moves UP
		}

		// 2-5.) At one below the top, move right
		c[1][col] = 'd';
	}

	// 3.) Cell (1, NCOLS - 1) should move UP instead of RIGHT 
	c[1][NCOLS - 1] = 'w';

	// 3.) Move back to where we started
	for (size_t col = NCOLS - 1; col > 0; col--) {
		c[0][col] = 'a'; // snake moves left
	}

	// 4.) From (0, 0) snake moves DOWN
	c[0][0] = 's';
}
