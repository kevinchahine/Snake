#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

#include "SolverBase.h"

class RandomSolver : public SolverBase
{
public:
	RandomSolver(const SnakeEngine& engine);

	virtual char solve() override;
};

