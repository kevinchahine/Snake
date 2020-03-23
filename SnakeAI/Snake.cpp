#include "Snake.h"

#include <algorithm>

Snake::Snake(size_t boardHeight, size_t boardWidth) :
	boardHeight(boardHeight),
	boardWidth(boardWidth)
{
}

bool Snake::operator==(const Position& position) const
{
	// iterate over the snakes body
	for (const auto& snakeCell : (*this)) {
		// If position matches one of the snakes cells,
		// then return true.
		if (snakeCell == position) {
			return true;
		}
	}

	// We didn't find a cell that matches with position
	return false;
}

bool Snake::bitItself() const
{
	// Iterator to the tip of the snakes tail
	const auto tailIter = this->begin();

	// Iterator to one past the snakes neck. (or the head)
	const auto headIter = prev(this->end());

	// See if a cell on the snake, from its tail to its neck (Not including its head)
	// equals its head.
	auto biteMarkCellIter = std::find(tailIter, headIter, head());

	// Snake bit itself if the bite march is somewhere before its head.
	// The snake can't really bite its own head
	return biteMarkCellIter != headIter;
}

const Position& Snake::head() const
{
	try {
		// back is actually the head
		auto& h = this->back();
		return h;
	}
	catch (std::exception & e) {
		std::cout << e.what() << '\n';

	}

	return this->back();
}

const Position& Snake::neck() const
{
	auto it = std::next(rbegin());

	return Position(*it);
}

void Snake::resetHeadRandom()
{
	int row = (rand() % boardHeight);
	int col = (rand() % boardWidth);

	this->clear();
	this->push_back(Position(row, col));

	// Give it a tail so that it will start at 2 cells long
	if (row > 0) {
		std::cout << "Moved up\n";
		growUpFast();
		moveDownFast();
	}
	else {
		std::cout << "Move down\n";
		growDownFast();
		moveUpFast();
	}
}

void Snake::resetHeadAt(Position headStartingPosition)
{
	this->clear();
	this->push_back(headStartingPosition);
}

bool Snake::isMoveUpValid() const
{
	Position headPosition = head();

	Position neckPosition = neck();
	
	return
		headPosition.row() > 0 && 
		headPosition.row() != neckPosition.row() + 1;
}

bool Snake::isMoveDownValid() const
{
	Position headPosition = head();

	Position neckPosition = neck();

	return
		headPosition.row() < boardHeight - 1 &&
		headPosition.row() != neckPosition.row() - 1;
}

bool Snake::isMoveLeftValid() const
{
	Position headPosition = head();

	Position neckPosition = neck();

	return
		headPosition.col() > 0 &&
		headPosition.col() != neckPosition.col() + 1;
}

bool Snake::isMoveRightValid() const
{
	Position headPosition = head();

	Position neckPosition = neck();

	return
		headPosition.col() < boardWidth - 1 &&
		headPosition.col() != neckPosition.col() - 1;
}

bool Snake::isMoveValid(char direction) const
{
	switch (direction)
	{
	case 'w':	return isMoveUpValid();
	case 's':	return isMoveDownValid();
	case 'a':	return isMoveLeftValid();
	case 'd':	return isMoveRightValid();
	default:	throw std::exception("Received invalid direction");
	}
}

void Snake::moveUpFast()
{
	// Move up the head
	growUpFast();

	// Pop off the old tail
	this->pop_front();
}

void Snake::moveDownFast()
{
	// Move down the head
	growDownFast();

	// Pop off the old tail
	this->pop_front();
}

void Snake::moveLeftFast()
{
	// Move left the head
	growLeftFast();

	// Pop off the old tail
	this->pop_front();
}

void Snake::moveRightFast()
{
	// Move right the head
	growRightFast();

	// Pop off the old tail
	this->pop_front();
}

void Snake::moveFast(char direction)
{
	switch (direction)
	{
	case 'w':	return moveUpFast();
	case 'd':	return moveRightFast();
	case 's':	return moveDownFast();
	case 'a':	return moveLeftFast();
	default:	throw std::exception("Received invalid direction");
	}
}

void Snake::moveUpValid()
{
	if (isMoveUpValid())
		moveUpFast();
}

void Snake::moveDownValid()
{
	if (isMoveDownValid())
		moveDownFast();
}

void Snake::moveLeftValid()
{
	if (isMoveLeftValid())
		moveLeftFast();
}

void Snake::moveRightValid()
{
	if (isMoveRightValid())
		moveRightFast();
}

void Snake::moveValid(char direction)
{
	switch (direction)
	{
	case 'w':	return moveUpValid();
	case 'd':	return moveRightValid();
	case 's':	return moveDownValid();
	case 'a':	return moveLeftValid();
	default:	throw std::exception("Received invalid direction");
	}
}

void Snake::growUpFast()
{
	Position headPosition = head();

	headPosition.row(headPosition.row() - 1);

	// Move head up one cell
	this->push_back(headPosition);
}

void Snake::growDownFast()
{
	Position headPosition = head();

	headPosition.row(headPosition.row() + 1);

	// Move head up one cell
	this->push_back(headPosition);
}

void Snake::growLeftFast()
{
	Position headPosition = head();

	headPosition.col(headPosition.col() - 1);

	// Move head left one cell
	this->push_back(headPosition);
}

void Snake::growRightFast()
{
	Position headPosition = head();

	headPosition.col(headPosition.col() + 1);

	// Move head right one cell
	this->push_back(headPosition);
}

void Snake::growFast(char direction)
{
	switch (direction)
	{
	case 'w':	return growUpFast();
	case 'd':	return growRightFast();
	case 's':	return growDownFast();
	case 'a':	return growLeftFast();
	default:	throw std::exception("Received invalid direction");
	}
}

void Snake::growUpValid()
{
	if (isMoveUpValid())
		growUpFast();
}

void Snake::growDownValid()
{
	if (isMoveDownValid())
		growDownFast();
}

void Snake::growLeftValid()
{
	if (isMoveLeftValid())
		growLeftFast();
}

void Snake::growRightValid()
{
	if (isMoveRightValid())
		growRightFast();
}

void Snake::growValid(char direction)
{
	switch (direction)
	{
	case 'w':	return growUpValid();
	case 'd':	return growRightValid();
	case 's':	return growDownValid();
	case 'a':	return growLeftValid();
	default:	throw std::exception("Received invalid direction");
	}
}
