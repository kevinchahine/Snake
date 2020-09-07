#pragma once

#include "Apple.h"

class UndoableApple : public Apple
{
public:
	UndoableApple();
	UndoableApple(const Apple& apple);
	UndoableApple(const UndoableApple&) = default;
	UndoableApple(UndoableApple&&) noexcept = default;
	~UndoableApple() noexcept = default;

	UndoableApple& operator=(const UndoableApple&) = default;
	UndoableApple& operator=(UndoableApple&&) noexcept = default;

	void print(std::ostream & os = std::cout) const;

	void reset();

	void moveTo(size_t row, size_t col);
	void moveTo(const Position & pos);
	void logPosition();

	bool isUndoLegal() const;
	void undoFast();
	void undoIfLegal();

private:
	std::vector<Position> applePositions;
};

