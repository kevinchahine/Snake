#pragma once

#include "Snake.h"

class UndoableSnake : public Snake
{
public:
	UndoableSnake(size_t boardHeight, size_t boardWidth);
	UndoableSnake(const Snake& snake);
	UndoableSnake(const UndoableSnake&) = default;
	UndoableSnake(UndoableSnake&&) noexcept = default;
	~UndoableSnake() noexcept = default;

	UndoableSnake& operator=(const UndoableSnake&) = default;
	UndoableSnake& operator=(UndoableSnake&&) noexcept = default;

	void print(std::ostream& os = std::cout) const;

	void resetHeadRandom();

	void resetHeadAt(Position headStartingPosition);

	// Legal moves are moves where you don't hit the wall or move back into
	// your neck.
	bool isUndoLegal() const;
	bool isMoveLegal(char direction) const;
	
	void moveUpFast();
	void moveDownFast();
	void moveLeftFast();
	void moveRightFast();
	void undoFast();
	void moveFast(char direction);

	// Move if it will not hit wall or the Snakes neck
	void moveUpIfLegal();
	void moveDownIfLegal();
	void moveLeftIfLegal();
	void moveRightIfLegal();
	void undoIfLegal();
	void moveIfLegal(char direction);
	void moveAnyLegal();

	void growUpFast();
	void growDownFast();
	void growLeftFast();
	void growRightFast();
	void growFast(char direction);

	// Grow if it will not hit wall or the Snakes neck
	void growUpIfLegal();
	void growDownIfLegal();
	void growLeftIfLegal();
	void growRightIfLegal();
	void growIfLegal(char direction);
	void growAnyLegal();
	uint64_t hashValue() const;

	size_t getNRows() const { return m_boardHeight; }
	size_t getNCols() const { return m_boardWidth; }

private:
	std::vector<Position> snakePositions;
};

