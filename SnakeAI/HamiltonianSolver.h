#pragma once

#include "SolverBase.h"

class HamiltonianSolver : public SolverBase
{
public:
	HamiltonianSolver(const SnakeState& gameState);

	virtual void reset() override;

	virtual char solve() override;

protected:
	void initializeCycle();

protected:
	BoardTemplate<char> hamiltonianCycle;
};

