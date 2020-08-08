#pragma once

#include "SolverBase.h"

class HamiltonianSolver : public SolverBase
{
public:
	HamiltonianSolver(const SnakeGame& m_gameState);

	virtual void reset() override;

	virtual char solve() override;

	static bool isSolution(const SnakeGame& game);

protected:

	void initializeCycle();

protected:
	BoardTemplate<char> hamiltonianCycle;

	class UnitTestHamiltonianSolver;
	friend UnitTestHamiltonianSolver;
};

