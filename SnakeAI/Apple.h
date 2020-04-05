#pragma once

#include "Position.h"

class Apple : public Position
{
public:
	Apple(size_t boardHeight, size_t boardWidth);
	Apple(const Apple&) = default;
	Apple(Apple&&) noexcept = default;
	~Apple() noexcept = default;

	Apple& operator=(const Apple&) = default;
	Apple& operator=(Apple&&) noexcept = default;

	void moveRandom();

	void moveTo(size_t row, size_t col);
	void moveTo(const Position& pos);

private:
	size_t boardHeight;
	size_t boardWidth;
};

