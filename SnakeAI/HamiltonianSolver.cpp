#include "HamiltonianSolver.h"

using namespace std;
using boost::container::static_vector;

HamiltonianSolver::HamiltonianSolver(const SnakeState& gameState) :
	SolverBase(gameState),
	hamiltonianCycle(gameState.getBoard().getNRows(), gameState.getBoard().getNCols())
{
	initializeCycle();

	hamiltonianCycle.print(cout);
}

void HamiltonianSolver::reset()
{
	vector<char> solutionPath = initializeCycleDynamic();

	Position pos = gameState.getSnake().head();
	
	cout << "Did our job. Here's the solution:\n";
	for (auto c : solutionPath) {
		cout << c << '\t';

		hamiltonianCycle(pos) = c;

		pos = pos.oneToThe(c);
	}

	system("pause");
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

bool HamiltonianSolver::isSolution(const SnakeState& game)
{
	const Snake & snake = game.getSnake();

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

vector<char> HamiltonianSolver::initializeCycleDynamic()
{
	// Used for getting valid moves, and forward checking
	SnakeState game = gameState;

	// vvvvv remove this vvvvvvv
	game.growFast(game.getAnyLegalAndSafeMove());
	game.growFast(game.getAnyLegalAndSafeMove());
	game.growFast(game.getAnyLegalAndSafeMove());
	game.growFast(game.getAnyLegalAndSafeMove());
	game.growFast(game.getAnyLegalAndSafeMove());
	game.growFast(game.getAnyLegalAndSafeMove());
	// ^^^^^ remove htis ^^^^^^^

	// Used for branching, backtracking and final solution
	vector<static_vector<char, 3>> validMoves;
	validMoves.reserve(game.getNCells());

	// 1.) --- Initialize validMoves with the current snake state ---
	initializeValidMoves(validMoves, game.getSnake());

	// 2.) --- Branch valid moves until a solution is found or branches run out ---
	while (true) {
		// remove vvvvv
		static int i = 0;
		if (i++ % 1 == 0) {
			cv::Mat image = cv::Mat::zeros(gameState.getNRows() * 40, gameState.getNCols() * 40, CV_8UC3);
			game.getBoard().print(image);
			cv::imshow("Hamiltonian Solver", image);
			cv::waitKey(0);
		}
		// remove ^^^^^^^^^

		//cout << validMoves.size() << '\n';

		// 2-1.) --- If validMoves is empty then there is no solution ---
		if (validMoves.empty()) {
			cout << "Hamiltonian Solver NO SOLUTION\n";
			return vector<char>();	// No solution was found
		}

		// 2-2.) --- Forward Checking ---
		if (/*fail forward checking*/ false) {
			// back track
		}

		// 2-3.) --- Check for solution ---
		if (isSolution(game)) {
			cout << "--- Hamiltonian Solver : Solution found ---\n";

			// finalize solution
			vector<char> solutionPath;

			solutionPath.resize(validMoves.size());
			transform(
				validMoves.begin(),
				validMoves.end(),
				solutionPath.begin(),
				[](const static_vector<char, 3>& moveVec) { return moveVec.front(); });

			return solutionPath;
		}

		// 3-4.) --- Iterate leaves ---
		static_vector<char, 3>& leaves = validMoves.back();
		// Are there any leaves to iterate 
		if (leaves.empty()) { // Maybe this if should be first (2-0.) and contain a pop_back loop
			// No more leaves. Back track
			validMoves.pop_back();
			
			if (validMoves.empty() == false) {
				if (validMoves.back().empty() == false) { 
					validMoves.back().pop_back(); 
				}
			}

			game.undoMoveSafe();
		}
		else {
			// Yes we have a few leaves. Search the last leaf.
			char nextMove = leaves.back();

			cout << "Moving " << nextMove << "\n";
			if (game.isMoveSafe(nextMove)) {
				game.growFast(nextMove);
			}
			else {
				cout << "Error can't move in that direction " << nextMove << '\n';
			}

			// Apply next move
			validMoves.emplace_back(game.getAllLegalAndSafeMoves());
		}
	} // end while (branch)
}

void HamiltonianSolver::initializeValidMoves(vector<static_vector<char, 3>>& validMoves, const Snake& snake) const
{
	validMoves.clear();

	if (snake.size() < 2) {
		// Bad. Snake is either 0 or 1 cells long, we can't do anything
		return;
	}

	// At this point snake length is guarenteed to be atleast 2

	Position prevPos = snake.tailTip();

	// Iterate along the snake from tail to head
	// Begin is the tail tip
	// End the the head
	for (auto snakeIt = snake.begin() + 1; snakeIt != snake.end(); snakeIt++) {
		validMoves.emplace_back();

		// Alias the current position on the snakes body
		const Position& currPos = *snakeIt;

		char move = 'x';

		// Figure out how to get from prevPos to currPos
		if (prevPos.upOne() == currPos) { move = 'w'; }
		else if (prevPos.downOne() == currPos) { move = 's'; }
		else if (prevPos.leftOne() == currPos) { move = 'a'; }
		else if (prevPos.rightOne() == currPos) { move = 'd'; }
		else {
			cout << "Error: " << __FILE__ << " line " << __LINE__
				<< " prevPos == " << prevPos << " currPos = " << currPos << '\n';
		}

		// Append the move that would take us from prevPos to currPos
		validMoves.back().push_back(move);

		prevPos = currPos;
	}

	// remove this
	for (const static_vector<char, 3> & moves : validMoves) {
		cout << "<";
		for (char m : moves) {
			cout << m << ' ';
		}
		cout << ">\t";
	}
	cout << "\n";
}
