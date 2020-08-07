#pragma once

#include "SolverBase.h"

class DefaultSolver : public SolverBase
{
public:
	DefaultSolver(const SnakeGame& m_gameState);

	// Clears any data that might be used in solve.
	virtual void reset() override;

	virtual char solve() override;
};

