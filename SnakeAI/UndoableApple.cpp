#include "UndoableApple.h"

UndoableApple::UndoableApple()
{}

UndoableApple::UndoableApple(const Apple & apple) :
	Apple(apple)
{
}

void UndoableApple::print(std::ostream& os) const
{
	os << "Apple " << static_cast<Position>(*this)
		<< applePositions.size() << " undos available" << '\n';
}

void UndoableApple::reset()
{
	Apple::reset();

	applePositions.clear();
}

void UndoableApple::moveTo(size_t row, size_t col)
{
	Apple::moveTo(row, col);

	// Save position for undoing
	applePositions.push_back(*this);

	// At this point their maybe either 1 (bad) or more apple positions. Do we have 1 (or even 0) positions?
	if (applePositions.size() < 2) {
		// Yes we only have one apple position. Thats bad because snakes always have atleast 2 positions we have to make sure 
		// that the number of apple positions and snake positions are always equal. 
		applePositions.push_back(*this);
	}
}

void UndoableApple::moveTo(const Position& pos)
{
	moveTo(pos.row(), pos.col());
}

void UndoableApple::logPosition()
{	
	// Save position for undoing
	applePositions.push_back(*this);
}

bool UndoableApple::isUndoLegal() const
{
	return applePositions.size() > 2;
}

void UndoableApple::undoFast()
{
	this->row(applePositions.back().row());
	this->col(applePositions.back().col());

	applePositions.pop_back();
}

void UndoableApple::undoIfLegal()
{
	if (isUndoLegal()) {
		undoFast();
	}
}
