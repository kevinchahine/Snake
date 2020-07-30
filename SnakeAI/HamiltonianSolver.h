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

	// Initializes cycle based on current snake state
	// returns true iff a hamiltonian cycle was found
	bool initializeCycleDynamic();

protected:
	BoardTemplate<char> hamiltonianCycle;
};

