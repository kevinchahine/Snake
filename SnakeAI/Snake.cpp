#include "Snake.h"

#include <algorithm>
#include <sstream>

Snake::Snake(size_t boardHeight, size_t boardWidth) :
	m_boardHeight(boardHeight),
	m_boardWidth(boardWidth)
{
	this->push_back(Position(0, 0));
	this->push_back(Position(0, 1));
}

bool Snake::operator==(const Position& position) const
{
	return this->isOnSnake(position);
}

void Snake::print(std::ostream& os) const
{
	os << "Snake (Head, Neck, Tail) (" << head() << ", " << neck() << ", " << tailTip() << ")"
		<< "length = " << size() << ' '
		<< snakePositions.size() << " undos available\n";
}

std::ostream& operator<<(std::ostream& os, const Snake& snake)
{
	for (int i = 0; i < snake.size(); i++) {
		os << snake[i] << ' ';
	}

	return os;
}

bool Snake::isBittingItself() const
{
	// Iterator to the tip of the snakes tail
	const auto tailIter = this->begin();

	// Iterator to one past the snakes neck. (or the head)
	const auto headIter = prev(this->end());

	// See if a cell on the snake, from its tail to its neck (Not including its head)
	// equals its head.

	auto iter = tailIter;
	for (iter = tailIter; iter != headIter; iter++) {
		if (*iter == head()) {
			std::cout << "Ouyi\n";
			break;
		}
	}

	auto biteMarkCellIter = iter;
	
	// Snake bit itself if the bite march is somewhere before its head.
	// The snake can't really bite its own head
	return biteMarkCellIter != headIter;
}

bool Snake::isOnSnake(const Position& position) const
{
	for (size_t i = 0; i < this->size(); i++) {
		if ((*this)[i] == position)
			return true;
	}

	return false;
}

const Position& Snake::head() const
{
	// back is actually the head
	if (this->empty()) {
		throw std::exception("Snake is empty and has no head");
	}

	return this->back();
}

const Position & Snake::neck() const
{
	const size_t size = this->size();

	return (*this)[size - 2];
}

const Position& Snake::tailTip() const
{
	// front is actually the tail
	if (this->empty()) {
		throw std::exception("Snake is empty and has no tail");
	}

	return this->front();
}

void Snake::resetHeadRandom()
{
	int row = (rand() % m_boardHeight);
	int col = (rand() % m_boardWidth);

	resetHeadAt(Position(row, col));
}

void Snake::resetHeadAt(Position headStartingPosition)
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

bool Snake::isMoveUpLegal() const
{
	Position headPosition = head();
	Position neckPosition = neck();
	
	return
		headPosition.row() > 0 && 
		headPosition.row() != neckPosition.row() + 1;
}

bool Snake::isMoveDownLegal() const
{
	Position headPosition = head();
	Position neckPosition = neck();

	return
		headPosition.row() < m_boardHeight - 1 &&
		headPosition.row() != neckPosition.row() - 1;
}

bool Snake::isMoveLeftLegal() const
{
	Position headPosition = head();
	Position neckPosition = neck();

	return
		headPosition.col() > 0 &&
		headPosition.col() != neckPosition.col() + 1;
}

bool Snake::isMoveRightLegal() const
{
	Position headPosition = head();
	Position neckPosition = neck();

	return
		headPosition.col() < m_boardWidth - 1 &&
		headPosition.col() != neckPosition.col() - 1;
}

bool Snake::isUndoLegal() const
{
	return snakePositions.size() > 2;
}

bool Snake::isMoveLegal(char direction) const
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

char Snake::getAnyLegalMove() const
{
	if (isMoveUpLegal()) return 'w';
	if (isMoveDownLegal()) return 's';
	if (isMoveLeftLegal()) return 'a';
	if (isMoveRightLegal()) return 'd';

	// --- We should never be able to reach this point. There should always be a valid move.
	throw std::exception("Snake::getAnyValidMove(): No moves are valid.");
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

void Snake::undoFast()
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

void Snake::moveFast(char direction)
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

void Snake::moveUpIfLegal()
{
	if (isMoveUpLegal())
		moveUpFast();
}

void Snake::moveDownIfLegal()
{
	if (isMoveDownLegal())
		moveDownFast();
}

void Snake::moveLeftIfLegal()
{
	if (isMoveLeftLegal())
		moveLeftFast();
}

void Snake::moveRightIfLegal()
{
	if (isMoveRightLegal())
		moveRightFast();
}

void Snake::undoIfLegal()
{
	if (isUndoLegal())
		undoFast();
}

void Snake::moveIfLegal(char direction)
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

void Snake::moveAnyLegal()
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

void Snake::growUpFast()
{
	// Save tail Pos for undo
	snakePositions.push_back(tailTip());

	Position headPosition = head();

	headPosition = headPosition.upOne();

	// Move head up one cell
	this->push_back(headPosition);
}

void Snake::growDownFast()
{
	// Save tail Pos for undo
	snakePositions.push_back(tailTip());

	Position headPosition = head();

	headPosition = headPosition.downOne();

	// Move head up one cell
	this->push_back(headPosition);
}

void Snake::growLeftFast()
{
	// Save tail Pos for undo
	snakePositions.push_back(tailTip());

	Position headPosition = head();

	headPosition = headPosition.leftOne();

	// Move head left one cell
	this->push_back(headPosition);
}

void Snake::growRightFast()
{
	// Save tail Pos for undo
	snakePositions.push_back(tailTip());

	Position headPosition = head();

	headPosition = headPosition.rightOne();

	// Move head right one cell
	this->push_back(headPosition);
}

void Snake::growFast(char direction)
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

void Snake::growUpIfLegal()
{
	if (isMoveUpLegal())
		growUpFast();
}

void Snake::growDownIfLegal()
{
	if (isMoveDownLegal())
		growDownFast();
}

void Snake::growLeftIfLegal()
{
	if (isMoveLeftLegal())
		growLeftFast();
}

void Snake::growRightIfLegal()
{
	if (isMoveRightLegal())
		growRightFast();
}

void Snake::growIfLegal(char direction)
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

void Snake::growAnyLegal()
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

uint64_t Snake::hashValue() const
{
	uint64_t hashValue = 0;

	for (size_t snakeIndex = 0; snakeIndex < this->size(); snakeIndex++) {
		const Position& pos = (*this)[snakeIndex];

		size_t cellIndex = pos.row() * this->m_boardWidth + pos.col();

		hashValue += (cellIndex + 1) * (snakeIndex + 1);
	}

	return hashValue;
}
