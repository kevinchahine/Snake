#include "DepthFirstSearchSolver.h"

DepthFirstSearchSolver::DepthFirstSearchSolver(const SnakeEngine& engine) :
	SolverBase(engine)
{}

char DepthFirstSearchSolver::solve()
{
	// Do we have any more moves in the solution?
	if (solution.size() == 0) {
		// No, we need to solve for the next move.
		std::cout << "Solution is empty\n";

		frontier.clear();
		explored.clear();

		solution.push(depthFirstSearch());
	}

	char nextMove = solution.top();
	solution.pop();

	return nextMove;
}

char DepthFirstSearchSolver::depthFirstSearch()
{
	pushValidMovesToFrontier(engine);

	// Are there more nodes in the frontier to search through?
	if (frontier.empty()) {
		// No. We must have reached a deadend
		return NULL;
	}

	// Grab the next node from the frontier.
	const Node& currentNode = frontier.back();
	frontier.pop_back();

	// Is node a goal state?
	if (currentNode.isGoal()) {
		// Yes. We have found a solution.
		// Return the move that got us here
		std::cout << "Solution found: Next move = " << currentNode.getMove() << '\n';
		return currentNode.getMove();
	}

	// At this point we have not found the goal yet.

	// currentNode has been search. Put it in explored
	// so that we do not search it again.
	explored.push_back(currentNode);

	// Expand the next possible moves
	pushValidMovesToFrontier(currentNode.getGameState());

	// Evaluate next move recursively.
	char nextMove = depthFirstSearch();
	solution.push(nextMove);
	return nextMove;
}

void DepthFirstSearchSolver::pushValidMovesToFrontier(const SnakeEngine& gameState)
{
	// Determine which moves are valid.
	if (gameState.snake.isMoveUpValid()) {
		Node nextGameState = Node('w', gameState);

		nextGameState.getGameState().snake.moveUpFast();
		
		if (std::find(frontier.begin(), frontier.end(), nextGameState) == frontier.end() &&
			std::find(explored.begin(), explored.end(), nextGameState) == explored.end()) {
			frontier.push_back(nextGameState);
		}
	}

	if (gameState.snake.isMoveDownValid()) {
		Node nextGameState = Node('s', gameState);

		nextGameState.getGameState().snake.moveDownFast();

		if (std::find(frontier.begin(), frontier.end(), nextGameState) == frontier.end() &&
			std::find(explored.begin(), explored.end(), nextGameState) == explored.end()) {
			frontier.push_back(nextGameState);
		}
	}

	if (gameState.snake.isMoveLeftValid()) {
		Node nextGameState = Node('a', gameState);

		nextGameState.getGameState().snake.moveLeftFast();

		if (std::find(frontier.begin(), frontier.end(), nextGameState) == frontier.end() &&
			std::find(explored.begin(), explored.end(), nextGameState) == explored.end()) {
			frontier.push_back(nextGameState);
		}
	}

	if (gameState.snake.isMoveRightValid()) {
		Node nextGameState = Node('d', gameState);

		nextGameState.getGameState().snake.moveRightFast();

		if (std::find(frontier.begin(), frontier.end(), nextGameState) == frontier.end() &&
			std::find(explored.begin(), explored.end(), nextGameState) == explored.end()) {
			frontier.push_back(nextGameState);
		}
	}
}

Node::Node(char move, const SnakeEngine& gameState) :
	std::pair<char, SnakeEngine>(move, gameState) {}

bool Node::isGoal() const
{
	const SnakeEngine& engine = getGameState();
	const Snake& snake = engine.snake;
	const Apple& apple = engine.apple;

	const Position& headPos = static_cast<const Position&>(snake.head());
	const Position& applePos = static_cast<const Position&>(apple);

	return snake.head() == static_cast<const Position&>(apple);
}

char Node::getMove() const
{
	return this->first;
}

const SnakeEngine& Node::getGameState() const
{
	return this->second;
}

SnakeEngine& Node::getGameState()
{
	return this->second;
}

bool Node::operator==(const Node& left) const
{
	return this->getGameState() == left.getGameState();
}
