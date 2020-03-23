#include "SolverBase.h"

SolverBase::SolverBase(const SnakeEngine& engine) :
	engine(engine)
{}

bool SolverBase::isMoveUpSafe() const
{
	const Snake& snake = engine.snake;
	const SnakeBoard& board = engine.board;

	return snake.isMoveUpValid() && board(snake.head().upOne()) != CELL::TAIL;
}

bool SolverBase::isMoveDownSafe() const
{
	const Snake& snake = engine.snake;
	const SnakeBoard& board = engine.board;

	return snake.isMoveDownValid() && board(snake.head().downOne()) != CELL::TAIL;
}

bool SolverBase::isMoveLeftSafe() const
{
	const Snake& snake = engine.snake;
	const SnakeBoard& board = engine.board;

	return snake.isMoveLeftValid() && board(snake.head().leftOne()) != CELL::TAIL;
}

bool SolverBase::isMoveRightSafe() const
{
	const Snake& snake = engine.snake;
	const SnakeBoard& board = engine.board;

	return snake.isMoveRightValid() && board(snake.head().rightOne()) != CELL::TAIL;
}

bool SolverBase::isMoveSafe(char move) const
{
	const Snake& snake = engine.snake;
	const SnakeBoard& board = engine.board;

	if (snake.isMoveValid(move) == false)
		return false;

	switch (move)
	{
	case 'w':	return board(snake.head().upOne()) != CELL::TAIL;
	case 's':	return board(snake.head().downOne()) != CELL::TAIL;
	case 'a':	return board(snake.head().leftOne()) != CELL::TAIL;
	case 'd':	return board(snake.head().rightOne()) != CELL::TAIL;
	default:
		throw std::exception("Invalid move");
	}
}
