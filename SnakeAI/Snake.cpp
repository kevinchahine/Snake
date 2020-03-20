#include "Snake.h"

const Position& Snake::peekHead() const
{
	// back is actually the head
	return this->back();
}

void Snake::moveUp()
{
	Position headPosition = peekHead();

	headPosition.row(headPosition.row() - 1);

	// Move head up one cell
	this->push(headPosition);

	// Pop off the old tail
	this->pop();
}

void Snake::moveDown()
{
}

void Snake::moveLeft()
{
}

void Snake::moveRight()
{
}
