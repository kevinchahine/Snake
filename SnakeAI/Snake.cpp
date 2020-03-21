#include "Snake.h"

Snake::Snake(size_t boardHeight, size_t boardWidth) :
	boardHeight(boardHeight),
	boardWidth(boardWidth)
{
}

const Position& Snake::head() const
{
	// back is actually the head
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

bool Snake::isMoveUpValid()
{
	Position headPosition = head();

	Position neckPosition = neck();
	
	return
		headPosition.row() > 0 && 
		headPosition.row() != neckPosition.row() + 1;
}

bool Snake::isMoveDownValid()
{
	Position headPosition = head();

	Position neckPosition = neck();

	return
		headPosition.row() < boardHeight - 1 &&
		headPosition.row() != neckPosition.row() - 1;
}

bool Snake::isMoveLeftValid()
{
	Position headPosition = head();

	Position neckPosition = neck();

	return
		headPosition.col() > 0 &&
		headPosition.col() != neckPosition.col() + 1;
}

bool Snake::isMoveRightValid()
{
	Position headPosition = head();

	Position neckPosition = neck();

	return
		headPosition.col() < boardWidth - 1 &&
		headPosition.col() != neckPosition.col() - 1;
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