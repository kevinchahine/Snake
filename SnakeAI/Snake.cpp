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

	auto iter = tailIter;
	for (iter = tailIter; iter != headIter; iter++) {
		if (*iter == head()) {
			std::cout << "Ouyi\n";
			break;
		}
	}

	auto biteMarkCellIter = iter;
	
	// Snake bit itself if the bite march is somewhere before its head.
	// The snake can't really bite its own head
	return biteMarkCellIter != headIter;
}

const Position& Snake::head() const
{
	// back is actually the head
	if (this->empty()) {
		throw std::exception("Snake is empty and has no head");
	}

	return this->back();
}

const Position & Snake::neck() const
{
	auto it = std::next(rbegin());

	return *it;
}

const Position& Snake::tailTip() const
{
	// front is actually the tail
	if (this->empty()) {
		throw std::exception("Snake is empty and has no tail");
	}

	return this->front();
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

bool Snake::isMoveUpLegal() const
{
	Position headPosition = head();
	Position neckPosition = neck();
	
	return
		headPosition.row() > 0 && 
		headPosition.row() != neckPosition.row() + 1;
}

bool Snake::isMoveDownLegal() const
{
	Position headPosition = head();
	Position neckPosition = neck();

	return
		headPosition.row() < boardHeight - 1 &&
		headPosition.row() != neckPosition.row() - 1;
}

bool Snake::isMoveLeftLegal() const
{
	Position headPosition = head();
	Position neckPosition = neck();

	return
		headPosition.col() > 0 &&
		headPosition.col() != neckPosition.col() + 1;
}

bool Snake::isMoveRightLegal() const
{
	Position headPosition = head();
	Position neckPosition = neck();

	return
		headPosition.col() < boardWidth - 1 &&
		headPosition.col() != neckPosition.col() - 1;
}

bool Snake::isMoveLegal(char direction) const
{
	switch (direction)
	{
	case 'w':	return isMoveUpLegal();
	case 's':	return isMoveDownLegal();
	case 'a':	return isMoveLeftLegal();
	case 'd':	return isMoveRightLegal();
	default:	throw std::exception("Received invalid direction");
	}
}

char Snake::getAnyLegalMove() const
{
	if (isMoveUpLegal()) return 'w';
	if (isMoveDownLegal()) return 's';
	if (isMoveLeftLegal()) return 'a';
	if (isMoveRightLegal()) return 'd';

	// --- We should never be able to reach this point. There should always be a valid move.
	throw std::exception("Snake::getAnyValidMove(): No moves are valid.");
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

void Snake::moveUpIfLegal()
{
	if (isMoveUpLegal())
		moveUpFast();
}

void Snake::moveDownIfLegal()
{
	if (isMoveDownLegal())
		moveDownFast();
}

void Snake::moveLeftIfLegal()
{
	if (isMoveLeftLegal())
		moveLeftFast();
}

void Snake::moveRightIfLegal()
{
	if (isMoveRightLegal())
		moveRightFast();
}

void Snake::moveIfLegal(char direction)
{
	switch (direction)
	{
	case 'w':	return moveUpIfLegal();
	case 'd':	return moveRightIfLegal();
	case 's':	return moveDownIfLegal();
	case 'a':	return moveLeftIfLegal();
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

void Snake::growUpIfLegal()
{
	if (isMoveUpLegal())
		growUpFast();
}

void Snake::growDownIfLegal()
{
	if (isMoveDownLegal())
		growDownFast();
}

void Snake::growLeftIfLegal()
{
	if (isMoveLeftLegal())
		growLeftFast();
}

void Snake::growRightIfLegal()
{
	if (isMoveRightLegal())
		growRightFast();
}

void Snake::growIfLegal(char direction)
{
	switch (direction)
	{
	case 'w':	return growUpIfLegal();
	case 'd':	return growRightIfLegal();
	case 's':	return growDownIfLegal();
	case 'a':	return growLeftIfLegal();
	default:	throw std::exception("Received invalid direction");
	}
}
