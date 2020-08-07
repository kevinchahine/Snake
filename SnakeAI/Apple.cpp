#include "Apple.h"

Apple::Apple() :
	Position(0, 0)
{}

void Apple::print(std::ostream& os) const
{
	os << "Apple " << static_cast<Position>(*this) 
		<< applePositions.size() << " undos available" << '\n';
}

void Apple::reset()
{
	applePositions.clear();
}

void Apple::moveTo(size_t row, size_t col)
{
	this->row(row);
	this->col(col); 
	
	// Save position for undoing
	applePositions.push_back(*this);

	// At this point their maybe either 1 (bad) or more apple positions. Do we have 1 (or even 0) positions?
	if (applePositions.size() < 2) {
		// Yes we only have one apple position. Thats bad because snakes always have atleast 2 positions we have to make sure 
		// that the number of apple positions and snake positions are always equal. 
		applePositions.push_back(*this);
	}
}

void Apple::moveTo(const Position& pos)
{
	moveTo(pos.row(), pos.col());
}

void Apple::logPosition()
{
	// Save position for undoing
	applePositions.push_back(*this);
}

bool Apple::isUndoLegal() const
{
	return applePositions.size() > 2;
}

void Apple::undoFast()
{
	this->row(applePositions.back().row());
	this->col(applePositions.back().col());

	applePositions.pop_back();
}

void Apple::undoIfLegal()
{
	if (isUndoLegal()) {
		undoFast();
	}
}
