#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
#include <queue>

#include "SnakeGame.h"

// Defines a sequence of moves that lead to a defined snake state
class SnakePath : public std::deque<char>
{
public:
	SnakePath() = default;
	SnakePath(const SnakeGame& startState);
	SnakePath(SnakeGame&& startState);
	SnakePath(const SnakePath&) = default;
	SnakePath(SnakePath&&) noexcept = default;
	virtual ~SnakePath() noexcept = default;
	SnakePath& operator=(const SnakePath&) = default;
	SnakePath& operator=(SnakePath&&) noexcept = default;

	friend std::ostream& operator<<(std::ostream& os, const SnakePath& path);

	const SnakeGame& destinationSnakeState() const;

	size_t pathLength() const {	return this->size();	}
	bool isGoalState() const;

	// appends a move to the end of the path and changes the snake state to match it
	void pushMove(char move);
	void popMove();
	char peekNextMove() const;

private:
	SnakeGame destinationState;
};



