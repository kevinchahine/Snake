#include "UndoableSnake.h"

UndoableSnake::UndoableSnake(size_t boardHeight, size_t boardWidth) :
	Snake(boardHeight, boardWidth)
{}

UndoableSnake::UndoableSnake(const Snake & snake) :
	Snake(snake)
{
}

void UndoableSnake::print(std::ostream& os) const
{
	os << "Snake (Head, Neck, Tail) (" << head() << ", " << neck() << ", " << tailTip() << ")"
		<< "length = " << size() << ' '
		<< snakePositions.size() << " undos available\n";
}

void UndoableSnake::resetHeadRandom()
{
	int row = (rand() % m_boardHeight);
	int col = (rand() % m_boardWidth);

	resetHeadAt(Position(row, col));
}

void UndoableSnake::resetHeadAt(Position headStartingPosition)
{
	// 'headStartingPosition' is to long to spell every time
	Position& p = headStartingPosition;

	this->clear();									// Delete snake
	this->push_back(Position(p.row(), p.col()));	// Place head at the random position
	snakePositions.clear();							// Clear the undo positions

	// Give it a tail so that it will start at 2 cells long
	if (p.row() > 0) {
		growUpFast();
		moveDownFast();
	}
	else {
		growDownFast();
		moveUpFast();
	}
}

bool UndoableSnake::isUndoLegal() const
{
	return snakePositions.size() > 2;
}

bool UndoableSnake::isMoveLegal(char direction) const
{
	switch (direction)
	{
	case 'w':	return isMoveUpLegal();
	case 's':	return isMoveDownLegal();
	case 'a':	return isMoveLeftLegal();
	case 'd':	return isMoveRightLegal();
	case 'z':	return isUndoLegal();
	default:	return false;
		//default:	throw std::exception("Received invalid direction");
	}
}

void UndoableSnake::moveUpFast()
{
	// Move up the head
	growUpFast();

	// Pop off the old tail
	this->pop_front();
}

void UndoableSnake::moveDownFast()
{
	// Move down the head
	growDownFast();

	// Pop off the old tail
	this->pop_front();
}

void UndoableSnake::moveLeftFast()
{
	// Move left the head
	growLeftFast();

	// Pop off the old tail
	this->pop_front();
}

void UndoableSnake::moveRightFast()
{
	// Move right the head
	growRightFast();

	// Pop off the old tail
	this->pop_front();
}

void UndoableSnake::undoFast()
{
	const Position& lastTailPos = snakePositions.back();
	const Position& currTail = tailTip();

	// Is lastTailPos the same as the current tail?
	if (lastTailPos == currTail) {
		// Yes. This means that the snake moved by "growing"
		// All we have to do is move the head back. 
		// Tail can stay where it is.
		this->pop_back();				// Chop off head
	}
	else {
		// No. This means that the snake moved by "moving" 
		// We have to move the head back and the tail
		this->pop_back();				// Chop off head
		this->push_front(lastTailPos);	// Move tail back
	}

	snakePositions.pop_back();
}

void UndoableSnake::moveFast(char direction)
{
	switch (direction)
	{
	case 'w':	return moveUpFast();
	case 'd':	return moveRightFast();
	case 's':	return moveDownFast();
	case 'a':	return moveLeftFast();
	case 'z':	return undoFast();
	default:	throw std::exception("Received invalid direction");
	}
}

void UndoableSnake::moveUpIfLegal()
{
	if (isMoveUpLegal())
		moveUpFast();
}

void UndoableSnake::moveDownIfLegal()
{
	if (isMoveDownLegal())
		moveDownFast();
}

void UndoableSnake::moveLeftIfLegal()
{
	if (isMoveLeftLegal())
		moveLeftFast();
}

void UndoableSnake::moveRightIfLegal()
{
	if (isMoveRightLegal())
		moveRightFast();
}

void UndoableSnake::undoIfLegal()
{
	if (isUndoLegal())
		undoFast();
}

void UndoableSnake::moveIfLegal(char direction)
{
	switch (direction)
	{
	case 'w':	return moveUpIfLegal();
	case 'd':	return moveRightIfLegal();
	case 's':	return moveDownIfLegal();
	case 'a':	return moveLeftIfLegal();
	case 'z':	return undoIfLegal();
		//default:	throw std::exception("Received invalid direction");
	}
}

void UndoableSnake::moveAnyLegal()
{
	if (isMoveUpLegal())			moveUpFast();
	else if (isMoveDownLegal())		moveDownFast();
	else if (isMoveLeftLegal())		moveLeftFast();
	else if (isMoveRightLegal())	moveRightFast();
	else {
		std::stringstream ss;
		ss << __FUNCTION__ << " line " << __LINE__
			<< ": No move is legal";
		throw std::exception(ss.str().c_str());
	}
}

void UndoableSnake::growUpFast()
{
	// Save tail Pos for undo
	snakePositions.push_back(tailTip());

	Position headPosition = head();

	headPosition = headPosition.upOne();

	// Move head up one cell
	this->push_back(headPosition);
}

void UndoableSnake::growDownFast()
{
	// Save tail Pos for undo
	snakePositions.push_back(tailTip());

	Position headPosition = head();

	headPosition = headPosition.downOne();

	// Move head up one cell
	this->push_back(headPosition);
}

void UndoableSnake::growLeftFast()
{
	// Save tail Pos for undo
	snakePositions.push_back(tailTip());

	Position headPosition = head();

	headPosition = headPosition.leftOne();

	// Move head left one cell
	this->push_back(headPosition);
}

void UndoableSnake::growRightFast()
{
	// Save tail Pos for undo
	snakePositions.push_back(tailTip());

	Position headPosition = head();

	headPosition = headPosition.rightOne();

	// Move head right one cell
	this->push_back(headPosition);
}

void UndoableSnake::growFast(char direction)
{
	switch (direction)
	{
	case 'w':	return growUpFast();
	case 'd':	return growRightFast();
	case 's':	return growDownFast();
	case 'a':	return growLeftFast();
	case 'z':	return undoFast();
	default:	throw std::exception("Received invalid direction");
	}
}

void UndoableSnake::growUpIfLegal()
{
	if (isMoveUpLegal())
		growUpFast();
}

void UndoableSnake::growDownIfLegal()
{
	if (isMoveDownLegal())
		growDownFast();
}

void UndoableSnake::growLeftIfLegal()
{
	if (isMoveLeftLegal())
		growLeftFast();
}

void UndoableSnake::growRightIfLegal()
{
	if (isMoveRightLegal())
		growRightFast();
}

void UndoableSnake::growIfLegal(char direction)
{
	switch (direction)
	{
	case 'w':	return growUpIfLegal();
	case 'd':	return growRightIfLegal();
	case 's':	return growDownIfLegal();
	case 'a':	return growLeftIfLegal();
	case 'z':	return undoIfLegal();
	default:	throw std::exception("Received invalid direction");
	}
}

void UndoableSnake::growAnyLegal()
{
	if (isMoveUpLegal())			growUpFast();
	else if (isMoveDownLegal())		growDownFast();
	else if (isMoveLeftLegal())		growLeftFast();
	else if (isMoveRightLegal())	growRightFast();
	else {
		std::stringstream ss;
		ss << __FUNCTION__ << " line " << __LINE__
			<< ": No move is legal";
		throw std::exception(ss.str().c_str());
	}
}

uint64_t UndoableSnake::hashValue() const
{
	uint64_t hashValue = 0;

	for (size_t snakeIndex = 0; snakeIndex < this->size(); snakeIndex++) {
		const Position& pos = (*this)[snakeIndex];

		size_t cellIndex = pos.row() * this->m_boardWidth + pos.col();

		hashValue += (cellIndex + 1) * (snakeIndex + 1);
	}

	return hashValue;
}
