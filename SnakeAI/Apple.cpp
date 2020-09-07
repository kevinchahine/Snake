#include "Apple.h"

Apple::Apple() :
	Position(0, 0)
{}

void Apple::print(std::ostream& os) const
{
	os << "Apple " << static_cast<Position>(*this) << '\n';
}

void Apple::reset()
{
}

void Apple::moveTo(size_t row, size_t col)
{
	this->row(row);
	this->col(col); 
}

void Apple::moveTo(const Position& pos)
{
	moveTo(pos.row(), pos.col());
}
