#pragma once

#include <queue>

#include "SolverBase.h"

class AStarSolver : public SolverBase
{
public:
	AStarSolver(const SnakeEngine& engine);

	virtual char solve() override;

	static int calcManhattanDist(const Position& p1, const Position& p2);
};

class Move
{
public:
	Move(char direction, int heiristic) :
		direction(direction),
		heiristic(heiristic) {}

	bool operator()(const Move& left) const {
		return heiristic < left.heiristic;
	}

	bool operator<(const Move& left) const {
		return heiristic < left.heiristic;
	}

	bool operator==(const Move& left) const {
		return heiristic == left.heiristic;
	}

	bool operator>(const Move& left) const {
		return heiristic > left.heiristic;
	}

	char direction;
	int heiristic;
};