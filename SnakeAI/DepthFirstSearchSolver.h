#pragma once

#include <queue>
#include <deque>

#include "SolverBase.h"

class DepthFirstSearchSolver : public SolverBase
{
public:
	DepthFirstSearchSolver(const SnakeEngine& engine);

	virtual char solve() override;

protected:
	char depthFirstSearch();

	void pushValidMovesToOpenList();

protected:
	std::queue<char> openList;
	std::queue<char> solution;
};


