#include "HamiltonianSolver.h"

using namespace std;
using boost::container::static_vector;

HamiltonianSolver::HamiltonianSolver(const SnakeGame& m_gameState) :
	SolverBase(m_gameState),
	hamiltonianCycle(m_gameState.board().getNRows(), m_gameState.board().getNCols())
{
	initializeCycle();

	hamiltonianCycle.print(cout);
}

void HamiltonianSolver::reset()
{
	// Remove. Creates Hamiltonian Cycle
	cout << "Solving Hamiltonian Cycle\n";
	SnakeGame game = search();
	cout << "Heres the solution:\n";
	game.board().print();
	system("pause");

	vector<char> solutionPath = initializeCycleDynamic();

	Position pos = m_gameState.snake().head();

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
	Position head = m_gameState.snake().head();

	// 2.) Match it up which the hamiltonian cycle and get the next move
	char nextMove = hamiltonianCycle(head);

	// 3.) Is it a valid move?
	if (m_gameState.isMoveLegal(nextMove) && m_gameState.isMoveSafe(nextMove)) {
		// Yes its legal and safe
		return nextMove;
	}
	else {
		cout << "!!! HamiltonianSolver::solve(). Could not use hamiltonian. Making another move instead\n";
		// No, so make any legal and safe move instead
		return m_gameState.getAnyLegalAndSafeMove();
	}
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

SnakeGame HamiltonianSolver::search() const
{
	using gamePtr = unique_ptr<SnakeGame>;

	SnakeGame game = m_gameState;

	queue<gamePtr> frontier;

	frontier.push(make_unique<SnakeGame>(game));

	do {
		if (frontier.empty()) {
			cout << "No solution\n";
			system("pause");
			return m_gameState; // No Solution 
		}

		gamePtr node = move(frontier.back());
		frontier.pop();

		node->board().show();
		cv::waitKey(0);

		if (isSolution(*node)) {
			cout << "Yay. Solution was found\n";
			return *node;
		}

		cout << "Starting with \n";
		node->board().print();
		//node->board().show("Starting with");
		static_vector<char, 3> branches = node->getAllLegalAndSafeMoves();

		cout << "--- Branch out: ---\n";
		for (char leaf : branches) {
			//cout << "\tWe can go " << leaf << "\n";

			gamePtr nextNode = make_unique<SnakeGame>(*node);
			cout << "nextNode = " << nextNode << '\t';

			// Do forward checking

			if (nextNode->isMoveLegal(leaf)) {
				if (nextNode->isMoveSafe(leaf)) {
					nextNode->growFast(leaf);

				}
				else {
					cout << "From:\n";
					nextNode->board().print();
					cout << "Growing " << leaf << " is not safe\n";
					system("pause");
				}
			}
			else {
				cout << "From:\n";
				nextNode->board().print();
				cout << "Growing " << leaf << " is not legal\n";
				system("pause");
			}

			//nextNode->board().print();
			//nextNode->board().show("NextNode");
			//cv::waitKey(0);

			frontier.push(move(nextNode));
			cout << "Frontier.back() = " << frontier.back() << '\n';
		}

	} while (true);
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
	SnakeGame game = m_gameState;

	// Used for branching, backtracking and final solution
	vector<static_vector<char, 3>> validMoves;
	validMoves.reserve(game.getNCells());

	// 1.) --- Initialize validMoves with the current snake state ---
	initializeValidMoves(validMoves, game.snake());

	validMoves.emplace_back(game.getAllLegalAndSafeMoves());
	cout << "Starting with: ";
	for (const auto& c : validMoves.back()) {
		cout << c << ' ';
	}
	cout << '\n';

	// 2.) --- Branch valid moves until a solution is found or branches run out ---
	while (true) {
		// remove vvvvv
		static int i = 0;
		if (i++ % 1 == 0) {
			cv::Mat image = cv::Mat::zeros(game.getNRows() * 40, game.getNCols() * 40, CV_8UC3);
			game.board().print(image);
			cv::imshow("Hamiltonian Solver", image);
			for (const auto& branch : validMoves) {
				if (branch.empty() == false)
				{
					cout << branch.back() << ' ';
				}
				else {
					cout << "--- ";
				}
			}
			cout << '\n';
			cv::waitKey(750);
		}
		// remove ^^^^^^^^^

		//cout << validMoves.size() << '\n';

		// 2-1.) --- If validMoves is < then the snake we started with then there is no solution ---
		if (validMoves.size() < m_gameState.snake().size()) {
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

			for (const auto& a : validMoves) {
				cout << a.back() << ' ';
			}
			cout << '\n';

			//solutionPath.resize(validMoves.size());
			//transform(
			//	validMoves.begin(),
			//	validMoves.end(),
			//	solutionPath.begin(),
			//	[](const static_vector<char, 3>& moveVec) { cout << moveVec.back() << ' '; return moveVec.back(); });
			system("pause");

			return solutionPath;
		}

		// 3-4.) --- Iterate leaves ---
		static_vector<char, 3>& leaves = validMoves.back();
		// Are there any leaves to iterate 
		if (leaves.empty()) { // Maybe this if should be first (2-0.) and contain a pop_back loop
			// No more leaves. Back track
			cout << "--- Back Tracking ---\n";
			validMoves.pop_back();

			if (validMoves.empty() == false) {
				if (validMoves.back().empty() == false) {
					validMoves.back().pop_back();
				}
			}

			game.undoMoveIfLegal(false);
		}
		else {
			cout << "--- Branching ---\n";
			// Yes we have a few leaves. Search the last leaf.
			char nextMove = leaves.back();

			// Apply next move
			cout << "Moving " << nextMove << "\n";
			if (game.isMoveSafe(nextMove)) {
				game.growFast(nextMove);
			}
			else {
				cout << "Error can't move in that direction " << nextMove << '\n';
				system("pause");
			}

			// Branch out more moves
			validMoves.emplace_back(game.getAllLegalAndSafeMoves());

			cout << "Added " << validMoves.back().size() << " new branches: ";
			for (const auto& c : validMoves.back()) {
				cout << c << ' ';
			}
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
