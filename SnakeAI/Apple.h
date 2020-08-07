#pragma once

#include "Position.h"

class Apple : public Position
{
public:
	Apple();
	Apple(const Apple&) = default;
	Apple(Apple&&) noexcept = default;
	~Apple() noexcept = default;

	Apple& operator=(const Apple&) = default;
	Apple& operator=(Apple&&) noexcept = default;

	void print(std::ostream& os = std::cout) const;

	void reset();

	void moveTo(size_t row, size_t col);
	void moveTo(const Position& pos);
	void logPosition();

	bool isUndoLegal() const;
	void undoFast();
	void undoIfLegal();

private:
	std::vector<Position> applePositions;
};

