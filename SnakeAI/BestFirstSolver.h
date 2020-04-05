#pragma once

#include "SolverBase.h"

class BestFirstSolver :	public SolverBase
{
public:
	BestFirstSolver(const SnakeState& gameState);

	virtual void reset() override;

	virtual char solve() override;
};

