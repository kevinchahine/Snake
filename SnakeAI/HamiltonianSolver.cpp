#include "HamiltonianSolver.h"

using namespace std;
using boost::container::static_vector;

HamiltonianSolver::HamiltonianSolver(const SnakeGame& m_gameState) :
	SolverBase(m_gameState),
	hamiltonianCycle(m_gameState.board().getNRows(), m_gameState.board().getNCols())
{
}

void HamiltonianSolver::reset()
{
	
}

char HamiltonianSolver::solve()
{
	return 'z';
}

bool HamiltonianSolver::isSolution(const SnakeGame& game)
{
	const Snake& snake = game.snake();

	const Position& head = snake.head();
	const Position& tail = snake.tailTip();

	int colDiff = abs(head.col() - tail.col());
	int rowDiff = abs(head.row() - tail.row());

	bool isGoal =
		(snake.size() == game.getNCells()) &&								// Is every cell is filled?
		((colDiff == 1 && rowDiff == 0) || (rowDiff == 1 && colDiff == 0))	// Is tail adjacent to head?
		;

	return isGoal;
}

void HamiltonianSolver::initializeCycle()
{
	// alias hamiltonianCycle to make its name shorter
	BoardTemplate<char>& c = hamiltonianCycle;

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
