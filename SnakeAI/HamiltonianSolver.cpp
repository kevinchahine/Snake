#include "HamiltonianSolver.h"

using namespace std;
using boost::container::static_vector;

// ------------------------------------ STAND ALONE FUNCTIONS -----------------

vector<static_vector<char, 3>> makeInitialStem(const Snake& snake)
{
	const size_t N_ROWS = snake.getNRows();
	const size_t N_COLS = snake.getNCols();

	vector<static_vector<char, 3>> branches(N_ROWS * N_COLS, static_vector<char, 3>());
	branches.resize(0);

	Position currCell = *snake.cbegin();
	for (Snake::const_iterator snakeIt = snake.begin() + 1; snakeIt != snake.end(); snakeIt++) {
		const Position& nextCell = *snakeIt;

		branches.emplace_back();

		branches.back().emplace_back(currCell.directionTo(nextCell));

		currCell = nextCell;
	}

	return branches;
}

static void backTrack(
	Snake& snake,
	BoardTemplate<bool> board,
	vector<static_vector<char, 3>> branches)
{
	// Do we have any branches to "prune"? We don't want to pop an empty vector.
	if (branches.empty() == false) {
		// Yes we have a branch.

		// Does this branch have any stems?
		if (branches.back().empty() == false) {
			// Yes it does have stems. Lets cut of the last one.
			board(snake.head()) = false;
			snake.undoFast();
			branches.back().pop_back();

			// Now that we cut off the last stem. We need to find a branch 
			while (branches.empty() == false && branches.back().empty()) {
				board(snake.head()) = false;
				snake.undoFast();
				branches.pop_back();
			}
		}
		else {
			// No it is a branch without stems "and therefore must be cut"
			board(snake.head()) = false;
			snake.undoFast();
			branches.pop_back();
		}
	}
}

// ------------------------------------ CLASS FUNCTIONS -----------------------

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
	return 'x';
}

bool HamiltonianSolver::isSolution(const Snake& snake)
{
	const size_t N_ROWS = snake.getNRows();
	const size_t N_COLS = snake.getNCols();

	const Position& head = snake.head();
	const Position& tail = snake.tailTip();

	int colDiff = abs(head.col() - tail.col());
	int rowDiff = abs(head.row() - tail.row());

	bool isGoal =
		(snake.size() == N_ROWS * N_COLS) &&								// Is every cell is filled?
		((colDiff == 1 && rowDiff == 0) || (rowDiff == 1 && colDiff == 0))	// Is tail adjacent to head?
		;

	// Does not test every cell in board. It is possible that the snake "moved over its body"
	// and is long enough to fill each cell in the board, but instead only covered cells more than once and some not
	// at all. This should only happen if Snake was used incorrectly.
	return isGoal;
}

BoardTemplate<char> HamiltonianSolver::search(const Snake& snake)
{
	const size_t N_ROWS = snake.getNRows();
	const size_t N_COLS = snake.getNCols();

	BoardTemplate<bool> board{ N_ROWS, N_COLS, false };

	vector<static_vector<char, 3>> branches = makeInitialStem(snake);

	do {
		// 1.) --- Is Solution Found? ---
		if (isSolution(snake)) {
			return HamiltonianSolver::generateSolution(snake);
		}

		// 2.) --- Is Solution Possible ---
		if (branches.back().size()) {
			branches.pop_back();
		}

	} while (true);

}

BoardTemplate<char> HamiltonianSolver::generateSolution(const Snake& snake)
{
	// Will contain the Hamiltonian Cycle solution where each element equals the next move the snake would make when 
	// passing through the cycle.
	BoardTemplate<char> solution{ snake.getNRows(), snake.getNCols() };

	for (int r = 0; r < solution.getNRows(); r++) {
		for (int c = 0; c < solution.getNCols(); c++) {
			solution(Position(r, c)) = '#';
		}
	}

	// Get position of the snakes head
	Position currCell = *snake.cbegin();

	// Iterate the snake from tail to head
	// Start one after the tail tip
	for (Snake::const_iterator snakeIt = snake.cbegin() + 1; snakeIt != snake.cend(); snakeIt++) {
		// Alias next cell position
		const Position& nextCell = *snakeIt;

		// Figure out the direction to go from current cell to next cell along the snake
		/**/ if (currCell.upOne() == nextCell)		solution(currCell) = 'w';	// next cell is up    one from the curr cell
		else if (currCell.downOne() == nextCell)	solution(currCell) = 's';	// next cell is down  one from the curr cell
		else if (currCell.leftOne() == nextCell)	solution(currCell) = 'a';	// next cell is left  one from the curr cell
		else if (currCell.rightOne() == nextCell)	solution(currCell) = 'd';	// next cell is right one from the curr cell
		else cout << "Error: " << __FUNCTION__ << "() currCell = " << currCell << " nextCell = " << nextCell << '\n';

		// current cell becomes the next cell
		currCell = nextCell;
	}

	// Finaly find the direction from the head to the tail tip. Remember, In a hamiltonian cycle the end of the cycle 
	// should also be the start of it (or in this case right next to it).
	const Position& head = snake.head();
	const Position& tail = snake.tailTip();

	/**/ if (head.upOne() == tail)		solution(currCell) = 'w';	// next cell is up    one from the curr cell
	else if (head.downOne() == tail)	solution(currCell) = 's';	// next cell is down  one from the curr cell
	else if (head.leftOne() == tail)	solution(currCell) = 'a';	// next cell is left  one from the curr cell
	else if (head.rightOne() == tail)	solution(currCell) = 'd';	// next cell is right one from the curr cell
	else cout << "Error: " << __FUNCTION__ << "() head = " << head << " tailTip = " << tail << '\n';

	return solution;
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
