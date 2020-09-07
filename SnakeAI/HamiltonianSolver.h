#pragma once

#include "SolverBase.h"
#include "UndoableSnakeGame.h"

#include <boost/optional/optional.hpp>

class HamiltonianSolver : public SolverBase
{
public:
	HamiltonianSolver(const SnakeGame& m_gameState);

	virtual void reset() override;

	virtual char solve() override;

	static bool isSolution(const Snake& game);

protected:
public:
	// Returns an empty board if no solution was found
	static boost::optional<BoardTemplate<char>> search(const Snake& snake);

	static BoardTemplate<char> generateSolution(const Snake& snake);

	void initializeCycle();

protected:
	BoardTemplate<char> hamiltonianCycle;
};

