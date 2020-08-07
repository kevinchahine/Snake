#pragma once

#include "SnakePath.h"

// A snake path associated with a path cost
class CostlySnakePath : public SnakePath
{
public:
	CostlySnakePath() = default;
	CostlySnakePath(const SnakeGame& startingState);
	CostlySnakePath(SnakeGame&& startingState);
	CostlySnakePath(const CostlySnakePath&) = default;
	CostlySnakePath(CostlySnakePath&&) noexcept = default;
	virtual ~CostlySnakePath() noexcept = default;
	CostlySnakePath& operator=(const CostlySnakePath&) = default;
	CostlySnakePath& operator=(CostlySnakePath&&) noexcept = default;

	// Compares costs according to path length + man Used for priority_queue sorting
	bool operator<(const CostlySnakePath& costlySnakePath) const;
	bool operator==(const CostlySnakePath& costlySnakePath) const;

	// Calculates the cost as the length of the path: g(n)
	int calcCostFromStartCost() const;

	// Calculates cost as the manhattan (approximate) distance to goal: h(n)
	int calcCostToDestination() const;

	// Calculates cost as the sum of length from start to approximate 
	// distance to goal: f(n) = g(n) + h(n)
	int calcTotalCost() const;

	// Idendifies CostlySnakePath by a single number. 
	// Hash is only based on sequence of moves and not start or destination state.
	uint64_t hashValue() const;
};

