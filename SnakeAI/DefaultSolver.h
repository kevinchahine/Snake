#pragma once

#include "SolverBase.h"

class DefaultSolver : public SolverBase
{
public:
	DefaultSolver(const SnakeEngine& engine);

	virtual char solve() override;
};

