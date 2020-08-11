#pragma once

#include "SolverBase.h"

class HamiltonianSolver : public SolverBase
{
public:
	HamiltonianSolver(const SnakeGame& m_gameState);

	virtual void reset() override;

	virtual char solve() override;

	static bool isSolution(const Snake& game);

protected:
	static BoardTemplate<char> search(const Snake& snake);

	static BoardTemplate<char> generateSolution(const Snake& snake);

	void initializeCycle();

protected:
	BoardTemplate<char> hamiltonianCycle;

};

