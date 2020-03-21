#include "Position.h"

Position::Position(int row, int col) :
	std::array<index, 2> { { row, col} }
{
}

Position Position::upOne() const
{
	return Position(row() - 1, col());
}

Position Position::downOne() const
{
	return Position(row() + 1, col());
}

Position Position::leftOne() const
{
	return Position(row(), col() - 1);
}

Position Position::rightOne() const
{
	return Position(row(), col() + 1);
}

index Position::row() const
{
	return (*this)[0];
}

void Position::row(const index& row)
{
	(*this)[0] = row;
}

index Position::col() const
{
	return (*this)[1];
}

void Position::col(const index& col)
{
	(*this)[1] = col;
}

