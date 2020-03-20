#include "Position.h"

SnakeBoard::index Position::row() const
{
	return (*this)[0];
}

void Position::row(const SnakeBoard::index& row)
{
	(*this)[0] = row;
}

SnakeBoard::index Position::col() const
{
	return (*this)[1];
}

void Position::col(const SnakeBoard::index& col)
{
	(*this)[1] = col;
}
