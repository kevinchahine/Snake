#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

#include "SolverBase.h"

class RandomSolver : public SolverBase
{
public:
	RandomSolver(const SnakeState& gameState);

	virtual void reset() override;

	virtual char solve() override;
};

