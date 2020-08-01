#include "Position.h"

Position::Position() :
	std::array<index, 2> { { 0, 0 } }
{
}

Position::Position(int row, int col) :
	std::array<index, 2> { { row, col} }
{
}

bool Position::operator==(const Position& position) const
{
	return 
		(*this)[0] == position[0] && 
		(*this)[1] == position[1];
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

Position Position::oneToThe(char move) const
{
	switch (move)
	{
	case 'w':	return upOne();
	case 's':	return downOne();
	case 'a':	return leftOne();
	case 'd':	return rightOne();
	default:	return *this;
	}
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

std::ostream & operator<<(std::ostream& os, const Position& position)
{
	os << '<' << position.row() << ", " << position.col() << '>';

	return os;
}
