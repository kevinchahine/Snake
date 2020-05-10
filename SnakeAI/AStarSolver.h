#pragma once

#include <queue>

#include "SolverBase.h"

#include "CostlySnakePath.h"
#include "Frontier.h"
#include "Explored.h"

class AStarSolver : public SolverBase
{
public:
	AStarSolver(const SnakeState& gameState);

	virtual void reset() override;
	virtual char solve() override;

private:
	// Searches for a optimal solution (or path) from start to a goal state.
	// Path is stored in this->solutionPath
	SnakePath search(const SnakeState& start);

private:
	SnakePath solutionPath;
};
