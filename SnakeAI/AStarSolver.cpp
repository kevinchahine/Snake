#include "AStarSolver.h"

AStarSolver::AStarSolver(const SnakeEngine& engine) :
	SolverBase(engine) {}

char AStarSolver::solve()
{
	const Snake& snake = engine.snake;
	const Apple& apple = engine.apple;
	const Position& head = snake.head();

	// Find shortest path to apple and avoid hitting tail
	
	// 1.) Find all valid moves
	std::priority_queue<Move, std::vector<Move>, std::greater<Move>> validMoves;
	
	// Determine which moves are valid.
	if (engine.snake.isMoveUpValid()) {
		int manhattanDist = calcManhattanDist(head.upOne(), apple);
		
		validMoves.push(Move('w', manhattanDist));
	}

	if (engine.snake.isMoveDownValid()) {
		int manhattanDist = calcManhattanDist(head.downOne(), apple);
		
		validMoves.push(Move('s', manhattanDist));
	}

	if (engine.snake.isMoveLeftValid()) {
		int manhattanDist = calcManhattanDist(head.leftOne(), apple);
		
		validMoves.push(Move('a', manhattanDist));
	}

	if (engine.snake.isMoveRightValid()) {
		int manhattanDist = calcManhattanDist(head.rightOne(), apple);
		
		validMoves.push(Move('d', manhattanDist));
	}

	// Copy current state into another solver which will do a recursive solve call 
	SnakeEngine nextMovesEngine(engine);
	AStarSolver nextMovesSolver(nextMovesEngine);
	
	// Try each valid direction in order of least manhattan distance
	while (validMoves.empty() == false) {
		const auto& move = validMoves.top();
		
		nextMovesEngine.snake.moveValid(move.direction);

		validMoves.pop();
	}

	return 'd';
}

int AStarSolver::calcManhattanDist(const Position& p1, const Position& p2)
{
	return 
		std::abs(p1.row() - p2.row()) +
		std::abs(p1.col() - p2.col());
}

