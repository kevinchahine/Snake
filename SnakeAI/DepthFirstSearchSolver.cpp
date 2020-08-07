#include "DepthFirstSearchSolver.h"

DepthFirstSearchSolver::DepthFirstSearchSolver(const SnakeGame& m_gameState) :
	SolverBase(m_gameState)
{}

void DepthFirstSearchSolver::reset()
{
	frontier.clear();
	explored.clear();
	while (solution.empty() == false) solution.pop();

	// Push current state to the frontier
	frontier.push_back(Node{ NULL, m_gameState });
}

char DepthFirstSearchSolver::solve()
{
	// Start solve operation over from scratch
	reset();
	
	// Pop the next move and return it
	char nextMove = depthFirstSearch(m_gameState);

	//std::cout << "Next move = '" << nextMove << "'\n";

	// Is nextMove valid and safe?
	if (nextMove != NULL) {
		// Yes it is valid and safe
		return nextMove;
	}
	else {
		// No, this move will kill us. But we have no other choises to just 
		// return any valid move.
		return m_gameState.getAnyLegalMove();
	}
}

char DepthFirstSearchSolver::depthFirstSearch(const SnakeGame& currGameState)
{
	// If the frontier is empty it means we have run out of moves to try.
	// There are no valid move that we can make except those that will
	// cause us to loose.
	if (frontier.empty()) {
		return NULL;	// There are no good moves to make
	}

	// Analyze the next possible move on the frontier
	Node nextNode = frontier.back();
	frontier.pop_back();

	// Is this a goal state?
	if (nextNode.isGoal()) {
		// Yes, it is a goal state. Return the move that got us there
		return nextNode.getMove();
	}

	// Now that we know that nextNode was not a goal state, we can push it to explored
	// so that we don't re-analyze it.
	explored.push_back(nextNode);

	// We are not on a goal or terminating state. Find the next possible moves 
	// that we can make.
	pushSafeMovesToFrontier(nextNode.getGameState());

	// From the current non goal non terminating state, analyze the next possible
	// move.
	char nextMove = depthFirstSearch(explored.back().getGameState());

	// Is the nextMove valid?
	if (nextMove != NULL) {
		// Its a promissing move.
		solution.push(nextMove);
	}
	else {
		// It is not a valid move, maybe it will kill us or lead to a dead end.
		return NULL;
	}
}

void DepthFirstSearchSolver::pushSafeMovesToFrontier(const SnakeGame& m_gameState)
{
	// Determine which moves are safe.
	// Which moves will not immediately kill us?
	if (m_gameState.isMoveUpSafe()) {
		Node nextGameState = Node('w', m_gameState);

		nextGameState.getGameState().moveUpFast();
		
		if (std::find(frontier.begin(), frontier.end(), nextGameState) == frontier.end() &&
			std::find(explored.begin(), explored.end(), nextGameState) == explored.end()) {
			frontier.push_back(nextGameState);
		}
	}

	if (m_gameState.isMoveDownSafe()) {
		Node nextGameState = Node('s', m_gameState);

		nextGameState.getGameState().moveDownFast();

		if (std::find(frontier.begin(), frontier.end(), nextGameState) == frontier.end() &&
			std::find(explored.begin(), explored.end(), nextGameState) == explored.end()) {
			frontier.push_back(nextGameState);
		}
	}

	if (m_gameState.isMoveLeftSafe()) {
		Node nextGameState = Node('a', m_gameState);

		nextGameState.getGameState().moveLeftFast();

		if (std::find(frontier.begin(), frontier.end(), nextGameState) == frontier.end() &&
			std::find(explored.begin(), explored.end(), nextGameState) == explored.end()) {
			frontier.push_back(nextGameState);
		}
	}

	if (m_gameState.isMoveRightSafe()) {
		Node nextGameState = Node('d', m_gameState);

		nextGameState.getGameState().moveRightFast();

		if (std::find(frontier.begin(), frontier.end(), nextGameState) == frontier.end() &&
			std::find(explored.begin(), explored.end(), nextGameState) == explored.end()) {
			frontier.push_back(nextGameState);
		}
	}

}

Node::Node(char move, const SnakeGame& m_gameState) :
	std::pair<char, SnakeGame>(move, m_gameState) {}

bool Node::isGoal() const
{
	/*const SnakeState& m_gameState = getGameState();
	const Snake& snake = m_gameState.snake;
	const Apple& m_apple = m_gameState.m_apple;

	const Position& headPos = static_cast<const Position&>(snake.head());
	const Position& applePos = static_cast<const Position&>(m_apple);

	return snake.head() == static_cast<const Position&>(m_apple);*/
	throw std::exception(__FUNCTION__);	// Remove when implemeted
	return false;
}

char Node::getMove() const
{
	return this->first;
}

const SnakeGame& Node::getGameState() const
{
	return this->second;
}

SnakeGame& Node::getGameState()
{
	return this->second;
}

bool Node::operator==(const Node& left) const
{
	// Two Nodes are equal if their snake and m_apple
	// are in the exact same places.
	// Does not account for the move.
	return this->getGameState() == left.getGameState();
}
