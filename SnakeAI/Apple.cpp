#include "Apple.h"

Apple::Apple(size_t boardHeight, size_t boardWidth) :
	Position(0, 0),
	boardHeight(boardHeight),
	boardWidth(boardWidth)
{}

void Apple::moveRandom()
{
	this->row(rand() % boardHeight);
	this->col(rand() % boardWidth);
}

void Apple::moveTo(size_t row, size_t col)
{
	// Limit out of bounds values.
	row = (row >= boardHeight ? boardHeight - 1 : row);
	col = (col >= boardWidth ? boardWidth - 1 : col);

	this->row(row);
	this->col(col);
}
